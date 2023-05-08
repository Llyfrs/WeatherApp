//
// Created by llyfr on 8.5.23.
//

#ifndef WEATHERAPP_SETTINGWINDOW_H
#define WEATHERAPP_SETTINGWINDOW_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class SettingWindow; }
QT_END_NAMESPACE

class SettingWindow : public QWidget {
Q_OBJECT

public:
    explicit SettingWindow(QWidget *parent = nullptr);

    ~SettingWindow() override;

private:
    Ui::SettingWindow *ui;

public slots:
    void save();
    void cancel();

    void cityEntered();
    void citySelected(const QString& string);
};


#endif //WEATHERAPP_SETTINGWINDOW_H
