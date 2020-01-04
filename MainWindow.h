#ifndef MAINWINDOW_H
#define MAINWINDO_H

#include <QtWidgets>

class MainWindow: public QWidget
{
public:
    MainWindow(QWidget* parent = 0);
private:
    QTableView* tableView;
};

#endif