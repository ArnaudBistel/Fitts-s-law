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


    // ----------------------------------
    // Résultats box
    // ----------------------------------
    results_layout = new QHBoxLayout;
    results_box = new QGroupBox(tr("Résultats"), this);


    // choix de a et b
    fitts_form = new QFormLayout;

    // choix de a
    a_spinbox = new QDoubleSpinBox;
    a_spinbox->setValue(0.2);
    a_spinbox->setDecimals(2);
    a_spinbox->setMaximum(1);
    a_spinbox->setMinimum(0);
    a_spinbox->setSingleStep(0.05);
    connect(a_spinbox, SIGNAL(valueChanged(double)), this, SLOT(setA(double)));
    connect(a_spinbox, SIGNAL(valueChanged(double)), this, SLOT(computeFitts()));
    fitts_form->addRow("Choix de a\t", a_spinbox);

    // choix de b
    b_spinbox = new QDoubleSpinBox;
    b_spinbox->setValue(0.1);
    b_spinbox->setDecimals(2);
    b_spinbox->setMaximum(1);
    b_spinbox->setMinimum(0);
    b_spinbox->setSingleStep(0.05);
    connect(b_spinbox, SIGNAL(valueChanged(double)), this, SLOT(setB(double)));
    connect(b_spinbox, SIGNAL(valueChanged(double)), this, SLOT(computeFitts()));
    fitts_form->addRow("Choix de b\t", b_spinbox);

    fitts_form->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
    results_layout->addLayout(fitts_form);



    // Stats form
    data_form = new QFormLayout;

    average_label = new QLabel();
    data_form->addRow("Moyenne pour cliquer\t", average_label);

    ecart_type_label = new QLabel();
    data_form->addRow("Ecart-type\t", ecart_type_label);

    erreur_type_label = new QLabel();
    data_form->addRow("Erreur type\t", erreur_type_label);

    results_layout->addLayout(data_form);


    // configuration du test
    configuration_form = new QFormLayout;

    target_number_label = new QLabel();
    configuration_form->addRow("Nombre de cibles\t", target_number_label);

    target_mini_size_label = new QLabel();
    configuration_form->addRow("Taille minimum des cibles\t", target_mini_size_label);

    target_max_size_label = new QLabel();
    configuration_form->addRow("Taille maximum des cibles\t", target_max_size_label);

    results_layout->addLayout(configuration_form);

    results_box->setLayout(results_layout);

    results_layout->insertSpacing(1, screen_width / 8);
    results_layout->insertSpacing(3, screen_width / 8);

    // ----------------------------------
    // Chart view
    // ----------------------------------
    chart = new QChart();

    chartView = new QChartView(this);
    chartView->resize(screen_width * 3/4,screen_height * 3/4);
    chartView->setRenderHint(QPainter::Antialiasing);


    // ----------------------------------
    // home and retry test buttons
    // ----------------------------------
    home_and_test_buttons_layout = new QHBoxLayout;

    go_home_button = new QPushButton("Accueil", this);
    connect(go_home_button, SIGNAL(clicked()), this, SLOT(goHome()));
    home_and_test_buttons_layout->addWidget(go_home_button);

    home_and_test_buttons_layout->insertSpacing(1, screen_width / 2);

    retry_test_button = new QPushButton("Refaire test", this);
    connect(retry_test_button, SIGNAL(clicked()), this, SLOT(retryTest()));
    home_and_test_buttons_layout->addWidget(retry_test_button);


    // ----------------------------------
    // Main layout
    // ----------------------------------
    main_layout = new QVBoxLayout;
    main_layout->addWidget(results_box);
    main_layout->addWidget(chartView);
    main_layout->addLayout(home_and_test_buttons_layout);
    this->setLayout(main_layout);
}






// ----------------------------------
// ------------- SLOTS -------------
// ----------------------------------




// affiche les courbes
void ResultsPage::displayResults()
{
    // récupère les data
    dataToPublish = static_cast<MainWindow*>(this->parent())->getFittsTestWindow().getFittsData().getData();

    int j = 1;
    QString results;

    chart = new QChart();
    chart->setTitle("Courbes théorique et empirique du test de Fitts.");

    QLineSeries *fitts_series = new QLineSeries();
    fitts_series->setName("Courbe de la loi de Fitts théorique");

    QLineSeries *test_series = new QLineSeries();
    test_series->setName("Courbe de la loi de Fitts empirique");

    j = 1;
    double max = 0.0;
    for (data_to_publish_tuple::const_iterator i = dataToPublish.begin(); i != dataToPublish.end(); ++i)
    {
        *fitts_series << QPointF(j, get<3>(*i));
        test_series->append(j, get<2>(*i));
        j++;

        // calcul du max pour un meilleur affichage
        if (max < get<3>(*i)) {
            max = get<3>(*i);
        }

        if (max < get<2>(*i)) {
            max = get<2>(*i);
        }
    }

    chart->addSeries(fitts_series);
    chart->addSeries(test_series);

    // axe des abscisses qui affiche les numéros de cible
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, j-1);
    axisX->setTickCount(j);
    axisX->setLabelFormat("%i");
    axisX->setTitleText("Numéro de cible");
    chart->addAxis(axisX, Qt::AlignBottom);

    // autres axes des abscisses qui affichent les distances et les tailles des cibles
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
    axisX_size->setRange(0, j-1);
    axisX_size->setTickCount(j);
    axisX_distance->setTickCount(j);
    axisX_distance->setRange(0, j-1);
    chart->addAxis(axisX_distance, Qt::AlignBottom);
    chart->addAxis(axisX_size, Qt::AlignBottom);

    // axe des ordonnées = le temps pour cliquer sur les cibles
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





// Calcule et affichage de la nouvelle courbe de Fitts théorique lorsque l'utilisateur modifie
// les paramètres a et b avec les spinbox
void ResultsPage::computeFitts()
{
    chart->removeAllSeries();
    chart->deleteLater();

    // calculer data avec le nouveau a ou b
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().getFittsData().computeTestResults();
    this->displayResults();
}





// Afficher les statistiques du test
void ResultsPage::displayData()
{
    vector<double> data = static_cast<MainWindow*>(this->parent())->getFittsTestWindow().getFittsData().getStatData();
    this->average_label->setText(QString::number(data.at(0), 'f', 3)  + " ms");
    this->ecart_type_label->setText(QString::number(data.at(1), 'f', 3) + " ms");
    this->erreur_type_label->setText(QString::number(data.at(2), 'f', 3) + " ms");
}



// Retourner à l'accueil
void ResultsPage::goHome()
{
    emit changeInterface("home_page");
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().stopCountdown();
}



// Retourner à la page de Test
void ResultsPage::retryTest()
{
    emit changeInterface("fitts_page");
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().startCountdown();
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().resetTest();
}







// ----------------------------------
// ------------- SETTERS -------------
// ----------------------------------


void ResultsPage::setTestParams(int number, int min, int max)
{
    this->target_number_label->setText(QString::number(number));
    this->target_mini_size_label->setText(QString::number(min));
    this->target_max_size_label->setText(QString::number(max));
}


void ResultsPage::setA(double a)
{
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().setA(a);
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().getFittsData().setA(a);
    if (this->a_spinbox->value() != a )
        this->a_spinbox->setValue(a);
    this->a = a;
}


void ResultsPage::setB(double b)
{
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().setB(b);
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().getFittsData().setB(b);

    if (this->b_spinbox->value() != b)
        this->b_spinbox->setValue(b);
    this->b = b;
}

