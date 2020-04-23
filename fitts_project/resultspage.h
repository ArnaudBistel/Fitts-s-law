#ifndef RESULTSPAGE_H
#define RESULTSPAGE_H

#include <QtWidgets>
#include <QtCharts>
#include "FittsData.h"
#include "homepage.h"

using namespace QtCharts;

class ResultsPage : public QWidget
{
    Q_OBJECT

public:
    ResultsPage(QWidget *parent, QString name);


    // ------------- SLOTS -------------
public slots:
    void displayResults();
    void displayData();
    void computeFitts();

    void goHome();
    void retryTest();

    // ------------- SETTERS -------------
    void setTestParams(int number, int min, int max);
    void setA(double a);
    void setB(double b);


signals:
    void changeInterface(QString name);


private:

    // ------------- ATTRIBUTES -------------
//    QLabel *results_label;
    double a;
    double b;

    typedef std::vector< std::tuple<int, int, double, double> > data_to_publish_tuple;
    data_to_publish_tuple dataToPublish;

    // ----------------------------------
    // Résultats box
    // ----------------------------------
    QHBoxLayout *results_layout;
    QGroupBox *results_box;

    // choix a et b
    QVBoxLayout *a_b_choice_layout;
    QFormLayout *a_b_form_layout;
    QLabel *a_b_choice_label;
    QDoubleSpinBox *a_spinbox;
    QDoubleSpinBox *b_spinbox;
    QFormLayout *fitts_form;

    // Stats form
    QFormLayout *data_form;
    QLabel *average_label;
    QLabel *ecart_type_label;
    QLabel *erreur_type_label;

    // configuration du test
    QFormLayout *configuration_form;
    QLabel *target_number_label;
    QLabel *target_mini_size_label;
    QLabel *target_max_size_label;


    // ----------------------------------
    // Chart view
    // ----------------------------------
    QChart *chart;
    QChartView *chartView;


    // ----------------------------------
    // home and retry test buttons
    // ----------------------------------
    QHBoxLayout *home_and_test_buttons_layout;
    QPushButton *go_home_button;
    QPushButton *retry_test_button;


    // ----------------------------------
    // Main layout
    // ----------------------------------
    QVBoxLayout *main_layout;


    // ------------- FRIENDS -------------
    friend class HomePage;
};

#endif // RESULTSPAGE_H
