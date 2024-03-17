#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sudokuwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void onNumberButtonClicked();
    ~MainWindow();
private slots:
    void onDifficultyChanged(int index);
private:
    Ui::MainWindow *ui;
    SudokuWidget * _sudoku;
};
#endif // MAINWINDOW_H
