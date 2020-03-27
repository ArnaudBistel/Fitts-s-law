#include "fittstestwindow.h"

FittsTestWindow::FittsTestWindow(QWidget *parent, QString name):
    QWidget(parent)
{
    this->setObjectName(name);
    connect(this,SIGNAL(changeInterface(QString)), this->parent(),SLOT(changeOnglet(QString)));

    instructions_label = new QLabel("Cliquez sur les cibles ROUGE\n");

    countdown_layout = new QHBoxLayout;
    countdown_text_label = new QLabel ("Le test commencera dans ");
    countdown_label = new QLabel("5");
    countdown_layout->addWidget(countdown_text_label);
    countdown_layout->addWidget(countdown_label);

    countdown_timer = new QTimer(this);
    connect(countdown_timer, SIGNAL(timeout()), this, SLOT(updateCountdown()));
    countdown_timer->start(1000);

    instructions_layout = new QVBoxLayout;
    instructions_layout->addWidget(instructions_label);
    instructions_layout->addLayout(countdown_layout);

    // test view
    rect = new QFrame;
    rect->setFixedSize(600,500);
    rect->setStyleSheet("background-color: rgb(251,255,206);");
    click_me_button = new QPushButton("Clic", rect);
    click_me_button->setVisible(false);
    connect(click_me_button, SIGNAL(clicked()), this, SLOT(changeButtonPosition()));

    x_coord = 26;
    y_coord = 36;

    // back and results
    back_results_layout = new QHBoxLayout;

    back_to_home_button = new QPushButton ("Retour", this);
    connect(back_to_home_button, SIGNAL(clicked()), this, SLOT(goBack()));
    back_results_layout->addWidget(back_to_home_button);

    results_button = new QPushButton("Résultats", this);
    results_button->setVisible(true);
    connect(results_button, SIGNAL(clicked()), this, SLOT(goToResults()));
    back_results_layout->addWidget(results_button);


    main_layout = new QVBoxLayout;
    main_layout->addLayout(instructions_layout);
    main_layout->addWidget(rect);
    main_layout->addLayout(back_results_layout);
    this->setLayout(main_layout);
}


void FittsTestWindow::changeButtonPosition()
{
    // en fonctin du temps?
    x_coord += 15;
    y_coord += 20;
    click_me_button->move(x_coord, y_coord);

}


void FittsTestWindow::updateCountdown()
{
    QString sec = countdown_label->text();
    int countdown = sec.toInt();
    countdown--;
    if(countdown > 0)
    {
        countdown_label->setText(QString::number(countdown));
    } else if (countdown == 0) {
        click_me_button->setVisible(true);
        countdown_label->setText("GO!");
    }
}


void FittsTestWindow::startCountdown()
{
    countdown_label->setText("6");
}


void FittsTestWindow::goBack()
{
    emit changeInterface("home_page");
}


void FittsTestWindow::goToResults()
{
    emit changeInterface("results_page");
}
