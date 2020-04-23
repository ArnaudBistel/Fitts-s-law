#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QSound>
#include "fittstestwindow.h"
#include "homepage.h"
#include "resultspage.h"
#include <QStyle>
#include <QDesktopWidget>


// Classe qui hérite de QStackedWidget et permet donc de transiter entre
// les différentes pages de l'application
class MainWindow : public QStackedWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

    // ------------- GETTERS -------------
    FittsTestWindow& getFittsTestWindow();
    ResultsPage& getResultsPage();

public slots:
    void changeOnglet(QString name);

private:
    // ------------- ATTRIBUTES -------------
    HomePage *home_page;
    FittsTestWindow *fitts_page;
    ResultsPage *results_page;
};

#endif // MAINWINDOW_H
