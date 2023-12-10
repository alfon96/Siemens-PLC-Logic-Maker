#include "Matrix.h"
#include <ctype.h>
#include <cstring>
#include <locale> 
#include <iomanip>
using namespace std;

	Matrix::Matrix(string in,int id,string parts,string wires,string w_matrix,string var_file,string pw_file){
		this->n_par = 0;
		this->ID = id;
		PARTS_FILE = parts;
		WIRES_FILE = wires;
		WIRES_MATRIX_FILE = w_matrix;
		VARIABLES_FILE = var_file;
		PW_FILE = pw_file;
		
		for(int i = 0;i<in.size();i++)
			input[i] = in[i];

		in_size = in.size();		
		this->row = in.size();
		this->col = this->row;
		for(int i = 0;i<100;i++)
			for(int j = 0;j<100;j++)
				this->M[i][j] = "-";	

		for(int i = 0;i<100;i++)
		{
			cols[i] = 0;
			par[i][0] = 0;
			par[i][1] = 0;
			rows[i] = 0;
		}
		
		for(int i = 0;i<200;i++)
			for(int j = 0;i<200;i++)
				L[i][j] = "-";	
					
		for(int i = 0;i<300;i++)
				for(int j = 0;i<300;i++)
					w[i][j] = "-";	
	}
	
	void Matrix::DelRow(int row_index){		
			for(int j = 0;j<col;j++)
				this->M[row_index][j] = "-";

	}
	
	void Matrix::DelCol(int col_index){
			for(int j = 0;j<row;j++)
				this->M[j][col_index] = "-";
	}
	
	void Matrix::DelRowCol(int row_index,int col_index){
		Matrix::DelRow(row_index);
		Matrix::DelCol(col_index);	
	}
	
	void Matrix::Print(){
		cout<<endl;
		cout<<"  ";
		for(int i = 0;i<this->col;i++)
		cout<<" "<<i;
		cout<<endl;
		for(int i = 0;i<this->row;i++)
		{	
			if(i<10)
			cout<<i<<"  ";
			else
			cout<<i<<" ";
			for(int j = 0;j<this->col;j++)
			{
			if(j<10)
				cout<<M[i][j]<<" ";
			else
				cout<<M[i][j]<<"  ";
			}
		cout<<endl;
		}		
	}
		
	void Matrix::Print_Par(){
		cout<<"\nParenthesis : ";
		// Print parenthesis matrix
		cout<<endl;
		cout<<"  ";
		for(int i = 0;i<2;i++)
		cout<<" "<<i;
		cout<<endl;
		
		for(int i = 0;i<this->n_par;i++)
		{	
			if(i<10)
			cout<<i<<"  ";
			else
			cout<<i<<" ";
			for(int j = 0;j<2;j++)
				cout<<par[i][j]<<" ";
		cout<<endl;
		}
			
	}
		
	std::tuple<int, int> Matrix::minCol(int col_index){
		int min = 7000;
		int index = 0;
		int temp[this->row][this->col];
		for(int i = 0;i<this->row;i++)
			for(int j = 0;j<this->col;j++)
			{
				int n = this->M[i][j].length();
    			char x[n + 1];
				strcpy(x, this->M[i][j].c_str());
				bool not_num = false;
				
				for(int k = 0;k<n;k++)
				{
					if(!isdigit(x[k]))
					{
						not_num = true;
						break;
					}
				}
				
				if(not_num)
					temp[i][j] = 0;	
				else
				temp[i][j] = stoi(this->M[i][j]);
			}
		for(int j = 0;j<this->row;j++)
			if(min>temp[j][col_index] and temp[j][col_index]!=0)
				{
					min = temp[j][col_index];
					index = j;
				}	
		return  std::make_tuple(index,min);
	}
	
	std::tuple<int, int> Matrix::minRow(int row_index){
		int index = 0;
		int temp[this->row][this->col];
		for(int i = 0;i<this->row;i++)
			for(int j = 0;j<this->col;j++)
			{
				int n = this->M[i][j].length();
    			char x[n + 1];
				strcpy(x, this->M[i][j].c_str());
				bool not_num = false;
				
				for(int k = 0;k<n;k++)
				{
					if(!isdigit(x[k]))
					{
						not_num = true;
						break;
					}
				}
				if(not_num)
					temp[i][j] = 0;	
				else
				temp[i][j] = stoi(this->M[i][j]);
			}	
		int min = 7000;
		for(int j = 0;j<this->col;j++)
			if(min>temp[row_index][j] and temp[row_index][j]!=0)
				{
					min = temp[row_index][j];
					index = j;
				}
		return  std::make_tuple(index,min);
	}
	
	void Matrix::Map(){
				
		for(int i = 0;i<this->in_size;i++)
		{
			bool Trigger_r = false;
			bool Trigger_c = false;
			bool Trigger_s = false;
		
			if(this->input[i] == '(')
				Trigger_r = true;
			if(this->input[i] == '[')
				Trigger_s = true;
			if(this->input[i] == '{')
				Trigger_c = true;
			
		if(Trigger_r+Trigger_s+Trigger_c)		
		{	
			for(int j =i;j<this->in_size;j++)
			{				
			if(this->input[j] == ')' and Trigger_r)
				this->M[i][j] =  to_string(j-i);
				
			if(this->input[j] == ']' and Trigger_s)
				this->M[i][j] =  to_string(j-i);
				
			if(this->input[j] == '}' and Trigger_c)
				this->M[i][j] = to_string(j-i);
			}
		}				
	}
	}

	void Matrix::InsertElement(int row_index,int col_index,string data){
		if(row_index<=this->row and col_index<= this->col and col_index>=0 and row_index>= 0)
			this->M[row_index][col_index] = data;
		else
			cout<<"Error in Matrix indexes";
	}
	
	void Matrix::Par_mask(){
		
		int col = 2;
		int row = 0;
		int y=0;
		
		for(int i = 0;i<this->in_size;i++)
			if(this->input[i]==')' or this->input[i]==']' or this->input[i]=='}')
				row++;
				
		int index[row];
		for(int i = 0;i<this->in_size;i++)
			if(this->input[i]==')' or this->input[i]==']' or this->input[i]=='}')
				index[y++] = i;
						
		int r=0;
		int min=0;
		this->n_par = row;
		
		for(int i = 0;i<row;i++)
		{
			tie(r, min) = this->minCol(index[i]);
			for(int j = 0;j<col;j++)
			{
				if(j==0)
					this->par[i][j] = r;
				else
					this->par[i][j] = index[i];
			}
			this->DelRowCol(r,index[i]);
			//cout<<endl;
		}
		
		int x=0;
		int z=0;
		for(int j = 0;j<row-1;j++)
		for(int i = 0;i<row-1;i++)
		{
				if(par[i][0]>par[i+1][0])
					{
						x = par[i][0];
						z = par[i][1];
						par[i][0] = par[i+1][0];
						par[i][1] = par[i+1][1];
						par[i+1][1] = z;
						par[i+1][0] = x;
					}
			}	
	}

	void Matrix::Filter_input(){
		
		char temp[100];
		
		for(int i =0;i<100;i++)
			temp[i] = ' ';
		
		int index = 0;
		int i_par = 0;
		int dim = this->n_par*2;
		int delete_par[dim];
		
		for(int i = 0;i<dim;i++)
		delete_par[i] = 100;

		for(int i =0;i<this->n_par;i++)
		{
			if(i!=0)
			{		// se parentesi doppie
				if(this->par[i][0] == par[i-1][0]+1 and this->par[i][1] == par[i-1][1]-1)
			{
				delete_par[i_par++] = this->par[i-1][0];
				delete_par[i_par++] = this->par[i-1][1];
			}
			}
			else
			{	// se parentesi dal primo all' elemento prima dell'uguale
				if(this->par[0][0] == 0 and this->par[0][1] >=in_size-2)
			{
				delete_par[i_par++] = this->par[0][0];
				delete_par[i_par++] = this->par[0][1];
			}
			}
				// se parentesi tra due +
				if(input[this->par[i][0]-1] != '*' and input[this->par[i][1]+1] !='*' )
			{
				delete_par[i_par++] = this->par[i][0];
				delete_par[i_par++] = this->par[i][1];
			}	
		}
	
		for(int i = 0;i<i_par;i++)
			{
			for(int j = 0;j<i_par-1;j++)
			{
				if(delete_par[j]>delete_par[j+1])
				{
				int temp = delete_par[j+1];
				delete_par[j+1] = delete_par[j];
				delete_par[j] = temp;
				}
				
			}
		}
			
		i_par = 0;
		index = 0;
		
		for(int i = 0;i<this->in_size;i++)
		{
			if(i!=delete_par[i_par] or delete_par[i_par]==100 )
			{
				temp[index++] = this->input[i];
			}
			else
			i_par++;
		}	
		cout<<endl;
		cout<<"\nnew length : "<<index<<endl;
		
		for(int i = 0;i<index;i++)
		input[i]=temp[i];		

		this->in_size = index;

		cout<<"\nin_size : "<<in_size<<endl;
		cout<<"\ninput rewritten : "<<endl;
		
		for(int i = 0;i<in_size;i++)
		cout<<input[i]<<" ";
	}

	void Matrix::Cols(){
		int a[in_size];
		int gamma[in_size] ;
		int beta[in_size] ;
		int eta[in_size] ;	
		int m = 0;
		int c=1;
		int max_a = 0;
		int pars[in_size];
		
		for(int i=0;i<in_size;i++)
		{
			a[i]=0;
			gamma[i]=0;
			beta[i]=0;
			eta[i]=0;
			pars[i] = 0;	
		}
		int cont = 1;
		for(int j = 0;j<n_par;j++)
		{
			for(int k = par[j][0];k<=par[j][1];k++)
			{
				pars[k] = cont;
			}
			cont++;
		}
		
		for(int k=0;k<in_size;k++)
		{
			
			if(input[k]=='*')
			gamma[k] = 1;
			
			if(input[k]== '*' and (input[k-1]==')' or input[k-1]==']' or input[k-1]=='}' ))
			{
				int open = 0;
				for(int j = k;j<in_size;j++)
				{
					if(input[j]==')' or input[j]==']' or input[j]=='}' )
					open--;
					if(input[j]=='(' or input[j]=='[' or input[j]=='{' )
					open++;
					
					if(!open)
					{
						if(input[j]=='*'  and pars[j]!=0 and (input[j-1]==')' or input[j-1]==']' or input[j-1]=='}'))
						eta[j]++;
						if(input[j]=='*'  and pars[j]==0)
						eta[j] = 1;
					}
				}
			}
			
			if(input[k]== '*' and (input[k+1]=='(' or input[k+1]=='[' or input[k+1]=='{' ))
			{
				bool done = false;
				for(int j = k;j>=0;j--)
				{
					if(eta[j]!=0)
					{
						done = true;
						break;
					}
					
				}
				if(done and eta[k]==0)
					eta[k]=1;
					
				done = false;
			}

		}
		
		a[0] = 1;
		
		for(int k=0;k<in_size-1;k++)
		{
			if(input[k] == '(' or input[k]=='[' or input[k]=='{' )
			beta[k] = a[k];
			
			if(input[k+2] == '+')
			{
				int closed = 0;
				for(int i=k+2;i>=0;i--)
				{
					if(input[i]==')' or input[i]==']' or input[i]=='}' )
						closed++;
					if(input[i] == '(' or input[i]=='[' or input[i]=='{' )
						closed--;
						
					//cout<<"\nclosed : "<<closed;
					
					if(closed<0)
					{
						m=i;
						break;
					}
				}
				if(m!=0)
				beta[k+1] = beta[m];
				else
				beta[k+1] = 1;
			}
			if((input[k]==')' or input[k]==']' or input[k]=='}' ) or (input[k]=='(' or input[k]=='[' or input[k]=='{' ) or beta[k] == 0)
			c=0;
			a[k+1] = a[k] + gamma[k]+eta[k] -1*(a[k]+gamma[k]+eta[k]-beta[k])*c;
			c=1;
			
			if(a[k+1]>max_a)
			max_a = a[k+1];
			
			if(input[k+1]=='*' and pars[k+1]==0 and  (input[k]==')' or input[k]==']' or input[k]=='}'))	
					a[k+1] = max_a;	
					
			if(input[k+1]=='*' and pars[k+1]==0 and (input[k]==')' or input[k]==']' or input[k]=='}') )	
					eta[k+1] = 1;	
			
			if(input[k+1]=='+' and pars[k+1]==0 )	
					a[k+1] = 1;
					
			if(input[k+1]=='=' and pars[k+1]==0 )	
					{
						bool ins = false;
						for(int i = k;i>=0;i--)
						{
							if(a[i] == max_a)
								if(pars[i] != 0)
									{
									ins = true;
									break;
									}	
						}
							if(ins)
							a[k+1] = max_a+2;
							else
							a[k+1] = max_a+1;
					}
					
				//inizio e fine delle parentesi stesso numero
			if(input[k+1]==')' or input[k+1]==']' or input[k+1]=='}')
			{
				int fix = -1;
				for(int i =0;i<n_par;i++)
				if(k+1 == par[i][1])
					{
						fix = i;
						break;
					}
				if(fix>=0)
					a[k+1] = a[par[fix][0]];
					//cout<<"\nfix : "<<fix;
			}
				
		}	
		
		
		cout<<endl;
		for(int i = 0;i<in_size;i++)
		cout<<input[i]<<" ";
		
		cout<<"   input"<<endl;
		for(int i = 0;i<in_size;i++)
			cout<<eta[i]<<" ";
			
			cout<<"   eta"<<endl;
		for(int i = 0;i<in_size;i++)
			cout<<beta[i]<<" ";
		
		cout<<"   beta"<<endl;
		for(int i = 0;i<in_size;i++)
			cout<<gamma[i]<<" ";
			
		cout<<"   gamma"<<endl;
		for(int i = 0;i<in_size;i++)
			cout<<pars[i]<<" ";
		cout<<"   pars"<<endl;
		
		for(int i = 0;i<in_size;i++)
			cout<<a[i]<<" ";
		cout<<"   a"<<endl;

	for(int i = 0;i<in_size;i++)
	cols[i] = a[i];	
	
	}
	
	void Matrix::Rows(){
		int a[in_size];
		int gamma[in_size] ;
		int beta[in_size] ;
		int eta[in_size] ;	
		int m = 0;
		int c=1;
		int max_a = 0;
		int pars[in_size];
		
		for(int i=0;i<in_size;i++)
		{
			a[i]=0;
			gamma[i]=0;
			beta[i]=0;
			eta[i]=0;
			pars[i] = 0;	
		}
		int cont = 1;
		for(int j = 0;j<n_par;j++)
		{
			for(int k = par[j][0];k<=par[j][1];k++)
			{
				pars[k] = cont;
			}
			cont++;
		}
		
		for(int k=0;k<in_size;k++)
		{
			if(input[k]=='+')
			gamma[k] = 1;
			
			if(input[k]=='+' and input[k-2]=='*' and pars[k]!=0 and (input[k-3]==')' or input[k-3]==']' or input[k-3]=='}' ))
			eta[k] ++;
			
			if(input[k]=='+' and input[k-2]=='*' and (input[k-3]==')' or input[k-3]==']' or input[k-3]=='}' ))
			eta[k] ++;

		}
		
		a[0] = 1;
		
		for(int k=0;k<in_size-1;k++)
		{
			if(input[k] == '(' or input[k]=='[' or input[k]=='{' )
			beta[k] = a[k];
			
			if(input[k+1] == '*' and (input[k] == ')' or input[k]==']' or input[k]=='}' ) and pars[k+1]!=0)
			{
				int b0 = 0;
				for(int j =k;j>=0;j--)
				{
					if(beta[j]!=0)
					{
						b0 = beta[j];
						break;
					}	
				}
				if(b0!=0)
					beta[k+1] = b0;
			}

			if((input[k]==')' or input[k]==']' or input[k]=='}' ) or (input[k]=='(' or input[k]=='[' or input[k]=='{' ) or beta[k] == 0)
			c=0;
			a[k+1] = a[k] + gamma[k]+eta[k] -1*(a[k]+gamma[k]+eta[k]-beta[k])*c;
			c=1;
			
			if(a[k+1]>max_a)
			max_a = a[k+1];
					
			if(input[k+1]=='*' and pars[k+1]==0 and (input[k]==')' or input[k]==']' or input[k]=='}') )	
					a[k+1] = 1;	
			
			if(input[k+1]=='+' and pars[k+1]==0 )	
					a[k+1] = max_a+1;
					
			if(input[k+1]=='=' and pars[k+1]==0 )	
					a[k+1] = 1;
		}	
		
		
		cout<<endl;
		cout<<"\nRows\n\n";
		for(int i = 0;i<in_size;i++)
		cout<<input[i]<<" ";
		
		cout<<"   input"<<endl;
		for(int i = 0;i<in_size;i++)
			cout<<eta[i]<<" ";
			
			cout<<"   eta"<<endl;
		for(int i = 0;i<in_size;i++)
			cout<<beta[i]<<" ";
		
		cout<<"   beta"<<endl;
		for(int i = 0;i<in_size;i++)
			cout<<gamma[i]<<" ";
			
		cout<<"   gamma"<<endl;
		for(int i = 0;i<in_size;i++)
			cout<<pars[i]<<" ";
		cout<<"   pars"<<endl;
		
		for(int i = 0;i<in_size;i++)
			cout<<a[i]<<" ";
		cout<<"   a"<<endl;


	for(int i = 0;i<in_size;i++)
	rows[i] = a[i];
		
	}

	void Matrix::Ladder_Matrix(){
		cout<<"\nLadder_Matrix\n\n";
		int r=0;
		int c=0;
		
		for(int i =0;i<in_size;i++){
			if(cols[i]>c)
			c=cols[i];
			if(rows[i]>r)
			r=rows[i];
		}
		
		cout<<"\nMatrix size : r = "<<r<<" ; c = "<<c<<endl;
		r_size = r+1;
		c_size = c+1;
		
		for(int i =0;i<r_size;i++)
			for(int j = 0;j<c_size;j++)
				L[i][j]="-";

		for(int i =0;i<r_size;i++)
				L[i][0]="S";
				
		for(int i = 0 ;i<in_size;i++)
		{
			
			if(isalpha(input[i])!=0)
			{
				L[rows[i]][cols[i]] = input[i];
			}
		}
		
		cout<<"\n Ladder Matrix Before \n\n";
		for(int i =0;i<r_size;i++)
		{
			cout<<"              ";
			for(int j = 0;j<c_size;j++)
			{
				cout<<L[i][j]<<" ";
			}
			cout<<endl;
		}
		
					int first_letter[r_size];
				for(int k = 0;k<r_size;k++)
				first_letter[k] = 0;
				
			int min = 8000;
				
					for(int z =1;z<r_size;z++){
						for(int h = 1;h<c_size;h++)
						{
							char search[L[z][h].length()+1];
							strcpy(search, L[z][h].c_str());
							
							if(isalpha(search[0]) and h<min)
									min = h;
						}
						first_letter[z] = min;
					min = 8000;
					}
			
	/*	for(int z =1;z<r_size;z++)	
		cout<<	endl<< "z : "<<z<<" col: "<<first_letter[z] ;
				
		*/		
				
				
				
				
		for(int i = 0 ;i<r_size;i++)
		{
			for(int j = 0 ;j<c_size-3;j++)
				if(L[i][j]!="-" and L[i][j]!="S" and L[i][j+1] == "-" and L[i][j+2]!="-" and first_letter[i+1]<=j )
					L[i][j+1] = "O";
		}
		
		// prima analisi
		
		for(int i = 0 ;i<r_size;i++)
		{
			for(int j = 0 ;j<c_size;j++)
				if(L[i][j]== "O")
					{
						bool gut = false;
						int k = i;
						for(int h = j;h>=0;h--)
						{
							if(L[k+1][h]!="-" and L[k+1][h]!="S" and L[k+1][h]!="O" and L[k+1][h]!="o")	
							{
								L[i+1][j] = "o";
								if(k+1!=r_size)
								k++;
								else
								break;
								h=j;
							}
								
							
						}
					}
		}
	
		// print
		cout<<"\n Ladder Matrix Prima analisi \n\n";
		
		cout<<"              ";
		for(int i =0;i<c_size;i++)
		cout<<i<<" ";
		

		cout<<endl;
		for(int i =1;i<r_size;i++)
		{
			cout<<"              ";
			for(int j = 0;j<c_size;j++)
			{
				cout<<L[i][j]<<" ";
			}
			cout<<endl;
		}	
			
	
			
		// seconda analisi
		
			int i = c_size;
			for(i;i>=0;i--)
				if(L[1][i]=="-")
					break;
			L[1][i] ="O";
			
			for(int j = 2 ;j<r_size;j++) // se almeno un elemento nella riga
			{
				bool gut = 0;
				bool auch = false;

				for(int k = i;k>=0;k--)
				{
					if(L[j][k] == "O" or (first_letter[j]>0 and first_letter[j]<100 and (first_letter[j-1]==8000 or j == r_size-1)))
					gut = true;
					
					char search[L[j][i-1].length()+1];
						strcpy(search, L[j][i-1].c_str());
							
					if( isalpha(search[0]))
					auch = true;
				}
	
					if(gut or auch)  // se almeno un elemento nella riga scrivi O
						L[j][i] = "o";

					
				}
					
		

		// print
		cout<<"\n Ladder Matrix After \n\n";
		
		cout<<"              ";
		for(int i =0;i<c_size;i++)
		cout<<i<<" ";
		

		cout<<endl;
		for(int i =1;i<r_size;i++)
		{
			cout<<"              ";
			for(int j = 0;j<c_size;j++)
			{
				cout<<L[i][j]<<" ";
			}
			cout<<endl;
		}
		
		
	}
	
	void Matrix::Filling_Parts()
	{
		
		for(int i =0;i<100;i++)
			for(int j =0;j<100;j++)
				w[i][j] = '-';
		
		int offset = 1;
		for(int i =0;i<c_size;i++)
		{
			
			for(int j =0;j<r_size;j++)
			{
				w[j][i+offset] = L[j][i];
			}
			offset+=2;
		}
		r_w = r_size;
		c_w = 3*c_size;
		cout<<"\nRighe w : "<<r_w<<" colonne w : "<<c_w;

		Print_w();
		
		cout<<"\nFilling_Parts\n\n";
		int n_or = 0;
		int num_elem = 0;
		
		// n_or vere
		for(int i = 0;i<r_size;i++)
			for(int j = 0;j<c_size;j++)
				if(L[i][j] == "O")
					n_or++;

		//numero elementi totali
		for(int i = 0;i<in_size;i++)
			if(isalpha(input[i]))
				num_elem++;

		cout<<"\nNumero di elementi : "<<num_elem;
		n_access = num_elem;
		n_name = n_or+num_elem;
		cout<<"\nNumero di or vere : "<<n_or;
		cout<<"\nNumero di elementi totali : "<<n_or+num_elem;
		
		// ACCESS_ID
		int k =0;
		for(int i = 1;i<r_size;i++)
		{
			for(int j = 0;j<c_size;j++)
			{
				if(L[i][j]!="-" and L[i][j]!="o" and L[i][j]!="O" and L[i][j]!="S")
				{
					P[k].Access_Scope_ID = ID++;
					P[k].r = i;
					P[k].c = 3*j+1;
					
					P[k++].name = L[i][j];
					
				}
				if(L[i][j]=="O")
				{
					P[k].Access_Scope_ID = -1;
					P[k].r = i;
					P[k].c = 3*j+1;
					P[k++].name = L[i][j];
				}	
				if(L[i][j]=="o")
				{
					P[k].Access_Scope_ID = -1;
					P[k].r = i;
					P[k].c = 3*j+1;
					P[k++].name = L[i][j];
				}		
		
			}
		}
		//Print_Parts(P,k);
		
		// NAME_ID
		k = 0;
		int k_or = 0;
		for(int i = 1;i<r_size;i++)
		{
			for(int j = 0;j<c_size;j++)
			{
				if(L[i][j]!="-" and L[i][j]!="S" and L[i][j]!="y")
				{

					if(L[i][j]!="o" and L[i][j]!="O" )
					{
						P[k].Name_ID = ID++;
						P[k].Or = false;
						P[k].Contact = true;
						P[k].Coil = false;
						P[k].r = i;
						P[k].c = 3*j+1;
						k++;	
					}

					if(L[i][j]=="O")
					{
						P[k].name = to_string(++k_or);
						L[i][j] = to_string(k_or);
						P[k].Name_ID = ID++;
						P[k].Coil = false;
						P[k].Or = true;
						P[k].Contact = false;
						P[k].r = i;
						P[k].c = 3*j+1;
						k++;
					}
					
					if(L[i][j]=="o")
					{
						for(int r=i;r>=0;r--)
							if(isNumber(L[r][j]))
								{
								P[k].name = L[i][j];
								P[k].r = i;
								P[k].c = 3*j+1;
								P[k].Name_ID = P[getPartsIndex(L[r][j],P)].Name_ID;
								break;
								}
								
							P[k].Coil = false;
							P[k].Contact = false;
							P[k].Or = false;
							k++;		
					}
					
					
				if(L[i][j] != "-")
				cout<<"\nw : "<<L[i][j];
				
				}
					if(L[i][j]=="y")
					{
						P[k].Name_ID = ID++;
						P[k].Or = false;
						P[k].Contact = false;
						P[k].Coil = true;
						k++;
					}	
			 
			}
			
		}
		
		
		//Print_L();
		// Print risultati
		//Print_Parts(P,k);
		n_parts = k;
		
		cout<<"\n parts_tot : "<<n_parts;
		//ToFile();
		//Print_Parts_ToFile(P);
}
 	void Matrix::Filling_Wires()
 	{

 		cout<<"\n\nFilling_Wires\n\n";
 		
 		//Print_w();
 		
 		int startcont = 55;
		int cont = startcont;
		int contact_n = 36;
		int power_cont = 4;
		bool contact = false;
		for(int i =0;i<r_size;i++){
			for(int j = power_cont;j<c_w;j++)
			{	
				// se contatto
				if(w[i][j]!="-" and w[i][j]!="O" and w[i][j]!="S")
				{
					cont++;	
					contact = true;
				}
				
				// se non è un contatto : "-,S"
				if(!contact and w[i][j] != "O")
				{
					int first = j;
					int last = 0;
		
					for(int k = j;k<c_w;k++)
						if(w[i][k] != "-")
						{
							last = k-1;
							break;
						}
						
					if(last>0)
					{
						w[i][j] = to_string(cont);
						
						w[i][last] = to_string(cont);
						j= last;	
					}
						
				}
			
				
				if(contact)
				{
					//cout<<"\nInside contact : "<<w[i][j];
					
					//w[i][j] = to_string(cont);
				//	if(w[i][j]!="o")
				//	w[i][j] = "-"+to_string(contact_n++);
					
					cont++;
					contact = false;
				}
				// solo se c'è la OR
				if(w[i][j]=="O")
					cont++;

			}
		}
		
		for(int i = 0;i<r_w;i++)
			for(int j = 0;j<power_cont;j++)
				w[i][j] = to_string(startcont);
		
		Print_w();
		
		cout<<"\nbasi : \n";
		int first_letter[r_size];
				for(int k = 0;k<r_size;k++)
				first_letter[k] = 0;
				int min = 8000;
				
					for(int z =1;z<r_size;z++){
						for(int h = 0;h<c_w;h++)
						{
							char search[w[z][h].length()+1];
							strcpy(search, w[z][h].c_str());
							
							if(isalpha(search[0]) and h<min)
								min = h;
						}
						first_letter[z] = min;
					min = 8000;
					}
					
	/*	for(int k = 0;k<r_size;k++)
			cout<<"\n Colonna prima lettera =  "<<first_letter[k]<<" rispetto alla riga i : "<<k<<endl;	*/	
		
		for(int i =0;i<r_size;i++){
			for(int j = power_cont;j<c_w;j++)
			{		
		// se un or
				if(w[i][j]=="o")
				{
					string num = " ";
					bool trovato = false;
					for(int k=j-1;k>=power_cont;k--)
					{
						char search[w[i][k].length()+1];
						strcpy(search, w[i][k].c_str()); 
						
						//  alla prima lettera
						if(isalpha(search[0]) and !trovato)
						{	
							num = w[i-1][--k];
							if(num!="-")
							trovato = true;
							else
							++k;
						}	
						// il primo numero dopo la prima lettera
						if(trovato and isNumber(w[i][k]))
						{
							w[i][k] = num;
							break;
						}
						
					}
				}
			}
		}
		
			
		for(int i =0;i<r_size;i++){

			{	
			
			int check = 0;
			if(first_letter[i]!=8000 and first_letter!=0)
				check = first_letter[i];
				
			if(check!=0)
				{
					// se la prima variabile non comincia all'inizio e sopra c'è una riga vuota
					if(check>4 and first_letter[i-1]==8000)
					{
						//cout<<"\nhere"<<" first : "<<w[i][first_letter[i]-1]<<" second : "<<w[i-2][first_letter[i]-1];
						w[i][first_letter[i]-1] = w[i-2][first_letter[i]-1];		
					}
				}
			
			}
			
		}
		fstream fout;
		fout.open("Wire_Map.txt",ios::out);
		// elimina "o" in eccesso
		for(int i =0;i<r_w;i++)
			for(int j =power_cont;j<c_w;j++)
				if(w[i][j] =="o")
					if(isNumber(w[i][j+1])  and isNumber(w[i][j+2]) )
						w[i][j+1] ="-";
						
		//elimina numeri inutili prima colonna
		for(int i = 0;i<r_w;i++)
					if(isNumber(w[i][4]))
						w[i][4] = "-";
		Print_w();
		
		for(int i =0;i<r_w;i++)
			for(int j = power_cont-1;j<c_w;j++)
				{
					if(isNumber(w[i][j]) and getWiresIndex(w[i][j],W)==-1 and w[i][j+1]!="O")
					{
						W[N_Wire++].ID = stoi(w[i][j]); 
						fout<<"\nWire ID : "<<W[N_Wire-1].ID<< " linked to : "<<w[i][j];
					}
						
					if(isAlpha(w[i][j]) and w[i][j]!="o" and w[i][j]!="O")
					{
					
						if(isNumber(w[i][j+1]))
						{
							W[N_Wire++].ID = stoi(w[i][j+1])-1; 
							fout<<"\nWire ID : "<<W[N_Wire-1].ID<< " linked to : "<<w[i][j];
						}
						else
						if(isNumber(w[i][j-1]))
						{
							W[N_Wire++].ID = stoi(w[i][j-1])+1; 
							fout<<"\nWire ID : "<<W[N_Wire-1].ID<< " linked to : "<<w[i][j];
						}
							
					}		
					
	
				}
		fout.close();
		cout<<"\n Totale wires : "<<N_Wire;
	}
	
	

	
	void Matrix::Associations(){
						
		int k_or = 1;
		// risolvi in1,in2 per gli ingressi or
		int col_or[r_w][c_w];
		for(int i =0;i<r_w;i++)
			for(int j =0;j<c_w;j++)
				col_or[i][j] = 0;
		
		for(int i =0;i<r_w;i++)
			for(int j =0;j<c_w;j++)
				if(w[i][j] == "O")
					{
						int temp = 1;
						col_or[i][j] = temp;
						for(int k=i+1;k<r_w;k++)
							{
							if(w[k][j]=="o")
								col_or[k][j] = ++temp;
							if(w[k][j] == "O")
								break;
							}
					}

		cout<<"\nMatrix Or : \n\n";
		for(int i =0;i<r_w;i++)
			{
				for(int j =0;j<c_w;j++)
				cout<<col_or[i][j]<< " " ;
				
				cout<<endl;
			}

		cout<<"\n\n Associations : \n";
		int power_cont = 3;
		
		for(int i =0;i<r_w;i++)
			for(int j = power_cont;j<c_w;j++)
			{
				int index = 0;
				int index_2 = 0;
				// se I - S
				if(isNumber(w[i][j]) and isAlpha(w[i][j+1]))
				{
					index = getWiresIndex(w[i][j],W);;
					index_2=0;
					if(w[i][j+1]=="O")
						index_2 = getPartsIndex(to_string(k_or++),P,i,j+1);
					else
						index_2 = getPartsIndex(w[i][j+1],P,i,j+1);

					//cout<<"\nO : "<<w[i][j+1];
					W[index].r = i;
					W[index].c = j+1;
					
					if(index!=-1)
					W[index].In[W[index].cont_in++] = P[index_2].Name_ID;
				}
				
				// se S - Q
				if(isNumber(w[i][j]) and isAlpha(w[i][j-1]))
				{
					index = getWiresIndex(w[i][j],W);
					index_2 = 0;
					
					if(w[i][j-1] == "O" or w[i][j-1] == "o")
					index_2 = getPartsIndex(to_string(k_or-1),P,i,j-1);
					else
					index_2 = getPartsIndex(w[i][j-1],P,i,j-1);
					
					if(index!=-1)
					W[index].Out = P[index_2].Name_ID;
					
					W[index].r = i;
					W[index].c = j-1;
					
				}
				
				// se S
				if(j>power_cont)
				{	
				// se letterale, diverso da O e o
				if(isNumber(w[i][j-1]) and (isNumber(w[i][j+1]) or j >= c_w-2) and isAlpha(w[i][j]) and w[i][j]!= "O" and w[i][j]!= "o" )
				{
					index = 0;
					if(isNumber(w[i][j+1]))
					index = getWiresIndex(w[i][j+1],W)-1;
					else
					if(isNumber(w[i][j-1]))
					index = getWiresIndex(w[i][j-1],W)+1;
					
					index_2 = getPartsIndex(w[i][j],P,i,j);
					
					cout<<"\nString : "<<w[i][j]<<" index_2 : "<<index_2<<" index_1 = "<<index;
					cout<<"\nOutput : "<<P[index_2].Access_Scope_ID;
					if(index!=-1)
					{
					W[index].Self = P[index_2].Access_Scope_ID;
					W[index].Operand = P[index_2].Name_ID;						
					}
					
					W[index].r = i;
					W[index].c = j+1;

				}
				
				}
			

			}
		
	/*	for(int i = 0;i<30;i++)
		cout<<"\nRows : "<<W[i].r<<" ; Columns : "<<W[i].c;*/
		
		/*for(int i = 0;i<r_w;i++)
			for(int j = 0;j<c_w;j++)
				cout<<"\nget_ind : "<<getWiresIndex(W,i,j);*/
				
		/*for(int i = 0;i<r_w;i++)
		for(int j = 0;j<c_w;j++)
		if(col[i]!=0)
			col[i][j]++;
			
		for(int i = 0;i<c_w;i++)
			if(col[i][j]!=0)
				W[getWiresIndex(i,j)].in_index = col[i][j];

		cout<<"\nN_or["<<i<<"] = "<<col[i];*/
			
		// associa gli indici in Wires
		for(int i =0;i<r_w;i++)
			for(int j =0;j<c_w;j++)
				if(col_or[i][j]!=0)
					for(int k = 0;k<r_w;k++)
					    W[getWiresIndex(W,k,j)].in_index = col_or[k][j];	
			
		int temp = 1;
		int max_c[c_w];
		for(int i = 0;i<c_w;i++)
		max_c[i] = 0;
		
		// Cardinalità in Parts
		for(int i =0;i<r_w;i++)
			for(int j =0;j<c_w;j++)
				{
					if(col_or[i][j]!=0)
						{
							for(int k = 0;k<r_w;k++)
								if(max_c[j]<col_or[k][j])
									max_c[j] = col_or[k][j];			
						}
					
				}			
		
		for(int i =0;i<r_w;i++)
			for(int j =0;j<c_w;j++)
				{
					if(col_or[i][j]!=0 and w[i][j]!="o")
						{
							cout<<"\nFirst : "<<w[i][j]<<" temp : "<<temp<<" max : "<<max_c[j];
							P[getPartsIndex(to_string(temp++),P,i,j)].Cardinality = max_c[j];
							//break;		
						}
				}
		
		
		/*for(int i = 0;i<n_parts;i++)
		cout<<"\nIn_index : "<<P[i].name<<" Cardinality : "<<P[i].Cardinality;	*/			
			
			
		/*for(int i = 0;i<40;i++)
		cout<<"\nIn_index : "<<W[i].in_index<<" row : "<<W[i].r<<" ; col : "<<W[i].c;	*/
			

		
		W[0].P = 1;
		//Print_Wires(W);
		cout<<"\nhere1";
		Print_Wires_ToFile(W);
		cout<<"\nhere2";
		Print_Wires_Matrix_ToFile();
		cout<<"\nhere3";
	}
	
	
	
	void Matrix::Populate_VarDB()
	{

		string Var_block_start = "<SW.Tags.PlcTag";
		string Var_block_end = "</SW.Tags.PlcTag>";
		bool inside = false;
		
		fstream fin;
		fin.open("variabili.xml",ios::in);
		
		cout<<"\nFile opened : "<<fin.is_open();
		int j = 0;
		
		while(!fin.eof())
		{
			string temp;
			getline(fin,temp,'\n');
			
			int VAR_start = temp.find(Var_block_start);
			int VAR_end = temp.find(Var_block_end);	
			
			while((VAR_start!=-1 and VAR_end==-1 or inside) and !fin.eof())
			{
			inside = true;
			VAR_start = temp.find(Var_block_start);
			VAR_end = temp.find(Var_block_end);
			
			if(!temp.empty())
			{
				// CALCOLO OFFSET
				int Offset_start = temp.find("%");
				int Offset_end = temp.find("<",Offset_start+1);
				string content;
			//	cout<<endl<<"Temp : "<<temp;
				if(Offset_start!=-1 and Offset_end!=-1)
				{
					//cout<<"\n\n var_offset : "<<temp<<" off_s : "<<Offset_start<<" Off_e : "<<Offset_end<<endl;
					content = temp.substr(Offset_start,Offset_end);
					int sep = content.find(".");
					
					if(sep!=-1)
					{
					//	cout<<"\n\n sep : "<<sep<<" content : "<<content.substr(2,sep-2)<<" later : "<<content.substr(sep+1,content.size())<<endl;
						int byte = stoi(content.substr(2,sep));
						int bit = stoi(content.substr(sep+1,content.size()));
						
						V[j].Offset = 8*byte+bit;
						//cout<<"\n Offset : "<<V[j].Offset;
					}
				
				}
				
				// GET NAME
				int name_offset = 17;
				string name_key = "          <Name>";
				int name_start = temp.find(name_key);
				int name_end = temp.find("<",name_start+name_offset);

				if(name_start!=-1 and name_end!=-1)
				{
					//cout<<"\n\n name,"<<temp<<",off_s,"<<name_start<<",Off_e,"<<name_end<<endl;
					content = temp.substr(name_start+name_offset-1,name_end-name_offset+1); 
					V[j].Name = content;
				//	cout<<"\nName : "<<V[j].Name;

				}
				
				// GET TYPE
				int type_offset = 25;
				string type_key = "          <DataTypeName>";
				int type_start = temp.find(type_key);
				int type_end = temp.find("<",type_start+type_offset);

				if(type_start!=-1 and type_end!=-1)
				{
					//cout<<"\n\ntype_key,"<<temp<<",off_s,"<<Offset_start<<",Off_e,"<<Offset_end<<endl;
					content = temp.substr(type_start+type_offset-1,type_end-type_offset+1);
					V[j].Type = content;
					//cout<<"\n Type : "<<V[j].Type;

				}
			
			//cout<<"\nindex : "<<j;
				}
			if(VAR_end!=-1)
			{	
		//	cout<<"\n Here : "<<temp;
				j++;
				inside = false;
				break;
			}
				
			getline(fin,temp,'\n');
			}
			

			//cout<<"\n To be processed : "<<temp;

		}	
		
		n_Var = j;
		Print_Var_ToFile();
		Linking_Var();
		Print_Parts_ToFile(P);
		PartsWiresFile();
	}
	
	void Matrix::Linking_Var(){
		
		int index = 0;
		for(int i = 0;i<n_parts;i++)
		{
			bool equal = false;
			

			for(int j = 0;j<i;j++)
				if(P[i].name == P[j].name or isNumber(P[i].name) or P[i].name=="o")
					{
						equal = true;
						j=n_parts+1; // exit from loop	
					}
					
					if(!equal)
					{
						string temp;
						cout<<"\n Variable : "<<P[i].name<<" is linked to : ";
						cin>>temp;

						V[getVarIndex(temp,V)].Linked = P[i].name;	
						index++;
					}	

		}
		
	}
	
	void Matrix::Print_Var_ToFile()
	{
		fstream fout;
		fout.open(VARIABLES_FILE.c_str(),ios::out);
		
		for(int j=0;j<n_Var;j++)
			{
				fout<<"\n"<<V[j].Name;
				fout<<","<<V[j].Type;
				fout<<","<<V[j].Offset;
				fout<<","<<V[j].Linked;
				fout<<",";
			}
		fout.close();	
	}
		
