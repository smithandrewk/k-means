/*
 * file: DataAnalytics.cpp
 * author: Andrew Smith
 * date: 12/09/19, 9:30PM
 * description: this file is the implmentation file for the DataAnalytics class with the function definitions. The DataAnalytics object implements a naive k-means algorithm. See README.md for more information.
 */
#include "../include/DataAnalytics.h"
#include <iostream>
#include <math.h>
using namespace std;

//Default Constructor
DataAnalytics::DataAnalytics()
{
    //Pointers initialize to NULL
    data = NULL;
    centroids = NULL;
    membership = NULL;
    mean = NULL;
    //Size intiializes to 0
    this->setrow(0);
    this->setcol(0);
    //Number of clusters defaults to 0
    this->setNumberOfClusters(0);
}
//Alternate Constructor
DataAnalytics::DataAnalytics(int rows, int columns, double value = 0)
{
    this->setrow(rows);
    this->setcol(columns);
    data = new double *[columns];
    for (int i = 0; i < columns; i++)
    {
        (data[i]) = new double[rows];
        for (int j = 0; j < rows; j++)
        {
            (data[i])[j] = value;
        }
    }
}
//Alternate Constructor
DataAnalytics::DataAnalytics(int rows, int columns, double **rhs)
{
    this->setrow(rows);
    this->setcol(columns);
    data = new double *[columns];
    for (int i = 0; i < columns; i++)
    {
        (data[i]) = new double[rows];
        for (int j = 0; j < rows; j++)
        {
            (data[i])[j] = (rhs[i])[j];
        }
    }
}
//Copy Constructor
DataAnalytics::DataAnalytics(const DataAnalytics &rhs)
{
    rows = rhs.getrow();
    columns = rhs.getcol();
    numberOfClusters = rhs.numberOfClusters;
    data = new double *[columns];
    centroids = new double *[numberOfClusters];
    membership = new int[rows];
    for (int i = 0; i < columns; i++)
    {
        (data[i]) = new double[rows];
        for (int j = 0; j < rows; j++)
        {
            //only execute once through outer for loop
            if (i == (columns - 1))
            {
                membership[j] = rhs.membership[j];
            }
            (data[i])[j] = (rhs.data[i])[j];
        }
    }
    for (int i = 0; i < numberOfClusters; i++)
    {
        (centroids[i]) = new double[columns];
        for (int j = 0; j < columns; j++)
        {
            (centroids[i])[j] = (rhs.centroids[i])[j];
        }
    }
}
//Destructor
DataAnalytics::~DataAnalytics()
{
    if (this->data == NULL)
    {
        return;
    }
    else
    {
        for (int i = 0; i < this->getcol(); i++)
        {
            if (this->data[i] == NULL)
            {
                continue;
            }
            else
            {
                delete[] this->data[i];
            }
        }
        delete[] this->data;
        delete[] this->membership;
        delete[] this->mean;
    }
    if (this->centroids == NULL)
    {
        return;
    }
    else
    {
        for (int i = 0; i < this->numberOfClusters; i++)
        {
            if (this->centroids[i] == NULL)
            {
                continue;
            }
            else
            {
                delete[] this->centroids[i];
            }
        }
        delete[] this->centroids;
    }
}
/**
 * Overloaded assignment operator. Copies all data members except the data matrix.
 * @param rhs DataAnalytics object to assign this to
 * @return constant DataAnalytics object to allow for cascading
 */

const DataAnalytics &DataAnalytics::operator=(const DataAnalytics &rhs)
{
    this->numberOfClusters = rhs.getNumberOfClusters();
    //Deciding not to set rows, because what if you train, then set rows of test in main, then set rows here?
    // this->setrow(rhs.getrow());
    //Deciding not to set columns for the same reason as above
    // this->setcol(rhs.getcol())
    centroids = new double *[numberOfClusters];
    for (int i = 0; i < numberOfClusters; i++)
    {
        //SHOULD be same number of columns
        (centroids[i]) = new double[columns];
        for (int j = 0; j < columns; j++)
        {
            (centroids[i])[j] = (rhs.centroids[i])[j];
        }
    }

    return *this;
}

/**
 * Overloaded equality operator based on size and content
 * @param rhs DataAnalytics object to compare this to
 * @return boolean. true if this and rhs ARE equal
 */
bool DataAnalytics::operator==(const DataAnalytics &rhs) const
{
    if ((this->getcol() != rhs.getcol()) || this->getrow() != rhs.getrow())
    {
        return false;
    }

    for (int i = 0; i < columns; i++)
    {

        for (int j = 0; j < rows; j++)
        {
            if ((data[i])[j] != (rhs.getData()[i])[j])
            {
                return false;
            }
        }
    }
    return true;
}
/**
 * Overloaded inequality operator based on size and content
 * @param rhs DataAnalytics object to compare this to
 * @return boolean. true if this and rhs are NOT equal
 */

