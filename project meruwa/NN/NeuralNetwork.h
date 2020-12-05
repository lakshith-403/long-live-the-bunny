#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>
#include "objects/TrainingData.h"
#include "objects/Net.h"

class NeuralNetwork{
	public:

	NeuralNetwork(){
		
	}

	Net net;
	void showVectorVals(string label, vector<double> &v);
	void trainNetwork(string dataSet);
	vector<double> feedForward(vector<double> input);
};