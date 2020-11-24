/*
11/21/2020 3:55pm
Lakshith Nishshanke

test program to create a genetic algorithm
*/


#include <bits/stdc++.h>

using namespace std;

#define DNALENGTH 5
#define POOLSIZE 100
#define MUTATIONPROB 2

const string target = "lakshith";

string bestsofar = "LAKSHITH";

class gene{
    public:
        string dna;

        string generateRandomGene(){
            string dna = "";
            for(int i=0;i<DNALENGTH;i++)dna += (char)('a'+(rand()%26));
            return dna;
        }

        int getFitness(){
            int r = 0;
            for(int i=0;i<DNALENGTH;i++)if(dna[i]==target[i])r++;
            return r;
        }

        void mutate(){
            for(int i=0;i<DNALENGTH;i++)if(rand()%100<MUTATIONPROB)dna[i]=(char('a'+(rand()%26)));   
        }

        gene(string in){
            dna = in;
        }

        gene(){
            dna = generateRandomGene();
        }
};

gene reproduce(gene a,gene b){
    string dna_a = a.dna;
    string dna_b = b.dna;
    string dna = "";
    for(int i=0;i<DNALENGTH;i++)
        dna += (char)(rand()%100<50?dna_a[i]:dna_b[i]);
    gene child = gene(dna);
    return child;
}

gene genePool[POOLSIZE];

map<int,int> survivalMap;
int upperBound = 0;

void generatePool(){
    for(int i=0;i<POOLSIZE;i++)
        genePool[i] = gene();
}

void calculateFitness(){
    int fitnessArray[POOLSIZE];
    fitnessArray[0] = genePool[0].getFitness();
    for(int i=1;i<POOLSIZE;i++)
        fitnessArray[i] = genePool[i].getFitness() + fitnessArray[i-1];
    for(int i=0;i<POOLSIZE;i++)
        survivalMap.insert({fitnessArray[i],i});
    upperBound = fitnessArray[POOLSIZE-1];
}

void generateNextGeneration(){
    gene nextGen[POOLSIZE];
    for(int i=0;i<POOLSIZE;i++){
        auto it = survivalMap.lower_bound(rand()%upperBound);
        int a = (*it).second;
        it = survivalMap.lower_bound(rand()%upperBound);
        int b = (*it).second;
        nextGen[i] = reproduce(genePool[a],genePool[b]);
    }
    for(int i=0;i<POOLSIZE;i++)genePool[i] = nextGen[i];  
}

pair<int,string> getBest(){
    int best = 0;
    string bestDNA = "";
    for(int i=0;i<POOLSIZE;i++)
        if(genePool[i].getFitness()>best){
            best = genePool[i].getFitness();
            bestDNA = genePool[i].dna;
        }
    return {best,bestDNA};
}

int getFitness(string a){
    int r = 0;
    for(int i=0;i<DNALENGTH;i++)if(a[i]==target[i])r++;
    return r;
}


int main(){
    srand(time(0));
    for(int i=0;i<100000;i++){
        generatePool();
        calculateFitness();
        if(i%100)continue;
        pair<int,string> best = getBest();
        if(getFitness(bestsofar)<getFitness(best.second)) bestsofar = best.second;
        cout << "generation: " << i << "\tbest fitness: " << best.first << "\tdna: " << best.second << "\n";
    }
    cout << "best so far: " << bestsofar << "\n";
}