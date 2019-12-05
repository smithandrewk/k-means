#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class FileHandler
{

public:
    FileHandler();
    ~FileHandler();
    bool isEqualToThree(int);
    void checkArgs(int, char **);
    void checkInFileOpen(ifstream &, char **);
    void checkOutFileOpen(ofstream &, char **);
    int getNumberOfRows(ifstream &);

private:
};
#endif
