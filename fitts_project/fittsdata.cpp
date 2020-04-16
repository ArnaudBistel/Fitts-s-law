#include "FittsData.h"
#include <iostream>


FittsData::FittsData() : target_number(), dataToPublish(), a(), b(), dataToCompute()
{
}


void FittsData::sendData(QPoint init_position, QPoint target_position, int targetSize, double timeToClick, int targetNumber)
{
    double distanceToTarget = this->computeDistance(init_position, target_position);
//            std::cout << "distance : " << distanceToTarget << endl ;
//            std::cout << "target size : " << targetSize << endl ;
//            std::cout << "time to click : " << timeToClick  << endl ;
//            std::cout << "target number : " << targetNumber << endl ;
//            std::cout << " --------------------------------- " << endl ;

    this->dataToCompute.push_back(tuple<int, int, double, int> (distanceToTarget, targetSize, timeToClick, targetNumber));
}

double FittsData::computeDistance(QPoint init_position, QPoint target_position)
{
//    std::cout << "init_position.x() : " << init_position.x() ;
//    std::cout << "target_position.x() : " << target_position.x()  << endl ;
//    std::cout << "init_position.y() : " << init_position.y() ;
//    std::cout << "target_position.y() : " << target_position.y() << endl  ;

    return sqrt( pow( (target_position.x() - init_position.x()) + (target_position.y() - init_position.y()) , 2 ) );
}


vector< tuple<int, int, double, double> > FittsData::getData()
{
//    for (data_to_publish_tuple::const_iterator i = dataToPublish.begin(); i != dataToPublish.end(); ++i)
//    {
//        // returns vector of tuple < distance to target, target size, time to click on target, theorical time to click on target >
//        std::cout << get<0>(*i) << endl ;
//    }
    return this->dataToPublish;
}

void FittsData::computeTestResults()
{
    dataToPublish.clear();
    for (data_to_compute_tuple::const_iterator i = dataToCompute.begin(); i != dataToCompute.end(); ++i)
    {
        std::cout << "fucking distance : " << get<0>(*i) << endl ;
        // returns vector of tuple < distance to target, target size, time to click on target, theorical time to click on target >
        dataToPublish.push_back( tuple<int, int, double, double>(get<0>(*i), get<1>(*i), get<2>(*i) / 1000, fittsEquation(get<0>(*i), get<1>(*i))));
    }
}

double FittsData::fittsEquation(int distanceToTarget, int targetSize)
{
    return this->a + (this->b * ( log2( (distanceToTarget / targetSize) + 1 )));
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
    this->b = b;
}

void FittsData::setTargetNumber(int n)
{
    this->target_number = n;
}
