#include "queue.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "graph.h"
#include <cstdlib>
#include <sstream>
#include <vector>
#include <climits>
#include <iomanip>
#include <stack>
#include <set>
#include <stdlib.h>

using namespace std;

struct VertexType
{
	string name;
	bool marked;
	int distance;
	string previous;
};

void insertionSort(vector<string> &cities, int numVertices);
void checkInFile(int argc);
void buildDGraph(Graph<string> &dGraph, string filename, vector<string> &cities, int &numVertices, int &numEdges, vector<VertexType> myVertices);
void printCities(vector<string> cities);
string setStart(int numVertices, vector<string> cities);
void printRow(int location, vector<VertexType> myVertices);
int findMin(vector<VertexType> myVertices, int numVertices);
void dijkstra(Graph<string> &dGraph, int numVertices, vector<VertexType> myVertices, vector< vector<string> >& allCycles, vector<string> cities, vector<string> cycle);
void updateTable(vector<VertexType> &myVertices, string s, int weight, string p);
void createTable(vector<VertexType> &myVertices, vector<string> cities, string firstCity);
void findCycles(Graph<string> &dGraph, vector<VertexType> myVertices, vector< vector<string> >& allCycles, vector<string> cycle, VertexType currentOriginal, string coNeighbor, string startName);
VertexType getVertex(string name, vector<VertexType> myVertices);

int main(int argc, char* argv[])
{
	checkInFile(argc);	// Checks to see if Filename is given
	// Creation of Input File:
	string filename = argv[1];
	Graph<string> dGraph;
	int numVertices;
	int numEdges;
	vector<VertexType> myVertices;
	vector<string> cities;
	vector<string> cycle;
	vector< vector<string> > allCycles;
	buildDGraph(dGraph, filename, cities, numVertices, numEdges, myVertices);	// Builds the Graph using the data from the external file.
	printCities(cities);	// Prints Cities found in file
	dijkstra(dGraph, numVertices, myVertices, allCycles, cities, cycle);	// Computes Dijkstra's Algorithm:
	return(0);
}


// Checks to see if Filename is given:
void checkInFile(int argc)
{
	if (argc > 1)
	{
		return;
	}
	else
	{
		cout << "No Filename entered..." << endl;
		exit(1);
	}
}

// Computes Dijkstra's Algorithm:
void dijkstra(Graph<string> &dGraph, int numVertices, vector<VertexType> myVertices, vector< vector<string> >& allCycles, vector<string> cities, vector<string> cycle)
{
	int cycleCount = 0;
	string startName = setStart(numVertices, cities);
	createTable(myVertices, cities, startName);
	vector< vector<string> > cycles;
	for (int numMarked = 0; numMarked < myVertices.size(); numMarked++)
	{
		VertexType currentOriginal = myVertices[numMarked];
		Queue<string> originalPaths;
		dGraph.GetToVertices(currentOriginal.name, originalPaths);
		while(!originalPaths.isEmpty())
		{
			string coNeighbor = originalPaths.dequeue();
			if (coNeighbor != currentOriginal.name)
			{
				VertexType coNeighborVertex = getVertex(coNeighbor, myVertices);
				if (!coNeighborVertex.marked)
				{
					int weight = dGraph.WeightIs(currentOriginal.name, coNeighborVertex.name);
					updateTable(myVertices, coNeighborVertex.name, weight + currentOriginal.distance, currentOriginal.name);
				}
				else
				{
					cycleCount++;
					findCycles(dGraph, myVertices, allCycles, cycle, currentOriginal, coNeighbor, startName);
	 			}
			}
		}
	}
	cout << "---------------------------------------------------------" << endl;
	cout << setw(14) << "Vertex" << setw(18) << "Distance" << setw(18) << "Previous\n" << endl;
	for (int i = 0; i < myVertices.size(); i++)
	{
			printRow(i, myVertices);
	}
	cout << "\n---------------------------------------------------------" << endl;
	if (cycleCount == 1)
		cout << " There was " << cycleCount << " unique cycle detected.\n" << endl;
	else
		cout << " There was " << cycleCount << " unique cycles detected.\n" << endl;

	if (cycleCount > 0)
	{
		cout << " One cycle is: ";
		for (int j = allCycles[0].size(); j > 0; j--)
		{
			cout << allCycles[0][j-1] << " -> ";
		}
		for (int j = allCycles[0].size(); j == allCycles[0].size(); j--)
		{
			cout << allCycles[0][j-1] << "\n" << endl;
		}
	}
}

