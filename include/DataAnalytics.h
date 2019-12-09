#include <iostream>
#include <omp.h>
using namespace std;

class DataAnalytics
{
    //TODO const qualification
    //?How to define in implementation file?
    friend istream &operator>>(istream &lhs, const DataAnalytics &rhs)
    {
        //TODO check for first line of data
        //TODO handle headers
        double temp(0);
        int i(0);

// #pragma omp parallel
//         {
//             for (int i = 0; i < rhs.getrow(); i++)
//             {
//                 for (int j = 0; j < rhs.getcol(); j++)
//                 {
//                     lhs >> (rhs.data[j])[i];
//                 }
//             }
//         }

        while (!lhs.eof())
        {
            for (int j = 0; j < rhs.getcol(); j++)
            {
                lhs >> (rhs.data[j])[i];
            }
            i += 1;
        }
        return lhs;
    }
    //?How to define in implementation file?
    friend ostream &operator<<(ostream &lhs, const DataAnalytics &rhs)
    {
        for (int i = 0; i < rhs.getrow(); i++)
        {
            for (int j = 0; j < rhs.getcol(); j++)
            {
                if (j == (rhs.getcol() - 1))
                {
                    lhs << (rhs.data[j])[i] << endl;
                }
                else
                {
                    lhs << (rhs.data[j])[i] << ", ";
                }
            }
        }
        return lhs;
    }

private:
    int rows, columns;
    double **data, **centroids;
    int *membership;
    int numberOfClusters;

public:
    //TODO proper member init

    DataAnalytics();
    DataAnalytics(int rows, int columns, double value);
    DataAnalytics(double **);
    DataAnalytics(const DataAnalytics &);
    ~DataAnalytics();
    //Ass
    const DataAnalytics &operator=(const DataAnalytics &);
    //Equality operator
    //?
    bool operator==(const DataAnalytics &) const;
    //Inequality operator
    //?unsure of rhs
    bool operator!=(const DataAnalytics &) const;
    void setcol(int columns);
    int getcol() const;
    void setNumberOfClusters(int);
    void setrow(int rows);
    int getrow() const;
    double **getData() const;

    void zeroMoment() const;
    void firstMoment() const;
    void secondMoment() const;
    void thirdMoment() const;
    void fourthMoment() const;
    double *nthMoment(int n) const;
    void kMeansClustering(int numberOfClusters);
    void classify() const;
    //not incl in project
    void printArray(double *arrayToPrint, int size);
    void printCentroids() const;
    void printMembership() const;
};
