#include "stdafx.h"
#include "CppUnitTest.h"
#include "../homework1/stdafx.h"
#include <fstream>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
struct Node {
	int num;
	struct Node* next[9];
};
typedef struct Node point;
point *head;
namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		

		/*如果发现你的编译一直有LINK2019错误，是因为你没有把原来的文件设置为lib..*/
		TEST_METHOD(TestCreate)
		{
			int* matrixarray[100000];
			int array[8] = { 1,2,4,5,6,7,8,9 };
			head = (point *)malloc(sizeof(point));
			memset(head,0,sizeof(point));
			sudoCreate creater = sudoCreate(100000, matrixarray);
			creater.generateMatrix(array, 0, 8);
			bool gloabelflag = false;
			int i = 0;
			for ( i ; i < 100000; i++) {
				int *matrix = matrixarray[i];
				point *p = head;
				bool flag = true;
				for (int j = 0; j < 72; j++) {
					int num = matrix[j];
					if (p->next[num-1] == NULL) {
						point *q = (point *)malloc(sizeof(point));
						memset(q,0,sizeof(point));
						q->num = num;
						p->next[num-1] = q;
						flag = false;
						break;
					}
					p = p->next[num-1];

				}
				if (flag == true)
				{
					int num = i;
					break;
				}
			}
			
			Assert::AreEqual(i, 100000);

		}
		TEST_METHOD(TestSwap) {

			int a = 5;
			int b = 6;
			sudoCreate::swap(&a, &b);
			Assert::AreEqual(a,6);
			Assert::AreEqual(b,5);
		}
		TEST_METHOD(TestcanFill) {

			int *matrixarray[100];
			int matrix[9][9] = {
				{0,0,5,3,0,0,0,0,0},
				{8,0,0,0,0,0,0,2,0},
				{0,7,0,0,1,0,5,0,0},
				{4,0,0,0,0,5,3,0,0},
				{0,1,0,0,7,0,0,0,6},
				{0,0,3,2,0,0,0,8,0},
				{0,6,0,5,0,0,0,0,9},
				{0,0,4,0,0,0,0,3,0},
				{0,0,0,0,0,9,7,0,0}

			};
			sudoSolver solver = sudoSolver(matrix,matrixarray);
			Assert::AreEqual(solver.canFill(0,0,5),false);
			Assert::AreEqual(solver.canFill(0,0,3),false);
			Assert::AreEqual(solver.canFill(0,0,4),false);
			Assert::AreEqual(solver.canFill(0,0,1),true);
			/*rowarray not initial ,dont use gloabal var*/
		}
		TEST_METHOD(TestFillin) {
			int *matrixarray[100];
			int matrix[9][9] = {
				{ 0,0,5,3,0,0,0,0,0 },
				{ 8,0,0,0,0,0,0,2,0 },
				{ 0,7,0,0,1,0,5,0,0 },
				{ 4,0,0,0,0,5,3,0,0 },
				{ 0,1,0,0,7,0,0,0,6 },
				{ 0,0,3,2,0,0,0,8,0 },
				{ 0,6,0,5,0,0,0,0,9 },
				{ 0,0,4,0,0,0,0,3,0 },
				{ 0,0,0,0,0,9,7,0,0 }

			};
			sudoSolver solver = sudoSolver(matrix, matrixarray);
			solver.fillin(0, 0, 1);
			Assert::AreEqual(solver.getMatrix()[0],1);
			Assert::AreEqual(solver.canFill(0,0,1),false);
		}
		TEST_METHOD(TestErase) {
			int *matrixarray[100];
			int matrix[9][9] = {
				{ 0,0,5,3,0,0,0,0,0 },
				{ 8,0,0,0,0,0,0,2,0 },
				{ 0,7,0,0,1,0,5,0,0 },
				{ 4,0,0,0,0,5,3,0,0 },
				{ 0,1,0,0,7,0,0,0,6 },
				{ 0,0,3,2,0,0,0,8,0 },
				{ 0,6,0,5,0,0,0,0,9 },
				{ 0,0,4,0,0,0,0,3,0 },
				{ 0,0,0,0,0,9,7,0,0 }

			};
			sudoSolver solver = sudoSolver(matrix, matrixarray);
			solver.erase(0, 2, 5);
			Assert::AreEqual(solver.getMatrix()[2], 0);
			Assert::AreEqual(solver.canFill(0, 2, 5), true);
		}
		
	};
}