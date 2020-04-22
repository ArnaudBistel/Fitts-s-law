#include "FittsData.h"
#include <iostream>


FittsData::FittsData() : target_number(), dataToPublish(), a(), b(), dataToCompute(), stat_data() {}

void FittsData::sendData(QPoint init_position, QPoint target_position, int targetSize, double timeToClick, int targetNumber)
{
    double distanceToTarget = this->computeDistance(init_position, target_position);
    this->dataToCompute.push_back(tuple<int, int, double, int> (distanceToTarget, targetSize, timeToClick, targetNumber));
}

double FittsData::computeDistance(QPoint init_position, QPoint target_position)
{
    return sqrt( pow( (target_position.x() - init_position.x()) + (target_position.y() - init_position.y()) , 2 ) );
}


double FittsData::computeStatData()
{
    stat_data.clear();
    double sum = 0;
    for (data_to_publish_tuple::const_iterator i = dataToPublish.begin(); i != dataToPublish.end(); ++i)
    {
        sum += get<2>(*i);
    }

    double average = sum / dataToPublish.size();
    this->stat_data.push_back( average );
    cout << "datatopublish size : " << dataToPublish.size() << endl;

    cout << "average : " << average << endl;

cout << "val : " << endl ;

    double temp = 0;
    double temp2 = 0;
    for (data_to_publish_tuple::const_iterator l = dataToPublish.begin(); l != dataToPublish.end(); ++l)
    {
        temp = (get<2>(*l) - average);
        cout << get<2>(*l) << ", ";
        temp = temp * temp ;
        temp2 += temp;
    }

cout << "temp2 : " << temp2 << endl ;

    temp2 = temp2 / dataToPublish.size();

    cout << "temp2 / 10: " << temp2 << endl ;



    double ecart_type = sqrt( temp2);
    this->stat_data.push_back( ecart_type );
    cout << "ecart type : "<< ecart_type << endl;

    this->stat_data.push_back( ecart_type / (sqrt (dataToPublish.size() )));
}

vector<double> FittsData::getStatData()
{
    return this->stat_data;
}


vector< tuple<int, int, double, double> > FittsData::getData()
{
    return this->dataToPublish;
}

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

double FittsData::fittsEquation(int distanceToTarget, int targetSize)
{
    double res = this->a + (this->b * ( log2( (distanceToTarget / targetSize) + 1 )));
    cout << "dans fittsEquation:" << endl;
    cout << " a : " << this->a;
    cout << "b : " << this->b;
    cout << "res : "<< res << endl;
//    return this->a + (this->b * ( log2( (distanceToTarget / targetSize) + 1 )));
    return res;

}

void FittsData::resetData()
{
    dataToPublish.clear();
    dataToCompute.clear();
}

void FittsData::setA(double a)
{
    this->a = a;
}

void FittsData::setB(double b)
{
        cout << "dans set b de fittsdata  : " << b <<endl;
    this->b = b;
}

void FittsData::setTargetNumber(int n)
{
    this->target_number = n;
}
