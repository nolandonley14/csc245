#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cctype>
#include <vector>

using namespace std;

void openFile(ifstream &infile, int argc, char* argv[]);
void unzip(map<string, char> &M, ifstream &infile, string line, int argc, char* argv[]);

int main(int argc, char* argv[]) {

    ifstream infile;
    map<string, char> M;
    map<string, char>::iterator j;
    string line;
    int numLine = 0;
    openFile(infile, argc, argv);
    unzip(M, infile, line,argc, argv);
    cout << "File Successfully Inflated Back to Original." << endl;
    return 0;
}

void openFile(ifstream &infile, int argc, char* argv[])
{
    string file = argv[argc-1];
    infile.open(file.c_str());
    if(!infile)
    {
        cout << "\tBad Filename Entered on Command Line -- Now Aborting." << endl;
        exit(1);
    }
    if (file.find(".zip") == -1)
    {
        cout << "\tFile Entered is not a ZIP file -- Now Aborting." << endl;
        exit(1);
    }
}

void unzip(map<string, char> &M, ifstream &infile, string line, int argc, char* argv[])
{

    int firstLine;
    int value;
    string code;

    infile >> firstLine;

    for(int i = 0; i < firstLine; i++)
    {
        infile >> value >> code;
        M[code] = (char) value;
    }

    infile >> line;
    infile.close();
    ofstream newFile;

    string file = argv[argc-1];
    file = file.substr(0, file.find("."));
    newFile.open(file.c_str());
    int pos = 0;
    int j = 1;
    for (int i = 0; i < line.length(); i++)
    {
        if (!(M.find(line.substr(pos, j)) == M.end()))
        {
            newFile << M.at(line.substr(pos,j));
            pos = i + 1;
            j = 1;
        }
        else
        {
            j++;
        }
    }
    newFile.close();
}
