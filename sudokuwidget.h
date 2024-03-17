#ifndef SUDOKUWIDGET_H
#define SUDOKUWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QString>
#include <QList>
#include <QPoint>

class SudokuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SudokuWidget(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void clearGrid();

private:
    int _difficulty; // 1 : easy
                     // 2 : medium
                     // 3 : hard
                     // 4 : insane
    int _grid[9][9];
    QList<int> _loadedCells;
    QList<QPoint> _highlightedCells;
    QPoint _selectedCellIndex;
signals:

public slots:
    void loadGrid();

};

#endif // SUDOKUWIDGET_H
