#include "huffman.h"
#include <iostream>
#include <iomanip>

using namespace std;

HuffmanTree:: HuffmanTree()
	: numChars(0), built(false) {}


void HuffmanTree:: insert(char ch, int weight) {
    HNode newNode = {ch, weight, -1, -1};
    built = false;
    nodes.push_back(newNode);
    numChars++;
}

void HuffmanTree:: print() {
	for (int i = 0; i < nodes.size(); i++)
	{
		cout << nodes[i].ch << " " << nodes[i].weight << endl;
	}
}

bool HNode::operator < (const HNode& otherNode) const
{
	if (weight < otherNode.weight)
		return true;
	else
		return false;
}

bool HuffmanTree:: inTree(char ch) {
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i].ch == ch)
			return true;
	}
	return false;
}

int HuffmanTree:: GetFrequency(char ch) {
	if(inTree(ch))
	{
		for (int i = 0; i < nodes.size(); i++)
			if (nodes[i].ch == ch)
				return nodes[i].weight;
	}
	cout << "This character is not in the tree" << endl;
	return 0;
}

int HuffmanTree:: GetFrequency(int i) {
	return nodes[i].weight;
}

bool HuffmanTree:: isInVector(vector<int> &visited, int num)
{
	if (find(visited.begin(), visited.end(), num) != visited.end())
	{
		return true;
	}
	else
		return false;
}

int HuffmanTree:: GetLowestFrequency(vector<int> &visited) {
	int low = 10000;
	int start = -1;
	for (int i = 0; i < nodes.size(); i++)
		if ((nodes[i].weight < low) && !(isInVector(visited, i)))
		{
			low = nodes[i].weight;
			start = i;
		}
	return start;
}

int HuffmanTree:: lookUp(char ch) {
	if(inTree(ch))
	{
		for (int i = 0; i < nodes.size(); i++)
			if (nodes[i].ch == ch)
				return i;
	}
	cout << "This character (" << ch << ") is not in the tree" << endl;
	return -1;
}

string HuffmanTree:: GetCode(char ch) {
	if (ch == ' ')
		return GetCode(lookUp('_'));
	else if (ch == '\n')
		return GetCode(lookUp('@'));
	else
		return GetCode(lookUp(ch));
}


string HuffmanTree:: GetCode(int i) {
	if (nodes[i].parent == -1)
		return "";
	else
		return (GetCode(nodes[i].parent) + (char) (nodes[i].childType + '0'));
}

void HuffmanTree:: PrintTable() {
	int combined = 1;
	cout << "\t~~~~~ ENCODING TABLE ~~~~~\n";
	cout << "Index \tChar \tWeight \tParent \tChildType" << endl;
	for (int i = 0; i < numChars; i++)
	{
		if(nodes[i].ch != ' ' && nodes[i].ch != '*')
		{
			cout << i << "\t" << nodes[i].ch << "\t" << nodes[i].weight << "\t" << nodes[i].parent << "\t" << nodes[i].childType << endl;
		}
		else if(nodes[i].ch == '*' && nodes[i].childType != -1)
		{
			cout << i << "\t" << 'T' << combined << "\t" << nodes[i].weight << "\t" << nodes[i].parent << "\t" << nodes[i].childType << endl;
			combined++;
		}
		else{
			cout << i << "\t" << 'T' << combined << "\t" << nodes[i].weight << "\t" << "0" << "\t" << -1 << endl;
		}
	}
}

int HuffmanTree:: numNodes() {
	int count = 0;
	for (int i = 0; i < nodes.size(); i++)
		count++;
	return count;
}


void HuffmanTree:: build() {
	// counter for combined characters
	vector<int> visited;

	//Step 2: Find 2 min weight and add their sum to MinHeap
	while (!built)
	{
		int lowestFreq = GetLowestFrequency(visited);
		visited.push_back(lowestFreq);
		int secondLowest = GetLowestFrequency(visited);
		visited.push_back(secondLowest);
		insert('*', nodes[lowestFreq].weight + nodes[secondLowest].weight);

		nodes[lowestFreq].childType = 0;
		nodes[secondLowest].childType = 1;

		nodes[lowestFreq].parent = nodes.size() - 1;
		nodes[secondLowest].parent = nodes.size() - 1;

		int counter = 0;
		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i].parent == -1)
			{
				counter++;
			}
		}
		if(counter == 1)
		{
			built = true;
		}
	}
}
