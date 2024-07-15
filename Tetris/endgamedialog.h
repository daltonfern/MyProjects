#ifndef ENDGAMEDIALOG_H
#define ENDGAMEDIALOG_H

#include <QDialog>

class QVBoxLayout;
class QLabel;
class QPushButton;

class EndGameDialog : public QDialog {
    Q_OBJECT

public:
    EndGameDialog(QWidget *parent = nullptr);
};

#endif // ENDGAMEDIALOG_H
