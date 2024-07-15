#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QFont>
#include <QTableWidget>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "mainwindow.h"
#include <gamewindow.h>

/**
 * @author Dalton Fernandes
 * @class MainWindow::MainWindow Renders game's main menu window
 *
 * Renders the game's main menu window by setting and scaling the background image.
 * Additionally, configures start button to launch the game window upon being pressed.
 */

/**
 * @brief MainWindow::MainWindow Main menu window constructor
 *
 * Constructs main menu window by calling displayUI and connecting the start button to the start game method
 *
 * @param parent Default parent widget
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    MainWindow::displayUI(this);
    connect(startBtn, &QPushButton::pressed, this, &MainWindow::start);
}

/**
 * @brief MainWindow::displayUI Render the main menu window content
 *
 * Sets and scales background image to fill main window and configures start button
 *
 * @param parent Parent widget connected to main window
 */
void MainWindow::displayUI(QWidget *parent)
{
    // Display main menu window background
    QLabel *menu = new QLabel(parent);
    QPixmap pix(":/imgs/menuBackground.png");
    menu->setGeometry(0, 0, 1280, 720);
    menu->setPixmap(pix.scaled(1280, 720));

    // Display START button
    startBtn = new QPushButton(parent);
    QFont font = startBtn->font();
    font.setPointSize(16);
    font.setFamily("Helvetica");
    startBtn->setStyleSheet("font-weight: bold;");
    startBtn->setFont(font);
    startBtn->setGeometry(QRect(QPoint(530,320), QSize(220, 60)));
    startBtn->setText("START");

    //Testing
    //QStringList usernames = {"User1", "User2", "User3", "User4", "User5", "User6"};
    //QList<int> scores = {100, 200, 150, 300, 250, 600};

    // Display SCOREBOARD table
    QTableWidget *scoreboard = new QTableWidget(parent);
    scoreboard->setFont(font);
    scoreboard->setStyleSheet("font-weight: bold;");
    scoreboard->setRowCount(5);
    scoreboard->setColumnCount(2);
    scoreboard->setGeometry(QRect(QPoint(850, 450), QSize(400, 200)));
    QStringList headers;
    headers << "Username" << "Score";
    scoreboard->setHorizontalHeaderLabels(headers);

    // Set stylesheets to enhance appearance
    scoreboard->setStyleSheet("QTableWidget { border: 2px solid black; border-radius: 5px; }"
                              "QHeaderView::section { background-color: lightgray; border: none; border-bottom: 2px solid black; }"
                              "QTableWidget::item { padding: 10px; border: none; }"
                              "QTableWidget::item:selected { background-color: lightblue; }");

    // Read data from the text file
    QFile file("data.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        int row = 0;
        while (!in.atEnd() && row < 5) {
            QString username = in.readLine().trimmed(); // Read username
            QString score = in.readLine().trimmed(); // Read score
            QTableWidgetItem *usernameItem = new QTableWidgetItem(username);
            QTableWidgetItem *scoreItem = new QTableWidgetItem(score);
            scoreboard->setItem(row, 0, usernameItem);
            scoreboard->setItem(row, 1, scoreItem);
            row++;
        }
        file.close();
    } else {
        qDebug() << "Failed to open file for reading";
    }
}

/**
 * @brief MainWindow::start Launches game window
 *
 * Used to connect launching game window to pressed action on start button
 */
void MainWindow::start()
{
    GameWindow *startGame = new GameWindow(nullptr);
    startGame->show();
}

