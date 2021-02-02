#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <cstdio>
#include "huffman.h"

using namespace std;

string openFile(ifstream &infile, int argc, char *argv[]);
void LetterFreq(ifstream &infile, int (&Letters)[256], string file, string &s);
void InsertHuffman(const int Letters[], HuffmanTree &ht);
void CreateZip(ifstream &infile, int argc, char* argv[], string file, HuffmanTree &ht, string s, int Letters[256]);

int main(int argc, char* argv[]) {
    ifstream infile;
    HuffmanTree ht;
    string s;
    int header;
    int Letters[256];
    string fileToZip = openFile(infile, argc, argv);
    LetterFreq(infile, Letters, fileToZip, s);
    InsertHuffman(Letters, ht);
    ht.build();
    CreateZip(infile, argc, argv, fileToZip, ht, s, Letters);
    return 0;
}

string openFile(ifstream &infile, int argc, char *argv[])
{
    string file;
    if(argc >= 3)
    {
        file = argv[2];
        return file;
    }
    else if(argc == 2)
    {
        file = argv[1];
        return file;
    }
    else if (argc <= 1)
    {
        cout << "\tBad Filename Entered on Command Line -- Now Aborting." << endl;
        exit(1);
    }
    else
    {
        exit(1);
    }
}


void LetterFreq(ifstream &infile, int (&Letters)[256], string file, string &s)
{
    char ch;
    infile.open(file);
    for (char ch = 0; ch <= char(126); ch++)
    {
        Letters[ch] = 0;
    }
    while(infile.get(ch))
    {
        Letters[ch]++;
        s += ch;
    }

}

void InsertHuffman(const int Letters[], HuffmanTree &ht)
{
    for (char ch = char(0); ch <= char(126); ch++)
    {
        if (Letters[ch] != 0 && ch != '\n' && ch != ' ')
        {
            ht.insert(ch, Letters[ch]);
        }
        else if (Letters[ch] != 0 && ch == '\n')
        {
            ht.insert('@', Letters[ch]);
        }
        else if (Letters[ch] != 0 && ch == ' ')
        {
            ht.insert('_', Letters[ch]);
        }
    }
}

void CreateZip(ifstream &infile, int argc, char* argv[], string file, HuffmanTree &ht, string s, int Letters[256])
{

    int header = ht.numNodes() - ht.numNodes()/2;
    file += ".zip";
    ofstream zipFile;
    string input = argv[1];
    
    if (input == "--t")
    {
        ht.PrintTable();
        remove(argv[2]);
    }
    else if (input == "--help"){
        string file = "help.txt";
        infile.open(file.c_str());
        string input;
        while(infile)
        {
            cout << "here" << endl;
            getline(infile, input);
            cout << input << endl;
        }
        exit(1);
    }
    else {
        remove(argv[1]);
    }

    zipFile.open(file.c_str());
    zipFile << header << endl;
    int source;
    for (char ch = char(0); ch <= char(126); ch++)
    {
        if (Letters[ch] != 0 && ch != '\n' && ch != ' ')
        {
            zipFile << (int) ch << " " << ht.GetCode(ch) << endl;
            source++;
        }
        else if (Letters[ch] != 0 && ch == '\n')
        {
            zipFile << (int) '\n' << " " << ht.GetCode('@') << endl;
            source++;
        }
        else if (Letters[ch] != 0 && ch == ' ')
        {
            zipFile << (int) ' ' << " " << ht.GetCode('_') << endl;
            source++;
        }
    }

    char ch;
    int numBits;
    for (int i = 0; i < s.length(); i++)
    {
        ch = s[i];
        zipFile << ht.GetCode(ch);
        numBits++;
    }
    zipFile.close();
    float ratio = (1 - (numBits) / (source * 8)) * 100;
    cout << "File successfully Compressed To " << numBits << " Bits (" << ratio << "% less)" << endl;

}
