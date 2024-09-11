#include "Define.h"
#include <random>
#include <iomanip> // WhiteSpace�� �����ϴ� ��ɾ ������ �ִ�.

#include <thread>

random_device rd;
mt19937 mt(rd());
uniform_int_distribution<int> Random_int {0,2};

float fMatrixOne[4][4]{};

float fMatrixTwo[4][4]{};

float fMatrixResult[4][4]{};

void InsertMatrix()
{
	int iTwoNum{}; // 2�� ����

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

void Matrix_X() // ����� ��
{
	memset(fMatrixResult, 0, sizeof(fMatrixResult));

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			for (int r = 0; r < 4; ++r)
			{
				fMatrixResult[i][j] += fMatrixOne[i][r] * fMatrixTwo[r][j];
			}
		}
	}

	cout << "=================================" << endl;
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

void ChangeNum(float* _pfChangeA, float* _pfChangeB)
{
	float fChange = *_pfChangeB;
	*_pfChangeB = *_pfChangeA;
	*_pfChangeA = fChange;
}


void Matrix_Det() // ��Ľ�
{
	int iCol{}; // ��
	int iRaw{}; // ��

	float fMatrix3_One[4][3][3]{}; // 3x3 ����� 4���� �����Ƿ� 4���� ����� ��

	float fMatrix3_Two[4][3][3]{}; // 3x3 ����� 4���� �����Ƿ� 4���� ����� ��


	float fMatrix2_One[4][2][2]{}; // 2x2 ����� 4���� �����Ƿ� 4���� ����� ��

	float fMatrix2_Two[4][2][2]{}; // 2x2 ����� 4���� �����Ƿ� 4���� ����� ��


	float fDet[2]{}; // 0 �� ù��° ��� 1�� �ι�° ���

	for (int i = 0; i < 4; ++i)
	{
		iCol = 0;
		iRaw = 0;

		for (int j = 0; j < 4; ++j) // 4x4 ���� 3x3 ���� ������
		{
			iRaw = 0;

			if (j == 0)
			{
				continue; // ���� ������ ���̸� ���� ������ �Ѿ
			}
			for (int k = 0; k < 4; ++k)
			{
				if (k == i)
				{
					continue; // ���� ������ ���̸� ���� ������ �Ѿ
				}

				fMatrix3_One[i][iCol][iRaw] = fMatrixOne[j][k] * fMatrixOne[0][i] * powf(-1, (0 + i));

				fMatrix3_Two[i][iCol][iRaw] = fMatrixTwo[j][k] * fMatrixTwo[0][i] * powf(-1, (0 + i));

				++iRaw;
			}
			++iCol;
		}

	
			fDet[0] += (fMatrix3_One[i][0][0] * fMatrix3_One[i][1][1] * fMatrix3_One[i][2][2]
				+ fMatrix3_One[i][0][1] * fMatrix3_One[i][1][2] * fMatrix3_One[i][2][0]
				+ fMatrix3_One[i][0][2] * fMatrix3_One[i][1][0] * fMatrix3_One[i][2][1])
				- (fMatrix3_One[i][0][0] * fMatrix3_One[i][1][2] * fMatrix3_One[i][2][1]
					+ fMatrix3_One[i][0][1] * fMatrix3_One[i][1][0] * fMatrix3_One[i][2][2]
					+ fMatrix3_One[i][0][2] * fMatrix3_One[i][1][1] * fMatrix3_One[i][2][0]);

			fDet[1] += (fMatrix3_Two[i][0][0] * fMatrix3_Two[i][1][1] * fMatrix3_Two[i][2][2]
				+ fMatrix3_Two[i][0][1] * fMatrix3_Two[i][1][2] * fMatrix3_Two[i][2][0]
				+ fMatrix3_Two[i][0][2] * fMatrix3_Two[i][1][0] * fMatrix3_Two[i][2][1])
				- (fMatrix3_Two[i][0][0] * fMatrix3_Two[i][1][2] * fMatrix3_Two[i][2][1]
					+ fMatrix3_Two[i][0][1] * fMatrix3_Two[i][1][0] * fMatrix3_Two[i][2][2]
					+ fMatrix3_Two[i][0][2] * fMatrix3_Two[i][1][1] * fMatrix3_Two[i][2][0]);

	}


	cout << "ù��° ����� ��Ľ��� ��" << endl;
	cout << setw(3) << fDet[0] << endl;


	cout << "�ι�° ����� ��Ľ��� ��" << endl;
	cout << setw(3) << fDet[1] << endl;

}

