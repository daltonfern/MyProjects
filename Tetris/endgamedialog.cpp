#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>


#include "endgamedialog.h"

/**
 * @author Dalton Fernandes
 * @brief EndGameDialog::EndGameDialog Construct the end game dialog
 *
 * Configures the end game dialog with the game over message and an exit button which closes the game window
 *
 * @param parent Parent widget, always set as the game window
 */
EndGameDialog::EndGameDialog(QWidget *parent) : QDialog(parent) {
    this->setModal(true);
    setWindowTitle("Game Over");
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *message = new QLabel("Game Over! You have reached the top.", this);
    layout->addWidget(message);

    QLineEdit *nameInput = new QLineEdit(this);
    nameInput->setPlaceholderText("Enter your name");
    layout->addWidget(nameInput);

    QPushButton *exitButton = new QPushButton("Exit", this);
    connect(exitButton, &QPushButton::clicked, this, &EndGameDialog::accept);
    layout->addWidget(exitButton);

    setLayout(layout);

}
