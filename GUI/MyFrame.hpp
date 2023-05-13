//
// Created by llyfr on 13.5.23.
//

#import <QtWidgets/QFrame>
#import <QtWidgets/QStyle>
#import <iostream>

#ifndef WEATHERAPP_MYFRAME_H
#define WEATHERAPP_MYFRAME_H

/**
 * Custom QFrame the overrides virtual method enterEvent()
 * that is triggered every time a moues enters the frame.
 * This is needed so we can update "Info Box" when we hover
 * over specific days.
 */
class MyFrame : public QFrame {
    Q_OBJECT

public:
    explicit MyFrame(QFrame* copy, QWidget* parent=nullptr) : QFrame(parent) {
        this->setGeometry(copy->geometry());
        this->setStyleSheet(copy->styleSheet());

        this->setFrameStyle(copy->frameStyle());
        this->setFrameRect(copy->frameRect());
        this->setFrameShadow(copy->frameShadow());

        this->show();

        QList<QWidget*> children = copy->findChildren<QWidget*>();
        for (QWidget* child : children) {
            child->setParent(this);
        }

        copy->deleteLater();
    }


signals:
    void mouseEntered();

protected:
    void enterEvent(QEnterEvent *event) override {
        emit mouseEntered();
    }


};
#endif //WEATHERAPP_MYFRAME_H
