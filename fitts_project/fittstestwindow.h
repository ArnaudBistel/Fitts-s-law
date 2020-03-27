#ifndef FITTSTESTWINDOW_H
#define FITTSTESTWINDOW_H

#include <QtWidgets>

class FittsTestWindow : public QWidget
{
  Q_OBJECT

public:
    FittsTestWindow(QWidget *parent,QString name);
    void startCountdown();

public slots:
    void updateCountdown();
    void changeButtonPosition();
    void goBack();
    void goToResults();

signals:
    void changeInterface(QString name);

private:

    // instructions
    QVBoxLayout *instructions_layout;
    QHBoxLayout *countdown_layout;
    QLabel *instructions_label;
    QLabel *countdown_text_label;
    QLabel *countdown_label;
    QTimer *countdown_timer;

    // test view
    int x_coord;
    int y_coord;
    QPushButton *click_me_button;
    QFrame *rect;
    QVBoxLayout *main_layout;

    // back and results
    QHBoxLayout *back_results_layout;
    QPushButton *back_to_home_button;
    QPushButton *results_button;

};

#endif // FITTSTESTWINDOW_H
