//
// Created by llyfr on 9.5.23.
//

#ifndef WEATHERAPP_HISTORY_H
#define WEATHERAPP_HISTORY_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class History; }
QT_END_NAMESPACE

class History : public QDialog {
Q_OBJECT

public:
    explicit History(QWidget *parent = nullptr);

    ~History() override;

private:
    Ui::History *ui;
};


#endif //WEATHERAPP_HISTORY_H
