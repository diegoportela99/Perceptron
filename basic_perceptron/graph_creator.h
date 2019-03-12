#ifndef GRAPH_CREATOR_H
#define GRAPH_CREATOR_H
#include "weighted_graph.h"
#include "perceptron_properties.h"

#include <vector>

class graph_creator : public perceptron_properties
{
public:
	graph_creator(); //default properties, layer = 1, input = 2, output = 1
	graph_creator(const int &input, const int &output, std::vector<int> layers);

	void setup_graph();
	

	//testing methods
	void dft_graph();
	void current_process();
	void structure_test();

private:
	bool node_setup = false;

	bool single_layer(); //returns a bool if there is only one layer of the graph network
	void setup_node_size();
	void structure_edges();
};

#endif // GRAPH_CREATOR_H

