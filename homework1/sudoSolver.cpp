#include "stdafx.h"
#include "sudoSolver.h"
#include "sudo.h"

extern void print(int *matrix);
extern int count;

sudoSolver::sudoSolver(int matrix[9][9],int **matrixarray)
{
	//一开始忘了初始化maxempty了
	this->maxempty = 0;
	this->solved = false;
	this->matrixarray = matrixarray;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			this->rowarray[i][j] = (i / 3) * 3 + j / 3;
		}
	}
	for(int i=0;i<9;i++)
		for (int j = 0; j < 9; j++) {
			this->matrix[i][j] = matrix[i][j];
			this->line[i][j] = this->column[i][j] = this->grid[i][j] = true;
		}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int num = this->matrix[i][j];
			if (num != 0) {
				this->line[i][num - 1] = false;
				this->column[j][num - 1] = false;
				this->grid[rowarray[i][j]][num - 1] = false;
			}
		}
	}
	bool flag = true;
	while (flag)
	{
		flag = false;
		for (int i = 0; i < 81; i++) {
			if (this->matrix[i / 9][i % 9] != 0)
				continue;
			int row = i/9;
			int col = i%9;
			int count = 0;
			int num = 0;
			for (int j = 1; j <= 9; j++) {
				if (canFill(row, col, j))
				{
					count += 1;
					num = j;
				}
			}
			if (count == 1)
			{
				fillin(row, col, num);
				flag = true;
			}
		}
	}

	for (int i = 0; i < 81; i++) {
		//这个是个问题
		int num =this->matrix[i / 9][i % 9];
		if (num == 0) {
			this->rchoice[maxempty] = i/9;
			this->cchoice[maxempty++] = i%9;
		}
	}

}




sudoSolver::~sudoSolver()
{
}
void sudoSolver:: solve(int arrayindex) {

	if (this->solved == true)
		return;
	if (arrayindex > maxempty - 1) {
		this->solved = true;
		int* newmatrix = (int *)malloc(81 * sizeof(int));
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				newmatrix[i * 9 + j] = this->matrix[i][j];
		this->matrixarray[count] = newmatrix;
		count++;
		return;
	}
	int i = rchoice[arrayindex];
	int j = cchoice[arrayindex];
//	print(this->matrix);
	for (int k = 1; k <= 9; k++) {
		if (canFill(i, j, k)) {
			this->fillin(i, j, k);
			solve(arrayindex + 1);
			this->erase(i, j, k);
		}
	}

}
void sudoSolver::fillin(int i, int j, int num)
{
	this->matrix[i][j] = num;
	this->line[i][num-1] = false;
	this->column[j][num-1] = false;
	this->grid[rowarray[i][j]][num-1] = false;
}
void sudoSolver::erase(int i,int j,int num)
{
	this->matrix[i][j] = 0;
	this->line[i][num-1] = true;
	this->column[j][num-1] = true;
	this->grid[rowarray[i][j]][num-1] = true;
}
bool sudoSolver::canFill(int i, int j, int num)
{
	return matrix[i][j]==0&&line[i][num-1] && column[j][num-1] && grid[rowarray[i][j]][num-1];
}
bool sudoSolver::getSolved() {
	return this->solved;
}
 /*void sudoSolver:: print(int matrix[9][9]) {

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}*/
 
int* sudoSolver:: getMatrix() {
	int *mat = (int *)malloc(81*sizeof(int ));
	for (int i = 0; i < 81; i++) {
		mat[i] = this->matrix[i / 9][i % 9];
	}
	return mat;
}