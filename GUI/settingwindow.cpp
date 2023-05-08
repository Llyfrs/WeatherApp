//
// Created by llyfr on 8.5.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SettingWindow.h" resolved

#include <iostream>
#include <QSettings>
#include <QCompleter>
#include "settingwindow.h"
#include "ui_settingwindow.h"
#include "../API/GeoAPI.h"


SettingWindow::SettingWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::SettingWindow) {
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SettingWindow::save);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &SettingWindow::cancel);

    connect(ui->cityEnter, &QLineEdit::returnPressed, this, &SettingWindow::cityEntered);


    QSettings settings;


    ui->API_key->setText(settings.value("API_key", "").toString());
    ui->spinBox_update->setValue(settings.value("update_interval", 1).toInt());
    ui->comboBox_update->setCurrentText(settings.value("update_unit", "seconds").toString());
    ui->fahrenheit->setChecked(settings.value("units", "standard").toString() == "imperial");
    ui->celsius->setChecked(settings.value("units", "standard").toString() == "metric");
    ui->city->setChecked(settings.value("location_type", "coordinates").toString() == "city");
    ui->cords->setChecked(settings.value("location_type", "coordinates").toString() == "coordinates");

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
        wordList.append(QString::fromStdString(i.name));
        std::cout << i.name << std::endl;
        std::cout << i.country << std::endl;
    }


    auto* completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    ui->cityEnter->setCompleter(completer);
    completer->complete();

    connect(completer, QOverload<const QString &>::of(&QCompleter::activated),
            this, &SettingWindow::citySelected);



}

void SettingWindow::citySelected(const QString& string) {

    std::cout << string.toStdString() << std::endl;

}
