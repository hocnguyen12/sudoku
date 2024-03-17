#include "sudokuwidget.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>

#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QRandomGenerator>
#include <QDateTime>
#include <QDebug>

#include <QMouseEvent>

SudokuWidget::SudokuWidget(QWidget *parent)
    : QWidget{parent}
{
    for (int row = 0; row < 9; ++row) {
       for (int col = 0; col < 9; ++col) {
           _grid[row][col] = 0;
        }
    }
    _selectedCellIndex = QPoint(-1, -1);
}

void SudokuWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPen pen;
    pen.setColor("#1d545c");
    pen.setWidth(3);

    int cellSize = 50;
    int gridSize = cellSize * 9;

    // Draw numbers
    painter.setFont(QFont("Arial", 16));
    int index = 0;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (_highlightedCells.contains(QPoint(row, col))) {
                painter.fillRect(col * cellSize, row * cellSize, cellSize, cellSize, QColor("#82B1BD"));
            }
            if (_selectedCellIndex == QPoint(row, col)) {
                painter.fillRect(col * cellSize, row * cellSize, cellSize, cellSize, QColor("#62A6FB"));
            }
            if (_grid[row][col] != 0) {
                QString number = QString::number(_grid[row][col]);

                // Si le nombre a été chargé à partir du fichier, utilisez une couleur de fond différente
                if (_loadedCells.contains(index)) {
                    painter.setPen(Qt::black);
                } else {
                    painter.setPen(pen);
                }

                painter.drawText(col * cellSize + 20, row * cellSize + 35, number);
            }
            index++;
        }
    }

    // Draw GRID
    // vertical lines
    for (int i = 0; i <= 9; ++i) {
        if (i % 3 == 0) {
            painter.setPen(pen);
        } else {
            painter.setPen(Qt::black);
        }
        painter.drawLine(i * cellSize, 0, i * cellSize, gridSize);
    }

    // horizontal lines
    for (int i = 0; i <= 9; ++i) {
        if (i % 3 == 0) {
            painter.setPen(pen);
        } else {
            painter.setPen(Qt::black);
        }
        painter.drawLine(0, i * cellSize, gridSize, i * cellSize);
    }
}

void SudokuWidget::clearGrid() {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            _grid[row][col] = 0;
        }
    }
}

void SudokuWidget::mousePressEvent(QMouseEvent *event) {
    QPoint clickPos = event->pos();

    _highlightedCells.clear();


    int cellSize = 50;
    int row = clickPos.y() / cellSize;
    int col = clickPos.x() / cellSize;

    if (row >= 0 && row < 9 && col >= 0 && col < 9) {
        // Changez la couleur de toutes les cases sur la ligne
        for (int i = 0; i < 9; ++i) {
            _highlightedCells.append(QPoint(row, i));
        }

        // Changez la couleur de toutes les cases sur la colonne
        for (int i = 0; i < 9; ++i) {
            _highlightedCells.append(QPoint(i, col));
        }

        _selectedCellIndex = QPoint(row, col);
        update();
    } else {
        _highlightedCells.clear();
        _selectedCellIndex = QPoint(-1, -1);
        update();
    }

    QWidget::mousePressEvent(event);
}

void SudokuWidget::loadGrid() {
    clearGrid();
    qDebug() << "SudokuWidget::LoadGrid";

    QString file_name = ":/grids/Insane.txt";

    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur lors de l'ouverture du fichier.";
        return;
    }

    QTextStream in(&file);

    QString firstLine = in.readLine();
    int numSuites = firstLine.toInt();

    QRandomGenerator::securelySeeded();
    int randomLine = QRandomGenerator::global()->bounded(1, numSuites + 1);

    QString selectedGrid;
    for (int i = 1; i <= numSuites; ++i) {
        selectedGrid = in.readLine();
        if (i == randomLine) {
            break;
        }
    }

    _loadedCells.clear();
    int index = 0;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (selectedGrid.at(index) != '0') {
                _grid[row][col] = selectedGrid.at(index).digitValue();
                _loadedCells.append(index);
            }
            index++;
        }
    }

    qDebug() << "Suite de chiffres choisie au hasard :" << selectedGrid;

    /*
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            qDebug() << _grid[row][col];
        }
    }*/

    file.close();

    // call paintEvent
    update();
}

