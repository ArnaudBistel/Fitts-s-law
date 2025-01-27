#include "homepage.h"
#include "mainwindow.h"

HomePage::HomePage(QWidget *parent, QString name):
    QWidget(parent)
{
    this->setObjectName(name);

    // méthode qui permet la transition entre les différentes pages de l'app
    connect(this, SIGNAL(changeInterface(QString)), this->parent(),SLOT(changeOnglet(QString)));

    // obtenir la taille de l'écran de l'utilisateur
    QRect window = QGuiApplication::screens().first()->geometry();
    int screen_width = window.width();
    int screen_height = window.height();

    int window_width = parent->width();
    int window_height = parent->height();


    // -------------------------------------
    // top layout, contient le titre de l'app
    // -------------------------------------
    title_label = new QLabel("Programme de test de la formule de Fitts");
    title_label->setFont(QFont("Roboto", 20, QFont::Bold, false));
    title_label->setAlignment(Qt::AlignCenter);
    title_layout = new QHBoxLayout;
    title_layout->addWidget(title_label);


    // -------------------------------------
    // Fitts's law formula
    // -------------------------------------
    fitts_formula_box = new QGroupBox(tr("Loi de Fitts"), this);
    fitts_formula_layout = new QVBoxLayout;

    // formule de Fitts
    fitts_formula_label = new QLabel("Formule utilisée : ");
    fitts_formula_layout->addWidget(fitts_formula_label);
    fitts_formula = new QLabel("T = a + b * log( D/W + 1 )");
    fitts_formula_layout->addWidget(fitts_formula);
    fitts_formula_layout->setAlignment(fitts_formula, Qt::AlignHCenter);
    fitts_formula_layout->insertSpacing(2, 15);

    // formulaire de choix de a et b
    fitts_form = new QFormLayout;
    fitts_form->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);

    // choix de a
    a_spinbox = new QDoubleSpinBox;
    a_spinbox->setValue(0.2);
    a_spinbox->setDecimals(2);
    a_spinbox->setMaximum(1);
    a_spinbox->setMinimum(0);
    a_spinbox->setSingleStep(0.05);
    connect(a_spinbox, SIGNAL(valueChanged(double)), this, SLOT(setA(double)));
    fitts_form->addRow("Choix de a\t\t\t", a_spinbox);

    // choix de b
    b_spinbox = new QDoubleSpinBox;
    b_spinbox->setValue(0.1);
    b_spinbox->setDecimals(2);
    b_spinbox->setMaximum(1);
    b_spinbox->setMinimum(0);
    b_spinbox->setSingleStep(0.05);
    connect(b_spinbox, SIGNAL(valueChanged(double)), this, SLOT(setB(double)));
    fitts_form->addRow("Choix de b\t\t\t", b_spinbox);

    fitts_formula_layout->addLayout(fitts_form);

    fitts_formula_box->setLayout(fitts_formula_layout);
    fitts_formula_box->setMaximumSize(QSize((int) window_width , (int) window_height * 0.33));


    // -------------------------------------
    // configuration box
    // -------------------------------------
    configuration_box = new QGroupBox(tr("Configuration du test"), this);

    // formulaire de configuration du test
    configuration_form = new QFormLayout;
//    configuration_form->setVerticalSpacing(15);
    configuration_form->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);

    // nombre de cibles
    target_number_spinbox = new QSpinBox;
    target_number_spinbox->setValue(10);
    target_number_spinbox->setRange(10,20);
    connect(target_number_spinbox, SIGNAL(valueChanged(int)), this, SLOT(setTargetNumber(int)));
    configuration_form->addRow("Nombre de cibles\t\t", target_number_spinbox);

    // taille minimum des cibles
    target_mini_size_spinbox = new QSpinBox;
    target_mini_size_spinbox->setValue(10);
    target_mini_size_spinbox->setRange(10,100);
    connect(target_mini_size_spinbox, SIGNAL(valueChanged(int)), this, SLOT(setTargetSizeMini(int)));
    configuration_form->addRow("Taille minimum des cibles\t\t", target_mini_size_spinbox);

    // taille maximale des cibles
    target_max_size_spinbox = new QSpinBox;
    target_max_size_spinbox->setValue(150);
    target_max_size_spinbox->setRange(150,300);
    connect(target_max_size_spinbox, SIGNAL(valueChanged(int)), this, SLOT(setTargetSizeMax(int)));
    configuration_form->addRow("Taille maximum des cibles\t\t", target_max_size_spinbox);

    configuration_box->setLayout(configuration_form);
    configuration_box->setMaximumSize(QSize((int) window_width , (int) window_height * 0.33));

    // -------------------------------------
    // layout qui contient les deux box
    // -------------------------------------
    params_layout = new QVBoxLayout;
    params_layout->addWidget(fitts_formula_box);
    params_layout->insertSpacing(1, screen_height * 1/7);
    params_layout->addWidget(configuration_box);
    params_layout->setAlignment(Qt::AlignHCenter);

    // -------------------------------------
    // quit / start buttons
    // -------------------------------------
    buttons_layout = new QHBoxLayout;

    quit_button= new QPushButton("Quitter");
    connect(quit_button, SIGNAL(clicked()), qApp, SLOT(quit()));
    buttons_layout->addWidget(quit_button);

    buttons_layout->insertSpacing(1, screen_width / 2);

    start_button= new QPushButton("Démarrer le test");
    connect(start_button, SIGNAL(clicked()), this, SLOT(launch_test()));
    buttons_layout->addWidget(start_button);


    // -------------------------------------
    // vertical layout that contains all the widgets in the HomePage
    // -------------------------------------
    vertical_layout = new QVBoxLayout();
    vertical_layout->addLayout(title_layout);
    vertical_layout->insertSpacing(1, screen_height * 1/7);
    vertical_layout->addLayout(params_layout);
    vertical_layout->insertSpacing(3, screen_height * 1/7);
    vertical_layout->addLayout(buttons_layout);

    this->setLayout(vertical_layout);
}


// envoie l'utilisateur sur la page de test
// en passant à FittsTestWindow les param du test
void HomePage::launch_test()
{
    emit changeInterface("fitts_page");
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().startCountdown();
    static_cast<MainWindow*>(this->parent())->getResultsPage().setTestParams(
                this->target_number_spinbox->value(),
                this->target_mini_size_spinbox->value(),
                this->target_max_size_spinbox->value());
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().resetTest();
}



// ------------- SETTERS -------------

void HomePage::setA(double a)
{
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().setA(a);
    static_cast<MainWindow*>(this->parent())->getResultsPage().setA(a);
}


void HomePage::setB(double b)
{
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().setB(b);
    static_cast<MainWindow*>(this->parent())->getResultsPage().setB(b);
}


void HomePage::setTargetNumber(int n)
{
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().setTargetNumber(n);
}


void HomePage::setTargetSizeMini(int m)
{
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().setTargetSizeMini(m);
}


void HomePage::setTargetSizeMax(int m)
{
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().setTargetSizeMax(m);
}


HomePage::~HomePage()
{
}

