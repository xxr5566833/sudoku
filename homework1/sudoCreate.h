#pragma once

class sudoCreate
{
public:
	sudoCreate(int num,int **matrixarray);
	~sudoCreate();
	/*int  choose(int index, int increment,FILE* fp);
	void print(int *matrix);
	bool canFill(int i,int j,int num);
	void fillin(int i, int j, int num);
	void erase(int i,int j,int num);*/
	void getMatrix(int array[8]);
	void generateMatrix(int *array,int i,int n);
	static void swap(int *a,int *b);
private:
	int num;
	int count;
	int **matrixarray;
	int matrix[9][9];
	bool line[9][9];
	bool column[9][9];
	bool grid[9][9];
	static const int numarray[9] ;
	static const int map[81];
};

