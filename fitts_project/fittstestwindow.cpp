#include "fittstestwindow.h"
#include <iostream>
#include "mainwindow.h"


FittsTestWindow::FittsTestWindow(QWidget *parent, QString name):
    QWidget(parent) , last_recorded_pos()
{
    this->setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    this->size(),
                    QGuiApplication::screens().first()->geometry()
                    )
                );

    a=0.2;
    b=0.1;
    target_number=10;
    target_size_max = 150;
    target_size_mini = 10;
    this->fitts_data = new FittsData() ;
    this->test_timer = new QElapsedTimer;

    // set test params
    // first click doesn't count
    click_count = -1;

    // test view
    rect = new QFrame;
    QRect window = QGuiApplication::screens().first()->geometry();
    int screen_width = window.width();
    int screen_height = window.height();

    rect->setFixedSize(screen_width * 2/3,screen_height * 2/3);
    rect->setStyleSheet("background-color: rgb(170,189,206); border: 1px solid grey;");

    this->setObjectName(name);
    connect(this,SIGNAL(changeInterface(QString)), this->parent(),SLOT(changeOnglet(QString)));

    instructions_label = new QLabel;
    instructions_label->setText("<font color=\"black\">Cliquez sur les cibles </font> <font color=\"red\">ROUGE</font><font color=\"black\"> !</font>");

    instructions_label->setFont(QFont("Roboto", 12, QFont::Bold, true));
    instructions_label->setAlignment(Qt::AlignHCenter);

    countdown_timer = new QTimer(this);
    connect(countdown_timer, SIGNAL(timeout()), this, SLOT(updateCountdown()));

    instructions_layout = new QVBoxLayout;
    instructions_layout->addWidget(instructions_label);

    click_me_button = new QPushButton("5", rect);

    // Get size of test screen
//    int window_width = rect->size().width()/2;
//    int window_height = rect->size().height()/2;
    int click_me_button_width = rect->size().width() / 10 ;
    if (click_me_button_width < 50 ){
        click_me_button_width = 50 ;
    }
    int click_me_button_height = click_me_button_width;
    click_me_button->setGeometry(((rect->width()) / 2) - (click_me_button_width/ 2), ((rect->height() / 2) - (click_me_button_height / 2)), click_me_button_width, click_me_button_height);


    click_me_button->setStyleSheet("background-color: rgb(217,72,72); color: white;");
    click_me_button->setEnabled(false);

    connect(click_me_button, SIGNAL(clicked()), this, SLOT(recordData()));
    connect(click_me_button, SIGNAL(clicked()), this, SLOT(changeButtonPosition()));

    test_finished_label = new QLabel("Test fini ! Recommencez ou allez voir les résultats.", rect);

    test_finished_label->setFont(QFont("Roboto", 12, QFont::Bold, true));

    int label_width = 375;
    int label_height = 50;
    test_finished_label->setGeometry(((rect->width()) / 2) - (label_width/ 2), ((rect->height() / 2) - (label_height / 2)), label_width, label_height);

    test_finished_label->setVisible(false);

    beep_file = new QString("../res/beep.wav");
    beeeep_file = new QString("../res/beeeep.wav");
    beep_sound = new QSound(*beep_file, this);
    beeeep_sound = new QSound(*beeeep_file, this);

    // back, reset and results
    bottom_buttons_layout = new QHBoxLayout;

    back_to_home_button = new QPushButton ("Retour", this);
    connect(back_to_home_button, SIGNAL(clicked()), this, SLOT(goBack()));
    bottom_buttons_layout->addWidget(back_to_home_button);

    bottom_buttons_layout->insertSpacing(1, screen_width / 3);

    // reset button in case the user wants to retry before the test ends
    reset_button = new QPushButton("Recommencer le test");
    connect(reset_button, SIGNAL(clicked()), this, SLOT(resetTest()));
    bottom_buttons_layout->addWidget(reset_button);

    results_button = new QPushButton("Résultats", this);
    results_button->setVisible(true);
    results_button->setEnabled(false);
    connect(results_button, SIGNAL(clicked()), this, SLOT(goToResults()));
    bottom_buttons_layout->addWidget(results_button);


    main_layout = new QVBoxLayout;
    main_layout->addLayout(instructions_layout);
    main_layout->addWidget(rect);
    main_layout->addLayout(bottom_buttons_layout);
    this->setLayout(main_layout);
}


void FittsTestWindow::changeButtonPosition()
{
    click_count++;

    // Initialize random speed
    QTime now = QTime::currentTime();
    qsrand(now.msec());

    // Generate random size
    int button_width = qrand()%300 + target_size_mini;
    while (button_width > target_size_max)
    {
        button_width = qrand()%300 + target_size_mini;
    }
    int button_height = button_width;

    // Get size of screen
    int window_width = rect->size().width();
    int window_height = rect->size().height();

    // Generate random position
    int x_coord = 0;
    int xTemp = (qrand()%window_width) - button_width;
    if(xTemp >= target_size_mini && xTemp < window_width - target_size_mini)
        x_coord = xTemp;

    int y_coord = 0;
    int yTemp = (qrand()%window_height) - button_height;
    if( yTemp >= target_size_mini && yTemp < window_height  - target_size_mini)
        y_coord = yTemp;

    click_me_button->setGeometry(x_coord, y_coord, button_width, button_height);

    // Set visual effects
    QString str="border-radius: ";
    str += QString::number(rand()%(button_height/2));
    str += "px; background-color: rgb(217,72,72)";
    str+=";";
    click_me_button->setStyleSheet(str);

    int remaining_target_number = target_number - click_count;
    click_me_button->setText(QString::number(remaining_target_number));
    click_me_button->setFont(QFont("Roboto", click_me_button->height() * 1/2 , QFont::Bold, true));

    if (click_count == 0)
    {
        if (beeeep_sound != NULL )
            beeeep_sound->stop();

        this->test_timer->start();
        this->fitts_data->setA(this->a);
        this->fitts_data->setB(this->b);
        this->fitts_data->setTargetNumber(this->target_number);
    }

    if (click_count >= target_number) {
        this->testFinished();
    }

}

