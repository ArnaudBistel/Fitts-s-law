#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QSound>
#include "fittstestwindow.h"
#include "homepage.h"
#include "resultspage.h"


class MainWindow : public QStackedWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
    FittsTestWindow& getFittsTestWindow();
    ResultsPage& getResultsPage();

public slots:
    void changeOnglet(QString name);
//    void setA(double A);

private:
    HomePage *home_page;
    FittsTestWindow *fitts_page;
    ResultsPage *results_page;
};

#endif // MAINWINDOW_H
