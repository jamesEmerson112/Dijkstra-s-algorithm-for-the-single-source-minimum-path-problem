//************************************************************
//
// An Thien Vo
// CS 302, Dr. Larmore 
// Assginment #7
//
//************************************************************

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct linkedlist
{
	int id;
	int neighbor;
	int weight;
	linkedlist *next;
};

class VertexNeighbor
{
private:
	linkedlist* head;
	int length;
public:
	// Constructor will initialize all of the members of the struct
	VertexNeighbor()
	{
		head = new linkedlist;   // creating a new struct pointer type
		head->id = -1;
		head->neighbor = 0;
		head->weight = 0;
		head->next = NULL;
		length = 0;
	};

	// Deconstructor will remove the class once it is done for the program	
	~VertexNeighbor()
	{
		linkedlist *current = head;
		while (current != NULL)
		{
			linkedlist* next = current->next;
			delete current;
			current = next;
		}
	};

	//******************************************************
	// void function insert will create a new node
	// and insert it into the linkedlist head
	// Condition: the vertex, its neighbors, their weights for each neighbor
	void insert(int i, int n, int w)
	{
		linkedlist *newNeighbor = new linkedlist;
		newNeighbor->id = i;
		newNeighbor->neighbor = n;
		newNeighbor->weight = w;
		newNeighbor->next = NULL;

		if(empty())
		{
			head = newNeighbor;
			length++;
			return;
		}

		newNeighbor->next = head;
		head = newNeighbor;
		length++;

	};

	// bool function empty() will check if the class (the linked list)
	// is empty
	bool empty()
	{
		if (length == 0)
			return true;
		return false;
	};

	// void function print will be use to print out:
	// the current vertex, its neighbor and their weight correspondingly
	void print(ofstream& outfile)
	{
		if (empty())
			return;
		else
		{
			linkedlist *current = head;
			while(current != NULL)
			{
				outfile << "(" << current->neighbor << "," << current->weight << ")  ";
				current = current->next;
			}
		}
	};

	// int function getID() will return the current vertex that a class vertex holds
	int getID()
	{
		return head->id;
	};

	// int function getLength() will return the number of neighbors belongng to its vertex
	int getLength()
	{
		return length;
	};

	// void function relax implements the relaxation function where
	// the distance between the starting vertex and the neighbor of the chosen vertex
	// should be less or equal the sum of the distance between the starting vertex
	// and the chosen vertex and the distance of the chosen vertex and its neighbors.
	// else the sum will be the distance between the starting vertex and the neighbor
	// of the chosen vertex
	// Condition: the array distance of each vertex, 
	//			  the array of the previousv vertex that a vertex 
	//					roots from the starting vertex to itself
	//			  and the starting vertex
	// Postcondition: compute the distance of the chosen vertex
	void relax(int* d, vector<int> *prev, int startingVertex)
	//void relax(int* d)
	{
		linkedlist *current = head;
		while(current)
		{
			if (d[current->neighbor] > d[current->id] + current->weight)
			{
				d[current->neighbor] = d[current->id] + current->weight;
				prev[current->neighbor].push_back(current->id);
						
				if (prev[current->neighbor][0] != prev[startingVertex][0])  // if the current u is not the
															   // starting vertex
				// then insert a bunch of vertex until it meets 0
				{
					inheritPrevVector(current, prev, startingVertex);
				}	
			}
			current = current->next;
		}
	}
	
protected:
	// void recursive function inheritPrevVector is used to update the 
	// the previous vertices that a vertex roots from the starting
	// vertex to itself because the relax void function tends to
	// only update the closest previous vertex that stands before the chose
	// one. 
	// Condition:	linkedlist the current linked list
	//				the array of the previous vertices
	// 				the starting vertex, used to compare if 
	//					the void function manages to track to the root
	//					of the vertex
	// Postcondition: find the track of previous vertices belonging to the chosen vertex.
	void inheritPrevVector(linkedlist* current, vector<int> *prev, int startingVertex)
	{
		int temp = prev[current->neighbor][0];						// LARMORE

		for (int i = prev[temp].size()-1; i >= 0; --i)
		{
			prev[current->neighbor].insert(prev[current->neighbor].begin(), prev[temp][i]);
		}
		if (prev[current->neighbor][0] != prev[startingVertex][0])
			inheritPrevVector(current, prev, startingVertex);
		else
			return;
	}
};

#endif 