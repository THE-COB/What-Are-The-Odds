#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <algorithm>

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

vector<int> mode(vector<int> vec){
	vector<int> uVecs;
	bool isRepeat;
	for(const int& i : vec){
	    isRepeat = false;
	    for(const int& j : uVecs){
	        if(i == j){
	            isRepeat = true;
	            break;
	        }
	    }
	    if(!isRepeat){
	        uVecs.push_back(i);
	    }
	}
	vector<int> modes;
	int most = 0;
	for(const int& i : uVecs){
	    if(count(vec.begin(),vec.end(),i) > most){
	        most = count(vec.begin(),vec.end(), i);
	        modes = {i};
	    }
	    else if(count(vec.begin(),vec.end(),i) == most){
	        modes.push_back(i);
	    }
	}
	return modes;
}

void finishGame(int answer){

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
	vector<Guess> rightGuesses = FSystem::readFile(gMax);
	vector<Guess> allGuesses = FSystem::allFiles();
	vector<int> goodGuesses;
	vector<int> badGuesses;
	for(Guess& i : rightGuesses){
		goodGuesses.push_back(i.getNum());
	}
	for(Guess& i : allGuesses){
		badGuesses.push_back(i.getNum());
	}
	if(badGuesses.size()>1){

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