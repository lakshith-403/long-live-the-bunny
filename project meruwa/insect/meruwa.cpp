#include "meruwa.h"
#include <fstream>
#include <iostream>

using namespace std;


void meruwa::move(int direction){
    switch (direction)
    {
    case 0:
        meruwa::position.first++;
        break;
    case 1:
        meruwa::position.second++;
        break;
    case 2:
        meruwa::position.first--;
        break;
    case 3:
        meruwa::position.second--;
        break;
    default:
        break;
    }
    meruwa::LightAmount += 20-(abs(meruwa::position.first-20) + abs(meruwa::position.second-20));
    meruwa::memory.push_back(direction);
}

int meruwa::think(){
    vector<double> results = meruwa::brain.feedForward((vector<double>){(double)meruwa::position.first,(double)meruwa::position.second});
    vector<int> converted;
    double MAX = -1009000.0;
    for(double r:results)
        MAX = max(r,MAX);
    for(double r:results)
        converted.push_back((int)(r==MAX));
    for(int i=0;i<4;i++)
        if(converted[i]==1)return i;
    return 0;
}

void meruwa::learnFrom(string dataset){
    meruwa::brain.trainNetwork(dataset);
}

void meruwa::saveMemory(string path){
    ofstream out(path);
    out << "topology: 2 4 4" << endl;
    pair<int,int> current = {0,0};
    for(int direction : meruwa::memory){
        out << "in: " << current.first << " " << current.second << endl;
        switch(direction){
            case 0:
                current.first++;
            break;
            case 1:
                current.second++;
            break;
            case 2:
                current.first--;
            break;
            case 3:
                current.second--;
            break;
        }
        out << "out: " << (direction==0) << " " << (direction==1) << " " << (direction==2) << " " << (direction==3) << endl;
    }
    out.flush();
    out.close();
}

