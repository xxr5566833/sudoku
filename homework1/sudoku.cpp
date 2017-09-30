// homework1.cpp: 定义控制台应用程序的入口点。
//
//一开始遇到明明已经定义了数组，但是还是说这个数组没定义或者其他很奇怪的
//问题是因为中文注释
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "sudoCreate.h"
#include "sudoSolver.h"

#define MAX 1000000


int *matrixarray[MAX];	
int count = 0;
int array[8] = { 1, 2, 4, 5, 6, 7, 8, 9 };
/*存储最后需要往文件中写的所有终局*/
int rowarray[9][9] = { 0 };
int colarray[9][9] = { 0 };
/*不知道起什么名字好...*/
/*从（行，列）到（所在九宫格是第几个，九宫格内的第几个位置）的转换（后者向前者转换
是相同的计算式子），提前记录对应的转换值，在用的时候就不用再计算了*/

void init();
/*这个函数就是计算上面这两个数组的*/

void readAndSolve(char* filepath);
void print(int *matrix);

int main(int argc,char* argv[])
{
	int num=0;
	char c;
	
	init();
	/*用于生成全排列的数组*/
	while (*++argv != NULL&&**argv == '-')
	{
		switch (*++*argv)
		{
		case'c':
			argv++;
			if (*argv == NULL)
			{
				std::cout << "please input a number" << std::endl;
				exit(0);
			}
			while ((c=*((*argv)++)) != '\0')
			{
				if (c >= '0'&&c <= '9')
				{
					num = num * 10 + c - '0';
					if (num > MAX)
					{
						std::cout << "too big number" << std::endl;
						break;
					}
				}
				else
				{
					std::cout << "input error" << std::endl;
					exit(0);
				}
			}
			{
				if (num == 0)
				{
					std::cout << "cannot smaller than 1" << std::endl;
					break;
				}
				FILE* fp = fopen("sudoku.txt", "w");
				sudoCreate creater = sudoCreate(num,matrixarray);
				//creater.choose(0,0,fp);
				creater.generateMatrix(array, 0, 8);
				sudo::print(matrixarray, num);
				fclose(fp);

			}
			break;
		case's':
			argv++;
			if (*argv == NULL)
			{
				std::cout << "please input a filepath" << std::endl;
			}
			readAndSolve(*argv);
			break;
		default:
			break;
		}
	}
	/*
	TODO:测试getline()函数的用法。
	}*/
	return 0;
}
/*****************************************************
Description:
	根据读入的文件路径，读取该文件内的数独问题，并解决
Input:
	文件路径的字符指针
Output:
	None
Require:
	None
Concrete Function:
	1.如果该路径下打开文件失败，则输出错误信息并结束程序
	2.根据路径打开文件-》读取好一个矩阵-》解决它
	直到文件结束
******************************************************/
void readAndSolve(char *filepath) {
	FILE* f;  
	FILE *fp;
	if ((f = fopen(filepath, "r")) == NULL || (fp = fopen("sudoku.txt", "w")) == NULL)
	{
		printf("cannot open file\n");
		exit(0);
	}
	int matrix[9][9] = { 0 };
	int temp;
	int i = 0;
	while (fscanf(f,"%d",&temp)!=EOF) {
		matrix[i / 9][i % 9] = temp;
		i++;
		if (i == 81) {
			sudoSolver* solver = new sudoSolver(matrix,matrixarray);
			solver->solve(0);
			if (!solver->getSolved()) {
				std::cout << "no solution" << std::endl;
			}
			delete solver;
			i = 0;
		}
	}
	sudo::print(matrixarray,count);
	fclose(fp);
	fclose(f);
}

void print(int *matrix) {

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			std::cout << matrix[i*9+j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void init()
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			rowarray[i][j] = (i / 3) * 3 + j / 3;
			colarray[i][j] = (i % 3) * 3 + j % 3;
		}
	}
}





