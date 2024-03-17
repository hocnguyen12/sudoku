#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sudokuwidget.h"

#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _sudoku = ui->sudokuWidget;
    //connect(ui->buttonLoad, SIGNAL(clicked(bool)), _sudoku, SLOT(SudokuWidget::loadGrid));
    connect(ui->buttonLoad, &QPushButton::clicked, _sudoku, &SudokuWidget::loadGrid);
}

MainWindow::~MainWindow()
{
    delete ui;
}

