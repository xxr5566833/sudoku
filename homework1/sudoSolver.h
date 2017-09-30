#pragma once

class sudoSolver
{
public:
	sudoSolver(int matrix[9][9],int **matrixarray);
	~sudoSolver();
	 void solve(int index);
	 bool canFill(int i,int j,int num);
	 //static void print(int matrix[9][9]);
	 bool getSolved();
	 void fillin(int i,int j,int num);
	 void erase(int i, int j, int num);
	 int *getMatrix();
	
private:
	int **matrixarray;
	int matrix[9][9];
	int rchoice[81];
	int cchoice[81];
	bool line[9][9];
	bool column[9][9];
	bool grid[9][9];
	int maxempty;
	bool solved;
	int rowarray[9][9];
};

