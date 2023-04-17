//
// Created by llyfr on 13.4.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <QMenuBar>
#include  <QTimer>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    // Set-ups the UI using ui_mainwindow.h that is generated based on .ui file
    ui->setupUi(this);

    this->setWindowTitle("Weather App");

    /*
    * Create menu bar
    * */

    auto* fileMenu = this->menuBar()->addMenu("Program");

    this->exitAction = new QAction("Exit", this);

    QObject::connect(this->exitAction, &QAction::triggered, this, &MainWindow::exit);
    fileMenu->addAction(this->exitAction);


    /*
     * Create and run Update loop
     * */
     auto* timer = new QTimer(this);

     QObject::connect(timer, &QTimer::timeout, this, &MainWindow::update);

     // TODO loads from user settings, or hour by default
     int hour = 1000 * 60 * 60;
     timer->start(hour);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::exit() {
    this->close();
}

void MainWindow::update() {
    std::cout << "Update Started" << std::endl;



    std::cout << "Update Ended" << std::endl;
}