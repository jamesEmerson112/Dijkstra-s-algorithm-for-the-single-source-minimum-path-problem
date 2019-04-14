//************************************************************
//
// An Thien Vo
// CS 302, Dr. Larmore 
// Assginment #7
//
//************************************************************

//************************************************************
// 
// Write a program which implments Dijstra's algorithm for the 
// single source minimum path problem on a weighted directed
// graph with no negative weights.
//
//************************************************************


#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <iomanip>
#include <string>
#include "Vo_An_ast7_linkedlist.h"

using namespace std;

const int INF = 987654321; 					// setting up the INFINITY value

// declaring a struct that hold a vertex and its distance from the starting vertex to itself as the final result
struct v
{
	int id;
	int dist;
	//vector<int> visitedNode;

	v(int id, int dist)
	{
		this->id = id;
		this->dist = dist;
	}
};

// struct compare is used as the CONDITION for the priority queue (min-heap)
struct compare
{
	bool operator()(v *left, v *right)
	{
		return left->dist > right->dist;
	}
};

/*
 * Dijkstra (G, weight, startingVertex)
 * 		Initialize(G, startingVertex)
 *			1. a Set S is initialized to NULL
 *			2. set Q = V[G] (all the vertices)
 *			3. d[startingVertex] = 0, and d[others] = INF;
 * 			while set is not empty
 *				u is the extracted min from Q // delete u from Q
 * 				S is the union of S and u
 *				for each vertex, v belongs to adjacent of u
 *					Relax (u,v,w)
 *						if d[u] <= d[u] + w(u,v) = d[v]
 */

void Dijkstra(VertexNeighbor *neighbor, int startingVertex, const int numberOfVertices, ofstream& outfile)
{

	// Initilize
	struct v *u; 				// struct to hold the u
	vector<v*> S;				// Array to hold "fully-processed" vertices
	priority_queue<v*, vector<v*>, compare> Q;				// priority queue to hold and extract the minimum distance that a vertex holds
	vector<int> *prev;										// to traverse/track the previous nodes.
	prev = new vector<int>[numberOfVertices]; 

	// initialize the starting vertex as 0;
	prev[startingVertex].push_back(startingVertex);
	//prev[startingVertex].push_back(startingVertex);

	// here since I have no idea how to work with a struct pointer 
	// as a parameter for a void function belonging to a class
	// I am creating a decoy array of distance to hold the values
	// of the struct d, which has id and unsolved distance.

	//*************************************************************************

	// Initialize where:
	//		the distance of the starting vertex = 0;
	//		the distance of the rest of vertices = INF
	int *distance = new int[numberOfVertices];
	distance[startingVertex] = 0;
	
	for (int i = 0; i < numberOfVertices; ++i)
	{
		if (i == startingVertex)
			continue;
		distance[i] = INF;
	}

	//*************************************************************************	

	// push all of the vertices to the minimum queue
	for (int i = 0; i < numberOfVertices; ++i)
	{
		Q.push(new v(neighbor[i].getID(), distance[i]));
	}

	/*
	 * 			while set is not empty
	 *				u is the extracted min from Q // delete u from Q
	 * 				S is the union of S and u
	 *				for each vertex, v belongs to adjacent of u
	 *					Relax (u,v,w)
	 *						if d[u] <= d[u] + w(u,v) = d[v]
	 */ 

	//*************************************************************************
	while (Q.size() != 0)    		// while set is not empty
	{
		// u is the extracted min from Q // delete u from Q
		u = Q.top(); 				// grab the unit with the smallest distance 
		Q.pop();					// remove it from set Q

		if (u->id < 0)				// if u, as a vertex, does not point at any vertices, then skip
		{
			continue;
		}

		outfile << "u = " << u->id << " dis[u] =" << u->dist << endl;	// testing

		// proceed to do relaxation
		for (int i = 0; i < numberOfVertices; ++i)
		{
			//if (u->id == 0)
			//	continue;
			if (u->id == neighbor[i].getID())
			{
				neighbor[u->id].relax(distance, prev, startingVertex);
			}
		} // relaxation done.

		// attempting to create an array of previous nodes for each vertex
		S.push_back(u); 			// technically, this marks vertex u is "done"

		// clear the queue Q to re-update it (re-updating the distances)
		for (int i = 0; i < static_cast<int>(Q.size()); ++i)
		{
			Q.pop();
		}
		
		// Re-enter the new value for the Q
		// if the vertex is already fully processed, which is u, skip
		// else push every unprocessed/partially processed vertices into the queue
		bool visited = false;
		for (int i = 0; i < numberOfVertices; ++i) 					
		{
			for (int j = 0; j < static_cast<int>(S.size()); ++j)
			{
				if (i == S[j]->id)
					visited = true;
			}
			if(!visited)
				Q.push(new v(neighbor[i].getID(), distance[i]));	//
			else
				visited = false;		
		}
		
	} // end while loop

	//*************************************************************************	
	// printing the result
	// adding destination into the vector for each vertex
	for (int i = 0; i < numberOfVertices; ++i)
	{
		if (i == startingVertex)
			continue;
		prev[i].push_back(i);
	}

	outfile << endl;
	for (int i = 0; i < numberOfVertices; ++i)
	{
		if (neighbor[i].getID() < 0) 		// if it's an extra vertex, skip it
			continue;
		outfile << "shortest path to " << neighbor[i].getID() << ": ";
		if (distance[i] != INF)
		{
			// printing previous, visited vertices before the destination
			for (int j = 0; j < static_cast<int>(prev[i].size()); ++j)
			{
				if (j == prev[i].size()-1)
					outfile << prev[i][j] << ": ";
				else
					outfile << prev[i][j] << ",";
			}	
			outfile << "length = " << distance[i] << endl;
		}
		else
			outfile << "length = INF" << endl;													// LARMORE
	}

	delete []distance;
}

