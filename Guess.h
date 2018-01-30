#include <iostream>
#include <vector>

using namespace std;
using std::vector;

#ifndef GUESS_H
#define GUESS_H

class Guess{
public:
	Guess(int m){
		max = m;
	}
	void setNum(int n){
		num = n;
	}
	bool isFull(){
		if(max != -1 && num != -1){
			return true;
		}
		return false;
	}
	int getMax(){
		return max;
	}
	int getNum(){
		return num;
	}
private:
	int max = -1;
	int num = -1;
};

#endif