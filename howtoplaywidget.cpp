// howtoplaydialog.cpp
#include "howtoplaywidget.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

HowToPlayWidget::HowToPlayWidget(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("How to Play");

    // Création des QLabel pour le texte
    QLabel *titleLabel = new QLabel("Welcome to Sudoku", this);
    QLabel *instructionLabel = new QLabel("Instructions :", this);
    QLabel *playInstructionLabel = new QLabel("To play, use the mouse.\n Once a square selected, you can chose a number from 1 to 9 to input a number.", this);

    // Création des QLabel pour les images
    QLabel *imageLabel1 = new QLabel(this);
    QPixmap pixmap1(":/img/sudoku1.png");
    imageLabel1->setPixmap(pixmap1);

    QLabel *imageLabel2 = new QLabel(this);
    QPixmap pixmap2(":/img/sudoku2.png");
    imageLabel2->setPixmap(pixmap2);

    // Création des layouts
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *textImageLayout = new QHBoxLayout;
    QVBoxLayout *textLayout = new QVBoxLayout;
    QVBoxLayout *imageLayout = new QVBoxLayout;

    // Ajout du titre au layout principal
    mainLayout->addWidget(titleLabel);

    // Ajout du layout texte-image au layout principal
    mainLayout->addLayout(textImageLayout);

    textImageLayout->addLayout(textLayout);
    textImageLayout->addLayout(imageLayout);

    // Ajout des labels de texte au layout texte-image
    textLayout->addWidget(instructionLabel);
    textLayout->addWidget(playInstructionLabel);

    // Ajout des labels d'image au layout texte-image
    imageLayout->addWidget(imageLabel1);
    imageLayout->addWidget(imageLabel2);
}

HowToPlayWidget::~HowToPlayWidget()
{
    // Nettoyez les ressources si nécessaire
}
