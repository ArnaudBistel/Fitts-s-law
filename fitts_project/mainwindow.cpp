#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow()

{
    center = new QWidget;
    setCentralWidget(center);

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
    fitts_formula_box = new QGroupBox(tr("Loi de Fitts"), center);

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
    a_spinbox = new QDoubleSpinBox(center);
    a_spinbox->setValue(0.2);
    a_spinbox->setDecimals(2);
    a_spinbox->setMaximum(1);
    a_spinbox->setMinimum(0);
    a_spinbox->setSingleStep(0.05);
    //connect(a_spinbox, SIGNAL(valueChanged(double d)), this, SLOT(setA()));
    a_b_form_layout->addRow("a", a_spinbox);

    b_spinbox = new QDoubleSpinBox(center);
    b_spinbox->setValue(0.1);
    b_spinbox->setDecimals(2);
    b_spinbox->setMaximum(1);
    b_spinbox->setMinimum(0);
    b_spinbox->setSingleStep(0.05);
    //connect(b_spinbox, SIGNAL(valueChanged(double d)), this, SLOT(setB()));
    a_b_form_layout->addRow("b", b_spinbox);

    a_b_choice_layout->addLayout(a_b_form_layout);
    fitts_box_layout->addLayout(a_b_choice_layout);

    fitts_formula_box->setLayout(fitts_box_layout);

    // -------------------------------------
    // configuration box
    // -------------------------------------
    configuration_box = new QGroupBox(tr("Configuration"), center);
    configuration_form = new QFormLayout;

    target_number_spinbox = new QSpinBox;
    target_number_spinbox->setValue(10);
    target_number_spinbox->setRange(10,20);
    configuration_form->addRow("Nombre de cibles", target_number_spinbox);

    target_mini_size_spinbox = new QSpinBox;
    target_mini_size_spinbox->setValue(10);
    target_mini_size_spinbox->setRange(10,100);
    configuration_form->addRow("Taille minimum des cibles", target_mini_size_spinbox);

    target_max_size_spinbox = new QSpinBox;
    target_max_size_spinbox->setValue(150);
    target_max_size_spinbox->setRange(150,250);
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
    connect(start_button, SIGNAL(clicked()), qApp, SLOT(launch_test()));
    buttons_layout->addWidget(start_button);

    // vertical layout that contains all the widgets in the mainwindow
    vertical_layout = new QVBoxLayout();

    vertical_layout->addLayout(title_layout);
    vertical_layout->addWidget(fitts_formula_box);
    vertical_layout->addWidget(configuration_box);
    vertical_layout->addLayout(buttons_layout);

    center->setLayout(vertical_layout);



}

void MainWindow::launch_test()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}

