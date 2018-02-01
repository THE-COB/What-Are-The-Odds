#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

#include "Guess.h"
using namespace std;
using std::vector;

#ifndef SOLVER_H
#define SOLVER_H

struct GuessData{
	int num;
	int score;
};
enum ScoreType{
	Good = 10,
	Bad = 5,
	Mode = 15,
	Mode2 = 10,
	BadProx = 4
};

class Solver{
public:
	Solver(vector<Guess> aGuesses, int m){
		gBois = aGuesses;
		for(Guess& i : gBois){
			if(i.getMax() != m){
				soloBads.push_back(i);
			}
		}
		max = m;
	}
	int solve(){
		srand(clock());
		if(gBois.size()<1){
			int finNum = rand()%max + 1;
			return finNum;
		}
		else{
			filler();
		}
		vector<int> allChoices;
		for(int i = 1; i<=max; i++){
			if(find(possInts.begin(), possInts.end(), i) == possInts.end()){
				GuessData newData;
				newData.num = i;
				newData.score = 1;
				finGuesses.push_back(newData);
			}
		}
		for(GuessData& i : finGuesses){
			for(int j = 0; j<max*i.score; j++){
				allChoices.push_back(i.num);
			}
		}
		int finInd = rand()%allChoices.size();
		int finNum = allChoices[finInd];
		return finNum;
	}
private:
	vector<Guess> gBois;
	vector<Guess> soloBads;
	vector<Guess> possGuesses;
	vector<int> possInts;
	vector<int> mode;
	vector<int> mode2;
	vector<GuessData> finGuesses;
	int max;

	vector<int> getMode(vector<int> vec, int modeNum){
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
		if(modeNum == 0){
			return modes;
		}
		else{
		    vector<int>::iterator it = find(vec.begin(), vec.end(), modes[0]);
		    for(int i = 0; i<modes.size(); i++){
				while(it != vec.end()){
	                vec.erase(vec.begin()+distance(vec.begin(),it));
	                it = find(vec.begin(), vec.end(), modes[i]);
				}
				it = find(vec.begin(), vec.end(), modes[i+1]);
			}
			return getMode(vec, modeNum-1);
		}
	}

	bool hasProx(Guess g){
		int range = max*0.1;
		if(g.getMax() >= max-range || g.getMax() <= max+range){
			return true;
		}
		return false;
	}

	int getScore(Guess g){
		int score = 1;
		if(g.getMax() == max){
			score=Good;
		}
		if(find(soloBads.begin(), soloBads.end(), g) != soloBads.end()){
			score=Bad;
			if(hasProx(g)){
				score+=BadProx;
			}
		}
		int gNum = g.getNum();
		if(find(mode.begin(), mode.end(), gNum) != mode.end()){
			score+=Mode;
		}
		if(find(mode2.begin(), mode2.end(), gNum) != mode2.end()){
			score+=Mode2;
		}
		return score;
	}

	void filler(){
		for(Guess& i : gBois){
			if(i.getNum()<=max){
				possGuesses.push_back(i);
			}
		}
		for(Guess& i : possGuesses){
			possInts.push_back(i.getNum());
		}
		mode = getMode(possInts, 0);
		mode2 = getMode(possInts, 1);
		finGuesses.resize(possGuesses.size());
		for(int i = 0; i<finGuesses.size(); i++){
			finGuesses[i].num = possGuesses[i].getNum();
			finGuesses[i].score = getScore(possGuesses[i]);
		}
		for(int i = 0; i<finGuesses.size(); i++){
			vector<int>::iterator it = find(possInts.begin(), possInts.begin()+i, finGuesses[i].num);
			if(it != possInts.end()){
				int d = distance(possInts.begin(), it);
				if(finGuesses[i].score != finGuesses[d].score){
					finGuesses[i].score+=finGuesses[d].score;
				}
				finGuesses.erase(finGuesses.begin()+d);
				possInts.erase(possInts.begin()+d);
			}
		}
	}

};

#endif