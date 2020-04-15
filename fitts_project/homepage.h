#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QtWidgets>

class HomePage : public QWidget
{
    Q_OBJECT

public:
    HomePage(QWidget *parent,QString name);
    ~HomePage();


public slots:
    void launch_test();
    void setA(double a);
    void setB(double b);
    void setTargetNumber(int n);
    void setTargetSizeMini(int m);
    void setTargetSizeMax(int m);

signals:
    void changeInterface(QString name);

private:

    // title layout
    QLabel *title_label;
    QHBoxLayout *title_layout;

    // Fitts's law formula box
    QGroupBox *fitts_formula_box;
    QHBoxLayout *fitts_box_layout;

    QVBoxLayout *fitts_formula_layout;
    QLabel *fitts_formula_label;
    QLabel *fitts_formula;

    QVBoxLayout *a_b_choice_layout;
    QFormLayout *a_b_form_layout;
    QLabel *a_b_choice_label;
    QDoubleSpinBox *a_spinbox;
    QDoubleSpinBox *b_spinbox;
    QFormLayout *fitts_form;

    // Configuration box
    QGroupBox *configuration_box;
    QFormLayout *configuration_form;
    QSpinBox *target_number_spinbox;
    QSpinBox *target_mini_size_spinbox;
    QSpinBox *target_max_size_spinbox;

    // quit / start buttons
//    QGridLayout *bottom_layout;
    QHBoxLayout *buttons_layout;
    QPushButton *quit_button;
    QPushButton *start_button;

    // main window elements
    QVBoxLayout *vertical_layout;
    QVBoxLayout *params_layout;
    QHBoxLayout *horizontal_layout;

};

#endif // HOMEPAGE_H
