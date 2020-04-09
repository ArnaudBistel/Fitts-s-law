#include "homepage.h"
#include "mainwindow.h"

HomePage::HomePage(QWidget *parent, QString name):
    QWidget(parent)
{

    this->setObjectName(name);
    connect(this, SIGNAL(changeInterface(QString)), this->parent(),SLOT(changeOnglet(QString)));


    // -------------------------------------
    // top layout, contains the title of the main window
    // -------------------------------------
    title_label = new QLabel("Programme de test de la formule de Fitts");
    title_label->setFont(QFont("Comic Sans MS", 20, QFont::Bold, true));
    title_label->setAlignment(Qt::AlignCenter);

    title_layout = new QHBoxLayout;
    title_layout->addWidget(title_label);


    // -------------------------------------
    // Fitts's law formula
    // -------------------------------------
    fitts_formula_box = new QGroupBox(tr("Loi de Fitts"), this);

    fitts_box_layout = new QHBoxLayout;

    fitts_formula_layout = new QVBoxLayout;
    fitts_formula_label = new QLabel("Formule utilisée : ");
    fitts_formula_layout->addWidget(fitts_formula_label);
    fitts_formula = new QLabel("T = a + b.log(D/W + 1)");
    fitts_formula_layout->addWidget(fitts_formula);

    fitts_box_layout->addLayout(fitts_formula_layout);

    // a and b choice for Fitts's formula
    a_b_choice_layout = new QVBoxLayout;

    a_b_choice_label = new QLabel("Choix de a et b : ");
    a_b_choice_layout->addWidget(a_b_choice_label);

    a_b_form_layout = new QFormLayout;
    a_spinbox = new QDoubleSpinBox(this);
    a_spinbox->setValue(0.2);
    a_spinbox->setDecimals(2);
    a_spinbox->setMaximum(1);
    a_spinbox->setMinimum(0);
    a_spinbox->setSingleStep(0.05);
    connect(a_spinbox, SIGNAL(valueChanged(double)), this, SLOT(setA(double)));
    a_b_form_layout->addRow("a", a_spinbox);

    b_spinbox = new QDoubleSpinBox(this);
    b_spinbox->setValue(0.1);
    b_spinbox->setDecimals(2);
    b_spinbox->setMaximum(1);
    b_spinbox->setMinimum(0);
    b_spinbox->setSingleStep(0.05);
    connect(b_spinbox, SIGNAL(valueChanged(double)), this, SLOT(setB(double)));
    a_b_form_layout->addRow("b", b_spinbox);

    a_b_choice_layout->addLayout(a_b_form_layout);
    fitts_box_layout->addLayout(a_b_choice_layout);

    fitts_formula_box->setLayout(fitts_box_layout);


    // -------------------------------------
    // configuration box
    // -------------------------------------
    configuration_box = new QGroupBox(tr("Configuration"), this);
    configuration_form = new QFormLayout;

    target_number_spinbox = new QSpinBox;
    target_number_spinbox->setValue(10);
    target_number_spinbox->setRange(10,20);
    connect(target_number_spinbox, SIGNAL(valueChanged(int)), this, SLOT(setTargetNumber(int)));
    configuration_form->addRow("Nombre de cibles", target_number_spinbox);

    target_mini_size_spinbox = new QSpinBox;
    target_mini_size_spinbox->setValue(10);
    target_mini_size_spinbox->setRange(10,100);
    connect(target_mini_size_spinbox, SIGNAL(valueChanged(int)), this, SLOT(setTargetSizeMini(int)));
    configuration_form->addRow("Taille minimum des cibles", target_mini_size_spinbox);

    target_max_size_spinbox = new QSpinBox;
    target_max_size_spinbox->setValue(150);
    target_max_size_spinbox->setRange(150,300);
    connect(target_max_size_spinbox, SIGNAL(valueChanged(int)), this, SLOT(setTargetSizeMax(int)));
    configuration_form->addRow("Taille maximum des cibles", target_max_size_spinbox);

    configuration_box->setLayout(configuration_form);


    // -------------------------------------
    // quit / start buttons
    // -------------------------------------
    buttons_layout = new QHBoxLayout;

    quit_button= new QPushButton("Quitter");
    connect(quit_button, SIGNAL(clicked()), qApp, SLOT(quit()));
    buttons_layout->addWidget(quit_button);

    start_button= new QPushButton("Démarrer le test");
    connect(start_button, SIGNAL(clicked()), this, SLOT(launch_test()));
    buttons_layout->addWidget(start_button);

    // vertical layout that contains all the widgets in the HomePage
    vertical_layout = new QVBoxLayout();

    vertical_layout->addLayout(title_layout);
    vertical_layout->addWidget(fitts_formula_box);
    vertical_layout->addWidget(configuration_box);
    vertical_layout->addLayout(buttons_layout);

    this->setLayout(vertical_layout);
}


void HomePage::setA(double a)
{
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().setA(a);
}


void HomePage::setB(double b)
{
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().setB(b);
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



void HomePage::launch_test()
{
    emit changeInterface("fitts_page");
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().startCountdown();
}


HomePage::~HomePage()
{
}

