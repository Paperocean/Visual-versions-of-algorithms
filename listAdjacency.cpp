#include "listAdjacency.h"

	ListAdjacency::ListAdjacency(int vNum) : V(vNum) {
		list = new pair<int, int>* [V];
		for (int i = 0; i < V; i++) {
			list[i] = new pair<int, int>[V];
			for (int j = 0; j < V; j++) {
				list[i][j] = make_pair(-1, -1);
			}
		}
		vertexLabels = new string[V];
	}

	ListAdjacency::~ListAdjacency() {
		for (int i = 0; i < V; i++) {
			delete[] list[i];
		}
		delete[] list;
	}

	int ListAdjacency::getV() {
		return V;
	}

	void ListAdjacency::addEdge(int i, int j, int w) {
		list[i][j] = make_pair(j, w);
		list[j][i] = make_pair(i, w);
	}

	void ListAdjacency::removeEdge(int i, int j) {
		list[i][j] = make_pair(-1, -1);
	}

	int ListAdjacency::getWeight(int i, int j)
	{
		if (list[i][j].first != -1)
			return list[i][j].second;
	}

	void ListAdjacency::printList()
	{
		cout << "List Adjacency: " << endl;
		for (int i = 0; i < V; i++) {
			cout << "Vertex " << i << ": ";
			for (int j = 0; j < V; j++) {
				const auto& neighbor = list[i][j];
				// where neighbor first is the vertex and neighbor second is the weight
				if (neighbor.first != -1) {
					cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	string* ListAdjacency::getVertexLabel() {
		return vertexLabels;
	}

	void ListAdjacency::setVertexLabel(int vertex, string vertexLabel)
	{
		vertexLabels[vertex] = vertexLabel;
	}

	vector<int> ListAdjacency::adjacentNodes(int i)
	{
		vector<int> adjNodes(V);
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				const auto& neighbor = list[i][j];
				if (neighbor.first != -1) {
					adjNodes[j] = neighbor.first;
				}
			}
		}
		return adjNodes;
	}

	vector<int> ListAdjacency::dijkstra(int start, int end) {
		// Create a priority queue to store vertices
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
		// Create a vector to store the distance from the start vertex to all other vertices
		vector<int> dist(V, INT_MAX);
		// Set the distance from the start vertex to itself to 0
		dist[start] = 0;
		// Insert the start vertex into the priority queue
		pq.push(make_pair(0, start));
		// While the priority queue is not empty
		while (!pq.empty()) {
			// Get the vertex with the smallest distance from the priority queue
			int u = pq.top().second;
			pq.pop();
			// For each neighbor of the vertex
			for (int i = 0; i < V; i++) {
				// If there is an edge between the vertex and its neighbor
				if (list[u][i].first != -1) {
					// Get the neighbor
					int v = list[u][i].first;
					// Get the weight of the edge between the vertex and its neighbor
					int weight = list[u][i].second;
					// If the distance from the start vertex to the neighbor is greater than the distance from the start vertex to the vertex plus the weight of the edge between the vertex and its neighbor
					if (dist[v] > dist[u] + weight) {
						// Update the distance from the start vertex to the neighbor
						dist[v] = dist[u] + weight;
						// Insert the neighbor into the priority queue
						pq.push(make_pair(dist[v], v));
					}
				}
			}
		}
		// Return the distance from the start vertex to the end vertex
		
		//cout << "The shortest path from vertex " << start << " to vertex " << end << " is " << dist[end] << endl;
		int value = dist[end];

		vector<pair<int, int>> vertexDist(V);
		for (int i = 0; i < V; i++) {
			vertexDist[i] = make_pair(i, dist[i]);
		}

		sort(vertexDist.begin(), vertexDist.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
			return a.second < b.second;
		});

		/*cout << "Distances" << endl;
		for (int i = 1; i < 6; i++) {
			cout << "Vertex " << vertexDist[i].first << ": ";
			vertexDist[i].second == INT_MAX ? cout << "INF" << " " : cout << vertexDist[i].second << " ";
			cout << endl;
		}
		cout << endl;*/

		return dist;
	}

	// What do dijkstra algorithm?
	// 1. Sort the vertices by their distance from the start vertex
	// 2. Initialize the distance from the start vertex to all other vertices to infinity
	// What also can be done?
