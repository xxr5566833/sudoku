#include "stdafx.h"
#include "sudoCreate.h"
#include "sudo.h"

extern int rowarray[9][9];
extern int colarray[9][9];
//extern int *matrixarray[1000000];
extern void print(int *matrix);

const int sudoCreate::numarray[9] = { 3,4,5,6,7,8,9,1,2 };


const int sudoCreate::map[81] = {
	1,2,3,4,5,6,7,8,9,
	4,5,6,7,8,9,1,2,3,
	7,8,9,1,2,3,4,5,6,
	2,1,4,3,6,5,8,9,7,
	3,6,5,8,9,7,2,1,4,
	8,9,7,2,1,4,3,6,5,
	5,3,1,6,4,2,9,7,8,
	6,4,2,9,7,8,5,3,1,
	9,7,8,5,3,1,6,4,2
};
/*****************************************************
Description:
	sudoCreate 的构造函数
Input:
	需要产生的数独数量
Require:
	None
Concrete Function:
	1.初始化matrix矩阵，填0
	2.初始化line column数组，便于第一种生成算法的可填性的判断
******************************************************/
sudoCreate::sudoCreate(int num,int **matrixarray)
{
	this->num = num;
	this->count = 0;
	this->matrixarray = matrixarray;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			this->matrix[i][j] = 0;
			this->line[i][j] = true;
			this->column[i][j] = true;
		}
}

/*****************************************************
Description:
	第二种数独生成算法的启动函数。
	(这个函数耦合性还是比较大，还需要改进)
Input:
	第一行的数字组成的数组，i和n表示生成从第i个元素到第n个元素的全排列
	fp是文件指针
Return:
	None
Calls:
	swap,getMatrix,generateMatrix
Require:
	array不是空指针
	array要全排列的部分的长度和n相等
	i>=0
	fp不为空指针
Concrete Function:
	1.生成第一行的全排列（第一个数字不动）
	2.对于每一个全排列调用getMatrix函数来根据第一行生成9*9的矩阵
******************************************************/
void sudoCreate:: generateMatrix(int *array,int i,int n) {
	if (this->count == this->num) {
		return;
	}
	if (i == n) {
		getMatrix(array);
	}
	else
	{
		for (int j = i; j < n; j++)
		{
			this->swap(array+i,array+j);
			generateMatrix(array,i+1,n);
			this->swap(array+i,array+j);
		}

	}
}
/*****************************************************
Description:
	就是交换两个int指针上的数字的值，不细说了
Input:
	要交换的两个数字对应的指针
Return:
	None

Require:
	a,b不是空指针
Concrete Function:
	交换两个指针位置上的数字的值
******************************************************/

 void sudoCreate::swap(int *a ,int *b) {
	int temp;
	temp = *b;
	*b = *a;
	*a = temp;
}

