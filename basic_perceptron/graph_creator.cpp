#include "pch.h"
#include "graph_creator.h"
#include "perceptron_properties.h"

#include <vector>
#include <iostream>

enum Node_Process {
	CREATED_NODES, STRUCTURED_GRAPH, APPLIED_ALGORITHM
};

typedef struct controlled_graph {
	//vector<int> edges; //method to remember the edges in graph
	weighted_graph<int> graph;
	std::vector<int> layers;

	unsigned int input = 2,
		output = 1;
};

Node_Process np;
controlled_graph cgraph;

graph_creator::graph_creator() {
	cgraph.layers.push_back(1);
} //constructor

graph_creator::graph_creator(const int &input, const int &output, std::vector<int> layers) {
	cgraph.layers = layers;
	cgraph.input = input;
}

void graph_creator::setup_graph() {
	setup_node_size(); //add the nodes to a graph
	structure_edges(); //structure edges to all the nodes created
}

void graph_creator::setup_node_size() {
	if (!node_setup) {
		int sum = 0;
		//get sum of nodes
		for (int i = 0; i < cgraph.layers.size(); i++) { sum = sum + cgraph.layers[i]; }
		int amount_of_nodes = cgraph.input + sum + cgraph.output;
		for (int i = 0; i < amount_of_nodes; i++) { cgraph.graph.add_vertex(i); }

		np = CREATED_NODES; //set enum to created nodes
		std::cout << "amount of nodes generated: " << amount_of_nodes << std::endl;

		node_setup = true;
	}
	else {
		std::cout << "Error. Nodes have been setup already; skipping..." << std::endl;
	}
}

bool graph_creator::single_layer() {
	if (cgraph.layers.size() <= 1) { return true; }
	return false;
}

// class that organizes the graph structure, adds the edges to the nodes and (experimental) also handles the remove of edges
class structuring {
public:
	structuring(weighted_graph<int> *g) { //pointer to memory location = &memory
		graph = g; //use graph pointer as a pointer rather than the weighted_graph parameters
	}//constructor
	
	void structure_graph() {}//applys the methods below and attaches edges to weighted graph

private:
	weighted_graph<int> *graph;
	
	std::vector<int> node_connection() {}
	
	void attach_first_layer() {} //attaches the first layer to the first layer of the hidden layer () ---> ()   () ... ()
	void attach_hidden_layer() {} //attaches the hidden layers together (feed forward) ()  () ---> ()  ()
	void attach_final_layer() {} //attaches the last hidden layer to the output
	
	//returns the bias
	int apply_bias() {return 0;}
	
	//apply weight to edges of structure
	int structure_weight() {return 0;}
};

void graph_creator::structure_edges() {
	//structure_test_method();
	structuring s = structuring(&(cgraph.graph)); //passes the graph memory location to class

}

class testing_methods{
public:
	//Testing method
	void dft_graph() {
		std::vector<int> glist = cgraph.graph.depth_first(0);
		for (int i = 0; i < glist.size(); i++) { std::cout << glist[i] << std::endl; }
	}

	void structure_test() {
		//TEST METHOD
		cgraph.graph.add_edge(0, 2, 1);
		cgraph.graph.add_edge(1, 2, 1);
		cgraph.graph.add_edge(0, 3, 1);
		cgraph.graph.add_edge(1, 3, 1);
		//    cgraph.graph.add_edge(2,4,1);
		//    cgraph.graph.add_edge(3,4,1);
		std::cout << std::endl;
		cgraph.graph.remove_edge(0, 2);
		cgraph.graph.remove_edge(1, 2);
		cgraph.graph.remove_edge(0, 3);
		cgraph.graph.remove_edge(1, 3);
		//    cgraph.graph.remove_edge(2,4);
		//    cgraph.graph.remove_edge(3,4);
	}

	void current_process() {
		switch (np) {
		case CREATED_NODES:
			std::cout << "Nodes have been generated, no connected edges to nodes in data structure" << std::endl;
			break;
		case STRUCTURED_GRAPH:
			std::cout << "Feed-Forward connection applied to nodes of data structure" << std::endl;
			break;
		case APPLIED_ALGORITHM:
			std::cout << "Algorithm has been applied to the data structure, perceptron should of separated the linearly separable dataset" << std::endl;
			break;
		}
	}
};

//sample method for connecting nodes together
void graph_creator::structure_test() {
	testing_methods tm;
	tm.structure_test();
}

//cout of current graph (dft)
void graph_creator::dft_graph() {
	testing_methods tm;
	tm.dft_graph();
}

//prints the current process
void graph_creator::current_process() {
	testing_methods tm;
	tm.current_process();
}

