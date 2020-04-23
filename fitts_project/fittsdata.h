#ifndef FITTSDATA_H
#define FITTSDATA_H

#include <vector>
#include <tuple>
#include <bits/stdc++.h>
#include <QtWidgets>

using namespace std;

class FittsData
{
public :
    FittsData();

private:
    //    int target_number;
    //    void setTargetNumber(int n);


    // ------------- ATTRIBUTES -------------
    // param pour la formule de Fitts
    double a;
    double b;
    // data à afficher sur la page résultats :
    // distance vers la cible, taille de la cible, temps pour atteindre la cible
    // temps théorique calculé avec Fitts
    typedef std::vector< std::tuple<int, int, double, double> > data_to_publish_tuple;
    data_to_publish_tuple dataToPublish;
    // contient les data qui permettent les calculs
    // position initiale du curseur, position de la cible à cliquer, taille de la cible,
    // temps pour atteindre la cible, numéro de la cible
    typedef std::vector< std::tuple<int, int, double, int> > data_to_compute_tuple;
    data_to_compute_tuple dataToCompute;
    // vector contenant les data sur les stats du test :
    // moyenne de temps pour cliquer, ecart-type, erreur type
    std::vector<double> stat_data;


    // ------------- METHODES -------------
    void sendData(QPoint init_position, QPoint target_position, int targetSize, double timeToClick, int targetNumber);
    double computeDistance(QPoint init_position, QPoint target_position);
    void computeTestResults();
    double fittsEquation(int distanceToTarget, int targetSize);
    double computeStatData();
    void resetData();


    // ------------- SETTERS -------------
    void setA(double a);
    void setB(double b);


    // ------------- GETTERS -------------
    vector<double> getStatData();
    std::vector< std::tuple<int, int, double, double> >  getData();


    // ------------- FRIENDS -------------
    friend class FittsTestWindow;
    friend class ResultsPage;

};

#endif // FITTSDATA_H
