#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <iostream>

#include <vector>
#include <queue>

template <typename vertex>
class weighted_graph
{
public:

	typedef struct VertexC {
		vertex weight;
		vertex memCurrent; //the distance from start of Vertex ( the Vertex vector )
		vertex memNext; //the distance from the start of Vertex ( the Vertex vector )
		weighted_graph::VertexC *ptr_location;
	};

	std::vector<vertex> Vertex;
	std::vector<VertexC> Edge;

	std::vector<vertex> dft;
	std::vector<vertex> bft;
	std::queue<vertex> bftQueue;


	// CHECK TO SEE IF VERTEX HAS BEEN MARKED OR NOT (if it exists)
	bool marked(vertex vertexMarked, int g);


	bool are_adjacent(const vertex&, const vertex&) const; //Returns true if the two vertices are
														   //adjacent, false otherwise.
	bool has_vertex(const vertex&) const; //Returns true if the passed in vertex is
										  //a vertex of the graph, false otherwise.

	void add_vertex(const vertex&); //Adds the passed in vertex to the graph (with no edges).
	void add_edge(const vertex&, const vertex&, const int&); //Adds an edge between the two vertices
															 //with the given weight (as an int).

	void remove_vertex(const vertex&); //Removes the given vertex. Should also clear any incident edges.
	void remove_edge(const vertex&, const vertex&); //Removes the edge between the two vertices, if it exists.
	void set_edge_weight(const vertex&, const vertex&, const int&); //Changes the edge weight between the two
																	//vertices to the new weight (the int).

	int get_edge_weight(const vertex&, const vertex&) const; //Returns the weight on the edge between the two vertices.
	int degree(const vertex&) const; //Returns the degree of the vertex.
	int weighted_degree(const vertex&); //Returns the sum of the weights on all the edges incident to the vertex.
	int num_vertices() const; //Returns the total number of vertices in the graph.
	int num_edges() const; //Returns the total number of edges in the graph (just the count, not the weight).
	int total_weight(); //Returns the sum of all the edge weights in the graph.

	std::vector<vertex> get_vertices(); //Returns a vector containing all the vertices.
	std::vector<vertex> get_neighbours(const vertex&); //Returns a vector containing the neighbours of the given vertex.

	//graph_iterator begin(); //Returns a graph_iterator pointing to the start of the vertex set.
	//#graph_iterator end(); //Returns a graph_iterator pointing to one-past-the-end of the vertex set.

	//neighbour_iterator neighbours_begin(const vertex&); //Returns a neighbour_iterator pointing to the start
														//of the neighbour set for the given vertex.
	//neighbour_iterator neighbours_end(const vertex&); //Returns a neighbour_iterator pointing to one-past-the-end
													  //of the neighbour set for the given vertex.

	std::vector<vertex> depth_first(const vertex&); //Returns the vertices of the graph in the order they
													//are visited in by a depth-first traversal starting at
													//the given vertex.
	std::vector<vertex> breadth_first(const vertex&); //Returns the vertices of the graph in the order they
													  //are visisted in by a breadth-first traversal starting
													  //at the given vertex.

	//weighted_graph<vertex> mst(); //Returns a minimum spanning tree of the graph.

};

template <typename vertex>
bool weighted_graph<vertex>::marked(vertex vertexMarked, int g) {
	switch (g) {
	case 0: // for the dft
		for (int i = 0; i < dft.size(); i++) {
			if (dft[i] == vertexMarked) {
				return true;
			}
		}
		return false;
		break;

	case 1: // for the bft
		for (int i = 0; i < bft.size(); i++) {
			if (bft[i] == vertexMarked) {
				return true;
			}
		}
		return false;
		break;
	}
}

template <typename vertex> bool weighted_graph<vertex>::has_vertex(const vertex& u) const {

	for (int i = 0; i < Vertex.size(); i++) {
		if (Vertex[i] == u) {
			return true;
		}
	}
	return false;
}

template <typename vertex> bool weighted_graph<vertex>::are_adjacent(const vertex& u, const vertex& v) const {

	for (int i = 0; i < Edge.size(); i++) {
		if (Edge[i].memCurrent == u && Edge[i].memNext == v) {
			return true;
		}
		if (Edge[i].memCurrent == v && Edge[i].memNext == u) {
			return true;
		}
	}

	return false;
}

template <typename vertex> void weighted_graph<vertex>::add_vertex(const vertex& v) {
	Vertex.push_back(v);
}

template <typename vertex> void weighted_graph<vertex>::add_edge(const vertex& u, const vertex& v, const int& weight) {
	VertexC *n = new VertexC(); //create new struct object
	n->weight = weight; //pass weight

	if (Vertex.size() > 1) { // as long as there are more than vertex
		for (int i = 0; i <= Vertex.size(); i++) {
			if (Vertex[i] == u) {
				n->memCurrent = Vertex[i]; // add current vertex
				n->ptr_location = n;
			}
			if (Vertex[i] == v) {
				n->memNext = Vertex[i];  // add next vertex
				n->ptr_location = n;
			}
		}
		//dynamically set deref pointer of struct
		Edge.push_back(*n);
	}
}