// Builds the Graph using the data from the External File:
void buildDGraph(Graph<string> &dGraph, string filename, vector<string> &cities, int &numVertices, int &numEdges, vector<VertexType> myVertices)
{
	ifstream infile;
	infile.open(filename);
	char start[30];
	char dest[30];
	char num[6];
	int weight;
	while (infile)
	{
		infile.getline(start, 30,';');
		infile.getline(dest, 30,';');
		infile.getline(num, 6);
		weight = atoi(num);
		bool conStart = false;
		bool conDest= false;
		for (int i=0; i < cities.size(); i++)
	    {
	        if (cities.at(i) == start)
	            conStart = true;
			if (cities.at(i) == dest)
		        conDest = true;
	    }
		if (!conStart && start[0] != 0)
		{
			dGraph.AddVertex(start);
			cities.push_back(start);
			numVertices++;
		}
		if (!conDest)
		{
			dGraph.AddVertex(dest);
			cities.push_back(dest);
			numVertices++;
		}
		dGraph.AddEdge(start, dest, weight);
		numEdges++;
	}
}

// Prints Cities found in External File:
void printCities(vector<string> cities)
{
	system("clear");
	cout << "~~~~~~~~~~~~~~~~~~ DIJKSTRA'S ALGORITHM ~~~~~~~~~~~~~~~~~~" << endl;
	cout << "\nA Weighted Graph Has Been Built For These " << cities.size() << " Vectors:" << endl;
	for (int i=0; i < cities.size(); i++)
	{
		if (i%3 == 0)
		{
			cout << '\n';
		}
		cout << setw(14) << cities.at(i);
	}
	cout << endl;
}

// Sorts the Cities Alphabetically:
void insertionSort(vector<string> &cities, int numVertices)
{
	for( int p = 1; p < cities.size( ); p++ )
	{
		string tmp = cities[ p ];

	    int j;
		for( j = p; j > 0 && (tmp.compare(cities[ j - 1 ]) < 0); j-- )
			cities[ j ] = cities[ j - 1 ];
		cities[ j ] = tmp;
	}
}

//Sets the Starting Value in Dijsktra's Algorithm:
string setStart(int numVertices, vector<string> cities)
{
	cout << "\n Please input your starting vertex: ";
	string response;
	getline(cin,response);
	bool isThere = false;
	for (int i = 0;	i < cities.size(); i++)
	{
		if (cities[i].compare(response) == 0)
		{
			return response;
		}
	}
	while (!isThere)
	{
		cout << " Starting location does not exist..." << endl;
		cout << " Please input your new vertex: ";
        	string response;
        	cin >> response;
		for (int i = 0; i < cities.size(); i++)
        	{
                	if (cities[i].compare(response) == 0)
			{
                        	return response;
                	}
        	}
	}
}

// Finds the minimum non-marked values in VertexType Array:
int findMin(vector<VertexType> myVertices, int numVertices)
{
 		int minWeight = INT_MAX - 1;
                int minThing = -1;
		for (int i = 0; i < numVertices; i++)
                {
                        if (myVertices[i].distance < minWeight && !myVertices[i].marked)
                        {
                                minWeight = myVertices[i].distance;
                                minThing = i;
                        }
			else if (myVertices[i].distance == minWeight && !myVertices[i].marked)
        		{
                                minWeight = myVertices[i].distance;
                                minThing = i;
                        }

		}
		return minThing;
}

