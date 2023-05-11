//
// Created by llyfr on 8.5.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SettingWindow.h" resolved

#include <iostream>
#include <QSettings>
#include <QCompleter>
#include <QLocale>
#include <QStringListModel>
#include "settingwindow.h"
#include "ui_settingwindow.h"
#include "../API/GeoAPI.h"


SettingWindow::SettingWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::SettingWindow) {
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SettingWindow::save);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &SettingWindow::cancel);

    connect(ui->cityEnter, &QLineEdit::returnPressed, this, &SettingWindow::cityEntered);
    connect(ui->API_Enter, &QPushButton::clicked, this, &SettingWindow::APIEntered);

    connect(ui->lat, &QLineEdit::returnPressed, this, &SettingWindow::cordsEntered);
    connect(ui->lon, &QLineEdit::returnPressed, this, &SettingWindow::cordsEntered);

    // I have it as a lambda function because its pure UI settings witch is what this constructor is for
    connect(ui->city, &QRadioButton::toggled, this, [this]() {
        ui->lat->setDisabled(true);
        ui->lon->setDisabled(true);
        ui->label_5->setDisabled(true);
        ui->label_6->setDisabled(true);

        ui->cityEnter->setDisabled(false);
        ui->label_4->setDisabled(false);
    });

    connect(ui->cords, &QRadioButton::toggled, this, [this]() {
        ui->lat->setDisabled(false);
        ui->lon->setDisabled(false);
        ui->label_5->setDisabled(false);
        ui->label_6->setDisabled(false);

        ui->cityEnter->setDisabled(true);
        ui->label_4->setDisabled(true);
    });


    // Didn't manage to set it up in QT designer so I have to do it here, might delete latter;
    ui->API_key->setEchoMode(QLineEdit::Password);
    ui->errorMessage->hide();

    auto * validator = new QDoubleValidator(-99999999.0, 99999999.0, 5);
    auto locale = QLocale(QLocale::English, QLocale::UnitedStates);  // Use '.' as decimal separator
    validator->setLocale(locale);
    ui->lat->setValidator(validator);
    ui->lon->setValidator(validator);


    QSettings settings;


    ui->API_key->setText(settings.value("API_key", "").toString());
    ui->spinBox_update->setValue(settings.value("update_interval", 2).toInt());
    ui->comboBox_update->setCurrentText(settings.value("update_unit", "minutes").toString());
    ui->fahrenheit->setChecked(settings.value("units", "standard").toString() == "imperial");
    ui->celsius->setChecked(settings.value("units", "standard").toString() == "metric");
    ui->city->setChecked(settings.value("location_type", "coordinates").toString() == "city");
    ui->cords->setChecked(settings.value("location_type", "coordinates").toString() == "coordinates");
    ui->lat->setText(settings.value("location_lat", 0).toString());
    ui->lon->setText(settings.value("location_lon", 0).toString());
    ui->cityEnter->setText(settings.value("location_name", "").toString());

}

void SettingWindow::save() {

    QSettings settings;
    std::cout << "Saving settings" << std::endl;

    if (ui->fahrenheit->isChecked()) {
        settings.setValue("units", "imperial");
    } else if (ui->celsius->isChecked()) {
        settings.setValue("units", "metric");
    } else {
        settings.setValue("units", "standard");
    }

    if(ui->city->isChecked()) {
        settings.setValue("location_type", "city");
    } else {
        settings.setValue("location_type", "coordinates");
    }


    // I'm not saving API key and only having that saved when it's confirmed it's valid using the enter button;

    settings.setValue("update_interval", ui->spinBox_update->value());
    settings.setValue("update_unit", ui->comboBox_update->currentText());

    settings.setValue("location_lat", ui->lat->text());
    settings.setValue("location_lon", ui->lon->text());

    settings.setValue("location_name", ui->cityEnter->text());

    emit settingsSaved();
    this->close();

}

void SettingWindow::cancel() {
    this->close();
}

SettingWindow::~SettingWindow() {
    delete ui;
}

void SettingWindow::cityEntered() {

    QSettings settings;

    std::string key = settings.value("API_key", "").toString().toStdString();

    if(key.empty()) {
        return;
    }

    API::GeoAPI geoAPI(key);

    std::vector<Location> loc = geoAPI.getLocations(ui->cityEnter->text().toStdString(), 10);

    QStringList wordList;

    for (auto &i : loc) {

        std::string name =  i.name + ", " + i.country;

        wordList.append(QString::fromStdString(name));
    }


    auto* completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    ui->cityEnter->setCompleter(completer);
    completer->complete();

    connect(completer, QOverload<const QModelIndex&>::of(&QCompleter::activated),
            this, [this,loc,completer](const QModelIndex &choice){

            QSettings settings;

            settings.setValue("location_lat", loc[choice.row()].lat);
            settings.setValue("location_lon", loc[choice.row()].lon);

            ui->lon->setText(QString::number(loc[choice.row()].lon));
            ui->lat->setText(QString::number(loc[choice.row()].lat));

            std::cout << choice.row() << std::endl;

            // Disables completer, so the results don't show if user wants to enter different location
            ui->cityEnter->setCompleter(nullptr);
    });


}

void SettingWindow::cordsEntered() {

    QSettings settings;

    std::string key = settings.value("API_key", "").toString().toStdString();

    if(key.empty()) {
        return;
    }

    API::GeoAPI geoAPI(key);

    double lat = ui->lat->text().toDouble();
    double lon = ui->lon->text().toDouble();

    Location loc = geoAPI.getLocation(lat, lon);

    ui->cityEnter->setText(QString::fromStdString(loc.name + ", " + loc.country));

}



// We are testing if the API key is valid
// This is the only place where we set API key in to settings
// So this makes sure the API key is either valid or empty string.
void SettingWindow::APIEntered() {

    QString API_key = ui->API_key->text();

    QSettings settings;

    API::GeoAPI geoAPI(API_key.toStdString());

    if(geoAPI.testAPIkey()) {
        ui->errorMessage->setText("API key is valid");
        ui->errorMessage->setStyleSheet("QLabel { color : green; }");
        ui->errorMessage->show();

        settings.setValue("API_key", API_key);

        emit settingsSaved();

    } else {
        ui->errorMessage->setText("API key is invalid");
        ui->errorMessage->setStyleSheet("QLabel { color : red; }");
        ui->errorMessage->show();

        settings.setValue("API_key", "");

        emit settingsSaved();

    }

}


