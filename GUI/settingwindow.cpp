//
// Created by llyfr on 8.5.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SettingWindow.h" resolved

#include <iostream>
#include <QSettings>
#include <QCompleter>
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


    ui->API_key->setEchoMode(QLineEdit::Password);


    QSettings settings;


    ui->API_key->setText(settings.value("API_key", "").toString());
    ui->spinBox_update->setValue(settings.value("update_interval", 1).toInt());
    ui->comboBox_update->setCurrentText(settings.value("update_unit", "seconds").toString());
    ui->fahrenheit->setChecked(settings.value("units", "standard").toString() == "imperial");
    ui->celsius->setChecked(settings.value("units", "standard").toString() == "metric");
    ui->city->setChecked(settings.value("location_type", "coordinates").toString() == "city");
    ui->cords->setChecked(settings.value("location_type", "coordinates").toString() == "coordinates");
    ui->lat->setText(settings.value("location_lat", "").toString());
    ui->lon->setText(settings.value("location_lon", "").toString());
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


    settings.setValue("API_key", ui->API_key->text());

    settings.setValue("update_interval", ui->spinBox_update->value());
    settings.setValue("update_unit", ui->comboBox_update->currentText());

    settings.setValue("location_lat", ui->lat->text());
    settings.setValue("location_lon", ui->lon->text());

    settings.setValue("location_name", ui->cityEnter->text());


    this->close();

}

void SettingWindow::cancel() {
    this->close();
}

SettingWindow::~SettingWindow() {
    delete ui;
}

void SettingWindow::cityEntered() {

    API::GeoAPI geoAPI("c37fc2bf45a37a8ff187e0955ee2e5ef");

    std::vector<Location> loc = geoAPI.getLocations(ui->cityEnter->text().toStdString(), 10);

    QStringList wordList;

    for (auto &i : loc) {

        std::string name =  i.name + ", " + i.country;

        wordList.append(QString::fromStdString(name));
        std::cout << i.name << std::endl;
        std::cout << i.country << std::endl;
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

            ui->lon->setText(QString::fromStdString(std::to_string(loc[choice.row()].lon)));
            ui->lat->setText(QString::fromStdString(std::to_string(loc[choice.row()].lat)));

            std::cout << choice.row() << std::endl;

            ui->cityEnter->setCompleter(nullptr);
    });


}

