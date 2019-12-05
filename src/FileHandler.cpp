
#include "../include/FileHandler.h"

FileHandler::FileHandler()
{
    // cout << "FileHandler.cpp::DefaultConstructor" << endl;
}

FileHandler::~FileHandler()
{
    // cout << "FileHandler.cpp::Destructor" << endl;
}
bool FileHandler::isEqualToThree(int argc)
{
    if (argc == 3)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void FileHandler::checkArgs(int argc, char **argv)
{
    if (!isEqualToThree(argc))
    {
        cout << "Usage: " << argv[0] << " <Input file> <outfile>" << endl;
        exit(1);
    }
}
void FileHandler::checkInFileOpen(ifstream &in_file, char **argv)
{
    if (in_file.fail())
    {
        cout << "Error openning the file " << argv[1] << " \n";
        exit(1);
    }
}

void FileHandler::checkOutFileOpen(ofstream &out_file, char **argv)
{
    if (out_file.fail())
    {
        cout << "Error openning the file " << argv[2] << " \n";
        exit(1);
    }
}
int FileHandler::getNumberOfRows(ifstream &file){
    // cout << "FileHandler::getNumberOfRows" << endl;
    string line;
    int counter(0);
    while(!file.eof()){
        getline(file, line);
        counter++;
    }
    //clear bad state after eof
    file.clear();
    //reset streampos pointer
    file.seekg(0);
    return counter;
}