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
    std::vector< std::tuple<int, int, double, double> >  getData();
    void sendData(QPoint init_position, QPoint target_position, int targetSize, int timeToClick, int targetNumber);

private:
    int target_number;
//    std::vector<double> dataToPublish;
    typedef std::vector< std::tuple<int, int, double, double> > data_to_publish_tuple;
    data_to_publish_tuple dataToPublish;

    double a;
    double b;
    typedef std::vector< std::tuple<int, int, double, int> > data_to_compute_tuple;
    data_to_compute_tuple dataToCompute;

    void setA(double a);
    void setB(double b);
    void setTargetNumber(int n);

    void computeTestResults();
    double fittsEquation(int distanceToTarget, int targetSize);
    void resetData();

    double computeDistance(QPoint init_position, QPoint target_position);

    friend class FittsTestWindow;

};

#endif // FITTSDATA_H
