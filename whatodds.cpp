#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <fstream>

#include "Guess.h"
#include "FSystem.h"
using namespace std;
using std::vector;

class Rand{
public:
	static int randInt(int highest){
		srand(time(NULL)+counter);
		int num = rand()%highest+1;
		counter++;
		return num;
	}
private:
	static int counter;
};

vector<int> mode(vector<int> nums){
	vector<int> temp = nums;
	vector<int>::iterator it;
	it = unique(temp.begin(), temp.end());
	temp.resize(distance(temp.begin(), it));
	int biggest = temp[0];
	for(int i = 1; i<temp.size(); i++){
		if(count(nums.begin(), nums.end(), temp[i]) > count(nums.begin(),nums.end(),biggest)){
			biggest = temp[i];
		}		
	}
	return {biggest, count(nums.begin(), nums.end(), biggest)};
}

vector<int> vecMode(vector<int> nums){
	vector<int> modes;
	vector<int> currMode = mode(nums);
	vector<int> nMode = currMode;
	do{
		modes.push_back(nMode[0]);
		for(int i = 0; i<nums.size(); i++){
			if(i == currMode[0]){
				nums.erase(nums.begin()+i);
			}
		}
		nMode = mode(nums);
	} while(nMode[1]==currMode[1]);

	return mode;
}

void startGame(bool arg, int m){
	int gMax;
	if(arg){
		gMax = m;
	}
	else{
		cout<<"Max?"<<endl;
		cin>>gMax;
	}
	int guess;
	Guess nGuess = Guess(gMax);
	vector<Guess> rightGuesses = readFile(gMax);
	vector<int> possGuesses;
	if(rightGuesses.size() > 0){
		for(const Guess& i : rightGuesses){
			possGesses.push_back(i.getNum());
		}
	}
}

int Rand::counter = 0;
int main(int argc, char** argv){
	if(argc>1)
		startGame(true, atoi(argv[1]));
	else
		startGame(false, 0);
	return 0;
}