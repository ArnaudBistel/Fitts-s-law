#include "resultspage.h"
#include "mainwindow.h"
#include <iostream>

// /////////////////////////////////////////
// TODO add moyenne table des cibles, distance moyenne, temps moyen etc...
// /////////////////////////////////////////
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

    chartView = new QChartView(this);
    chartView->resize(screen_width * 2/3,screen_height * 2/3);
    chartView->setRenderHint(QPainter::Antialiasing);

    chart = new QChart();

    fitts_formula_layout = new QHBoxLayout;
    fitts_formula_box = new QGroupBox(tr("Loi de Fitts"), this);
    fitts_form = new QFormLayout;

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

//    fitts_formula_label = new QLabel("T = a + b.log(D/W + 1)");
//    fitts_formula_layout->addWidget(fitts_formula_label);

    data_form = new QFormLayout;

    average_label = new QLabel();

    data_form->addRow("Moyenne pour cliquer\t", average_label);

    ecart_type_label = new QLabel();

    data_form->addRow("Ecart-type\t", ecart_type_label);

    erreur_type_label = new QLabel();

    data_form->addRow("Erreur type\t", erreur_type_label);

//    configuration_form->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
//    configuration_form->setRowWrapPolicy(QFormLayout::DontWrapRows);
//    configuration_form->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
//    configuration_form->setLabelAlignment(Qt::AlignLeft);

    fitts_formula_layout->addLayout(data_form);




    configuration_form = new QFormLayout;

    target_number_label = new QLabel();

    configuration_form->addRow("Nombre de cibles \t", target_number_label);

    target_mini_size_label = new QLabel();

    configuration_form->addRow("Taille minimum des cibles \t", target_mini_size_label);

    target_max_size_label = new QLabel();

    configuration_form->addRow("Taille maximum des cibles \t", target_max_size_label);

//    configuration_form->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
//    configuration_form->setRowWrapPolicy(QFormLayout::DontWrapRows);
//    configuration_form->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
//    configuration_form->setLabelAlignment(Qt::AlignLeft);

    fitts_formula_layout->addLayout(configuration_form);

    fitts_formula_layout->insertSpacing(1, screen_width / 8);
    fitts_formula_layout->insertSpacing(3, screen_width / 8);

    fitts_formula_box->setLayout(fitts_formula_layout);



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

    main_layout->addLayout(home_and_test_buttons_layout);

    this->setLayout(main_layout);
}



void ResultsPage::computeFitts()
{
    chart->removeAllSeries();

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


void ResultsPage::displayData()
{
    vector<double> data = static_cast<MainWindow*>(this->parent())->getFittsTestWindow().getFittsData().getStatData();
    this->average_label->setText(QString::number(data.at(0), 'f', 3)  + " ms");
    this->ecart_type_label->setText(QString::number(data.at(1), 'f', 3) + " ms");
    this->erreur_type_label->setText(QString::number(data.at(2), 'f', 3) + " ms");
}



void ResultsPage::displayResults()
{
    dataToPublish = static_cast<MainWindow*>(this->parent())->getFittsTestWindow().getFittsData().getData();

    int j = 1;
    QString results;

    results.append(" a : " + QString::number(this->a_spinbox->value()) + "\n");
                results.append(" b : " + QString::number(this->b_spinbox->value()) + "\n");
    for (data_to_publish_tuple::const_iterator i = dataToPublish.begin(); i != dataToPublish.end(); ++i)
    {
//        results.append(QString::number(j));
//        results.append ("distance to target : ");
//        results.append(QString::number(get<0>(*i)));
//        results.append("\n target size : ");
//        results.append(QString::number(get<1>(*i)));
//        results.append("\n time to click : ");
//        results.append(QString::number(get<2>(*i)));
        results.append("\n Fitts time : ");
        results.append(QString::number(get<3>(*i)));
        results.append("");

        j++;
        // returns vector of tuple < distance to target, target size, time to click on target, theorical time to click on target >
    }
            results.append(" ------------------------------------------- ");
//    std::cout << "coucoué" << endl ;
    std::cout << results.toStdString() << endl ;

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
//        *test_series << QPointF(j, get<2>(*i));
        test_series->append(j, get<2>(*i));
        j++;

        if (max < get<3>(*i)) {
            max = get<3>(*i);
        }

        if (max < get<2>(*i)) {
            max = get<2>(*i);
        }
    }

    chart->addSeries(fitts_series);
    chart->addSeries(test_series);
    chart->setTitle("Courbes théorique et empirique du test de Fitts.");

    QValueAxis *axisX = new QValueAxis;
//    axisX->setRange(1, j-1);
    axisX->setRange(0, j-1);
    axisX->setTickCount(j);
//    axisX->setTickCount(j-1);
    axisX->setLabelFormat("%i");
    axisX->setTitleText("Numéro de cible");
    chart->addAxis(axisX, Qt::AlignBottom);

    j = 1;
    QCategoryAxis *axisX_distance = new QCategoryAxis;
    axisX_distance->setTitleText("Distance jusqu'à la cible en pixel");
    QCategoryAxis *axisX_size = new QCategoryAxis;
    axisX_size->setTitleText("Taille de la cible en pixel");

    for (data_to_publish_tuple::const_iterator i = dataToPublish.begin(); i != dataToPublish.end(); ++i)
    {
        axisX_distance->append(QString::number(get<0>(*i)),j);
        axisX_size->append(QString::number(get<1>(*i)),j);
        j++;
    }

//    axisY3->append("Low", 1);
//    axisY3->append("Medium", 2);
//    axisY3->append("High", 3);

    axisX_size->setRange(0, j-1);
    axisX_size->setTickCount(j);
    axisX_distance->setTickCount(j);
    axisX_distance->setRange(0, j-1);

    chart->addAxis(axisX_distance, Qt::AlignBottom);
    chart->addAxis(axisX_size, Qt::AlignBottom);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0.0, max + 0.15);
    axisY->setTickCount(j-1);
    axisY->setLabelFormat("%.4f");
    axisY->setTitleText("Temps pour cliquer sur la cible en secondes");
    chart->addAxis(axisY, Qt::AlignLeft);

    fitts_series->attachAxis(axisY);
    test_series->attachAxis(axisY);

    fitts_series->attachAxis(axisX_distance);
    fitts_series->attachAxis(axisX_size);
    test_series->attachAxis(axisX_distance);
    test_series->attachAxis(axisX_size);

    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChart(chart);
    chart->setTheme(QChart::ChartThemeBlueCerulean);
    chartView->repaint();
}



void ResultsPage::setA(double a)
{
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().setA(a);
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().getFittsData().setA(a);
    if (this->a_spinbox->value() != a )
        this->a_spinbox->setValue(a);
        cout << "dans setA" <<endl;
    this->a = a;
}


void ResultsPage::setB(double b)
{
    cout << "dans set b de resultspage  : " << b <<endl;
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().setB(b);
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().getFittsData().setB(b);

    if (this->b_spinbox->value() != b)
        this->b_spinbox->setValue(b);
        cout<< "dans setB " << endl;
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
//    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().resetTest();
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().stopCountdown();
}
