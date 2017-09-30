#pragma once
#include<iostream>
#include <fstream>
#include <sstream>

class sudo
{
private:
	int m[9][9];
	public:
		sudo();
		~sudo();
		static void print(int *matrixarray[],int max)
		{	
			char *str = (char *)malloc(max * 163*sizeof(char)+1);
			int index = 0;
			for (int i = 0; i < max; i++) {
				int *matrix = matrixarray[i];
				for (int i = 0; i <9; i++) {
					for (int j = 0; j < 9; j++) {
						str[index++]= matrix[i * 9 + j]+'0';
						str[index++] = ' ';
					}
					str[index-1] = '\n';
				}
				str[index++] = '\n';
			}
			str[index] = '\0';
			std::fstream out("sudoku.txt",std::ios::out);
			out << str;
			out.close();
			/*FILE* fp = fopen("sudoku.txt","w");
			fprintf(fp,"%s", str);
			fclose(fp);*/
		}
		static void print( int *matrix,FILE* fp) {
			/*控制台的sudoku.exe的生成的文件的位置和ide里运行生成文件的位置不一样！*/
			char * str = (char *)malloc(164*sizeof(char ));
			int index = 0;
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					str[index++]=matrix[i * 9 + j];
					//fprintf(fp,"%d",matrix[i*9+j]);
					if (j != 8)
						str[index++]=' ';
						//fprintf(fp, " ");
					//行末无空格！！
					//std::cout << matrix[i][j] << " ";
				}
				str[index++] = '\n';
				//fprintf(fp, "\n");
				//std::cout << std::endl;
			}
			str[index++] = '\n';
			str[index] = '\0';
			//fprintf(fp, "\n");
			fprintf(fp,"%s",str);
			//std::cout << std::endl;
		}
		static void printbyChar(int *matrix, FILE* fp) {
			/*控制台的sudoku.exe的生成的文件的位置和ide里运行生成文件的位置不一样！*/
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					fprintf(fp, "%d", matrix[i*9+j]);
					if (j != 8)
						fprintf(fp, " ");
					//行末无空格！！
					//std::cout << matrix[i][j] << " ";
				}
				fprintf(fp, "\n");
				//std::cout << std::endl;
			}
			fprintf(fp, "\n");
			//std::cout << std::endl;
		}
		static void print(int matrix[9][9], FILE* fp) {
			/*控制台的sudoku.exe的生成的文件的位置和ide里运行生成文件的位置不一样！*/
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					fprintf(fp, "%d", matrix[i][j]);
					if (j != 8)
						fprintf(fp, " ");
					//行末无空格！！
					//std::cout << matrix[i][j] << " ";
				}
				fprintf(fp, "\n");
				//std::cout << std::endl;
			}
			fprintf(fp, "\n");
			//std::cout << std::endl;
		}




};



