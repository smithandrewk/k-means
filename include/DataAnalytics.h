/*
 * file: DataAnalytics.h
 * author: Andrew Smith
 * date: 12/09/19, 9:30PM
 * description: this file is the header file for the DataAnalytics class. The DataAnalytics object implements a naive k-means algorithm. See README.md for more information.
 */
#include <iostream>
#include <omp.h>
using namespace std;
//TODO implement openmp. Haven't had time yet.
class DataAnalytics
{

    friend istream &operator>>(istream &lhs, const DataAnalytics &rhs);
    friend ostream &operator<<(ostream &lhs, const DataAnalytics &rhs);

private:
    int rows, columns;
    double **data, **centroids;
    int *membership;
    double *mean;
    int numberOfClusters;

public:
    DataAnalytics();
    DataAnalytics(int rows, int columns, double value);
    DataAnalytics(int rows, int columns, double **);
    DataAnalytics(const DataAnalytics &);
    ~DataAnalytics();
    const DataAnalytics &operator=(const DataAnalytics &);
    bool operator==(const DataAnalytics &) const;
    bool operator!=(const DataAnalytics &) const;
    void setcol(int columns);
    int getcol() const;
    void setNumberOfClusters(int);
    int getNumberOfClusters() const;
    void setrow(int rows);
    int getrow() const;
    double **getData() const;

    void zeroMoment() const;
    void firstMoment();
    void secondMoment() const;
    void thirdMoment() const;
    void fourthMoment() const;
    double *nthMoment(int n) const;
    void kMeansClustering(int numberOfClusters);
    void classify() const;
    void printArray(double *arrayToPrint, int size);
    void printCentroids() const;
    void printMembership() const;
    bool isDifferentCentroids(double **last);
};