template <typename vertex> void weighted_graph<vertex>::remove_vertex(const vertex& u) {
	for (int i = 0; i < Vertex.size(); i++) {
		if (Vertex[i] == u) {
			Vertex.erase(Vertex.begin() + i);
		}
	}
}


template <typename vertex> void weighted_graph<vertex>::remove_edge(const vertex& u, const vertex& v) {
	for (int i = 0; i < Edge.size(); i++) {
		if (Edge[i].memCurrent == u && Edge[i].memNext == v) {
			//std::cout << Edge[i].ptr_location << std::endl; //Printing pointer location (for testing)
			delete Edge[i].ptr_location;
			Edge.erase(Edge.begin() + i);
		}
		else if (Edge[i].memCurrent == v && Edge[i].memNext == u) {
			//std::cout << Edge[i].ptr_location << std::endl; //Printing pointer location (for testing)
			delete Edge[i].ptr_location;
			Edge.erase(Edge.begin() + i);
		}
	}
}


template <typename vertex> void weighted_graph<vertex>::set_edge_weight(const vertex& u, const vertex& v, const int& weight) {
	for (int i = 0; i < Edge.size(); i++) {
		if (Edge[i].memCurrent == u && Edge[i].memNext == v) {
			Edge[i].weight = weight;
		}
	}
}

template <typename vertex> int weighted_graph<vertex>::get_edge_weight(const vertex& u, const vertex& v) const {
	for (int i = 0; i < Edge.size(); i++) {
		if (Edge[i].memCurrent == u && Edge[i].memNext == v) {
			return Edge[i].weight;
		}
		if (Edge[i].memCurrent == v && Edge[i].memNext == u) {
			return Edge[i].weight;
		}
	}
	return 0;
}

template <typename vertex> int weighted_graph<vertex>::degree(const vertex& u) const {
	int degree = 0;
	for (int i = 0; i < Vertex.size(); i++) {
		if (Vertex[i] == u) {
			for (int n = 0; n < Edge.size(); n++) {
				if (Edge[n].memCurrent == Vertex[i] || Edge[n].memNext == Vertex[i]) {
					degree++;
				}
			}
		}
	}
	return degree;
}

template <typename vertex> int weighted_graph<vertex>::weighted_degree(const vertex& u) {
	int degreeWeight = 0;
	for (int i = 0; i < Vertex.size(); i++) {
		if (Vertex[i] == u) {
			for (int n = 0; n < Edge.size(); n++) {
				if (Edge[n].memCurrent == Vertex[i] || Edge[n].memNext == Vertex[i]) {
					degreeWeight += Edge[n].weight;
				}
			}
		}
	}
	return degreeWeight;
}

template <typename vertex> int weighted_graph<vertex>::num_vertices() const {
	return Vertex.size();
}

template <typename vertex> int weighted_graph<vertex>::num_edges() const {
	return Edge.size();
}

template <typename vertex> int weighted_graph<vertex>::total_weight() {
	int total = 0;

	for (int i = 0; i < Edge.size(); i++) {
		total += Edge[i].weight;
	}

	return total;
}

template <typename vertex>	std::vector<vertex> weighted_graph<vertex>::get_vertices() {
	return Vertex;
}

template <typename vertex>	std::vector<vertex> weighted_graph<vertex>::get_neighbours(const vertex& u) {
	std::vector<int> neighbours;

	for (int i = 0; i < Vertex.size(); i++) { //for all the vertecies
		if (Vertex[i] == u) { //if the target vertex is found ( u )
			for (int n = 0; n < Edge.size(); n++) { //search all the edges with that vertex
				if (Edge[n].memCurrent == Vertex[i]) { // if the edges current is = to vertex
					neighbours.push_back(Edge[n].memNext); //push back the opposite vertex of that edge i.e (a) -------- (b), if (a) is found then neighbour is (b).
				}
				if (Edge[n].memNext == Vertex[i]) { // if the edges next is = to vertex
					neighbours.push_back(Edge[n].memCurrent); //push back the opposite vertex of that edge i.e (b) -------- (a), if (b) is found then neighbour is (a).
				}
			}
		}
	}

	return neighbours; //return the list of all neighbouring vertecies
}

template <typename vertex> std::vector<vertex> weighted_graph<vertex>::depth_first(const vertex& start_vertex) {
	std::vector<vertex> neighbours = get_neighbours(start_vertex); //create a list of all neighbouring vertecies
	dft.push_back(start_vertex); //push back current vertex

	for (int i = 0; i < neighbours.size(); i++) { //for all the neighbours of this vertex
		if (!marked(neighbours[i], 0)) { // if the vertex is not marked
			depth_first(neighbours[i]); // recursively move through all neighbouring vertices
		}
	}

	return dft; //return the list
}

template <typename vertex> std::vector<vertex> weighted_graph<vertex>::breadth_first(const vertex& start_vertex) {

	bftQueue.push(start_vertex);

	while (!bftQueue.empty()) {
		vertex u = bftQueue.front();
		bftQueue.pop();
		std::vector<vertex> neighbours = get_neighbours(u); //create a list of all neighbouring vertecies

		if (!marked(u, 1)) {
			bft.push_back(u);
			for (int i = 0; i < neighbours.size(); i++) {
				bftQueue.push(neighbours[i]);
			}
		}
	}

	return bft;
}

#endif // GRAPH_H


