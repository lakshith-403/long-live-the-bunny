#include <fstream>
#include <iostream>
#include <vector>
#include "E:\!Lakshith\Projects\project meruwa\NN\NeuralNetwork.h"

using namespace std;

class meruwa{
    public:

    meruwa(){
        LightAmount = 0;
    }
    
    NeuralNetwork brain;
    vector<int> memory;

    pair<int,int> position;
    int LightAmount;

    void saveMemory(string path);
    void learnFrom(string dataset);
    int think();
    
    void move(int direction);
};