// Prints a given row in a Summary Table:
void printRow(int location, vector<VertexType> myVertices)
{
	if (myVertices[location].distance != INT_MAX && myVertices[location].distance != INT_MIN)
	{
		cout << setw(14) << myVertices[location].name << setw(18) << myVertices[location].distance << setw(16) << myVertices[location].previous << endl;
	}
	else
	 cout << setw(14) << myVertices[location].name << setw(18) << "Not On Path" << setw(16) << "N/A" << endl;
}

void updateTable(vector<VertexType> &myVertices, string s, int weight, string p)
{
	VertexType vertex;
	VertexType tmp;
	vertex.name = s;
	vertex.marked = false;
	vertex.distance = weight;
	vertex.previous = p;
	for (int i = 0; i < myVertices.size(); i++)
	{
		if (myVertices[i].name == vertex.name)
		{
			if (vertex.distance == INT_MIN)
			{
				vertex.distance = INT_MAX;
				vertex.previous = "";
				myVertices[i] = vertex;
			}
			else if (vertex.distance <= myVertices[i].distance)
			{
				myVertices[i] = vertex;
			}
			else
			{
				vertex.distance = myVertices[i].distance;
				vertex.previous =  myVertices[i].previous;
				myVertices[i] = vertex;
			}
			tmp = getVertex(p, myVertices);
			tmp.marked = true;
			for (int l = 0 ; l < myVertices.size(); l++)
			{
				if (tmp.name == myVertices[l].name)
				{
					myVertices[l] = tmp;
				}
			}
		}
	}
	for(int p = 1; p < myVertices.size( ); p++ )
	{
		VertexType tmp = myVertices[ p ];

	    int j;
		for( j = p; j > 0 && tmp.distance < myVertices[j-1].distance; j-- )
			myVertices[ j ] = myVertices[ j - 1 ];
		myVertices[ j ] = tmp;
	}
}

void createTable(vector<VertexType> &myVertices, vector<string> cities, string firstCity)
{
	VertexType vertex;
	for (int i = 0; i < cities.size(); i++)
	{
		if ((cities[i] == firstCity) && (i == 0))
		{
			vertex.name = firstCity;
			vertex.marked = false;
			vertex.distance = 0;
			vertex.previous = "N/A";
			myVertices.push_back(vertex);
		}
		else if (cities[i] == firstCity && (i > 0))
		{
			vertex.name = firstCity;
			vertex.marked = false;
			vertex.distance = 0;
			vertex.previous = "N/A";
			VertexType tmp;
			tmp = myVertices[0];
			myVertices[0] = vertex;
			myVertices.push_back(tmp);
		}
		else
		{
			vertex.name = cities[i];
			vertex.marked = false;
			vertex.distance = INT_MAX;
			vertex.previous = "";
			myVertices.push_back(vertex);
		}
	}
}

VertexType getVertex(string name, vector<VertexType> myVertices)
{
	for (int i = 0; i < myVertices.size(); i++)
	{
		if (myVertices[i].name == name)
		{
			return myVertices[i];
		}
	}
}

string getVertexName(string name, vector<VertexType> myVertices)
{
	for (int i = 0; i < myVertices.size(); i++)
	{
		if (myVertices[i].name == name)
		{
			return myVertices[i].name;
		}
	}
}

void findCycles(Graph<string> &dGraph, vector<VertexType> myVertices, vector< vector<string> >& allCycles, vector<string> cycle, VertexType currentOriginal, string coNeighbor, string startName)
{
	if (currentOriginal.previous == coNeighbor)
	{
		cycle.push_back(currentOriginal.name);
		cycle.push_back(coNeighbor);
		allCycles.push_back(cycle);
		cycle.clear();
	}
	else if (coNeighbor == startName)
	{
		while (currentOriginal.name != startName)
		{
			cycle.push_back(currentOriginal.name);
			currentOriginal = getVertex(currentOriginal.previous, myVertices);
		}
		cycle.push_back(startName);
		allCycles.push_back(cycle);
		cycle.clear();
	}
}
