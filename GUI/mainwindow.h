//
// Created by llyfr on 13.4.23.
//

#ifndef WEATHERAPP_MAINWINDOW_H
#define WEATHERAPP_MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>


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

public slots:
    void exit();
    void update();

};


#endif //WEATHERAPP_MAINWINDOW_H
