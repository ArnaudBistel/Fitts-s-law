#include "resultspage.h"
#include "mainwindow.h"
#include <iostream>

ResultsPage::ResultsPage(QWidget *parent, QString name):
    QWidget(parent)
{
    this->setObjectName(name);
    connect(this, SIGNAL(changeInterface(QString)), this->parent(), SLOT(changeOnglet(QString)));

    QRect window = QGuiApplication::screens().first()->geometry();
    int screen_width = window.width();

    results_label = new QLabel(this);
    // returns vector of tuple < distance to target, target size, time to click on target, theorical time to click on target >


    home_and_test_buttons_layout = new QHBoxLayout(this);

    go_home_button = new QPushButton("Accueil", this);
    connect(go_home_button, SIGNAL(clicked()), this, SLOT(goHome()));
    home_and_test_buttons_layout->addWidget(go_home_button);

    home_and_test_buttons_layout->insertSpacing(1, screen_width / 2);

    retry_test_button = new QPushButton("Refaire test", this);
    connect(retry_test_button, SIGNAL(clicked()), this, SLOT(retryTest()));
    home_and_test_buttons_layout->addWidget(retry_test_button);

    main_layout = new QVBoxLayout;
    main_layout->addWidget(results_label);
    main_layout->addLayout(home_and_test_buttons_layout);
    main_layout->setSizeConstraint(QLayout::SetMinimumSize);
}


void ResultsPage::displayResults()
{
    results_label->setText("couc");
        dataToPublish = static_cast<MainWindow*>(this->parent())->getFittsTestWindow().getFittsData().getData();
    //    dataToPublish.push_back( tuple<int, int, double, double>(get<0>(*i), get<1>(*i), get<2>(*i), fittsEquation(get<0>(*i), get<1>(*i))));
        int j = 1;
        QString results;
        for (data_to_publish_tuple::const_iterator i = dataToPublish.begin(); i != dataToPublish.end(); ++i)
        {
            results.append(QString::number(j));
            results.append ("distance to target : ");
            results.append(QString::number(get<0>(*i)));
            results.append("\n target size : ");
            results.append(QString::number(get<1>(*i)));
            results.append("\n time to click : ");
            results.append(QString::number(get<2>(*i)));
            results.append("\n Fitts time : ");
            results.append(QString::number(get<3>(*i)));
            results.append("\n\n");

            j++;
            // returns vector of tuple < distance to target, target size, time to click on target, theorical time to click on target >
        }
        std::cout << "coucoué" << endl ;
        std::cout << results.toStdString() << endl ;
        results_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        results_label->setWordWrap(true);
        results_label->setText(results);
}



void ResultsPage::retryTest()
{
    emit changeInterface("fitts_page");
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().startCountdown();
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().resetTest();
}


void ResultsPage::goHome()
{
    emit changeInterface("home_page");
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().resetTest();
}
