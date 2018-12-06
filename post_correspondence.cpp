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
		Domino(string t, string b){this->top=t; this->bottom=b; this->valid=true;};
		Domino(){this->valid=false;};
		string getTop() const {if(this->valid) return this->top; return "BAD";};
		string getBottom() const {if(this->valid) return this->bottom; return "BAD";};
		void print() const {if(this->valid )cout << "[" << this->top << "/" << this->bottom << "] "; else cout << "[INVALID]";};
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
		dominoes.push_back(Domino(top, bottom));
		for(unsigned int i=0; i<dominoes.size(); i++){
			cout << i+1 << ":";
			dominoes[i].print();
		}
		cout << endl;
	} while (cont);
	cout << endl;
	cont = true;
	dominoes.shrink_to_fit();
	string top = "";
	string bottom = "";
	vector<unsigned int> order = vector<unsigned int>();
	phrase = "exit";
	string reset = "reset";
	string str = "";
	do{
		cout << endl;
		cout << "{";
		top = "";
		bottom = "";
		for(unsigned int i=0; i<order.size(); i++){
			top = top + dominoes[order[i]-1].getTop();
			bottom = bottom + dominoes[order[i]-1].getBottom();
		}
		for(unsigned int i=0; i<dominoes.size(); i++){
			cout << i+1 << ":";
			dominoes[i].print();
		}
		cout << "}" << endl;
		cout << "Add Domino by number-- \"" << reset << "\" to reset -- \"" << phrase << "\" to exit" << endl;
		cout << "{";
		for(unsigned int i=0; i<order.size(); i++){
			if(i>0)
				cout << ",";
			cout << order[i];
		}
		cout << "}\n|" << top << "|\n|" << bottom << "|" << endl;
		str = "";
		cin >> str;
		if(str.compare(phrase)==0){
			cont = false;
			break;
		} else if(str.compare(reset)==0){
			top = "";
			bottom = "";
			order.clear();
			cout << "Reset top and bottom" << endl;
		} else if (str.compare("undo")==0){
			order.pop_back();
			cout << "Undid one operation" << endl;
		} else {
			unsigned int num = atoi(str.c_str());
			last_top = top;
			last_bottom = bottom;
			top = top + dominoes[num-1].getTop();
			bottom = bottom + dominoes[num-1].getBottom();
			order.push_back(num);
			bool matching = top.length()==bottom.length();
			for(unsigned int i=0; i<top.length() && i<bottom.length(); i++){
				if(top[i]!=bottom[i]){
					matching = false;
					cout << "Doesn't match:" << endl;
					for(unsigned int j=0; j<top.length(); j++){
						if(j>=bottom.length() || top[j]==bottom[i])
							cout << top[j];
						else{
							if(j==0 || top[j-1]==bottom[j-1])
								cout << "<";
							cout << top[j];
							if(j+1>=top.length() || j+1>=bottom.length() || top[j+1]==bottom[j+1])
								cout << ">";
						}
					}
					cout << endl;
					for(unsigned int j=0; j<bottom.length(); j++){
						if(j>=top.length() || top[j]==bottom[j])
							cout << bottom[j];
						else{
							if(j==0 || top[j-1]==bottom[j-1])
								cout << "<";
							cout << bottom[j];
							if(j+1>=top.length() || j+1>=bottom.length() || top[j+1]==bottom[j+1])
								cout << ">";
						}
					}
					order.pop_back();
					cout << "Undid previous action" << endl;
					break;
				}
			}
			if(matching){
				cont = false;
				cout << "Top and Bottom Match!\n\"" << top << "\"\n\"" << bottom << "\"" << endl;
				cout << "{";
				for(unsigned int i=0; i<order.size(); i++){
					if(i!=0)
						cout << ",";
					cout << order[i];
				}
				cout << "}" << endl;
			}
		}
	} while (cont);
	
	return 0;
}