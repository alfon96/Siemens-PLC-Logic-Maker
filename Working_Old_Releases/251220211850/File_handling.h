#ifndef File_handling_h
#define File_handling_h
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class File_handling{
	private:
	int n_equations;
	string input[50];
	public:
	File_handling();
	void LoadInput();
	int NumEqTot(){return n_equations;}
	string GetInput(int index){return input[index];}
};

#endif
