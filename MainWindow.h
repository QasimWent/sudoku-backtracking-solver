#ifndef MAINWINDOW_H
#define MAINWINDO_H

#include <QtWidgets>
#include "SudokuModel.h"

class MainWindow: public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);

private:
    QTableView* tableView;
    SudokuModel* myModel;

private slots:
    void handleButton();
};

#endif