void Matrix_OddNum()
{
	float fMatrix_One_Even[4][4]{};
	float fMatrix_Two_Even[4][4]{};

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if ((int)fMatrixOne[i][j] % 2 == 0)
			{
				fMatrix_One_Even[i][j] = fMatrixOne[i][j];
			}

			if ((int)fMatrixTwo[i][j] % 2 == 0)
			{
				fMatrix_Two_Even[i][j] = fMatrixTwo[i][j];
			}
		}
	}

	cout << "=================================" << endl;
	cout << "ù��° ���" << endl;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			cout << setw(3) << fMatrix_One_Even[i][j];
		}
		cout << endl;
	}
	cout << "=================================" << endl;

	cout << endl;

	cout << "=================================" << endl;
	cout << "�ι�° ���" << endl;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			cout << setw(3) << fMatrix_Two_Even[i][j];
		}
		cout << endl;
	}
	cout << "=================================" << endl;

	cout << endl;


	char ccIn{};

	while (true)
	{
		cin >> ccIn;

		if (ccIn == 'e')
		{
			break;
		}

	}

	float fMatrix_One_Odd[4][4]{};
	float fMatrix_Two_Odd[4][4]{};

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if ((int)fMatrixOne[i][j] % 2 != 0)
			{
				fMatrix_One_Odd[i][j] = fMatrixOne[i][j];
			}

			if ((int)fMatrixTwo[i][j] % 2 != 0)
			{
				fMatrix_Two_Odd[i][j] = fMatrixTwo[i][j];
			}
		}
	}

	cout << "=================================" << endl;
	cout << "ù��° ���" << endl;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			cout << setw(3) << fMatrix_One_Odd[i][j];
		}
		cout << endl;
	}
	cout << "=================================" << endl;

	cout << endl;

	cout << "=================================" << endl;
	cout << "�ι�° ���" << endl;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			cout << setw(3) << fMatrix_Two_Odd[i][j];
		}
		cout << endl;
	}
	cout << "=================================" << endl;

	cout << endl;

	ccIn = '\0';
	while (true)
	{
		cin >> ccIn;

		if (ccIn == 'e')
		{
			break;
		}

	}

}

void Matrix_T() // ��ġ���
{
	for (int i = 1; i < 4; ++i) // �ٲٱ� 1
	{
		ChangeNum(&fMatrixOne[0][i], &fMatrixOne[i][0]);
		ChangeNum(&fMatrixTwo[0][i], &fMatrixTwo[i][0]);
	}

	for (int i = 2; i < 4; ++i) // �ٲٱ� 2
	{
		ChangeNum(&fMatrixOne[3][i], &fMatrixOne[i][3]);
		ChangeNum(&fMatrixTwo[3][i], &fMatrixTwo[i][3]);
	}

	ChangeNum(&fMatrixOne[2][1], &fMatrixOne[1][2]);
	ChangeNum(&fMatrixTwo[2][1], &fMatrixTwo[1][2]);

	Matrix_Det();

	cout << "=================================" << endl;
}

void Matrix_Int_X(char _Num) // ��� ���ϱ�
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
	//thread t1(Matrix_Int_X,'5');

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
		case 'm': // ����
			Matrix_X();
			break;

		case 'a': // ����
			Matrix_Plus();
			break;

		case 'd': // �E��
			Matrix_Minus();
			break;

		case 'r': // ��Ľ��� ��
			Matrix_Det();
			break;

		case 't': // ��ġ��� �� �� ��Ľ��� ��
			Matrix_T();
			break;

		case 'e': // ¦���� �ٽ� ������ Ȧ�� 
			Matrix_OddNum();
			break;

		case 's':
			InsertMatrix();
			break;

		case 'q':
			return 0;
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