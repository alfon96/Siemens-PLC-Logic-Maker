#ifndef Matrix_h
#define Matrix_h
#include <iostream>
#include <string>
#include <fstream>
#include <tuple>
using namespace std;

class Matrix {
	private:
		string M[100][100];
		int in_size;
		int par[100][2];
		int row;
		int col;
		int n_par;
		int se[100][2];
		int se_size;
		char input[200];
		char mask_input[200];
		int cols[100];
		int rows[100];
		string L[200][200];
		string K[200][200];
		string w[300][300];
		string saved_numbers[300][300];
		string PARTS_FILE;
		string PW_FILE;
		string WIRES_FILE;
		string WIRES_MATRIX_FILE;
		string VARIABLES_FILE;
		int n_y = 0;
		int max_c = 25;
		int y_place[60];
		int y_index[60];
		int r_w;
		int c_w;
		int r_size;
		int c_size;
		int ID;
		int n_access;
		int n_name;
		int n_parts;
		int N_Wire;
		int n_stop;
		int r_stop[10];
		int c_stop[10];
		int n_Var;
		int negations;
		struct Var_DB{
			string Name;
			int Offset;
			string Type;
			string Area;
			bool Informative;
			string Linked;
		};
		struct Parts{
			string name;
			int Access_Scope_ID;
			int Name_ID;
			int Cardinality;
			int r;
			int c;
			bool Negated;
			bool Or;
			bool Contact;
			bool Coil;
		};
		struct Wires{
			int ID;
			int In[200];
			int Operand;
			int Out;
			int r;
			int c;
			int in_index;
			int Self;
			string test;
			int cont_in;
			bool P;
		};
		Var_DB V[2000];
		Parts P[800];
		Wires W[800];
	public:
		~Matrix();
		void In_mask(string);
		int getPartsIndex(string,Parts[],int,int);
		int getPartsIndex(string,Parts[]);
		Matrix(string,int,string,string,string,string,string);
		void DelRow(int);
		void InsRow(int[]);
		void InsCol(int[]);
		void DelCol(int);
		std::tuple<int, int> minRow(int);
		std::tuple<int, int> minCol(int);
		void Par_mask();
		void Map();
		void DelRowCol(int,int);
		void Print();
		void Print_Par();
		void InsertElement(int,int,string);
		void Filter_input();
		void Cols();
		void Rows();
		void Ladder_Matrix();
		void Ladder_Matrix_Analysis();
		void Print_L();
		void Print_w();
		void Print_Parts(Parts[],int);
		void Filling_Parts();
		void Filling_Wires();
		void ToFile();
		bool isNumber(const string& );
		bool isAlpha(const string& );
		int getWiresIndex(string ,Wires[]);
		void Associations();
		void Print_Wires(Wires[]);
		void Print_Wires_ToFile(Wires[]);
		void Print_Wires_Matrix_ToFile();
		int getWiresIndex(Wires[],int,int);
		int getWiresIndex(string,Wires[],int,int);
		void Print_Parts_ToFile(Parts[]);
		void Populate_VarDB();
		void Print_Var_ToFile();
		int getVarIndex(string,Var_DB[]);
		int getVarIndex(string);
		void Linking_Var();
		int get_ID(){return this->ID;};
		int put_ID(int id){this->ID = id;};
		void PartsWiresFile();
		void LoadLadderMatrix();
		void PrintLtoFile();
};

#endif
