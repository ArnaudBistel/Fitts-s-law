#include "FittsData.h"
#include <iostream>



// Constructeurs qui initiliase les attributs
FittsData::FittsData() : a(), b(), dataToPublish(), dataToCompute(), stat_data() {}
//FittsData::FittsData() : target_number(), dataToPublish(), a(), b(), dataToCompute(), stat_data() {}




// ----------------------------------
// ------------- METHODES -------------
// ----------------------------------

// Méthode appelée par FittsTestWindow pour fournir les data du test au fur et à mesure que l'utilisateur clique sur les cibles
void FittsData::sendData(QPoint init_position, QPoint target_position, int targetSize, double timeToClick, int targetNumber)
{
    double distanceToTarget = this->computeDistance(init_position, target_position);
    this->dataToCompute.push_back(tuple<int, int, double, int> (distanceToTarget, targetSize, timeToClick, targetNumber));
}



// Calcule de la distance entre le curseur et la cible suivante
double FittsData::computeDistance(QPoint init_position, QPoint target_position)
{
    return sqrt( pow( (target_position.x() - init_position.x()) + (target_position.y() - init_position.y()) , 2 ) );
}


// remplit le vector attribut dataToPublish
void FittsData::computeTestResults()
{
    dataToPublish.clear();
    for (data_to_compute_tuple::const_iterator i = dataToCompute.begin(); i != dataToCompute.end(); ++i)
    {
        // returns vector of tuple < distance to target, target size, time to click on target, theorical time to click on target >
        dataToPublish.push_back( tuple<int, int, double, double>(get<0>(*i), get<1>(*i), get<2>(*i) / 1000, fittsEquation(get<0>(*i), get<1>(*i))));
    }
    this->computeStatData();
}


// Applique la formule de Fitts
double FittsData::fittsEquation(int distanceToTarget, int targetSize)
{
    double res = this->a + (this->b * ( log2( (distanceToTarget / targetSize) + 1 )));
    return res;
}


// Calcule de la moyenne du temps moyen pour cliquer sur les cibles, de l'écart-type et de l'erreur type
double FittsData::computeStatData()
{
    stat_data.clear();

    // Moyenne pour cliquer sur les cibles
    double sum = 0;
    for (data_to_publish_tuple::const_iterator i = dataToPublish.begin(); i != dataToPublish.end(); ++i)
    {
        sum += get<2>(*i);
    }
    double average = sum / dataToPublish.size();
    this->stat_data.push_back( average );

    // Ecart type
    double temp = 0;
    double temp2 = 0;
    for (data_to_publish_tuple::const_iterator l = dataToPublish.begin(); l != dataToPublish.end(); ++l)
    {
        temp = (get<2>(*l) - average);
        temp = temp * temp ;
        temp2 += temp;
    }
    temp2 = temp2 / dataToPublish.size();
    double ecart_type = sqrt( temp2);
    this->stat_data.push_back( ecart_type );

    // erreur type
    this->stat_data.push_back( ecart_type / (sqrt (dataToPublish.size() )));
}


// Vide les vectors de data lorsque l'on relance le test
void FittsData::resetData()
{
    dataToPublish.clear();
    dataToCompute.clear();
}





// ----------------------------------
// ------------- SETTERS -------------
// ----------------------------------

void FittsData::setA(double a)
{
    this->a = a;
}


void FittsData::setB(double b)
{
    this->b = b;
}




// ----------------------------------
// ------------- GETTERS -------------
// ----------------------------------

vector<double> FittsData::getStatData()
{
    return this->stat_data;
}


vector< tuple<int, int, double, double> > FittsData::getData()
{
    return this->dataToPublish;
}


