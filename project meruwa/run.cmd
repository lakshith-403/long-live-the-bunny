g++ -c NN/objects/Neuron.cpp -o bin/Neuron.o
g++ -c NN/objects/Net.cpp -o bin/Net.o
g++ -c NN/objects/TrainingData.cpp -o bin/TrainingData.o
g++ -c NN/NeuralNetwork.cpp -o bin/NeuralNetwork.o
g++ -c insect/meruwa.cpp -o bin/meruwa.o
g++ -c simulation.cpp -o bin/simulation.o
g++ bin/Neuron.o bin/Net.o bin/TrainingData.o bin/NeuralNetwork.o bin/meruwa.o bin/simulation.o -o main.exe
main.exe