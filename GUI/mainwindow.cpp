//
// Created by llyfr on 13.4.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <QMenuBar>
#include  <QTimer>
#include <iostream>
#include <fstream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../API/WeatherAPI.h"
#include "settingwindow.h"


QPixmap stringStreamToPixmap(std::stringstream stream) {
    std::vector<char> buffer((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    QByteArray image_data = QByteArray::fromRawData(buffer.data(), buffer.size());

// Create a QPixmap object from the image data
    QPixmap pixmap;
    pixmap.loadFromData(image_data);

    return pixmap;
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    // Set-ups the UI using ui_mainwindow.h that is generated based on .ui file
    ui->setupUi(this);

    this->setWindowTitle("Weather App");



    QCoreApplication::setOrganizationName("Llyfr Inc.");
    QCoreApplication::setOrganizationDomain("llyfr.com");
    QCoreApplication::setApplicationName("Weather App");


    this->geoAPI = API::GeoAPI("c37fc2bf45a37a8ff187e0955ee2e5ef");
    Location loc = geoAPI.getLocation("Nový Jičín");

    this->weatherAPI = API::WeatherAPI("c37fc2bf45a37a8ff187e0955ee2e5ef",loc);

    /*
    * Create menu bar
    * */

    auto* fileMenu = this->menuBar()->addMenu("Program");

    this->exitAction = new QAction("Exit", this);
    this->settingsAction = new QAction("Settings", this);


    QObject::connect(this->exitAction, &QAction::triggered, this, &MainWindow::exit);
    QObject::connect(this->settingsAction, &QAction::triggered, this, &MainWindow::openSettings);


    fileMenu->addAction(this->settingsAction);
    fileMenu->addAction(this->exitAction);


    /*
     * Create and run Update loop
     * */
     auto* timer = new QTimer(this);

     QObject::connect(timer, &QTimer::timeout, this, &MainWindow::update);

     // TODO loads from user settings, or hour by default
     int hour = 1000 * 60 * 60;
     timer->start(hour);


     this->update();

     this->openSettings();

}



MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::exit() {
    this->close();
}

/**
 *
 */

void MainWindow::update() {
    std::cout << "Update Started" << std::endl;


    auto forecast = this->weatherAPI.getForecast();

    std::vector<QLabel*> icons = {ui->mainIcon, ui->icon_1, ui->icon_2, ui->icon_3, ui->icon_4, ui->icon_5};
    std::vector<QLabel*> temps = {ui->mainTemp, ui->temp_1, ui->temp_2, ui->temp_3, ui->temp_4, ui->temp_5};


    for(int i = 0 ; i < 6; i++) {
        QPixmap pixmap = stringStreamToPixmap(API::getImageFromUrl(forecast.getWeather(i).icon));
        icons[i]->setPixmap(pixmap);

        temps[i]->setText(QString::number(forecast.getTemperature(i)) + "°C");

    }

    std::cout << "Update Ended" << std::endl;
}


void MainWindow::openSettings() {

    std::cout << "Opening Settings" << std::endl;

    // Leave parent null so it appears as a new window
    auto* settings = new SettingWindow();

    // Makes the main window unclickable
    settings->setWindowModality(Qt::ApplicationModal);
    settings->show();
    settings->raise();

}


void MainWindow::openDay() {

}



