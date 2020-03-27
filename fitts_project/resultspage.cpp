#include "resultspage.h"

ResultsPage::ResultsPage(QWidget *parent, QString name):
    QWidget(parent)
{
    this->setObjectName(name);
    connect(this, SIGNAL(changeInterface(QString)), this->parent(), SLOT(changeOnglet(QString)));



    home_and_test_buttons_layout = new QHBoxLayout(this);

    go_home_button = new QPushButton("Accueil", this);
    connect(go_home_button, SIGNAL(clicked()), this, SLOT(goHome()));
    home_and_test_buttons_layout->addWidget(go_home_button);

    retry_test_button = new QPushButton("Refaire test", this);
    connect(retry_test_button, SIGNAL(clicked()), this, SLOT(retryTest()));
    home_and_test_buttons_layout->addWidget(retry_test_button);

    main_layout = new QVBoxLayout;
    main_layout->addLayout(home_and_test_buttons_layout);
}




void ResultsPage::retryTest()
{
    emit changeInterface("fitts_page");
}


void ResultsPage::goHome()
{
    emit changeInterface("home_page");
}
