#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <time.h>

using namespace std;

class Domino{
	private: 
		string top;
		string bottom;
		bool valid;
	public:
		Domino(string top, string bottom){this->top=top; this->bottom=bottom; this->valid=true;};
		Domino(){this->valid=false;};
		string getTop() const {if(this->valid) return this->top; return "BAD";};
		string getBottom() const {if(this->valid) return this->bottom; return "BAD";};
		void print() const {cout << "[" << this->top << "/" << this->bottom << "] ";};
};

int main(){
	vector<Domino> dominoes = vector<Domino>();
	bool cont = true;
	string phrase = "end";
	do{
		cout << "Input Dominoes: \"" << phrase << "\" to quit\nInput top:" << endl;
		string top = "";
		cin >> top;
		if(top.compare(phrase)==0){
			cont = false;
			break;
		}
		cout << "Input bottom:" << endl;
		string bottom = "";
		cin >> bottom;
		if(bottom.compare(phrase)==0){
			cont = false;
			break;
		}
		dominoes.push_back(*(new Domino(top, bottom)));
		for(unsigned int i=0; i<dominoes.size(); i++){
			cout << i << ":";
			dominoes[i+1].print();
		}
		cout << endl;
	} while (cont);
	cout << endl;
	cont = true;
	dominoes.shrink_to_fit();
	string top = "";
	string bottom = "";
	phrase = "exit";
	string reset = "reset";
	string str = "";
	do{
		cout << endl;
		cout << "{";
		for(unsigned int i=0; i<dominoes.size(); i++){
			cout << i << ":";
			dominoes[i+1].print();
		}
		cout << "}" << endl;
		cout << "Add Domino by number-- \"" << reset << "\" to reset -- \"" << phrase << "\" to exit\n" << top << "\n" << bottom << endl;
		str = "";
		cin >> str;
		if(str.compare(phrase)==0){
			cont = false;
			break;
		} else if(str.compare(reset)==0){
			top = "";
			bottom = "";
			cout << "Reset top and bottom" << endl;
		} else {
			unsigned int num = atoi(str.c_str());
			top = top + dominoes[num-1].getTop();
			bottom = bottom + dominoes[num-1].getBottom();
		}
	} while (cont);
	
	for(unsigned int i=0; i<dominoes.size(); i++){
		delete &(dominoes[i]);
	}
	return 0;
}