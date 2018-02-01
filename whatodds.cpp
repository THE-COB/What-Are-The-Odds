#include <iostream>
#include <vector>
#include <algorithm>

#include "Guess.h"
#include "FSystem.h"
#include "Solver.h"
using namespace std;
using std::vector;

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

	Solver newSolve(allGuesses, gMax);
	finishGame(newSolve.solve(), &nGuess);
}

int main(int argc, char** argv){
	if(argc>1)
		startGame(true, atoi(argv[1]));
	else
		startGame(false, 0);
	return 0;
}