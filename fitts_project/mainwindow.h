#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QMainWindow>
#include <QtWidgets>
#include <QSound>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

public slots:
    void launch_test();
//    void updateReveil();
//    void browse();
//    void calculerTempsAvantAlarme();

private:
    Ui::MainWindow *ui;

    QWidget *center;

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

    // Configuration box
    QGroupBox *configuration_box;
    QFormLayout *configuration_form;
    QSpinBox *target_number_spinbox;
    QSpinBox *target_mini_size_spinbox;
    QSpinBox *target_max_size_spinbox;

    // quit / start buttons
    QHBoxLayout *buttons_layout;
    QPushButton *quit_button;
    QPushButton *start_button;

    // main window elements
    QVBoxLayout *vertical_layout;

//    QGroupBox *horloge_group_box;

//    void chargerSon();
//    QPushButton *play_audio_bouton;
//    QTimeEdit *heure_actuelle_spinbox;
//    QTimeEdit *alarme_spinbox;

//    QLabel *son_alarme_label;
//    QLabel *temps_avant_alarme_texte_label;
//    QLabel *temps_avant_alarme_label;
//    QString fichier_audio;
//    QPushButton *son_choix_bouton;
//    QSpinBox *nombre_sec_alarme_spinbox;
//    int alarme_seconde;
//    QSound *son_alarme;



};
#endif // MAINWINDOW_H
