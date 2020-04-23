#ifndef FITTSTESTWINDOW_H
#define FITTSTESTWINDOW_H

#include <QtWidgets>
#include <QSound>
#include "homepage.h"
#include "FittsData.h"
#include "resultspage.h"
#include <QFontDatabase>

class FittsTestWindow : public QWidget
{
  Q_OBJECT

public:
    FittsTestWindow(QWidget *parent,QString name);


    // ------------- SLOTS -------------
public slots:
    void changeButtonPosition();
    void recordData();

    void startCountdown();
    void updateCountdown();
    void stopCountdown();

    void goBack();
    void resetTest();
    void goToResults();

signals:
    void changeInterface(QString name);

private:

    // ------------- ATTRIBUTES -------------

    // ----------------------------------
    // Instructions
    // ----------------------------------
    QVBoxLayout *instructions_layout;
//    QHBoxLayout *countdown_layout;
    QLabel *instructions_label;

    // ----------------------------------
    // Fenêtre de test
    // ----------------------------------
    QFrame *rect;

    // ----------------------------------
    // Cible
    // ----------------------------------
    QPushButton *click_me_button;
    QTimer *countdown_timer;
    QLabel *test_finished_label;
    QString *beep_file;
    QString *beeeep_file;
    QSound *beep_sound;
    QSound *beeeep_sound;

    // ----------------------------------
    // back, reset and results
    // ----------------------------------
    QHBoxLayout *bottom_buttons_layout;
    QPushButton *back_to_home_button;
    QPushButton *results_button;
    QPushButton *reset_button;

    // -------------------------------------
    // vertical layout that contains all the widgets in the HomePage
    // -------------------------------------
    QVBoxLayout *main_layout;

    // ----------------------------------
    // Paramètres de test
    // ----------------------------------
    QElapsedTimer *test_timer;
    int click_count;
    int target_number;
    double a;
    double b;
    int target_size_mini;
    int target_size_max;
    FittsData *fitts_data;
    QPoint last_recorded_pos;


    // ------------- METHODES -------------
    void testFinished();
    void initTarget();


    // ------------- SETTERS -------------
    void setA(double a);
    void setB(double b);
    void setTargetNumber(int n);
    void setTargetSizeMini(int m);
    void setTargetSizeMax(int m);


    // ------------- GETTERS -------------
    FittsData& getFittsData();


    // ------------- FRIENDS -------------
    friend class MainWindow;
    friend class HomePage;
    friend class ResultsPage;

};

#endif // FITTSTESTWINDOW_H
