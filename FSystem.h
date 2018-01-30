#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Guess.h"
using namespace std;
using std::vector;
using std::string;

#ifndef FSYSTEM_H
#define FSYSTEM_H

class FSystem{
public:
	static void writeFile(Guess newGuess){
		ofstream fileObj;
		maxFile(newGuess.getMax());
		fileObj.open("GuessFiles/"+to_string(newGuess.getMax())+".dat", ios::app);
		fileObj.write((char*)&newGuess, sizeof(newGuess));
		fileObj.close();
	}
	static vector<Guess> readFile(int max){
		ifstream fileObj;
		vector<Guess> allGuesses;
		Guess tempGuess;
		fileObj.open("GuessFiles/"+to_string(max)+".dat", ios::in);
		fileObj.read((char*)&tempGuess, sizeof(tempGuess));
		while(fileObj.good()){
			allGuesses.push_back(tempGuess);
			fileObj.read((char*)&tempGuess, sizeof(tempGuess));
		}
		return allGuesses;
	}
	static vector<Guess> allFiles(){
		vector<int> allFiles = maxFile();
		vector<Guess> allGuesses;
		for(const int& i : allFiles){
			for(const Guess& j : readFile(i)){
				allGuesses.push_back(j);
			}
		}
		return allGuesses;
	}
private:
	static vector<int> maxFile(){
		ifstream fileObj;
		string tempMax;
		vector<int> maxes;
		fileObj.open("maxfile.txt");
		while(!fileObj.eof()){
			getline(fileObj, tempMax);
			try{
				maxes.push_back(stoi(tempMax));
			}catch(const exception& e){
				return maxes;
			}
		}
		return maxes;
	}
	static void maxFile(int m){
		vector<int> allMaxes = maxFile();
		for(const int& i : allMaxes){
			if(i == m){
				return;
			}
		}
		ofstream fileObj;
		fileObj.open("maxfile.txt", ios::app);
		fileObj<<m<<"\n";
	}
};

#endif