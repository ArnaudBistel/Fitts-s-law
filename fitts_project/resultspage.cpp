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
    int screen_height = window.height();


    results_label = new QLabel(this);
    // returns vector of tuple < distance to target, target size, time to click on target, theorical time to click on target >



//    QSplineSeries *series = new QSplineSeries();
//            series->setName("test");
//                        series->append(2, 4);
//                        series->append(3, 8);
//                        series->append(7, 4);
//                        series->append(10, 5);
//                        *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
//                        QChart *charta = new QChart();
//                        charta->legend()->hide();
//                        charta->addSeries(series);

//                        charta->setTitle("Simple spline chart example");
//                        charta->createDefaultAxes();
//                        charta->axisY()->setRange(0, 10);
    chartView = new QChartView(this);
    chartView->resize(screen_width * 2/3,screen_height * 2/3);
    chartView->setRenderHint(QPainter::Antialiasing);
//    chartView->setChart(charta);

     chart = new QChart();

// //////////////////////////////////////////////////////////////////////
        fitts_formula_layout = new QHBoxLayout;
       fitts_formula_box = new QGroupBox(tr("Loi de Fitts"), this);
    fitts_form = new QFormLayout;
//    fitts_form->setVerticalSpacing(15);
    a_spinbox = new QDoubleSpinBox;
    a_spinbox->setValue(0.2);
    a_spinbox->setDecimals(2);
    a_spinbox->setMaximum(1);
    a_spinbox->setMinimum(0);
    a_spinbox->setSingleStep(0.05);
    connect(a_spinbox, SIGNAL(valueChanged(double)), this, SLOT(setA(double)));
        connect(a_spinbox, SIGNAL(valueChanged(double)), this, SLOT(computeFitts()));
    fitts_form->addRow("Choix de a  \t\t", a_spinbox);

    b_spinbox = new QDoubleSpinBox;
    b_spinbox->setValue(0.1);
    b_spinbox->setDecimals(2);
    b_spinbox->setMaximum(1);
    b_spinbox->setMinimum(0);
    b_spinbox->setSingleStep(0.05);
    connect(b_spinbox, SIGNAL(valueChanged(double)), this, SLOT(setB(double)));
            connect(b_spinbox, SIGNAL(valueChanged(double)), this, SLOT(computeFitts()));
    fitts_form->addRow("Choix de b \t\t", b_spinbox);

    fitts_form->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);

    fitts_formula_layout->addLayout(fitts_form);

//    configuration_box = new QGroupBox(tr("Configuration"), this);
    configuration_form = new QFormLayout;

//    configuration_form->setVerticalSpacing(15);
        target_number_label = new QLabel();
//        target_number_spinbox = new QSpinBox;
//    target_number_spinbox->setValue(10);
//    target_number_spinbox->setRange(10,20);
//    connect(target_number_spinbox, SIGNAL(valueChanged(int)), this, SLOT(setTargetNumber(int)));
    configuration_form->addRow("Nombre de cibles \t", target_number_label);
//    target_number_spinbox->setReadOnly(true);

    target_mini_size_label = new QLabel();
//    target_mini_size_spinbox = new QSpinBox;
//    target_mini_size_spinbox->setValue(10);
//    target_mini_size_spinbox->setRange(10,100);
//    connect(target_mini_size_spinbox, SIGNAL(valueChanged(int)), this, SLOT(setTargetSizeMini(int)));
    configuration_form->addRow("Taille minimum des cibles \t", target_mini_size_label);
//    target_mini_size_spinbox->setReadOnly(true);

    target_max_size_label = new QLabel();
//    target_max_size_spinbox = new QSpinBox;
//    target_max_size_spinbox->setValue(150);
//    target_max_size_spinbox->setRange(150,300);
//    connect(target_max_size_spinbox, SIGNAL(valueChanged(int)), this, SLOT(setTargetSizeMax(int)));
//    target_max_size_spinbox->setReadOnly(true);
    configuration_form->addRow("Taille maximum des cibles \t", target_max_size_label);

    configuration_form->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);

//    configuration_box->setLayout(configuration_form);
//    configuration_box->setMaximumSize(QSize((int) window_width , (int) window_height * 0.33));

    fitts_formula_layout->addLayout(configuration_form);

    fitts_formula_box->setLayout(fitts_formula_layout);
