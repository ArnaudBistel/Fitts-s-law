#include "homepage.h"
#include "mainwindow.h"

HomePage::HomePage(QWidget *parent, QString name):
    QWidget(parent)
{


    this->setObjectName(name);

    connect(this, SIGNAL(changeInterface(QString)), this->parent(),SLOT(changeOnglet(QString)));

    QRect window = QGuiApplication::screens().first()->geometry();
    int screen_width = window.width();
    int screen_height = window.height();

    int window_width = parent->width();
    int window_height = parent->height();

    cout << "window_width : " << window_width <<endl;
    cout << "window_height: " << window_height<<endl;
    // -------------------------------------
    // top layout, contains the title of the main window
    // -------------------------------------
    title_label = new QLabel("Programme de test de la formule de Fitts");
    title_label->setFont(QFont("Roboto", 20, QFont::Bold, true));
    title_label->setAlignment(Qt::AlignCenter);

    title_layout = new QHBoxLayout;
    title_layout->addWidget(title_label);


    // -------------------------------------
    // Fitts's law formula
    // -------------------------------------
    fitts_formula_box = new QGroupBox(tr("Loi de Fitts"), this);
    fitts_formula_layout = new QVBoxLayout;

//    fitts_box_layout = new QHBoxLayout;

    fitts_formula_label = new QLabel("Formule utilisée : ");

    fitts_formula_layout->addWidget(fitts_formula_label);
    fitts_formula = new QLabel("T = a + b.log(D/W + 1)");
    fitts_formula_layout->addWidget(fitts_formula);
    fitts_formula_layout->setAlignment(fitts_formula, Qt::AlignHCenter);
    fitts_formula_layout->insertSpacing(2, 15);

//    fitts_box_layout->addLayout(fitts_formula_layout);

    fitts_form = new QFormLayout;
    fitts_form->setVerticalSpacing(15);
    a_spinbox = new QDoubleSpinBox;
    a_spinbox->setValue(0.2);
    a_spinbox->setDecimals(2);
    a_spinbox->setMaximum(1);
    a_spinbox->setMinimum(0);
    a_spinbox->setSingleStep(0.05);
    connect(a_spinbox, SIGNAL(valueChanged(double)), this, SLOT(setA(double)));
    fitts_form->addRow("Choix de a  \t\t", a_spinbox);

    b_spinbox = new QDoubleSpinBox;
    b_spinbox->setValue(0.1);
    b_spinbox->setDecimals(2);
    b_spinbox->setMaximum(1);
    b_spinbox->setMinimum(0);
    b_spinbox->setSingleStep(0.05);
    connect(b_spinbox, SIGNAL(valueChanged(double)), this, SLOT(setB(double)));
    fitts_form->addRow("Choix de b \t\t", b_spinbox);

    fitts_form->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);

    fitts_formula_layout->addLayout(fitts_form);




    fitts_formula_box->setLayout(fitts_formula_layout);
    fitts_formula_box->setMaximumSize(QSize((int) window_width , (int) window_height * 0.33));

//    // a and b choice for Fitts's formula
//    a_b_choice_layout = new QVBoxLayout;

//    a_b_choice_label = new QLabel("Choix de a et b : ");
//    a_b_choice_layout->addWidget(a_b_choice_label);

//    a_b_form_layout = new QFormLayout;
//    a_b_form_layout->addRow("a", a_spinbox);


//    a_b_choice_layout->addLayout(a_b_form_layout);
//    fitts_box_layout->addLayout(a_b_choice_layout);

