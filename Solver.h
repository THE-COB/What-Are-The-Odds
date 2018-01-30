#include <iostream>
#include <vector>

using namespace std;
using std::vector;

#ifndef SOLVER_H
#define SOLVER_H

class Solver{
public:
	Solver(vector<int> gGuesses, vector<int> bGuesses, int m){
		goods = gGuesses;
		bads = bGuesses;
		max = m;
	}
	int solve(){
		if(bads.size()<1){
			srand(clock());
			int num = rand()%max + 1;
			return num;
		}
	}
private:
	vector<int> goods;
	vector<int> bads;
	int max;
};

#endif