#include "File_handling.h"
#include "File_handling.cpp"
#include <iostream>
using namespace std;

int main()
{
	File_handling F;
	F.LoadInput();
	for(int i = 0;i<F.NumEqTot();i++)
	cout<<endl<<F.GetInput(i);
}