//    fitts_formula_box->setLayout(fitts_box_layout);


    // -------------------------------------
    // configuration box
    // -------------------------------------
    configuration_box = new QGroupBox(tr("Configuration"), this);
    configuration_form = new QFormLayout;

    configuration_form->setVerticalSpacing(15);
    target_number_spinbox = new QSpinBox;
    target_number_spinbox->setValue(10);
    target_number_spinbox->setRange(10,20);
    connect(target_number_spinbox, SIGNAL(valueChanged(int)), this, SLOT(setTargetNumber(int)));
    configuration_form->addRow("Nombre de cibles \t", target_number_spinbox);

    target_mini_size_spinbox = new QSpinBox;
    target_mini_size_spinbox->setValue(10);
    target_mini_size_spinbox->setRange(10,100);
    connect(target_mini_size_spinbox, SIGNAL(valueChanged(int)), this, SLOT(setTargetSizeMini(int)));
    configuration_form->addRow("Taille minimum des cibles \t", target_mini_size_spinbox);

    target_max_size_spinbox = new QSpinBox;
    target_max_size_spinbox->setValue(150);
    target_max_size_spinbox->setRange(150,300);
    connect(target_max_size_spinbox, SIGNAL(valueChanged(int)), this, SLOT(setTargetSizeMax(int)));
    configuration_form->addRow("Taille maximum des cibles \t", target_max_size_spinbox);

    configuration_form->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);

    configuration_box->setLayout(configuration_form);
    configuration_box->setMaximumSize(QSize((int) window_width , (int) window_height * 0.33));

    // -------------------------------------
    // quit / start buttons
    // -------------------------------------
    buttons_layout = new QHBoxLayout;


    quit_button= new QPushButton("Quitter");
    connect(quit_button, SIGNAL(clicked()), qApp, SLOT(quit()));
    buttons_layout->addWidget(quit_button);


//    buttons_layout->insertSpacing(1, window_width / 2);
    buttons_layout->insertSpacing(1, screen_width / 2);

    start_button= new QPushButton("Démarrer le test");
    connect(start_button, SIGNAL(clicked()), this, SLOT(launch_test()));
    buttons_layout->addWidget(start_button);

    // vertical layout that contains all the widgets in the HomePage
    vertical_layout = new QVBoxLayout();

    vertical_layout->addLayout(title_layout);
    vertical_layout->insertSpacing(1, screen_height * 1/7);
//    vertical_layout->insertSpacing(1, this->height() * 1/4);
//    vertical_layout->addWidget(fitts_formula_box);
//    vertical_layout->addWidget(configuration_box);
    params_layout = new QVBoxLayout;
    params_layout->addWidget(fitts_formula_box);
    params_layout->insertSpacing(1, screen_height * 1/7);
    params_layout->addWidget(configuration_box);
    params_layout->setAlignment(Qt::AlignHCenter);
    vertical_layout->addLayout(params_layout);

    vertical_layout->insertSpacing(3, screen_height * 1/7);
//    vertical_layout->insertSpacing(3, this->height() * 1/4);
    vertical_layout->addLayout(buttons_layout);

/*    horizontal_layout = new QHBoxLayout;
    horizontal_layout->insertSpacing(0, window_width * 0.25 );
//        horizontal_layout->insertSpacing(0, screen_height / 4 );
    horizontal_layout->addLayout(vertical_layout);
//    horizontal_layout->insertSpacing(2, screen_height / 4 );
//        horizontal_layout->insertSpacing(2, window_height * 0.33 );
//    vertical_layout->setStrechFactor(title_layout,1);
//    vertical_layout->setStrechFactor(fitts_formula_box,2);
//    vertical_layout->setStrechFactor(configuration,1);
*/

//    vertical_layout->setStyleSheet("background: rgb(170,189,206);");
    this->setLayout(vertical_layout);
//        this->setLayout(horizontal_layout);
}


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



void HomePage::launch_test()
{
    emit changeInterface("fitts_page");
    static_cast<MainWindow*>(this->parent())->getFittsTestWindow().startCountdown();
    static_cast<MainWindow*>(this->parent())->getResultsPage().setTestParams(
                this->target_number_spinbox->value(),
                this->target_mini_size_spinbox->value(),
                this->target_max_size_spinbox->value());
}


HomePage::~HomePage()
{
}

