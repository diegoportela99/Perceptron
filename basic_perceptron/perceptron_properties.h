#ifndef PERCEPTRON_PROPERTIES_H
#define PERCEPTRON_PROPERTIES_H

#include <vector>

//Used for the maths behind the basic linearly seperable datasets, the perceptron algorithm and properties of nodes in the weighted graph
class perceptron_properties
{
public:
	//values of the graph structure nodes used for processing
	typedef struct node_value {
		unsigned int sum;

		//... all that is needed for now
	};

	perceptron_properties();
	virtual ~perceptron_properties();

protected:

	//get the sum of weighted graph (Net = [dot product of w - weight and corresponding x - input] - θ
	int weighted_sum();
	//apply the perceptron algorithm to find the weights for a dataset
	void perceptron_algorithm();
};


#endif // PERCEPTRON_PROPERTIES_H
