#include "mainwindow.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // ajout de la police Roboto utilisée dans l'application
    QFontDatabase::addApplicationFont(".res/fonts/ROBOTO-REGULAR.ttf");
    QFontDatabase::addApplicationFont(".res/fonts/ROBOTO-BOLD.ttf");
    QFontDatabase::addApplicationFont(".res/fonts/ROBOTO-LIGHT.ttf");
    QFontDatabase::addApplicationFont(".res/fonts/ROBOTO-THIN.ttf");
    a.setFont(QFont("Roboto", 11));

    MainWindow w;
    w.setWindowTitle("Loi de Fitts");
    w.show();
    return a.exec();
}
