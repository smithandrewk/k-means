#include "../include/DataAnalytics.h"
#include <iostream>
#include <math.h>
using namespace std;

//Default Constructor
DataAnalytics::DataAnalytics()
{
    data = NULL;
    this->setcol(0);
    this->setrow(0);
}
//Alternate Constructor
DataAnalytics::DataAnalytics(int rows, int columns, double value)
{
    this->setrow(rows);
    this->setcol(columns);
    data = new double *[columns];
}
DataAnalytics::DataAnalytics(double **)
{
}
DataAnalytics::DataAnalytics(const DataAnalytics &)
{
}
DataAnalytics::~DataAnalytics()
{
}
//Ass
const DataAnalytics &DataAnalytics::operator=(const DataAnalytics &)
{
}
//Equality operator
//?
bool DataAnalytics::operator==(const DataAnalytics &) const
{
}
//Inequality operator
//?unsure of rhs
bool DataAnalytics::operator!=(const DataAnalytics &) const
{
}
//Concatenates two arrays
const double **DataAnalytics::operator+(double **rhs) const
{
}
//TODO check for valid values
void DataAnalytics::setcol(int columns)
{
    this->columns = columns;
    this->data = new double *[columns];
}
int DataAnalytics::getcol() const
{
    return this->columns;
}
//TODO check for valid values
void DataAnalytics::setrow(int rows)
{
    this->rows = rows;
}
int DataAnalytics::getrow() const
{
    return this->rows;
}
void DataAnalytics::zeroMoment() const
{
    double **zeroMoment = new double *[this->getcol()];

    //Init each zeroMoment to be printed
    for (int i = 0; i < this->getcol(); i++)
    {
        //Index 0 - number of points in each column of data
        //Index 1 - minimum value of column
        //Index 2 - maximum value of column
        zeroMoment[i] = new double[3];
    }

    //Finishes row, then proceeds to next
    for (int i = 0; i < this->getrow(); i++)
    {
        for (int j = 0; j < this->getcol(); j++)
        {
            //Iterate number of points in column
            (zeroMoment[j])[0]++;
            //Check if new minumum value
            if ((this->data[j])[i] < (zeroMoment[j])[1])
            {
                (zeroMoment[j])[1] = (this->data[j])[i];
            }
            //Check if new maximum value
            if ((this->data[j])[i] > (zeroMoment[j])[2])
            {
                (zeroMoment[j])[2] = (this->data[j])[i];
            }
        }
    }
    //To print
    for (int i = 0; i < this->getcol(); i++)
    {
        cout << i << ": #pts: " << (zeroMoment[i])[0] << " min: " << (zeroMoment[i])[1] << " max: " << (zeroMoment[i])[2] << endl;
    }
}
void DataAnalytics::firstMoment() const
{
    //One entry for each column (the mean)
    double *firstMoment = nthMoment(1);
    for (int i = 0; i < this->getcol(); i++)
    {
        firstMoment[i] /= this->getrow();
        cout << i << ": mean: " << firstMoment[i] << endl;
    }
}
void DataAnalytics::secondMoment() const
{
    //One entry for each column (the variance)
    double *secondMoment = nthMoment(2);
    for (int i = 0; i < this->getcol(); i++)
    {
        secondMoment[i] /= this->getrow();
        cout << i << ": variance: " << secondMoment[i] << endl;
    }
}
void DataAnalytics::thirdMoment() const
{
    //One entry for each column (the skewness)
    double *thirdMoment = nthMoment(3);
    for (int i = 0; i < this->getcol(); i++)
    {
        thirdMoment[i] /= this->getrow();
        cout << i << ": skewness: " << thirdMoment[i] << endl;
    }
}
void DataAnalytics::fourthMoment() const
{
    //One entry for each column (the kurtosis)
    double *fourthMoment = nthMoment(4);
    for (int i = 0; i < this->getcol(); i++)
    {
        fourthMoment[i] /= this->getrow();
        cout << i << ": kurtosis: " << fourthMoment[i] << endl;
    }
}
double *DataAnalytics::nthMoment(int n) const
{
    //One entry for each column (the variance)
    double *nthMoment = new double[getcol()];
    //use openmp
    for (int i = 0; i < getrow(); i++)
    {
        for (int j = 0; j < getcol(); j++)
        {
            (nthMoment[j]) += pow((this->data[j])[i], n);
        }
    }
    return nthMoment;
}
void DataAnalytics::kMeansClustering(int numberOfClusters) const
{
    //need to select random centroids
    double** centroids = new double*[numberOfClusters];
    //get first n rows as initial centroids where n is number of columns (dimensions)
    for (int i = 0; i < numberOfClusters; i++)
    {
        centroids[i] = new double[this->getcol()];
        for (int j = 0; j < this->getcol(); j++)
        {
            (centroids[i])[j] = (this->data[j])[i];
        }
    }
    //centroid check
    // for (int i = 0; i < numberOfClusters; i++)
    // {
    //     for (int j = 0; j < this->getcol(); j++)
    //     {
    //         cout << (centroids[i])[j] << " ";
    //     }
    //     cout << endl;
    // }
    
    
    
}
void DataAnalytics::classify() const
{
}
//not incl in project
/**
 * To print an array of double values given the size
 * @param arrayToPrint pointer to array of doubles
 * @param size number of elements in arrayToPrint
 * @return void
 */

void DataAnalytics::printArray(double *arrayToPrint, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arrayToPrint[i] << " ";
    }
    cout << endl;
}
