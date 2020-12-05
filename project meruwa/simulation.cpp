#include <bits/stdc++.h>
#include "insect/meruwa.h"
#include <time.h>

#define POOLSIZE 100
#define LIFETIME 20
#define GENERATIONS 10

using namespace std;

meruwa genePool[POOLSIZE];

void generateRandomPool(){
    for(int i=0;i<POOLSIZE;i++){
        meruwa m;
        m.position = {0,0};
        m.LightAmount = 0;
        genePool[i] = m;
    }
}

bool comp(meruwa m1,meruwa m2){
    return m1.LightAmount > m2.LightAmount;
}

int main(){
    srand(time(0));
    generateRandomPool();
    
    for(int gen=0;gen<GENERATIONS;gen++){
        int best = 0;
        //sorting genes in the order of fitness
        sort(genePool,genePool+POOLSIZE,comp);
        best = genePool[0].LightAmount;
        cout << "saving memory ...";
        //saving memory
        for(int gene=0;gene<POOLSIZE;gene++){
            genePool[gene].saveMemory("memory/"+to_string(gene)+".data");
        }
        cout << "\tdone\n";
        cout << "\nbest fitness : " << best << "\n\n";
        cout << "generation: " << gen+1 << "\n";
        //creating random generation of offsprings
        generateRandomPool();
        cout << "Learning ...\n";
        //teaching them from best (1/10)th of ancesstors
        for(int gene=0;gene<POOLSIZE;gene++){
            int ancesstor = rand()%(POOLSIZE);
            genePool[gene].learnFrom("memory/"+to_string(ancesstor)+".data");
        }
        cout << "done\n";
        //simulating the lifetime
        cout << "simulating ...";
        for(int i=0;i<LIFETIME;i++){
            for(int gene=0;gene<POOLSIZE;gene++){
                int direction = genePool[gene].think();
                genePool[gene].move(direction);
            }
        }
        cout << "\tdone\n";
    }
}