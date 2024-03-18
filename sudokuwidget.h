#ifndef SUDOKUWIDGET_H
#define SUDOKUWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QString>
#include <QList>
#include <QPoint>
#include <QLabel>
#include <QFile>
#include <QMap>

// Définissez une fonction de comparaison pour QPoint
struct QPointCompare {
    bool operator()(const QPoint& p1, const QPoint& p2) const {
        if (p1.x() == p2.x()) {
            return p1.y() < p2.y();
        }
        return p1.x() < p2.x();
    }
};

// Spécialisez qMapLessThanKey pour QPoint
template<>
inline bool qMapLessThanKey<QPoint>(const QPoint& key1, const QPoint& key2) {
    return QPointCompare()(key1, key2);
}

class SudokuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SudokuWidget(QWidget *parent = nullptr);
    void addNumber(int number);
    void setDifficulty(int diff);
    void setMode(int mode);

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
    QList<QPoint> _selectedCells; // highlights all the grids with the same value as the one selected
    QPoint _selectedCellIndex;
    QLabel * _diffLabel;

    int _mode; // 0 : normal
              //1 : note
    QMap<QPoint, QList<int>> _notes;
signals:

public slots:
    void loadGrid();
    void clearGrid();

signals:
    void gameEnded();
};

#endif // SUDOKUWIDGET_H
