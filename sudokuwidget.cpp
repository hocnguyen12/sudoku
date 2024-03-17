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
#include <QPushButton>

#include <QMouseEvent>

#include <QMessageBox>

SudokuWidget::SudokuWidget(QWidget *parent)
    : QWidget{parent}
{
    _difficulties << "Easy" << "Medium" << "Hard" << "Insane";

    for (int row = 0; row < 9; ++row) {
       for (int col = 0; col < 9; ++col) {
           _grid[row][col] = 0;
        }
    }
    _selectedCellIndex = QPoint(-1, -1);
    _difficulty = 1; // Easy by default


    _diffLabel = new QLabel(this);
    _diffLabel->move(0, 475);

/*
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(_diffLabel);
    setLayout(mainLayout);*/

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
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (_highlightedCells.contains(QPoint(row, col))) {
                painter.fillRect(col * cellSize, row * cellSize, cellSize, cellSize, QColor("#E5D1D1"));
            }
            if (_selectedCellIndex == QPoint(row, col)) {
                painter.fillRect(col * cellSize, row * cellSize, cellSize, cellSize, QColor("#B7A7A7"));
            }
            if (_grid[row][col] != 0) {
                QString number = QString::number(_grid[row][col]);

                // Si le nombre a été chargé à partir du fichier, utilisez une couleur de fond différente
                if (_loadedCells.contains(QPoint(row, col))) {
                    painter.setPen(Qt::black);
                } else {
                    painter.setPen(pen);
                }

                if (_incorrectCells.contains(QPoint(row, col))) {
                    painter.setPen(Qt::red);
                }

                painter.drawText(col * cellSize + 20, row * cellSize + 35, number);
            }
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
    _highlightedCells.clear();
    _loadedCells.clear();
}

void SudokuWidget::addNumber(int number) {
    qDebug() << "SudokuWidget::addNumber : " << number;

    if (_selectedCellIndex != QPoint(-1, -1)) {
       if (!_loadedCells.contains(_selectedCellIndex)) {
            _grid[_selectedCellIndex.x()][_selectedCellIndex.y()] = number;
            update();
       }
       if (isIncorrect(_selectedCellIndex.x(), _selectedCellIndex.y()) && !_incorrectCells.contains(_selectedCellIndex)) {
           _incorrectCells.append(_selectedCellIndex);
       } else if (isIncorrect(_selectedCellIndex.x(), _selectedCellIndex.y()) && _incorrectCells.contains(_selectedCellIndex)){
       } else {
           _incorrectCells.removeOne(_selectedCellIndex);
       }
       qDebug() << _incorrectCells;
    }
    update();
    checkEnd();
}

bool SudokuWidget::isIncorrect(int row, int col) {
    int value = _grid[row][col];
    // Check row
    for (int i = 0; i < 9; ++i) {
        if (i != col && _grid[row][i] == value) {
            return true;
        }
    }
    // check column
    for (int i = 0; i < 9; ++i) {
        if (i != row && _grid[i][col] == value) {
            return true;
        }
    }
    // Check 3x3 region
    int regionRow = row / 3 * 3;
    int regionCol = col / 3 * 3;
    for (int i = regionRow; i < regionRow + 3; ++i) {
        for (int j = regionCol; j < regionCol + 3; ++j) {
            if (i != row && j != col && _grid[i][j] == value) {
                return true;
            }
        }
    }
    return false;
}

void SudokuWidget::checkEnd() {
    bool flag = true;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (_grid[row][col] == 0)
                flag = false;
        }
    }
    if (!_incorrectCells.isEmpty()){
        flag = false;
    }

    if (flag) {
        QMessageBox msgBox;
        msgBox.setText("You have won.");
        msgBox.exec();
        // STOP TIMER
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

    QString file_name;
    switch(_difficulty) {
        case 1:
            file_name = ":/grids/Easy.txt";
            break;
        case 2:
            file_name = ":/grids/Medium.txt";
            break;
        case 3:
            file_name = ":/grids/Hard.txt";
            break;
        case 4:
            file_name = ":/grids/Insane.txt";
            break;
    }
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening file";
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
            QString text = "Grid ";
            text.append(_difficulties[_difficulty - 1]);
            text.append('#');
            text.append(QString::number(i));
            qDebug() << text;
            _diffLabel->setText(text);
            _diffLabel->adjustSize();
            _diffLabel->show();
            break;
        }
    }
    qDebug() << "diff : " << _difficulty;

    _loadedCells.clear();
    int index = 0;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (selectedGrid.at(index) != '0') {
                _grid[row][col] = selectedGrid.at(index).digitValue();
                _loadedCells.append(QPoint(row, col));
            }
            index++;
        }
    }
    qDebug() << "GRID :" << selectedGrid;

    file.close();

    // call paintEvent
    update();
}

void SudokuWidget::setDifficulty(int diff) {
    _difficulty = diff;
}