void FittsTestWindow::recordData()
{
        QPoint current_pos = rect->mapFromGlobal(QCursor::pos());

        // compute distance between last recorded position and target center
        if(click_count >= 0)
        {
            double time_elapsed = test_timer->restart();
            this->fitts_data->sendData(last_recorded_pos, QPoint(click_me_button->x(), click_me_button->y()), click_me_button->width(), time_elapsed, click_count);
        }
        last_recorded_pos.setX(current_pos.x());
        last_recorded_pos.setY(current_pos.y());
}



void FittsTestWindow::testFinished()
{
    //        cout << "Dans test finished" << endl;
    test_finished_label->setVisible(true);
    click_me_button->setVisible(false);
    results_button->setEnabled(true);
    this->fitts_data->computeTestResults();
//    this->fitts_data->getData();
}


void FittsTestWindow::resetTest()
{
//    cout << " dans resetTest " << endl;
    // set test params
    // first click doesn't count
    click_count = -1;

    this->fitts_data->resetData();

    results_button->setEnabled(false);


    if( beep_sound != NULL){
        beep_sound->stop();
    }

    if (beeeep_sound != NULL ){
        beeeep_sound->stop();
    }

    // Get size of screen
//    int window_width = rect->size().width()/2;
//    int window_height = rect->size().height()/2;
    int click_me_button_width = rect->size().width() / 10 ;
    if (click_me_button_width < 50 ){
        click_me_button_width = 50 ;
    }
    int click_me_button_height = click_me_button_width;
    click_me_button->setGeometry(((rect->width()) / 2) - (click_me_button_width/ 2), ((rect->height() / 2) - (click_me_button_height / 2)), click_me_button_width, click_me_button_height);

    click_me_button->setVisible(true);
    click_me_button->setEnabled(false);

    click_me_button->setText("6");
    click_me_button->setFont(QFont("Roboto", click_me_button->width() * 1 / 3, QFont::Bold, true));
    click_me_button->setStyleSheet("background-color: rgb(217,72,72); color: white;");

    beep_sound->play();

    countdown_timer->start(1000);
    test_finished_label->setVisible(false);
}


void FittsTestWindow::updateCountdown()
{;
//    cout << "Dans update coundtown" << endl;
    QString sec = click_me_button->text();
    int countdown = sec.toInt();
    countdown--;
    if(countdown > 0)
    {
        click_me_button->setText(QString::number(countdown));
        beep_sound->play();
    } else if (countdown == 0) {
        click_me_button->setEnabled(true);
        click_me_button->setText("Click me !");
        click_me_button->setFont(QFont("Roboto", click_me_button->width() * 1 / 7, QFont::Bold, true));
        countdown_timer->stop();
        beeeep_sound->play();
    }
}


void FittsTestWindow::startCountdown()
{
//    cout << "Dans start coundtown" << endl;
    click_me_button->setText("6");
    click_me_button->setFont(QFont("Roboto", click_me_button->width() * 1 / 3, QFont::Bold, true));
    countdown_timer->start(1000);
    beep_sound->play();
}

void FittsTestWindow::stopCountdown()
{
//    cout << "Dans stop coundtown" << endl;
    countdown_timer->stop();
}


void FittsTestWindow::goBack()
{
//    this->resetTest();
    countdown_timer->stop();
    emit changeInterface("home_page");
}


void FittsTestWindow::goToResults()
{

    if( beep_sound != NULL){
        beep_sound->stop();
    }

    if (beeeep_sound != NULL ){
        beeeep_sound->stop();
    }
    countdown_timer->stop();
    emit changeInterface("results_page");
    static_cast<MainWindow*>(this->parent())->getResultsPage().displayResults();
    static_cast<MainWindow*>(this->parent())->getResultsPage().displayData();
}

void FittsTestWindow::setA(double a)
{
    this->a = a;
//    QTextStream(stdout) << "a" << endl;
}

void FittsTestWindow::setB(double b)
{
    this->b = b;
//        QTextStream(stdout) << "b" << endl;
}

void FittsTestWindow::setTargetNumber(int n)
{
    this->target_number = n;
//        QTextStream(stdout) << "t number" << endl;
}

void FittsTestWindow::setTargetSizeMini(int m)
{
    this->target_size_mini = m;
//        QTextStream(stdout) << "t min" << endl;
}

void FittsTestWindow::setTargetSizeMax(int m)
{
    this->target_size_max = m;
//        QTextStream(stdout) << "t max" << endl;
}


FittsData& FittsTestWindow::getFittsData()
{
    return *fitts_data;
}