// Utilities	
	void Matrix::ToFile()
	{
		fstream fout;
		fout.open("Parts.txt",ios::in);
		cout<<" Open : "<<fout.is_open()<<endl;
		
		for(int i=0;i<n_parts;i++)
			{
				fout<<"\nName : "<<P[i].name;
				fout<<" Access_Scope_ID : "<<P[i].Access_Scope_ID;
				fout<<" Name_ID : "<<P[i].Name_ID;
				fout<<" riga: "<<P[i].r;
				fout<<" colonna : "<<P[i].c;
			}
		fout.close();
	}
	
	void Matrix::Print_L()
	{
		cout<<"\nPrint_L : \n";
		cout<<"              ";
		for(int i =0;i<c_size;i++)
		cout<<i<<" ";
		

		cout<<endl;
		for(int i =1;i<r_size;i++)
		{
			cout<<"              "<<i<<" ";
			for(int j = 0;j<c_size;j++)
			{
				cout<<L[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	
	void Matrix::Print_w()
	{
		cout<<"\nPrint_W : \n";
		
		cout<<"  ";
		for(int i =0;i<c_w;i+=3)
		{
		cout<<std::setw(5) << std::setfill(' ')<<i;
		cout<<std::setw(5) << std::setfill(' ')<<i+1;
		cout<<std::setw(5) << std::setfill(' ')<<i+2;
		}
		cout<<"\n  ";
		for(int i =0;i<c_size;i++)
		{
		cout<<std::setw(5) << std::setfill(' ')<<"I";
		cout<<std::setw(5) << std::setfill(' ')<<"S";
		cout<<std::setw(5) << std::setfill(' ')<<"Q";
		}
		cout<<endl;
		for(int i =1;i<r_w;i++)
		{
			cout<<std::setw(3) << std::setfill(' ')<<i<<" ";
			for(int j = 0;j<c_w;j++)
			{
				cout<<std::setw(3) << std::setfill(' ') <<w[i][j]<<"  ";
			}
			cout<<endl;
		}
	}
	
	void Matrix::Print_Parts(Parts P [], int k){
		cout<<"\nParts :  \n";
			for(int i=0;i<k;i++)
			{
				cout<<"\nAccess_Scope_ID : "<<P[i].Access_Scope_ID;
				cout<<"\nName_ID : "<<P[i].Name_ID;
				cout<<"\nName : "<<P[i].name;
				cout<<"\n k: "<<i;
				cout<<"\n r: "<<P[i].r;
				cout<<"\n c: "<<P[i].c<<endl;
			}
}
	
	void Matrix::Print_Parts_ToFile(Parts P[]){
		fstream fout;
		fout.open(PARTS_FILE.c_str(),ios::out);
	
			fout<<"  <Parts>";
			for(int i=0;i<n_parts;i++)
			{
				if(P[i].name!="o" and !isNumber(P[i].name))
				{
				fout<<"\n    <Access Scope=\"GlobalVariable\" UId=\""<<P[i].Access_Scope_ID<<"\">";
				fout<<"\n      <Symbol>";				
				fout<<"\n       <Component Name=\""<<V[getVarIndex(P[i].name)].Name<<"\" />";			
				fout<<"\n        <Address Area=\"Memory\" Type=\""<<V[getVarIndex(P[i].name)].Type<<"\" BitOffset=\""<<V[getVarIndex(P[i].name)].Offset<<"\" Informative=\"true\" />";
				fout<<"\n      </Symbol>";
				fout<<"\n    </Access>";
				}
			}
			for(int i=0;i<n_parts;i++)
			{
				if(P[i].Contact)
				fout<<"\n    <Part Name=\"Contact\" UId=\""<<P[i].Name_ID<<"\" /> ";
				if(P[i].Or)
				{
					fout<<"\n    <Part Name=\"O\" UId=\""<<P[i].Name_ID<<"\" > ";
					fout<<"\n    <TemplateValue Name=\"Card\" Type=\"Cardinality\">"<<P[i].Cardinality<<"</TemplateValue>";
					fout<<"\n	 </Part>";
				}

				if(P[i].Coil)
				fout<<"\n    <Part Name=\"Coil\" UId=\""<<P[i].Name_ID<<"\" /> ";
			}
			fout<<"\n  </Parts>";
			fout.close();
}
	
	
	void Matrix::Print_Wires(Wires W[]){
		cout<<"\nParts :  \n";
			for(int i=0;i<N_Wire;i++)
			{
				cout<<"\nID : "<<W[i].ID;
				for(int j =0;j<W[i].cont_in;j++)
					cout<<"\nIn["<<j<<"] : "<<W[i].In[j];

				cout<<"\nOut : "<<W[i].Out;
				cout<<"\nSelf : "<<W[i].Self;
				cout<<"\nOperand : "<<W[i].Operand;
				cout<<endl;

			}
	
}

	void Matrix::Print_Wires_ToFile(Wires W[]){
		fstream fout;
		fout.open(WIRES_FILE.c_str(),ios::out);
		
		//START ALL
		fout<<"<Wires>";
			for(int i=0;i<N_Wire;i++)
			{
				//ID
				fout<<"\n  <Wire UId=\""<<W[i].ID<<"\">";
				//OUT
				if(W[i].Out!=0)
				 fout<<"\n    <NameCon UId=\""<<W[i].Out<<"\" Name=\"out\" />";
				 
				 //IN
				 if(W[i].P)
					fout<<"\n      <Powerrail />";
				for(int j =0;j<W[i].cont_in;j++)
				{
					
					if(!W[i].P and W[i].in_index>0)
				 		fout<<"\n    <NameCon UId=\""<<W[i].In[j]<<"\" Name=\"in"<<W[i].in_index<<"\" />";
				 	else
				 		fout<<"\n    <NameCon UId=\""<<W[i].In[j]<<"\" Name=\"in\" />";
				 	
				}
				//SELF
				if(W[i].Self!=0)
				{
					fout<<"\n    <IdentCon UId=\""<<W[i].Self<<"\" />";
      				fout<<"\n    <NameCon UId=\""<<W[i].Operand<<"\" Name=\"operand\" />";	
				}
				//END WIRE
				fout<<"\n</Wire>";
			}
			//END ALL
			fout<<"\n</Wires>";
			fout.close();	
}

void Matrix::Print_Wires_Matrix_ToFile()
	{
		fstream fout;
		fout.open(WIRES_MATRIX_FILE.c_str(),ios::out);

		fout<<"  ";
		for(int i =0;i<c_w;i+=3)
		{
		fout<<std::setw(5) << std::setfill(' ')<<i;
		fout<<std::setw(5) << std::setfill(' ')<<i+1;
		fout<<std::setw(5) << std::setfill(' ')<<i+2;
		}
		fout<<"\n  ";
		for(int i =0;i<c_size;i++)
		{
		fout<<std::setw(5) << std::setfill(' ')<<"I";
		fout<<std::setw(5) << std::setfill(' ')<<"S";
		fout<<std::setw(5) << std::setfill(' ')<<"Q";
		}
		fout<<endl;
		for(int i =1;i<r_w;i++)
		{
			fout<<std::setw(3) << std::setfill(' ')<<i<<" ";
			for(int j = 0;j<c_w;j++)
			{
				fout<<std::setw(3) << std::setfill(' ') <<w[i][j]<<"  ";
			}
			fout<<endl;
		}
	}


	bool Matrix::isNumber(const string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

bool Matrix::isAlpha(const string& str)
{
    char search[str.length()+1];
	strcpy(search, str.c_str()); 

	if(isalpha(search[0]))
	return true;
	else
	return false;
}
	int Matrix::getPartsIndex(string name,Parts P[],int r ,int c)
	{
		for(int i =0;i<100;i++)
			if(P[i].name == name and P[i].r == r and P[i].c ==c)
				return i;
		return 0;
	}
	
	int Matrix::getWiresIndex(Wires W[],int r ,int c)
	{
		for(int i =0;i<100;i++)
			if( W[i].r == r and W[i].c ==c)
				return i;
		return -1;
	}
	
	int Matrix::getPartsIndex(string name,Parts P[])
	{
		for(int i =0;i<100;i++)
			if(P[i].name == name)
				return i;
		return 0;
	}
	
	int Matrix::getWiresIndex(string num,Wires W[],int r, int c)
	{
		for(int i=0;i<100;i++)
			if(W[i].ID == stoi(num) and W[i].r == r and W[i].c ==c)
				return i;
		return -1;
	}

	int Matrix::getWiresIndex(string num,Wires W[])
	{
		for(int i=0;i<100;i++)
			if(W[i].ID == stoi(num))
				return i;
		return -1;
	}

	int Matrix::getVarIndex(string name,Var_DB V[])
	{
		for(int i=0;i<2000;i++)
			if(V[i].Name == name)
				return i;
		return -1;
	}	
	
	int Matrix::getVarIndex(string name)
	{
		for(int i=0;i<2000;i++)
			if(V[i].Linked == name)
				return i;
		return -1;
	}
	
	void Matrix::PartsWiresFile(){
		fstream finP;
		finP.open(PARTS_FILE.c_str(),ios::in);
		fstream finW;
		finW.open(WIRES_FILE.c_str(),ios::in);
		fstream fout;
		fout.open(PW_FILE.c_str(),ios::out);
		fstream finB;
		finB.open("Before.txt",ios::in);
		fstream finA;
		finA.open("After.txt",ios::in);
		
		while(!finB.eof()){
			string temp;
			getline(finB,temp,'\n');
			fout<<temp<<"\n";
		}
		while(!finP.eof()){
			string temp;
			getline(finP,temp,'\n');
			fout<<temp<<"\n";
		}
		while(!finW.eof()){
			string temp;
			getline(finW,temp,'\n');
			fout<<temp<<"\n";
		}
		while(!finA.eof()){
			string temp;
			getline(finA,temp,'\n');
			fout<<temp<<"\n";
		}
		fout.close();		
	}
	
		Matrix::~Matrix(){
		cout<<"\nDistruzione in corso\n";

	}
