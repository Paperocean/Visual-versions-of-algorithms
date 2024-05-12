#ifndef LISTADJACENCY_H
#define LISTADJACENCY_H

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
Is it a table of linked lists?
- Yes, it is a table of linked lists

And how it works?
- The table is an array of linked lists
- The size of the table is the number of vertices
- The table is initialized with nullptrs
- If there is an edge between vertex i and vertex j, then the linked list at index i contains the vertex j
- If there is no edge between vertex i and vertex j, then the linked list at index i does not contain the vertex j

Example:
- Let's say we have 4 vertices
- The table is an array of linked lists
- The table is initialized with nullptrs
- If there is an edge between vertex 0 and vertex 1, then the linked list at index 0 contains the vertex 1
- If there is no edge between vertex 0 and vertex 1, then the linked list at index 0 does not contain the vertex 1
- If there is an edge between vertex 1 and vertex 2, then the linked list at index 1 contains the vertex 2


Is it better than matrix adjacency? Why?
- It depends on the problem
- If the graph is sparse, then list adjacency is better | what mean sparse? | sparse means that the number of edges is less than the number of vertices
- If the graph is dense, then matrix adjacency is better | what mean dense? | dense means that the number of edges is greater than the number of vertices
*/

class ListAdjacency {
private:
	pair<int,int>** list;
	int V;
	string* vertexLabels;

public:
	ListAdjacency(int size);
	~ListAdjacency();
	void addEdge(int i, int j, int w);
	void removeEdge(int i, int j);
	int getWeight(int i, int j);
	void printList();
	string* getVertexLabel();
	void setVertexLabel(int vertex, string vertexLabel);
	vector<int> adjacentNodes(int node);
	int getV();
	vector<int> dijkstra(int start, int end);
};

#endif // !LISTADJACENCY_H