bool DataAnalytics::operator!=(const DataAnalytics &rhs) const
{
    if (*this == rhs)
    {
        return false;
    }
    else
    {
        return true;
    }
}
/**
 * To set member variable columns for this. Calls destructor if data is not null, initializes data and membership arrays.
 * @param columns number of columns in data to set
 * @return void
 */
void DataAnalytics::setcol(int columns)
{
    //Doesn't check to see if data has already been initialized..
    //setcol should be private
    //but valafar called setcol in sample main
    if (!(this->getData() == NULL))
    {
        this->~DataAnalytics();
    }

    if (columns == 0)
    {
        this->data = NULL;
        this->membership = NULL;
    }
    else
    {
        this->data = new double *[columns];
        for (int i = 0; i < columns; i++)
        {
            (this->data[i]) = new double[this->getrow()];
        }
        //Initialize membership
        this->membership = new int[this->getrow()];
        for (int i = 0; i < this->getrow(); i++)
        {
            membership[i] = 0;
        }
    }
    this->columns = columns;
}
/**
 * To get member variable columns for this
 * @return number of columns in data
 */
int DataAnalytics::getcol() const
{
    return this->columns;
}
/**
 * To set member variable rows for this
 * @param rows number of rows in data to set
 * @return void
 */

void DataAnalytics::setrow(int rows)
{
    if (rows >= 0)
    {
        this->rows = rows;
    }
}
/**
 * To get member variable rows for this
 * @return number of rows in data
 */
int DataAnalytics::getrow() const
{
    return this->rows;
}
/**
 *
 * To get member variable data for this
 * @return double pointer for data points which are doubles
 */
double **DataAnalytics::getData() const
{
    return this->data;
}
/**
 * To get the member variable numberOfClusters
 * @return number of clusters
 *
 */

int DataAnalytics::getNumberOfClusters() const
{
    return this->numberOfClusters;
}
/**
 * To set the member variable numberOfClusters
 * @param n numberOfClusters input by user in main.cpp for kmeans classification
 * @return void
 */
void DataAnalytics::setNumberOfClusters(int n)
{
    if (n >= 0)
    {
        this->numberOfClusters = n;
    }
    else
    {
        cout << "Invalid number of clusters: " << n << " (should be >=0)" << endl;
        exit(0);
    }
}
/**
 * Calcuates the proprietary "zero moment".
 * in zeroMoment array,
 * Index 0 - number of points in each column of data
 * Index 1 - minimum value of column
 * Index 2 - maximum value of column
 * @return void
 *
 */

