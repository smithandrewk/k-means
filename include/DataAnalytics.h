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

    /**
     * Overloaded stream extraction operator which checks if there is enough data in the datafile, reads in the data and stores in this->data. DOES NOT HANDLE HEADERS. Not very happy about this. Works well, with nice efficiency, when input files are formatted as OCTAVE outputs. There are a few edge cases that cause errors.
     * @param lhs input stream to read from
     * @param rhs DataAnalytics object to read into
     */
    //?How to define in implementation file?
    friend istream &operator>>(istream &lhs, const DataAnalytics &rhs)
    {
        //TODO handle headers
        //TODO handle blank lines in middle
        int i(-1);
        int lastI;
        char str[256] = {};
        int byte(0);
        bool first(true);
        int numCols(0);
        int numRows(0);
        while ((i = lhs.get()) != EOF)
        {

                //Not enough data in file
                if (lhs.peek() == EOF && numRows + 1 < rhs.getrow())
                {
                    //Not enough rows
                    cout << "Expected: " << rhs.getrow() << " rows. Got " << numRows << " rows\nYou allocated more rows than were present in your data file." << endl;
                    //TODO deconstructors
                    exit(1);
                    //this following else if eats up the very last data point, but I think it also causes errors
                }else if (lhs.peek()==EOF){
                (rhs.data[numCols])[numRows] = atof(str);
                numRows++;
                return lhs;
            }
            //Octave formats data files with a space first
            if (i == ' ' && first)
            {
                first = false;
                continue;
            }
            //if any character is read that isn't a space or an endline
            else if (!(i == ' ' || i == '\n'))
            {
                //use char *str as buffer for characters in file
                char c = i;
                str[byte++] = c;
            }
            //we just saw an endline character
            else if (lastI == '\n')
            {
                if ((i == ' ') && lhs.peek() != ' ' && lhs.peek() != '\n')
                {
                    //valid new line after a series of Blanks
                    continue;
                }
                else if (i == ' ' || i == '\n')
                {
                    //Blank Line
                }
            }
            //Legal endline

            else if (i == '\n')
            {
                //numCols is one behind
                if (numCols + 1 < rhs.getcol())
                {
                    //not enough cols
                    cout << "Expected: " << rhs.getcol() << " columns in each row. Row " << (numRows + 1) << " had " << numCols << endl;
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
                    //just right number of columns
                    //take in double in buffer
                    (rhs.data[numCols])[numRows] = atof(str);
                    //reset byte counter
                    byte = 0;
                    //reset column counter
                    numCols = 0;
                    //new row (numRows == 1 when we have read 1 row entirely..)
                    numRows++;
                }
                //Last line
                if (numRows == rhs.getrow())
                {
                    //if next char is not end of file
                    if (!(lhs.peek() == ' ' || lhs.peek() == '\n'))
                    {
                        //more than getrow lines
                        cout << "Expected: " << rhs.getrow() << " rows. Got " << numRows << " rows" << endl;
                        //TODO deconstructors
                        exit(1);
                    }
                    else
                    {
                        return lhs;
                    }
                }
                //If there is a space at the beginning of the next line, clean it up
                if (lhs.peek() == ' ')
                {
                    //octave cleanup
                    lhs.get();
                }
                else if (lhs.peek() == '\n')
                {
                    //Blank
                }
            }
            //Delimiter for new column
            else if (i == ' ')
            {
                //Convert char arr str to double
                (rhs.data[numCols])[numRows] = atof(str);
                //Reset byte counter for buffer
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
