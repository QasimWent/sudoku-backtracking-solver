#include <QTableView>
#include <QPushButton>
#include "MainWindow.h"
//#include "SudokuModel.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
    QVBoxLayout* vbox = new QVBoxLayout();
    QHBoxLayout* hbox = new QHBoxLayout();

    tableView = new QTableView(this);
    myModel = new SudokuModel(this);
    tableView->setModel(myModel);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QPushButton* solveBtn = new QPushButton("Solve", this);
    connect(solveBtn, SIGNAL (clicked()), this, SLOT (handleButton()));

    hbox->addWidget(solveBtn, 1, Qt::AlignRight);

    vbox->addWidget(tableView);
    vbox->addSpacing(10);
    vbox->addLayout(hbox);

    setLayout(vbox);
}

void MainWindow::handleButton()
{
    myModel->changeTable();
}