void DataAnalytics::zeroMoment() const
{
    double **zeroMoment = new double *[this->getcol()];
    //Init each zeroMoment to be printed
    for (int i = 0; i < this->getcol(); i++)
    {

        zeroMoment[i] = new double[3];
        for (int j = 0; j < 3; j++)
        {
            (zeroMoment[i])[j] = 0;
        }
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
    // dealloc
    for (int i = 0; i < this->getcol(); i++)
    {

        delete[] zeroMoment[i];
    }
    delete[] zeroMoment;
}
/**
 * Calulcates the first moment, which is the mean, on each column of data
 * @return void because the function prints
 *
 */

void DataAnalytics::firstMoment()
{
    //One entry for each column (the mean)
    // double *firstMoment = nthMoment(1);
    this->mean = nthMoment(1);
    for (int i = 0; i < this->getcol(); i++)
    {
        this->mean[i] /= this->getrow();
        cout << i << ": mean: " << this->mean[i] << endl;
    }
}
/**
 * Calulcates the second moment, which is the variance around the mean, on each column of data
 * @return void because the function prints
 *
 */
void DataAnalytics::secondMoment() const
{
    double *secondMoment = new double[this->getcol()];
    for (int i = 0; i < this->getcol(); i++)
    {
        secondMoment[i] = 0;
    }

    for (int i = 0; i < this->getcol(); i++)
    {
        for (int j = 0; j < this->getrow(); j++)
        {
            (secondMoment[i]) += pow((this->data[i])[j] - this->mean[i], 2);
        }
        cout << i << ": variance: " << secondMoment[i] << endl;
    }
    delete[] secondMoment;
}
/**
 * Calulcates the third moment, which is skewness, on each column of data
 * @return void because the function prints
 *
 */
void DataAnalytics::thirdMoment() const
{
    //One entry for each column (the skewness)
    double *thirdMoment = nthMoment(3);
    for (int i = 0; i < this->getcol(); i++)
    {
        thirdMoment[i] /= this->getrow();
        cout << i << ": skewness: " << thirdMoment[i] << endl;
    }
    delete[] thirdMoment;
}
/**
 * Calulcates the fourth moment, which is kurtosis, on each column of data
 * @return void because the function prints
 *
 */
void DataAnalytics::fourthMoment() const
{
    //One entry for each column (the kurtosis)
    double *fourthMoment = nthMoment(4);
    for (int i = 0; i < this->getcol(); i++)
    {
        fourthMoment[i] /= this->getrow();
        cout << i << ": kurtosis: " << fourthMoment[i] << endl;
    }
    delete[] fourthMoment;
}
/**
 * Helper function to calulcate the nth moment on each column of data with a geometric series.
 * @param n the number of the moment to calculate
 * @return array which is the nth moment on each column (not divided by n yet in the geometric series)
 *
 */
double *DataAnalytics::nthMoment(int n) const
{
    //One entry for each column (the variance)
    double *nthMoment = new double[getcol()];
    for (int i = 0; i < this->getcol(); i++)
    {
        nthMoment[i] = 0;
    }

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

/**
 * naive implementation of k-means
 * @param numberOfClusters number of clustersto classify the data points into
 * @return void
 */
void DataAnalytics::kMeansClustering(int numberOfClusters)
{
    //set number of clusters as member variable
    this->setNumberOfClusters(numberOfClusters);
    //intialize centroids as member variable
    this->centroids = new double *[numberOfClusters];
    //get first n rows as initial centroids where n is number of columns (dimensions)
    for (int i = 0; i < numberOfClusters; i++)
    {
        //Initialization
        centroids[i] = new double[this->getcol()];
        //This loop traverses each row
        for (int j = 0; j < this->getcol(); j++)
        {
            //i is cluster number, j is column
            (centroids[i])[j] = (this->getData()[j])[i];
        }
    }
    cout << "INITIAL CENTROIDS" << endl;
    printCentroids();
    //initialize 2d array for centroid values from last classification to determine convergence
    double **lastCentroids = new double *[this->numberOfClusters];
    for (int i = 0; i < this->numberOfClusters; i++)
    {
        lastCentroids[i] = new double[this->getcol()];
        for (int j = 0; j < this->getcol(); j++)
        {
            (lastCentroids[i])[j] = 0;
        }
    }

    //convergence occurs when centroids don't chance over one iteration
    do
    {
        for (int i = 0; i < this->numberOfClusters; i++)
        {
            for (int j = 0; j < this->getcol(); j++)
            {
                (lastCentroids[i])[j] = (this->centroids[i])[j];
            }
        }
        classify();

    } while (isDifferentCentroids(lastCentroids));
    //deallocation
    for (int i = 0; i < this->numberOfClusters; i++)
    {
        delete[] lastCentroids[i];
    }
    delete[] lastCentroids;
}
/**
 * Helper function to determine if the centroids have changed.
 * @param last 2d array of previous centroids to determine if they are equal to this' centroids
 * @return boolean. true if the centroids ARE DIFFERENT
 */

bool DataAnalytics::isDifferentCentroids(double **last)
{
    bool ret = false;
    for (int i = 0; i < this->numberOfClusters; i++)
    {
        for (int j = 0; j < this->getcol(); j++)
        {
            if ((last[i])[j] != (this->centroids[i])[j])
            {
                ret = true;
            }
        }
    }
    return ret;
}
/**
 * Actual meat and potatoes of k-means algorithm. Classifies a set of points based upon given centroids and the distance between each point and each centroid
 * @return void
 */


void DataAnalytics::classify() const
{
    //calc dist between every point and both centroids, favoring the smaller dist
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
                insideSqrt += pow((centroids[j])[k] - ((this->data[k])[i]), 2);
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
        membership[i] = minCentroid;
    }
    //determine centroid again
    //clear last centroid
    for (int i = 0; i < numberOfClusters; i++)
    {
        for (int j = 0; j < this->getcol(); j++)
        {
            (this->centroids[i])[j] = 0;
        }
    }
    //add all pts
    //Initialize numberOfPointsInCluster
    int *numberOfPointsInCluster = new int[numberOfClusters];
    for (int i = 0; i < numberOfClusters; i++)
    {
        numberOfPointsInCluster[i] = 0;
    }
    //Sum all points and count numberOfPointsInCluster
    for (int i = 0; i < this->getrow(); i++)
    {
        for (int j = 0; j < this->getcol(); j++)
        {
            (this->centroids[membership[i]])[j] += (this->data[j])[i];
        }
        numberOfPointsInCluster[membership[i]] += 1;
    }

    //Divide each cluster sum by numberOfPointsInCluster
    for (int i = 0; i < numberOfClusters; i++)
    {
        for (int j = 0; j < this->getcol(); j++)
        {
            (this->centroids[i])[j] /= numberOfPointsInCluster[i];
        }
    }
    delete[] numberOfPointsInCluster;
    cout << "NEW CENTROIDS" << endl;
    printCentroids();
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
/**
 * To print this' membership array for testing
 * @return void
 */
void DataAnalytics::printMembership() const
{
    // Print membership
    for (int i = 0; i < this->getrow(); i++)
    {
        cout << membership[i] << endl;
    }
}
/**
 * To print this' centroids for testing
 * @return void because this is a printing function
 *
 */


void DataAnalytics::printCentroids() const
{
    for (int i = 0; i < this->numberOfClusters; i++)
    {
        for (int j = 0; j < this->getcol(); j++)
        {
            cout << (this->centroids[i])[j] << " ";
        }
        cout << endl;
    }
}
