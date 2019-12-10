/*
 * file: DataAnalytics.h
 * author: Andrew Smith
 * date: 12/09/19, 9:30PM
 * description: this file is the header file for the DataAnalytics class. The DataAnalytics object implements a naive k-means algorithm. See README.md for more information.
 */
#include <iostream>
#include <omp.h>
using namespace std;

class DataAnalytics
{
    //TODO IGNORE BLANK LINES
    //?How to define in implementation file?
    /**
     * Overloaded stream extraction operator which checks if there is enough data in the datafile, reads in the data and stores in this->data
     * @param lhs input stream to read from
     * @param rhs DataAnalytics object to read into
     */

    friend istream &operator>>(istream &lhs, const DataAnalytics &rhs)
    {
        //TODO check for first line of data
        //TODO handle headers

        int i(-1);
        int lastI;
        char str[256] = {};
        int byte(0);
        bool first(true);
        int numCols(0);
        int numRows(0);
        while ((i = lhs.get()) != EOF)
        {
            if(numRows+1>rhs.getrow()){
                //Too many rows
                    cout << "Expected: " << rhs.getrow() << " rows. Counter was about to exceed that. There are a greater number of rows in your data file than you indicated." << endl;
                    //TODO deconstructors
                    exit(1);
            }
            if (lhs.peek() == EOF && numRows+1<rhs.getrow())
            {
                //Not enough rows
                    cout << "Expected: " << rhs.getrow() << " rows. Got "<<numRows<<" rows"<< endl;
                    //TODO deconstructors
                    exit(1);
            } else if (lhs.peek()==EOF){
                (rhs.data[numCols])[numRows] = atof(str);
                numRows++;
            }
            //Octave formats data files with a space first
            if (i == ' ' && first)
            {
                first = false;
                continue;
            }
            else if (!(i == ' ' || i == '\n'))
            {
                char c = i;
                str[byte++] = c;
            }
            else if (lastI == '\n')
            {
                if (i == ' ' && lhs.peek() != ' ' && lhs.peek() != '\n')
                {
                    //valid new line after a series of Blanks
                    continue;
                }
                else if (i == ' ' || i == '\n')
                {
                    //Blank Line
                }
            }
            else if (i == '\n')
            {
                //Legal endline
                //numCols is one behind
                if (numCols + 1 < rhs.getcol())
                {
                    //not enough cols
                    cout << "Expected: " << rhs.getcol() << " columns in each row. Row " << (numRows + 1) << " had " << numCols + 1 << endl;
                    //TODO deconstructors
                    exit(1);
                }
                else if (numCols + 1 > rhs.getcol())
                {
                    //too many cols
                    cout << "Expected: " << rhs.getcol() << " columns in each row. Row " << (numRows + 1) << " had " << numCols + 1 << endl;
                    //TODO deconstructors
                    exit(1);
                }
                else
                {
                    //just right
                    //reset for next row
                    // cout << "numcols: " << numCols << "numrows: " << numRows << endl;

                    (rhs.data[numCols])[numRows] = atof(str);
                    byte=0;
                    numCols = 0;
                    numRows++;
                }
                if (lhs.peek() == ' ')
                {
                    //octave cleanup
                    lhs.get();
                }
            }
            else if (i == ' ')
            {
                // cout << "numcols: " << numCols << "numrows: " << numRows << endl;
                (rhs.data[numCols])[numRows] = atof(str);
                // cout << str;
                byte = 0;
                //new column
                numCols++;
            }
            lastI = i;
        }
        return lhs;
    }
    /**
     * Overloaded stream insertion operator which checks if there is enough data in the datafile, reads in the data and stores in this->data
     * @param lhs output stream to print to
     * @param rhs DataAnalytics object to read from
     */
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
