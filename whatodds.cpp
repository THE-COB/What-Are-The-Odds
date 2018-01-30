#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

#include "Guess.h"
#include "FSystem.h"
#include "Solver.h"
using namespace std;
using std::vector;

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

void finishGame(int answer, Guess* newG){
	int num;
	string a;
	cout<<"GO"<<endl;
	cin>>a;
	cout<<answer<<endl;
	num = stoi(a);
	newG->setNum(num);
	if(num == answer){
		cout<<"I was right!!"<<endl;
	}
	else{
		cout<<"Darn, I didn't get it"<<endl;
	}
	FSystem::writeFile(*newG, answer);
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
	Solver newSolve(goodGuesses, badGuesses, gMax);

	finishGame(newSolve.solve(), &nGuess);
}

int main(int argc, char** argv){
	if(argc>1)
		startGame(true, atoi(argv[1]));
	else
		startGame(false, 0);
	return 0;
}