//    fitts_formula_box->setLayout(configuration_form);










    main_layout = new QVBoxLayout;
    main_layout->addWidget(fitts_formula_box);
    main_layout->addWidget(chartView);
    // bottom buttons
    home_and_test_buttons_layout = new QHBoxLayout;

    go_home_button = new QPushButton("Accueil", this);
    connect(go_home_button, SIGNAL(clicked()), this, SLOT(goHome()));
    home_and_test_buttons_layout->addWidget(go_home_button);

    home_and_test_buttons_layout->insertSpacing(1, screen_width / 2);

    retry_test_button = new QPushButton("Refaire test", this);
    connect(retry_test_button, SIGNAL(clicked()), this, SLOT(retryTest()));
    home_and_test_buttons_layout->addWidget(retry_test_button);

//    main_layout->insertSpacing(1, screen_width / 2);
//    main_layout->addWidget(results_label);
    main_layout->addLayout(home_and_test_buttons_layout);
//    main_layout->setSizeConstraint(QLayout::SetMinimumSize);
    this->setLayout(main_layout);
}

void ResultsPage::computeFitts()
{
    chart->removeAllSeries();
//            delete chart;
    // calculer data avec new a et b
    chart->deleteLater();
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().getFittsData().computeTestResults();
    this->displayResults();
}


void ResultsPage::setTestParams(int number, int min, int max)
{
    this->target_number_label->setText(QString::number(number));
        this->target_mini_size_label->setText(QString::number(min));
            this->target_max_size_label->setText(QString::number(max));
}

void ResultsPage::displayResults()
{
//    results_label->setText("couc");
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
//        results_label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
//        results_label->setWordWrap(true);
//        results_label->setText(results);
     chart = new QChart();
        QLineSeries *fitts_series = new QLineSeries();
        QLineSeries *test_series = new QLineSeries();
        fitts_series->setName("Courbe de la loi de Fitts théorique");
        test_series->setName("Courbe de la loi de Fitts empirique");
        j = 1;
        double max = 0.0;
        for (data_to_publish_tuple::const_iterator i = dataToPublish.begin(); i != dataToPublish.end(); ++i)
        {

            *fitts_series << QPointF(j, get<3>(*i));
//            fitts_series->append(j, get<3>(*i));
            test_series->append(j, get<2>(*i));
            j++;

            if (max < get<3>(*i)) {
                max = get<3>(*i);
            }

            if (max < get<2>(*i)) {
                max = get<2>(*i);
            }
//            series->append(2, 4);
//            series->append(3, 8);
//            series->append(7, 4);
//            series->append(10, 5);
//            *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
        }


//        chart->legend()->hide();
        chart->addSeries(fitts_series);
        chart->addSeries(test_series);
        chart->setTitle("Courbes théorique et empirique du test de Fitts.");
//        chart->createDefaultAxes();
//        chart->axisY()->setRange(0, 5);

        QValueAxis *axisX = new QValueAxis;
        axisX->setRange(1, j-1);
        axisX->setTickCount(j-1);
        axisX->setLabelFormat("%i");
        axisX->setTitleText("Numéro de cible");
        chart->addAxis(axisX, Qt::AlignBottom);

        QValueAxis *axisY = new QValueAxis;
        axisY->setRange(0.0, max + 0.15);
        axisY->setTickCount(j-1);
        axisY->setLabelFormat("%.4f");
        axisY->setTitleText("Temps pour cliquer sur la cible");
        chart->addAxis(axisY, Qt::AlignLeft);

        fitts_series->attachAxis(axisY);
        test_series->attachAxis(axisY);
//        fitts_series->attachAxis(axisX);
//        fitts_series->attachAxis(axisY);

//        QValueAxis *axisY = new QValueAxis;
//        axisY->setRange(0, 5);
//        axisY->setTickCount(5);
//        chart->addAxis(axisY, Qt::AlignBottom);

        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setChart(chart);
        chartView->repaint();



}



void ResultsPage::setA(double a)
{
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().setA(a);
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().getFittsData().setA(this->a);
    this->a_spinbox->setValue(a);
    this->a = a;
}


void ResultsPage::setB(double b)
{
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().setB(b);
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().getFittsData().setB(this->b);
    this->b_spinbox->setValue(b);
    this->b = b;
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
        static_cast<MainWindow*>(this->parent())->getFittsTestWindow().stopCountdown();
}
