//
// Created by llyfr on 13.4.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <QMenuBar>
#include  <QTimer>
#include <iostream>
#include <fstream>
#include <QSettings>
#include <QtConcurrent/QtConcurrent>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../API/WeatherAPI.h"
#include "settingwindow.h"
#include "history.h"


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


    /*
    * Create menu bar
    * */

    auto* fileMenu = this->menuBar()->addMenu("Program");

    this->exitAction = new QAction("Exit", this);
    this->settingsAction = new QAction("Settings", this);
    this->historyAction = new QAction("History", this);


    QObject::connect(this->exitAction, &QAction::triggered, this, &MainWindow::exit);
    QObject::connect(this->settingsAction, &QAction::triggered, this, &MainWindow::openSettings);
    QObject::connect(this->historyAction, &QAction::triggered, this, &MainWindow::openHistory);


    fileMenu->addAction(this->settingsAction);
    fileMenu->addAction(this->historyAction);
    fileMenu->addAction(this->exitAction);



    /*
     * Create and run Update loop
     * */
     auto* timer = new QTimer(this);

     QObject::connect(timer, &QTimer::timeout, this, &MainWindow::update);


     QSettings settings;

     std::map<QString, int> converter = {
             {"hours", 3600},
             {"minutes", 60 },
             {"seconds", 1}
     };

     // TODO loads from user settings, or hour by default
     int interval = 1000 * settings.value("updateInterval", 2).toInt() * converter[settings.value("updateIntervalUnit", "minutes").toString()];
     timer->start(interval);


     QtConcurrent::run([this](){this->update();});

     //this->openSettings();

     this->openHistory();

}



MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::exit() {
    this->close();
}

/**
 * Updates all the UI elements.
 * Is getting run as a separate thread so developer should keep that in mind.
 * QSetting is tread safe according to the documentation
 */

void MainWindow::update() {
    std::cout << "Update Started" << std::endl;


    QSettings settings;

    QString API_key = settings.value("API_key", "").toString();

    if (API_key == "") {
        std::cout << "API key not set" << std::endl;
        return;
    }

    Location loc;
    loc.lat = settings.value("location_lat").toDouble();
    loc.lon = settings.value("location_lon").toDouble();

    API::WeatherAPI weatherAPI(API_key.toStdString(), loc);


    auto forecast = weatherAPI.getForecast();

    std::vector<QLabel*> icons = {ui->mainIcon, ui->icon_1, ui->icon_2, ui->icon_3, ui->icon_4, ui->icon_5};
    std::vector<QLabel*> temps = {ui->mainTemp, ui->temp_1, ui->temp_2, ui->temp_3, ui->temp_4, ui->temp_5};


    for(int i = 0 ; i < 6; i++) {

        std::string icon = (i == 0) ? forecast.getHourlyForecast(i).weather.icon : forecast.getDailyForecast(i).weather.icon;
        int temp = (i == 0) ? forecast.getHourlyForecast(i).temperature : forecast.getDailyForecast(i).temperature.day;

        QPixmap pixmap = stringStreamToPixmap(API::getImageFromUrl(icon));
        icons[i]->setPixmap(pixmap);

        temps[i]->setText(QString::number(temp) + "°C");

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


    // Prevents freeze when closing the setting window
    // ! Must be kept in mind, we just introduced a threading in to our program;
    connect(settings, &SettingWindow::settingsSaved, [this](){QtConcurrent::run([this](){this->update();});});

}


void MainWindow::openDay() {

}

void MainWindow::openHistory() {

    auto* history = new History();

    history->setWindowModality(Qt::ApplicationModal);
    history->show();

}



