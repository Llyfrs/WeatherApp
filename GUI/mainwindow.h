//
// Created by llyfr on 13.4.23.
//

#ifndef WEATHERAPP_MAINWINDOW_H
#define WEATHERAPP_MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QTimeZone>
#include "../API/WeatherAPI.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);



    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

    QAction* exitAction;
    QAction* settingsAction;

    QTimer* timer;


    std::vector<std::pair<double, QPixmap>> moonIcons;


    void showDayData(const DailyForecast& day, QTimeZone timeZone);

    void setWind(Wind wind);
    void setMisc(Atmospheric atmospheric);

    void setCelestial(DailyForecast day, QTimeZone timeZone);

public slots:
    void exit();
    void openSettings();
    void openDay();
    void update();

};


#endif //WEATHERAPP_MAINWINDOW_H
