Project 4 - Dijkstra's Algorithm Implementation
Nolan Donley


Problem Description: Given a digraph, and a starting vertex, produce a summary table
    of the shortest paths to all other vertices using Dijkstra's algorithm. Also
    check the graph for cycles, and print out a cyclic path if one exists. The Input
    file consists of three pieces of semi-colon separated information per line.
    i.e. Atlanta;Washington;600 -
        Starting Vertex: Atlanta
        Destination Vertex: Washington
        Weight: 600

The Graph class will be used to construct the digraph from the data given in the input file.
Functions for this class include:

void MakeEmpty();
bool IsEmpty() const;
bool IsFull() const;
void AddVertex(VertexType);
void AddEdge(VertexType, VertexType, int);
int WeightIs(VertexType, VertexType) const;
void GetToVertices(VertexType, Queue<VertexType>&) const;
void ClearMarks();
void MarkVertex(VertexType);
bool IsMarked(VertexType) const;

This class is using an adjacency matrix approach to implementing a digraph.

The steps I used to solve this problem are as follows:

1. Read in Data and construct a digraph
2. Create the initial Table based on Starting Vertex
3. Visit every Vertex and at each one do the following:
    A. Queue the possible paths exiting the vertex
    B. Dequeue one at a time and check if marked:
        i. if not marked, check weight:
            a. if its lower than weight stored in table, update table with new weight
            b. if its larger, discard that edge
        ii. if marked:
            a. discard edge
            b. cycle count goes up one, can check for additional cycles from that vertex.
4. Iterate through the vertices and print them out in order of lowest weight

Sample Input File:

Austin;Dallas;200
Dallas;Austin;200
Washington;Dallas;1300
Washington;Atlanta;600
Atlanta;Washington;600
Atlanta;Houston;800
Houston;Atlanta;800
Denver;Chicago;1000
Austin;Houston;160
Chicago;Denver;1000
Dallas;Chicago;900
Dallas;Denver;780
Denver;Atlanta;1400

Sample Output:

~~~~~~~~~~~~~~~~~~ DIJKSTRA'S ALGORITHM ~~~~~~~~~~~~~~~~~~

A Weighted Graph Has Been Built For These 7 Vectors:

        Austin        Dallas    Washington
       Atlanta       Houston        Denver
       Chicago

 Please input your starting vertex: Austin
 ---------------------------------------------------------
        Vertex          Distance         Previous

        Dallas                 0             N/A
        Austin               200          Dallas
       Houston               360          Austin
        Denver               780          Dallas
       Chicago               900          Dallas
       Atlanta              1160         Houston
    Washington              1760         Atlanta

---------------------------------------------------------
 There was 5 unique cycles detected.

 One cycle is: Dallas -> Austin -> Dallas
