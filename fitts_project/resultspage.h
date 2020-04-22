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

public slots:
    void retryTest();
    void goHome();
    void displayResults();
    void setA(double a);
    void setB(double b);
    void computeFitts();
    void setTestParams(int number, int min, int max);
    void displayData();

signals:
    void changeInterface(QString name);

private:
    QLabel *results_label;
    double a;
    double b;
    QChartView *chartView;
    // amin layout
    QVBoxLayout *main_layout;

    typedef std::vector< std::tuple<int, int, double, double> > data_to_publish_tuple;
    data_to_publish_tuple dataToPublish;

    // home and retry test buttons
    QHBoxLayout *home_and_test_buttons_layout;
    QPushButton *go_home_button;
    QPushButton *retry_test_button;

    // Configuration box
//    QGroupBox *configuration_box;
    QFormLayout *configuration_form;
    QLabel *target_number_label;
    QLabel *target_mini_size_label;
    QLabel *target_max_size_label;

    // Data form
//    QGroupBox *configuration_box;
    QFormLayout *data_form;
    QLabel *average_label;
    QLabel *ecart_type_label;
    QLabel *erreur_type_label;



    // Fitts's law formula box
    QGroupBox *fitts_formula_box;
    QHBoxLayout *fitts_box_layout;
    QLabel *fitts_formula_label;

    QHBoxLayout *fitts_formula_layout;
    QLabel *fitts_formula;

    QVBoxLayout *a_b_choice_layout;
    QFormLayout *a_b_form_layout;
    QLabel *a_b_choice_label;
    QDoubleSpinBox *a_spinbox;
    QDoubleSpinBox *b_spinbox;
    QFormLayout *fitts_form;
    QChart *chart;

    friend class HomePage;
};

#endif // RESULTSPAGE_H
