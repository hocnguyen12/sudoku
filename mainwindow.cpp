#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sudokuwidget.h"

#include <QHBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Sudoku");
/*
    QIcon fileOpen = QIcon::fromTheme("document-open");
    QIcon fileSave = QIcon::fromTheme("document-save-as");
    QIcon adressNew = QIcon::fromTheme("document-new");
    ui->action_Open->setIcon(fileOpen);
    ui->action_Save_as->setIcon(fileSave);
    ui->action_New_Invoice->setIcon(adressNew);

    QIcon file = QIcon::fromTheme("document-file");
    ui->menu_File->setIcon(file);
    QIcon option = QIcon::fromTheme("options");
    ui->menu_Option->setIcon(option);
*/
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

    connect(ui->buttonClear, &QPushButton::clicked, _sudoku, &SudokuWidget::clearGrid);

    // Création d'un QTimer pour mettre à jour le temps écoulé
    timer = new QTimer(this);
    ui->_time->setText("00:00:00");
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);

    // Connecte le signal "clicked()" du bouton "loadButton" à la fonction startTimerOnLoad()
    connect(ui->buttonLoad, &QPushButton::clicked, this, &MainWindow::startTimerOnLoad);

    connect(ui->action_Quit, &QAction::triggered, this, &MainWindow::close);

    connect(ui->action_New, &QAction::triggered, this, &MainWindow::newGame);
    connect(ui->action_How_To_Play, &QAction::triggered, this, &MainWindow::openHowToPlay);
    connect(ui->action_Rules, &QAction::triggered, this, &MainWindow::showRules);
    connect(ui->action_About, &QAction::triggered, this, &MainWindow::showAbout);
    connect(ui->action_Credits, &QAction::triggered, this, &MainWindow::showCredits);

    // connecter le signal gameEnded a l'arret du timer
    connect(_sudoku, &SudokuWidget::gameEnded, this, &MainWindow::stopTimer);
    connect(ui->buttonClear, &QPushButton::clicked, this, &MainWindow::stopAndResetTimer);

    // DARK and LIGHT modes
    connect(ui->action_Dark, &QAction::triggered, this, [this]() {
        loadStyleSheet(":/stylesheets/darkMode.qss");
    });

    connect(ui->action_Light, &QAction::triggered, this, [this]() {
        loadStyleSheet(":/stylesheets/lightMode.qss");
    });

    // NOTE button
    ui->noteMode->setCheckable(true);
    connect(ui->noteMode, &QCheckBox::stateChanged, this, &MainWindow::onToggleButtonStateChanged);
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

void MainWindow::startTimerOnLoad()
{
    timer->start(1000); // Met à jour toutes les 1000 ms (1 seconde)
    startTime = QTime::currentTime();
}


void MainWindow::updateTime()
{
    QTime currentTime = QTime::currentTime();
    int elapsed = startTime.secsTo(currentTime);

    QTime displayTime = QTime(0, 0).addSecs(elapsed);
    QString displayString = displayTime.toString("hh:mm:ss");

    ui->_time->setText(displayString);
}

void MainWindow::stopTimer() {
    timer->stop();
}

void MainWindow::stopAndResetTimer() {
    timer->stop();
    ui->_time->setText("00:00:00");
}

void MainWindow::openHowToPlay()
{
    HowToPlayWidget *howToPlayDialog = new HowToPlayWidget(this);
    howToPlayDialog->exec();
}

void MainWindow::showRules()
{
    QString rulesText = "Sudoku Rules :\n\n"
                        "1. The objective is to fill a 9x9 grid with digits so that each column, each row, and each of the nine 3x3 subgrids that compose the grid contain all of the digits from 1 to 9.\n\n"
                        "2. Each number can only appear once in each row, column, and 3x3 subgrid.\n\n"
                        "3. Some cells will already be filled in at the beginning of the game. The player's job is to fill in the remaining cells.\n\n"
                        "4. A valid Sudoku solution must obey the above rules and must have a unique solution.";

    QMessageBox::information(this, "Sudoku Rules", rulesText);
}

void MainWindow::showAbout()
{
    QString aboutText = "<b>Sudoku 1.1.0</b><br>"
                        "Based on TP4 Interfaces graphiques<br><br>"
                        "Copyrights Ensicaen<br>"
                        "All rights reserved<br><br>"
                        "<i>Note : </i> This software is provided 'as-is', without any express or implied warranty.";

    QMessageBox::about(this, "About", aboutText);
}

void MainWindow::showCredits()
{
    QString creditsText = "<b>Project Credits</b><br><br>"
                          "<b>Students:</b><br>"
                          "- Paul NGUYEN<br>"
                          "- Cécile LU<br>"
                          "<b>Course Professor:</b><br>"
                          "- Prof. Sebastien Fourey<br><br>"
                          "<b>TP Supervisor:</b><br>"
                          "- Prof. Jean-Jacques SCHWARTZMANN";

    QMessageBox::information(this, "Credits", creditsText);
}

void MainWindow::newGame()
{
    int number = rand() % 4 + 1;
    _sudoku->setDifficulty(number);
    _sudoku->loadGrid();
}

void MainWindow::loadStyleSheet(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier de style" << fileName;
        return;
    }

    QTextStream in(&file);
    QString styleSheet = in.readAll();
    qApp->setStyleSheet(styleSheet);

    file.close();
}

void MainWindow::onToggleButtonStateChanged(){
    if (ui->noteMode->isChecked()) {
        _sudoku->setMode(1);
    } else {
        _sudoku->setMode(0);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

