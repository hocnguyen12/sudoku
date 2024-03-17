#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sudokuwidget.h"|
#include "howtoplaywidget.h"
#include <QTimer>
#include <QTime>
#include <QDebug>

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
    void stopTimer();
    void stopAndResetTimer();
    void loadStyleSheet(const QString &fileName);

private slots:
    void onDifficultyChanged(int index);
    void onToggleButtonStateChanged();
    void updateTime();
    void startTimerOnLoad();
    void openHowToPlay();
    void showRules();
    void showAbout();
    void showCredits();
    void newGame();
private:
    Ui::MainWindow *ui;
    SudokuWidget * _sudoku;
    QTimer *timer;
    QTime startTime;
};
#endif // MAINWINDOW_H
