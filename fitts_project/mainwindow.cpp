#include "mainwindow.h"


// Classe qui hérite de QStackedWidget et permet donc de transiter entre
// les différentes pages de l'application
MainWindow::MainWindow()
{
    home_page = new HomePage(this, "home_page");
    this->addWidget(static_cast<QWidget*>(home_page));

    fitts_page = new FittsTestWindow(this, "fitts_page");
    this->addWidget(static_cast<QWidget*>(fitts_page));

    results_page = new ResultsPage(this, "results_page");
    this->addWidget(static_cast<QWidget*>(results_page));

    this->setCurrentWidget(home_page);
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
}



// ----------------------------------
// ------------- GETTERS -------------
// ----------------------------------


FittsTestWindow& MainWindow::getFittsTestWindow()
{
    return *fitts_page;
}


ResultsPage& MainWindow::getResultsPage()
{
    return *results_page;
}


MainWindow::~MainWindow()
{}


//Controlleur : slot pour changer de page
void MainWindow::changeOnglet(QString name)
{
    if((name == home_page->objectName()) && home_page)
    {
        this->setCurrentWidget(home_page);
        return;
    }
    else if((name == fitts_page->objectName()) && fitts_page)
    {
        this->setCurrentWidget(fitts_page);
        fitts_page->startCountdown();
        return;
    }
    else if((name == results_page->objectName()) && results_page)
    {
        this->setCurrentWidget(results_page);
        return;
    }
    else
    {
        QMessageBox::information(0,tr("Erreur changement onglet"),tr("Impossible de changer l'interface pour l'onglet ")+name+tr(".\nCet onglet n'existe plus ou n'a pas été créer."));
    }
}
