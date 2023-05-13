//
// Created by llyfr on 13.4.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <QMenuBar>
#include <QTimer>
#include <iostream>
#include <fstream>
#include <QSettings>
#include <QtConcurrent/QtConcurrent>
#include <QStyleFactory>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <utility>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingwindow.h"
#include "MyFrame.hpp"


QPixmap stringStreamToPixmap(std::stringstream stream) {
    std::vector<char> buffer((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    QByteArray image_data = QByteArray::fromRawData(buffer.data(), buffer.size());

    // Create a QPixmap object from the image data
    QPixmap pixmap;
    pixmap.loadFromData(image_data);

    return pixmap;
}

// AI writen, not that I don't know what it does but still
std::string capitalize(std::string text) {
    for (int x = 0; x < text.length(); x ++) {
        if ( x == 0) {
            text[x] = toupper(text [x]);
        } else if ( text [ x - 1] == ' ') {
            text[x] = toupper(text [x]);
        }
    }
    return text;
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

    QObject::connect(this->exitAction, &QAction::triggered, this, &MainWindow::exit);
    QObject::connect(this->settingsAction, &QAction::triggered, this, &MainWindow::openSettings);

    fileMenu->addAction(this->settingsAction);
    fileMenu->addAction(this->exitAction);


    /*
     * Set-up moon icons
     * */

    this->moonIcons = {
            {0.95, QPixmap("icons/moon/new-moon.png")},
            {0.80, QPixmap("icons/moon/waning-crescent-moon.png")},
            {0.70, QPixmap("icons/moon/last-quarter-moon.png")},
            {0.55, QPixmap("icons/moon/waning-gibbous-moon.png")},
            {0.45, QPixmap("icons/moon/full-moon.png")},
            {0.30, QPixmap("icons/moon/waxing-gibbous-moon.png")},
            {0.20, QPixmap("icons/moon/first-quarter-moon.png")},
            {0.05, QPixmap("icons/moon/waxing-crescent-moon.png")},
            {0.00, QPixmap("icons/moon/new-moon.png")}
    };

    ui->moonPhaseText->setAlignment( Qt::AlignCenter);
    ui->label_3->setAlignment( Qt::AlignCenter);

    ui->moonRise->setPixmap( QPixmap("icons/moonRise.png"));
    ui->moonDown->setPixmap( QPixmap("icons/moonDown.png"));
    ui->sunRise->setPixmap( QPixmap("icons/sunRise.png"));
    ui->sunDown->setPixmap( QPixmap("icons/sunDown.png"));



    // Replaces QFrames with MyFrame that inherits from QFrame but unlocks mouse tracking;
    // Not a 1:1 copy right now so if some other that basic changes to the QFrame are made they might not transfer to MyFrame
    ui->frame_1 = new MyFrame(ui->frame_1, this);
    ui->frame_2 = new MyFrame(ui->frame_2, this);
    ui->frame_3 = new MyFrame(ui->frame_3, this);
    ui->frame_4 = new MyFrame(ui->frame_4, this);
    ui->frame_5 = new MyFrame(ui->frame_5, this);
    ui->mainFrame = new MyFrame(ui->mainFrame, this);


    /*
     * Create and run Update loop
     * */
     this->timer = new QTimer(this);
     QObject::connect(this->timer, &QTimer::timeout, this, &MainWindow::update);

     QtConcurrent::run([this](){this->update();});

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
        return;
    }

    std::map<QString, int> converter = {{"hours", 3600},
                                        {"minutes", 60 },
                                        {"seconds", 1}};

    // Default is 2 minutes, witch should last the whole day on free calls
    int interval = 1000 * settings.value("update_interval", 2).toInt() * converter[settings.value("update_unit", "minutes").toString()];
    std::cout << "Interval: " << interval << std::endl;
    timer->start(interval);


    Cords cords(settings.value("location_lat").toDouble(), settings.value("location_lon").toDouble());
    API::WeatherAPI weatherAPI(API_key.toStdString(), cords, settings.value("units", "metric").toString().toStdString());


    auto forecast = weatherAPI.getForecast();

    // Alternatively we could give all the frames same name and use findChildren

    std::vector<QLabel*> icons = {ui->icon_1, ui->icon_2, ui->icon_3, ui->icon_4, ui->icon_5};
    std::vector<QLabel*> temps = {ui->temp_1, ui->temp_2, ui->temp_3, ui->temp_4, ui->temp_5};
    std::vector<QLabel*> statuses = {ui->status_1, ui->status_2, ui->status_3, ui->status_4, ui->status_5};
    std::vector<QLabel*> dates = {ui->date_1, ui->date_2, ui->date_3, ui->date_4, ui->date_5};
    std::vector<QLabel*> wind = {ui->wind_1, ui->wind_2, ui->wind_3, ui->wind_4, ui->wind_5};
    std::vector<QLabel*> humidity = {ui->hum_1 , ui->hum_2, ui->hum_3, ui->hum_4, ui->hum_5};
    std::vector<QFrame*> frames = {ui->frame_1, ui->frame_2, ui->frame_3, ui->frame_4, ui->frame_5};

    std::map<QString, QString> units = {
            {"metric", "°C"},
            {"imperial", "°F"},
            {"standard", "K"}
    };

    QString unit = units[settings.value("units", "metric").toString()];
    QTimeZone timeZone = QTimeZone(forecast.getDailyForecast().time.offset);


    for(int i = 0 ; i < 5; i++) {

        // Day 0 is today, so we skip it
        DailyForecast day = forecast.getDailyForecast(i+1);

        QPixmap pixmap = stringStreamToPixmap(API::getImageFromUrl(day.weather.icon));
        icons[i]->setPixmap(pixmap);

        temps[i]->setText(QString::number((int)day.temperature.day) + unit);
        temps[i]->setAlignment(Qt::AlignCenter);

        statuses[i]->setText(QString::fromStdString(capitalize(day.weather.description)));
        statuses[i]->setAlignment(Qt::AlignCenter);


        QDateTime date = QDateTime::fromSecsSinceEpoch(day.time.dt, timeZone);
        dates[i]->setText(date.toString("dddd d"));
        dates[i]->setAlignment(Qt::AlignCenter);

        wind[i]->setText(QString::number((int)day.wind.speed) + " m/h");
        humidity[i]->setText(QString::number((int)day.atmospheric.humidity) + "%");


        connect((MyFrame*)frames[i], &MyFrame::mouseEntered, [this, day, timeZone]() {this->showDayData(day, timeZone);});

    }


    HourlyForecast current = forecast.getHourlyForecast(0);
    DailyForecast day = forecast.getDailyForecast(0);

    QPixmap pixmap = stringStreamToPixmap(API::getImageFromUrl(current.weather.icon));
    ui->mainIcon->setPixmap(pixmap);
    ui->mainCity->setText(settings.value("location_name", "").toString());
    ui->mainTemp->setText(QString::number((int)current.temperature) + unit);
    ui->mainStatus->setText(QString::fromStdString(capitalize(current.weather.description)));

    auto update_main = [this,current, day, timeZone]() {

        this->setWind(current.wind);
        this->setMisc(current.atmospheric);
        this->setCelestial(day, timeZone);

    };

    update_main();

    connect((MyFrame*)ui->mainFrame, &MyFrame::mouseEntered, [update_main]() {update_main();});



    std::cout << "Update Ended" << std::endl;
}


void MainWindow::openSettings() {

    std::cout << "Opening Settings" << std::endl;

    // Leave parent null so it appears as a new window
    auto* settings = new SettingWindow();

    // Makes the main window non-clickable
    settings->setWindowModality(Qt::ApplicationModal);
    settings->show();
    settings->raise();


    // Prevents freeze when closing the setting window
    // ! Must be kept in mind, we just introduced a threading in to our program;
    connect(settings, &SettingWindow::settingsSaved, [this](){QtConcurrent::run([this](){this->update();});});

}


void MainWindow::openDay() {

}


void MainWindow::showDayData(const DailyForecast& day, QTimeZone timeZone) {

    this->setWind(day.wind);
    this->setMisc(day.atmospheric);
    this->setCelestial(day, std::move(timeZone));

}

void MainWindow::setWind(Wind wind) {

    ui->speed->setText("Speed: " + QString::number(wind.speed) + " m/h");
    ui->gust->setText("Gust: " + QString::number(wind.gust) + " m/h");
    ui->degree->setText("Degree: " + QString::number(wind.degree) + "°");


}

void MainWindow::setMisc(Atmospheric atmospheric) {

    ui->pressure->setText("Pressure: " + QString::number(atmospheric.pressure) + " hPa");
    ui->cloud->setText("Clouds: " + QString::number(atmospheric.clouds) + "%");
    ui->uvi->setText("UV Index: " + QString::number(atmospheric.uvi));

}

void MainWindow::setCelestial(DailyForecast day, QTimeZone timeZone) {

    ui->sunRiseTime->setText(QDateTime::fromSecsSinceEpoch(day.time.sunrise, timeZone).toString("hh:mm"));
    ui->sunDownTime->setText(QDateTime::fromSecsSinceEpoch(day.time.sunset, timeZone).toString("hh:mm"));

    ui->moonRiseTime->setText(QDateTime::fromSecsSinceEpoch(day.time.moonrise, timeZone).toString("hh:mm"));
    ui->moonDownTime->setText(QDateTime::fromSecsSinceEpoch(day.time.moonset, timeZone).toString("hh:mm"));


    ui->moonPhaseText->setText(QString::number(day.time.moon_phase));

    for(const auto& pair : this->moonIcons) {
        if(day.time.moon_phase >= pair.first) {
            ui->moon_phase->setPixmap(pair.second);
            break;
        }
    }

}



