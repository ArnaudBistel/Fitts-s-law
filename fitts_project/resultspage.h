#ifndef RESULTSPAGE_H
#define RESULTSPAGE_H

#include <QtWidgets>

class ResultsPage : public QWidget
{
    Q_OBJECT

public:
    ResultsPage(QWidget *parent, QString name);

public slots:
    void retryTest();
    void goHome();

signals:
    void changeInterface(QString name);

private:
    // amin layout
    QVBoxLayout *main_layout;


    // home and retry test buttons
    QHBoxLayout *home_and_test_buttons_layout;
    QPushButton *go_home_button;
    QPushButton *retry_test_button;

};

#endif // RESULTSPAGE_H
