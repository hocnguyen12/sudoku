#ifndef SUDOKUWIDGET_H
#define SUDOKUWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QString>
#include <QList>
#include <QPoint>
#include <QLabel>

class SudokuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SudokuWidget(QWidget *parent = nullptr);
    void addNumber(int number);
    void setDifficulty(int diff);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    bool isIncorrect(int row, int col);
    void checkEnd();
private:
    int _difficulty; // 1 : easy
                     // 2 : medium
                     // 3 : hard
                     // 4 : insane
    QStringList _difficulties;
    int _grid[9][9];
    QList<QPoint> _loadedCells;
    QList<QPoint> _highlightedCells;
    QList<QPoint> _incorrectCells;
    QPoint _selectedCellIndex;
    QLabel * _diffLabel;
signals:

public slots:
    void loadGrid();
    void clearGrid();

};

#endif // SUDOKUWIDGET_H