/*****************************************************
Description:
	根据输入的第一行每个数字的位置，产生数独矩阵
	(这个函数耦合性还是比较大，还需要改进)
Input:
	第一行的数字组成的数组（不包括第一个数字）
	fp是要写入的文件的指针
Return:
	None
Calls:
	swap,sudo::pirnt()
Require:
	array不是空指针
	fp不是空指针
Concrete Function:
	1.根据生成的第一行的数字排列和已有的映射关系，产生整个数独矩阵
	2.对这个数独矩阵进行 行和列的交换，产生等价数独，并把这个数独矩阵存好
	3.当产生的数独矩阵数量达到要求时，输出产生的数独矩阵到文件中，结束程序
******************************************************/
void sudoCreate::getMatrix(int array[8])
{
	this->matrix[0][0] = 3;						//(0,0)上数字固定为3	
	for (int i = 1; i < 9; i++) {
		this->matrix[0][i] = array[i - 1];
	}
	/*根据map的关系生成相应的矩阵*/
	for (int i = 1; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			this->matrix[i][j] = this->matrix[0][map[i * 9 + j]-1];
		}
	}
	/*使用多层for循环产生行和列不同交换情况的组合
	具体是这样的：（从第0列开始）
	第一层循环是用于是否交换第1列和第2列
	第二层循环是用于第3,4,5列的不同排列情况，从(3,4,5)产生全排列可以这么交换：
	(3,4,5)交换(1,2)列得到(3,5,4)
	(3,5,4)交换(0,1)列得到(5,3,4)
	(5,3,4)交换(1,2)列得到(5,4,3)
	(5,4,3)交换(0,1)列得到(4,5,3)
	(4,5,3)交换(1,2)列得到(4,3,5)
	(4,3,5)交换(0,1)列得到(3,4,5)
	可以生成整个全排列并恢复为原来的状态
	这也是下面的switch语句的含义
	之后几层循环同理
	*/
	for (int i1 = 0; i1 < 2; i1++) {
		switch (i1) {
		case 0:
		case 1:
			for (int j = 0; j < 9; j++) {
				this->swap(&(matrix[j][1]),&(matrix[j][2]));
			}
			break;
		default:
			break;
		}
		for (int i2 = 0; i2 < 6; i2++) {
			switch (i2) {
			case 1:
			case 3:
			case 5:
				for (int j = 0; j < 9; j++) {
					this->swap(&(matrix[j][3]),&(matrix[j][4]));
				}
				break;
			case 0:
			case 2:
			case 4:
				for (int j = 0; j < 9; j++) {
					this->swap(&(matrix[j][4]),&(matrix[j][5]));
				}
				break;
			default:
				break;
			}
			for (int i3 = 0; i3 < 6; i3++) {
				switch (i3) {
				case 1:
				case 3:
				case 5:
					for (int j = 0; j < 9; j++) {
						this->swap(&(matrix[j][6]), &(matrix[j][7]));
					}
					break;
				case 0:
				case 2:
				case 4:
					for (int j = 0; j < 9; j++) {
						this->swap(&(matrix[j][7]), &(matrix[j][8]));
					}
					break;

				default:
					break;
				}
				for (int i4 = 0; i4 < 2; i4++) {
					switch (i4) {
					case 0:
					case 1:
						for (int j = 0; j < 9; j++) {
							this->swap(&(matrix[1][j]), &(matrix[2][j]));
						}
						break;
					default:
						break;
					}
					for (int i5 = 0; i5 < 6; i5++) {
						switch (i5) {
						case 1:
						case 3:
						case 5:
							for (int j = 0; j < 9; j++) {
								this->swap(&(matrix[3][j]), &(matrix[4][j]));
							}
							break;
						case 0:
						case 2:
						case 4:
							for (int j = 0; j < 9; j++) {
								this->swap(&(matrix[4][j]), &(matrix[5][j]));
							}
							break;
	
						default:
							break;
						}
						/*将产生的矩阵存好*/
						int* newmatrix = (int *)malloc(81*sizeof(int));
						for (int i = 0; i < 9; i++)
							for (int j = 0; j < 9; j++)
								newmatrix[i*9+j] = this->matrix[i][j];
						matrixarray[count] =newmatrix;
						this->count++;

						if (this->count == this->num) {
							return ;
						}

					}
				}
			}
		}
	}
	return ;
}
sudoCreate::~sudoCreate()
{}

/*bool sudoCreate::canFill(int i, int j, int num)
{
	//没有检查这个空是不是已经有值了！另外一个算法中不需要检测是因为我把所有空都跳出来了
	return this->matrix[i][j] == 0 && this->line[i][num - 1] && this->column[j][num - 1];
	
}*/

/*void sudoCreate:: fillin(int i, int j, int num)
{
	this->matrix[i][j] = num;
	this->line[i][num-1] = false;
	this->column[j][num - 1] = false;
}

void sudoCreate::erase(int i,int j,int num) {
	this->matrix[i][j] = 0;
	this->line[i][num - 1] = true;
	this->column[j][num - 1] = true;
}


int sudoCreate::  choose(int gridindex, int arrayindex,FILE* fp) {
	int  num = sudoCreate::numarray[arrayindex]; 
	for (int i = 0; i < 9; i++) {
		int row = rowarray[gridindex][i];
		int col = colarray[gridindex][i];
		if (this->canFill(row,col,num)) {
			this->fillin(row, col, num);
			if (gridindex == 8) {
				if (arrayindex == 8) {
					int* newmatrix = (int *)malloc(81 * sizeof(int));
					for (int i = 0; i < 9; i++)
						for (int j = 0; j < 9; j++)
							newmatrix[i * 9 + j] = this->matrix[i][j];
					matrixarray[count] = newmatrix;
					this->count++;

					if (this->count == this->num) {
						sudo::print(matrixarray, this->num);
						exit(0);
					}
				}
				else {
					choose(0, arrayindex + 1,fp);
				}
			}
			else {
				choose(gridindex + 1, arrayindex,fp);
			}
			this->erase(row, col, num);
		}
	}	
	return 0;
}
void sudoCreate:: print(int *matrix) {

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			std::cout << matrix[i*9+j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}*/
