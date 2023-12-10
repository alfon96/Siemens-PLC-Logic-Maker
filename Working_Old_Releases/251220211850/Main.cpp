#include <iostream>
#include <string>
#include <fstream>
#include "Matrix.h"
#include "Matrix.cpp"
#include "File_handling.h"
#include "File_handling.cpp"
using namespace std;

//(a+b)*c+{d*e+f*(g+h)}=y
//{l+m*(a+b)*c+[d*e+f]*[a+(b+c)*l+m]}*c=y
//(a+b)*(c+d)*(e+f)*(d+e*f+g)=y
//(a+b)*(c+d)*d+f*c+e*[f+g*(e+d)*w]=y

string PARTS_FILE;
string WIRES_FILE;
string WIRES_MATRIX_FILE;
string VARIABLES_FILE;
string PW_FILE;

string PARTS = "Parts";
string WIRES = "Wires";
string WIRES_MATRIX = "Wires_Matrix";
string VARIABLES = "Variables";
string PW = "PW";

int file_number = 0;

void Files_indexing(){
	PARTS_FILE = PARTS+"_"+to_string(file_number)+ ".xml";
	WIRES_FILE = WIRES+"_"+to_string(file_number)+ ".xml";
	WIRES_MATRIX_FILE = WIRES_MATRIX+"_"+to_string(file_number)+ ".txt";
	PW_FILE = PW+"_"+to_string(file_number)+ ".xml";
	VARIABLES_FILE = VARIABLES+"_"+to_string(file_number++)+ ".csv";
}
int ID = 21;

int main(){
	Files_indexing();
	string input;
	File_handling F;
	F.LoadInput();
	int n_equations = F.NumEqTot();
	cout<<"Numero di equazioni totali : "<<n_equations;
	for(int i = 0;i<n_equations;i++)
	{
	input = F.GetInput(i);
	Matrix *M = new Matrix(input,ID,PARTS_FILE,WIRES_FILE,WIRES_MATRIX_FILE,VARIABLES_FILE,PW_FILE);
	M->Map();
	M->Par_mask();
	M->Filter_input();
	M->Map();
	M->Par_mask();
	M->Cols();
	
	
	M->Rows();
	M->Ladder_Matrix();
	}
	Matrix *M = new Matrix(input,ID,PARTS_FILE,WIRES_FILE,WIRES_MATRIX_FILE,VARIABLES_FILE,PW_FILE);
	M->LoadLadderMatrix();
	M->Ladder_Matrix_Analysis();
	M->Filling_Parts();
	M->Filling_Wires();
	M->Associations();
	M->Populate_VarDB();
	ID = M->get_ID();
	cout<<"\nFinished!";
}
