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
    connect(ui->buttonLoad, &QPushButton::clicked, _sudoku, &SudokuWidget::loadGrid);

    connect(ui->button1, &QPushButton::clicked, this, &MainWindow::onNumberButtonClicked);
    connect(ui->button2, &QPushButton::clicked, this, &MainWindow::onNumberButtonClicked);
    connect(ui->button3, &QPushButton::clicked, this, &MainWindow::onNumberButtonClicked);
    connect(ui->button4, &QPushButton::clicked, this, &MainWindow::onNumberButtonClicked);
    connect(ui->button5, &QPushButton::clicked, this, &MainWindow::onNumberButtonClicked);
    connect(ui->button6, &QPushButton::clicked, this, &MainWindow::onNumberButtonClicked);
    connect(ui->button7, &QPushButton::clicked, this, &MainWindow::onNumberButtonClicked);
    connect(ui->button8, &QPushButton::clicked, this, &MainWindow::onNumberButtonClicked);
    connect(ui->button9, &QPushButton::clicked, this, &MainWindow::onNumberButtonClicked);

    connect(ui->difficultyCbox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onDifficultyChanged);
}

void MainWindow::onNumberButtonClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        int number = button->text().toInt();
        _sudoku->addNumber(number);
    }
}

void MainWindow::onDifficultyChanged(int index) {
    _sudoku->setDifficulty(index + 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

