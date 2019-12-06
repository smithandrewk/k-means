#include "../include/DataAnalytics.h"
#include <iostream>
#include <math.h>
using namespace std;

//Default Constructor
DataAnalytics::DataAnalytics()
{
    data = new double*;
    this->setrow(0);
    this->setcol(0);
}
//Alternate Constructor
DataAnalytics::DataAnalytics(int rows, int columns, double value)
{
    data = new double *[columns];
    this->setrow(rows);
    this->setcol(columns);
}
DataAnalytics::DataAnalytics(double **)
{
}
DataAnalytics::DataAnalytics(const DataAnalytics &rhs)
{
    this->data = rhs.getData();
    this->columns = rhs.getcol();
    this->rows = rhs.getrow();
}
DataAnalytics::~DataAnalytics()
{
    // if (this->data == NULL)
    // {
    //     return;
    // }
    // else
    // {
    //     for (int i = 0; i < this->getcol(); i++)
    //     {
    //         if (this->data[i] == NULL)
    //         {
    //             continue;
    //         }
    //         else
    //         {
    //             delete[] this->data[i];
    //         }
    //     }
    //     delete[] this->data;
    // }
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
    //Doesn't check to see if data has already been initialized..
    //setcol should be private
    //but valafar called setcol in sample main
    // if (columns == 0)
    // {
    //     this->data = NULL;
    // }
    // else
    // {
    //     this->data = new double *[columns];
    // }
    this->columns = columns;
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
double **DataAnalytics::getData() const
{
    return this->data;
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
            if ((this->getData()[j])[i] < (zeroMoment[j])[1])
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
    //dealloc
    // for (int i = 0; i < this->getcol(); i++)
    // {

    //     delete zeroMoment[i];
    // }
    // delete[]zeroMoment;
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
    double **centroids = new double *[numberOfClusters];
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
    //calc dist between every point and both centroids, favoring the smaller dist
    int *membership = new int[this->getrow()];
    //one interation of memebrship
    for (int i = 0; i < this->getrow(); i++)
    {
        //distance formula
        //for each centroid
        int minCentroid(-1);
        double minDist(0);
        for (int j = 0; j < numberOfClusters; j++)
        {
            double insideSqrt(0);

            for (int k = 0; k < this->getcol(); k++)
            {
                // cout << "init insideqrt: "<<insideSqrt<<endl;
                insideSqrt += pow((centroids[j])[k] - ((this->data[k])[i]), 2);
                // cout << "centroids[j][k]: " << (centroids[j])[k] << " this->data[k][i]: "<<(this->data[k])[i]<<endl;
                // cout << "diff" << (centroids[j])[k] - ((this->data[k])[i]) << endl;
                // cout << "i: " << i << " j: " << j << " k: " << k << " insidesqrt: "<<insideSqrt<< endl;
            }
            //is distance
            double distance(sqrt(insideSqrt));
            if (distance < minDist)
            {
                minCentroid = j;
                minDist = distance;
            }
            else if (minCentroid == -1)
            {
                minCentroid = j;
                minDist = distance;
            }
        }
        cout << "minCentroid: " << minCentroid << " mindist: " << minDist << endl;
        membership[i] = minCentroid;
    }
    for (int i = 0; i < this->getrow(); i++)
    {
        cout << membership[i] << endl;
    }
    //determine centroid again
    //clear last centroid
    for (int i = 0; i < numberOfClusters; i++)
    {
        for (int j = 0; j < this->getcol(); j++)
        {
            (centroids[i])[j] = 0;
        }
    }
    //add all pts
    int *numberOfPointsInCluster = new int[numberOfClusters];
    for (int i = 0; i < this->getrow(); i++)
    {
        for (int j = 0; j < this->getcol(); j++)
        {
            (centroids[membership[i]])[j] += (this->data[j])[i];
            numberOfPointsInCluster[membership[i]] += 1;
        }
    }
    cout << numberOfPointsInCluster[0] << endl
         << numberOfPointsInCluster[1] << endl;
    //divide by n
    for (int i = 0; i < numberOfClusters; i++)
    {
        for (int j = 0; j < this->getcol(); j++)
        {
            (centroids[i])[j] /= numberOfPointsInCluster[i];
            cout << (centroids[i])[j] << endl;
        }
    }
    delete[] numberOfPointsInCluster;
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
