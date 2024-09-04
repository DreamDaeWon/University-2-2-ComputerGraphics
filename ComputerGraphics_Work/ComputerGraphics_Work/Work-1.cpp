#include "Define.h"
#include <random>
#include <iomanip>


random_device rd;
mt19937 mt(rd());
uniform_int_distribution<int> Random_int {0,2};

float fMatrixOne[4][4]{};

float fMatrixTwo[4][4]{};

float fMatrixResult[4][4]{};

void InsertMatrix()
{
	int iTwoNum{}; // 2ÀÇ °³¼ö

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (iTwoNum == 2)
			{
				while (true)
				{
					fMatrixOne[i][j] = Random_int(mt);

					if (fMatrixOne[i][j] != 2)
					{
						break;
					}
				}
			}
			else
			{
				fMatrixOne[i][j] = Random_int(mt);
			}
			if (fMatrixOne[i][j] == 2)
			{
				++iTwoNum;
			}
		}
	}


	iTwoNum = 0;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (iTwoNum == 2)
			{
				while (true)
				{
					fMatrixTwo[i][j] = Random_int(mt);

					if (fMatrixTwo[i][j] != 2)
					{
						break;
					}
				}
			}
			else
			{
				fMatrixTwo[i][j] = Random_int(mt);
			}
			if (fMatrixTwo[i][j] == 2)
			{
				++iTwoNum;
			}
		}
	}
}



void Matrix_Plus()
{
	cout << "=================================" << endl;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			fMatrixResult[i][j] = fMatrixOne[i][j] + fMatrixTwo[i][j];
		}
	}
	
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			cout << setw(3) << fMatrixResult[i][j];
		}
		cout << endl;
	}
	cout << "=================================" << endl;

	cout << endl;
}

void Matrix_Minus()
{
	cout << "=================================" << endl;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			fMatrixResult[i][j] = fMatrixOne[i][j] - fMatrixTwo[i][j];
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			cout << setw(3) << fMatrixResult[i][j];
		}
		cout << endl;
	}
	cout << "=================================" << endl;

	cout << endl;
}

void Matrix_X()
{

}

void Matrix_Int_X(char _Num) // »ó¼ö °öÇÏ±â
{
	int Num = _Num - 48;

	float fMatrixResult_Two[4][4]{};

	cout << "=================================" << endl;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			fMatrixResult[i][j] = fMatrixOne[i][j] * Num;
			fMatrixResult_Two[i][j] = fMatrixTwo[i][j] * Num;
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			cout << setw(3) << fMatrixResult[i][j];
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			cout << setw(3) << fMatrixResult_Two[i][j];
		}
		cout << endl;
	}

	cout << "=================================" << endl;

	cout << endl;
}

int main()
{
	InsertMatrix();

	while (true)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				cout << setw(3) << fMatrixOne[i][j];
			}
			cout << endl;
		}

		cout << endl;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				cout << setw(3) << fMatrixTwo[i][j];
			}
			cout << endl;
		}
		char cIN{};
		cin >> cIN;

		switch (cIN)
		{
		case 'm': // °ö¼À

			break;

		case 'a': // µ¡¼À
			Matrix_Plus();
			break;

		case 'd': // –E¼À
			Matrix_Minus();
			break;

		case 'r':

			break;

		case 't':

			break;

		case 'e':

			break;

		case 's':
			InsertMatrix();
			break;

		case 'q':

			break;

		default:
			if (cIN <= '9' && cIN >= '1')
			{
				Matrix_Int_X(cIN);

				break;
			}
			else
			{
				continue;
			}
		}


	}

	





	return 0;
}