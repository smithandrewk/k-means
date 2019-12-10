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
        int numberOfLines(0);

        //TODO doesn't handle blank lines..
        char *a = new char[256];
        while (lhs.getline(a, 256))
        {
            numberOfLines++;
        }
        lhs.clear();
        lhs.seekg(0);

        if (numberOfLines > rhs.getrow())
        {
            cout << "There might be some extra lines in your data file...\nExpected: " << rhs.getrow() << " lines\nRead: " << numberOfLines << " lines" << endl;
            exit(1);
        }
        else if (numberOfLines < rhs.getrow())
        {
            cout << "There might be some missing lines in your data file...\nExpected: " << rhs.getrow() << " lines\nRead: " << numberOfLines << " lines" << endl;
            exit(1);
        }
        int numInThisRow(0);
        for (int i = 0; i < rhs.getrow(); i++)
        {
            for (int j = 0; j < rhs.getcol(); j++)
            {
                if (lhs.peek() == '\n')
                {
                    if (numInThisRow > rhs.getcol())
                    {
                        cout << "Expected: " << rhs.getcol() << " columns in each row. Row " << (i+1) << " had more than that." << endl;
                        //TODO deconstructors
                        exit(1);
                    }
                    else if (numInThisRow < rhs.getcol())
                    {
                        cout << "Expected: " << rhs.getcol() << " columns in each row. Row " << (i+1) << " had less than that." << endl;
                        //TODO deconstructors
                        exit(1);
                    }
                    numInThisRow = 0;
                }

                lhs >> (rhs.data[j])[i];
                numInThisRow++;
            }
        }
        delete[] a;
        return lhs;
    }
    //?How to define in implementation file?
    friend ostream &operator<<(ostream &lhs, const DataAnalytics &rhs)
    {
        for (int i = 0; i < rhs.getrow(); i++)
        {
            for (int j = 0; j < rhs.getcol(); j++)
            {
                //Updated valafar instructions
                lhs << (rhs.data[j])[i] << " ";
            }
            lhs << rhs.membership[i] << endl;
        }
        return lhs;
    }

private:
    int rows, columns;
    double **data, **centroids;
    int *membership;
    double *mean;
    int numberOfClusters;

public:
    DataAnalytics();
    DataAnalytics(int rows, int columns, double value);
    DataAnalytics(int rows, int columns,double **);
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
    //TODO reconcile with website given by valafar
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
    bool isDifferentCentroids(double **last);
};
