//
// Created by llyfr on 9.5.23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_History.h" resolved

#include <QStandardItemModel>

#include "history.h"
#include "ui_history.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <QSortFilterProxyModel>


History::History(QWidget *parent) : QDialog(parent), ui(new Ui::History) {
    ui->setupUi(this);

    QStandardItemModel *model = new QStandardItemModel();

    // Set the number of rows and columns

    connect(ui->lineEdit, &QLineEdit::textChanged, [model, this](const QString &text) {
        QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
        proxyModel->setSourceModel(model);
        proxyModel->setFilterFixedString(text);
        ui->tableView->setModel(proxyModel);
    } );


    model->setColumnCount(6);



    // Set the header data
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("City"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Lat"));
    model->setHeaderData( 2, Qt::Horizontal, QObject::tr("Lon"));
    model->setHeaderData( 3, Qt::Horizontal, QObject::tr("Temperature"));
    model->setHeaderData( 4, Qt::Horizontal, QObject::tr("Wind Speed"));
    model->setHeaderData( 5, Qt::Horizontal, QObject::tr("Cloudiness"));


    std::vector<QString> cities = {"Nový Jičín", "New Yourk", "Brno", "London", "Ostrava"};
    srand (time(nullptr));

    for(int i = 0; i < 57; i++) {
        QList<QStandardItem *> row;

        row << new QStandardItem(cities[rand() % 5]);
        row << new QStandardItem(QString::number(rand() % 100));
        row << new QStandardItem(QString::number(rand() % 100));
        row << new QStandardItem(QString::number(rand() % 42 - 10));
        row << new QStandardItem(QString::number(rand() % 16));
        row << new QStandardItem(QString::number(rand() % 100));

        model->insertRow(i, row);

    }

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->verticalHeader()->setVisible(false);

    ui->tableView->setColumnWidth(1, 20);
    ui->tableView->setColumnWidth(2, 20);



}

History::~History() {
    delete ui;
}
