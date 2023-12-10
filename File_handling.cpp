#include "File_handling.h"
#include <ctype.h>
#include <cstring>
#include <locale> 
#include <iomanip>
using namespace std;


    File_handling::File_handling(){
	n_equations = 0;
}

void File_handling::LoadInput(){
	fstream fin;
	fin.open("Input.txt",ios::in);
	cout<<"\nOpened : "<<fin.is_open();
	int cont = 0;
	while(!fin.eof())
	{
		string temp;
		getline(fin,temp,'\n');
		cont++;
	}
	fin.close();
	n_equations = cont;
	
	fin.open("Input.txt",ios::in);
	cont = 0;
	while(!fin.eof())
	{
		string temp;
		getline(fin,temp,'\n');
		input[cont++] = temp;
	}
	fin.close();
	
}

