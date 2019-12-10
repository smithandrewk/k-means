#include <iostream>
#include <fstream>
#include <string>
#include "../include/DataAnalytics.h"

using namespace std;

int main(int argc, char **argv)
{
    int row, col;
    string fname;
    ifstream in_file;
    ofstream out_file;
    DataAnalytics train, test;

    cout << "Please enter the name of the train file, rows, and columns: ";
    cin >> fname;
    cin >> row;
    cin >> col;
    train.setrow(row);
    train.setcol(col);

    in_file.open(fname);
    if (in_file.fail())
    {
        cout << "Error openning the file " << argv[1] << " \n";
        exit(1);
    }
    in_file >> train;
    in_file.close();

    cout << "Zeroeth statistical moment: " << endl;
    train.zeroMoment();
    cout << "First statistical moment: " << endl;
    train.firstMoment();
    cout << "Second statistical moment: " << endl;
    train.secondMoment();
    cout << "Third statistical moment: " << endl;
    train.thirdMoment();
    cout << "Fourth statistical moment: " << endl;
    train.fourthMoment();

    train.kMeansClustering(2);

    cout << "Please enter the name of the testing file, rows, and columns: ";
    cin >> fname;
    cin >> row;
    cin >> col;
    test.setrow(row);
    test.setcol(col);

    in_file.open(fname);
    if (in_file.fail())
    {
        cout << "Error openning the file " << argv[1] << " \n";
        exit(1);
    }
    in_file >> test;
    in_file.close();
    cout << "-----TRAIN------" << endl;
    cout << "col: " << train.getcol() << endl;
    cout << "row: " << train.getrow() << endl;
    cout << "number of clusters: " << train.getNumberOfClusters() << endl;
    cout << "-----TEST------" << endl;
    cout << "col: " << test.getcol() << endl;
    cout << "row: " << test.getrow() << endl;
    cout << "number of clusters: " << test.getNumberOfClusters() << endl;

    test = train;
    cout << "-----TEST-AFTER-EQUALITY------" << endl;
    cout << "col: " << test.getcol() << endl;
    cout << "row: " << test.getrow() << endl;
    cout << "number of clusters: " << test.getNumberOfClusters() << endl;
    test.classify();

    cout << "Please enter the output file: ";
    cin >> fname;

    out_file.open("mom");
    if (out_file.fail())
    {
        cout << "Error openning the file " << argv[2] << " \n";
        exit(1);
    }

    out_file << test << endl;
    out_file.close();

    return 0;
}
