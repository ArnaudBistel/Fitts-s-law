#include "mainwindow.h"

MainWindow::MainWindow()
{
    home_page = new HomePage(this, "home_page");
    this->addWidget(static_cast<QWidget*>(home_page));

    fitts_page = new FittsTestWindow(this, "fitts_page");
    this->addWidget(static_cast<QWidget*>(fitts_page));

    results_page = new ResultsPage(this, "results_page");
    this->addWidget(static_cast<QWidget*>(results_page));

    this->setCurrentWidget(home_page);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}


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


// slot pour changer d'onglet
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
