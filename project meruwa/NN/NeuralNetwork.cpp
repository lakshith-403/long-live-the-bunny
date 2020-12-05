#include "NeuralNetwork.h"

using namespace std;

void NeuralNetwork::showVectorVals(string label, vector<double> &v)
{
	cout << label << " ";
	for(unsigned i = 0; i < v.size(); ++i)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

vector<double> NeuralNetwork::feedForward(vector<double> input){
	vector<double> result;
	net.feedForward(input);
	net.getResults(result);
	return result;
}

void NeuralNetwork::trainNetwork(string dataSet)
{
	TrainingData trainData(dataSet);
    
	vector<unsigned> topology;

	trainData.getTopology(topology);
	Net myNet(topology);

	vector<double> inputVals, targetVals, resultVals;
	int trainingPass = 0;
	// cout << "training neural Network \n";
	while(!trainData.isEof())
	{
		++trainingPass;
		
		// cout << endl << "Pass" << trainingPass << "\n";

		// Get new input data and feed it forward:
		if(trainData.getNextInputs(inputVals) != topology[0])
			break;
		// showVectorVals("Inputs :", inputVals);
		myNet.feedForward(inputVals);

		// Collect the net's actual results:
		myNet.getResults(resultVals);
		// cout << "Outputs: ";
		
		// showVectorVals("Outputs:", resultVals);

		// Train the net what the outputs should have been:
		trainData.getTargetOutputs(targetVals);
		// showVectorVals("Targets:", targetVals);
		
		assert(targetVals.size() == topology.back());

		myNet.backProp(targetVals);

		// Report how well the training is working, average over recnet
		// cout << "Net recent average error: "
		    //  << myNet.getRecentAverageError() << endl;
	}
	net = myNet;
	// cout << "Network succesfully trained" << endl;
	cout << ".";

}
