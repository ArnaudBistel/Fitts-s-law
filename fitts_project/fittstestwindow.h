#ifndef FITTSTESTWINDOW_H
#define FITTSTESTWINDOW_H

#include <QtWidgets>
#include <QSound>
#include "homepage.h"
#include "FittsData.h"
#include "resultspage.h"

class FittsTestWindow : public QWidget
{
  Q_OBJECT

public:
    FittsTestWindow(QWidget *parent,QString name);
    void startCountdown();
//    FittsTestWindow(const FittsTestWindow& fitts);

public slots:
    void updateCountdown();
    void changeButtonPosition();
    void goBack();
    void goToResults();
    void resetTest();
    void recordData();
//    void initializeTest();

signals:
    void changeInterface(QString name);

private:
    void testFinished();
    void setA(double a);
    void setB(double b);
    void setTargetNumber(int n);
    void setTargetSizeMini(int m);
    void setTargetSizeMax(int m);


    // instructions
    QVBoxLayout *instructions_layout;
    QHBoxLayout *countdown_layout;
    QLabel *instructions_label;
//    QLabel *countdown_text_label;
//    QLabel *countdown_label;
    QTimer *countdown_timer;

    // test
//    QLabel *mouse_position_label;
//    QLabel *label;

    // test view
    int x_coord;
    int y_coord;
    QPushButton *click_me_button;
    QFrame *rect;
    QVBoxLayout *main_layout;
    QLabel *test_finished_label;
    QElapsedTimer *test_timer;

    // back reset and results
    QHBoxLayout *bottom_buttons_layout;
    QPushButton *back_to_home_button;
    QPushButton *results_button;
    QPushButton *reset_button;

    // test parameters
    int click_count;

private:
    int target_number;
    double a;
    double b;
    int target_size_mini;
    int target_size_max;
    FittsData *fitts_data;
    QPoint last_recorded_pos;
    FittsData& getFittsData();
    QString *beep_file;
    QString *beeeep_file;
    QSound *beep_sound;
    QSound *beeeep_sound;

    friend class MainWindow;
    friend class HomePage;
    friend class ResultsPage;

};

#endif // FITTSTESTWINDOW_H