void printChoice();
void readAndImplement(string name, ofstream& outfile); 							// reading the input of the small graph, and perhaps run Dijkstra straight out
											// of the colony?
void printAuthorName();
void printAuthorNameOutfile(ofstream& outfile);

int main()
{
	printAuthorName();
	string inputFileName;
	string outputFileName;
	ofstream outfile;
	cout << "Please firstly enter your output file name: " << endl;
	cin >> outputFileName;
	outfile.open(outputFileName.c_str());
	printAuthorNameOutfile(outfile);
	printChoice();
	int choice;
	cin >> choice;
	bool shouldEnd = false;
	while(cin)
	{
		switch(choice)
		{
			case 1:
				inputFileName = "smallgraph.txt";
				readAndImplement(inputFileName, outfile);
				break;
			case 2:
				inputFileName = "mediumgraph.txt";
				readAndImplement(inputFileName, outfile);
				break;
			case 3:
				inputFileName = "biggraph.txt";
				readAndImplement(inputFileName, outfile);
				break;			
			case 4:
				cout << "Please enter the name of your input file: " << endl;
				cin >> inputFileName;
				readAndImplement(inputFileName, outfile);
				break;
			default:
				cout << "End program. Thank you." << endl << endl;
				shouldEnd = true;
				break;
		}
		if (!shouldEnd)
		{
			printChoice();
			cin >> choice;	
		}
		else
			break;	
	}

	outfile.close();

	// system("pause");   // For the Visual Studio
	return 0;
}

//***********************************************************************
void printAuthorName()
{
	cout << setfill('*') << setw(80) << "*" << endl;
	cout << "An Thien Vo - CS 302 - Dr. Larmore - Assignment #7\n";
	cout << "Dijkstra" << endl;
	cout << setfill('*') << setw(80) << "*" << endl;
}

void printAuthorNameOutfile(ofstream& outfile)
{
	outfile << setfill('*') << setw(80) << "*" << endl;
	outfile << "An Thien Vo - CS 302 - Dr. Larmore - Assignment #7\n";
	outfile << "Dijkstra" << endl;
	outfile << setfill('*') << setw(80) << "*" << endl;	
}

void printChoice()
{
	cout << "********************************************************" << endl;
	cout << "Please select the following choice: \n";
	cout << "1. To run the given small graph" << endl;
	cout << "2. To run the given medium graph" << endl;
	cout << "3. To run the given big graph" << endl;
	cout << "4. To run your own graph" << endl;	
}

void readAndImplement(string inputFileName, ofstream& outfile)
{

	// declaring variables 	
	ifstream infile;				// to hold the input file name
	int numberOfVertices = 0;		// variable holds the total number of vertices
	int source = 0;						// variable holds the starting vertex

	infile.open(inputFileName.c_str());		// open file

	// check if the file is valid
	if (!infile)
	{
		cout << "Wrong input file!" << endl;
		return;
	}

	infile >> numberOfVertices;		// Take the total number of vertices firstly

	//int vertex[numberOfVertices];
	int vertex, u, w;				// variable to hold the input data for vertex, neighbor, and their weight
	VertexNeighbor *neighbor;		// declare an array of class VerNeighbor, which is a linked list to hold
									// the id (vertex), its neighbors, and their weights correspondingly 
	neighbor = new VertexNeighbor[numberOfVertices];		
	
	// int index = 0;					

	// infile >> source >> u >> w; 				// take the starting vertex in firstly

	// neighbor[source].insert(source, u, w);		// verify this is the source

	while(!infile.eof())
	{
		infile >> vertex >> u >> w;					// take the regular data for the rest of the vertices
		neighbor[vertex].insert(vertex, u, w);		// id = vertex, adj = u, weight = w
	}

	// print out the neighbor tables
	for (int i = 0; i < numberOfVertices; ++i)
	{
		outfile << i << ": ";
		neighbor[i].print(outfile);
		outfile << endl;
	}


	// implement Dijkstra algorithm 
	outfile << endl;
	Dijkstra(neighbor, source, numberOfVertices, outfile);
	outfile << endl;

	infile.close();
	delete [] neighbor;
}