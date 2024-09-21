#include "Define.h"

struct Pos
{
	int iX{};
	int iY{};
	bool b{ false };
};


Pos MyBorad[30][30]{};

bool AllBoard[30][30]{};
bool AllBoardTwo[30][30]{};

int iRight{}; // ����
int iDown{}; // ����


Pos iSquare[2]{}; // ��ǻ� 0�� ������


Pos iSquareTwo[2]{};
int iRightTwo{}; // ����
int iDownTwo{}; // ����

void PrintBoard()
{
	memset(&AllBoard, false, sizeof(AllBoard));
	memset(&AllBoardTwo, false, sizeof(AllBoardTwo));


	Pos pSubPos[2]{};

	if (iSquare[0].iY >= 30 && iSquare[0].iX >= 30)
	{
		iSquare[0].iX = iSquare[0].iX - 30;

		iSquare[0].iY = iSquare[0].iY - 30;
	}
	else if (iSquare[0].iX >= 30)
	{
		iSquare[0].iX = iSquare[0].iX - 30;
	}
	else if (iSquare[0].iY >= 30)
	{
		iSquare[0].iY = iSquare[0].iY - 30;
	}





	if (iSquare[0].iX < 0 && iSquare[0].iY < 0)
	{
		iSquare[0].iX = iSquare[0].iX + 30;
		iSquare[0].iY = iSquare[0].iY + 30;
	}
	else if (iSquare[0].iX < 0)
	{
		iSquare[0].iX = iSquare[0].iX + 30;
	}
	else if (iSquare[0].iY < 0)
	{
		iSquare[0].iY = iSquare[0].iY + 30;
	}




	// ������ �� ó��

	// ���� bool ������ ó���Ͽ��� ������ ������ �͵��� ������ ����


	for (int i = iSquare[0].iY; i < iSquare[0].iY + iDown; ++i)
	{
		for (int j = iSquare[0].iX; j < iSquare[0].iX + iRight; ++j)
		{
			int iX = j; // ��
			int iY = i; // ��

			if (iY < 0)
			{
				iY = iY + 30;
			}
			if (iX < 0)
			{
				iX = iX + 30;
			}
			if (iY >= 30)
			{
				iY = iY - 30;
			}
			if (iX >= 30)
			{
				iX = iX - 30;
			}



			if (iX >= 0 && iX <= 29 && iY >= 0 && iY <= 29)
			{
				AllBoard[iY][iX] = true;
			}
		}
	}





	if (iSquareTwo[0].iY >= 30 && iSquareTwo[0].iX >= 30)
	{
		iSquareTwo[0].iX = iSquareTwo[0].iX - 30;

		iSquareTwo[0].iY = iSquareTwo[0].iY - 30;
	}
	else if (iSquareTwo[0].iX >= 30)
	{
		iSquareTwo[0].iX = iSquareTwo[0].iX - 30;
	}
	else if (iSquareTwo[0].iY >= 30)
	{
		iSquareTwo[0].iY = iSquareTwo[0].iY - 30;
	}





	if (iSquareTwo[0].iX < 0 && iSquareTwo[0].iY < 0)
	{
		iSquareTwo[0].iX = iSquareTwo[0].iX + 30;
		iSquareTwo[0].iY = iSquareTwo[0].iY + 30;
	}
	else if (iSquareTwo[0].iX < 0)
	{
		iSquareTwo[0].iX = iSquareTwo[0].iX + 30;
	}
	else if (iSquareTwo[0].iY < 0)
	{
		iSquareTwo[0].iY = iSquareTwo[0].iY + 30;
	}




	// ������ �� ó��

	// ���� bool ������ ó���Ͽ��� ������ ������ �͵��� ������ ����


	for (int i = iSquareTwo[0].iY; i < iSquareTwo[0].iY + iDownTwo; ++i)
	{
		for (int j = iSquareTwo[0].iX; j < iSquareTwo[0].iX + iRightTwo; ++j)
		{
			int iX = j; // ��
			int iY = i; // ��

			if (iY < 0)
			{
				iY = iY + 30;
			}
			if (iX < 0)
			{
				iX = iX + 30;
			}
			if (iY >= 30)
			{
				iY = iY - 30;
			}
			if (iX >= 30)
			{
				iX = iX - 30;
			}



			if (iX >= 0 && iX <= 29 && iY >= 0 && iY <= 29)
			{
				AllBoardTwo[iY][iX] = true;
			}
		}
	}




	char cAllBoard[30][30]{};



	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			if (AllBoard[i][j])
			{
				cAllBoard[i][j] = '0';
			}
			else if (AllBoardTwo[i][j])
			{
				cAllBoard[i][j] = 'X';
			}
			else
			{
				cAllBoard[i][j] = '.';
			}

			if (AllBoard[i][j] && AllBoardTwo[i][j])
			{
				cAllBoard[i][j] = '#';
			}

		}
	}


	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			if (cAllBoard[i][j] == '0')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << " 0 ";
			}
			else if (cAllBoard[i][j] == 'X')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << " X ";
			}
			else if (cAllBoard[i][j] == '#')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cout << " # ";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << " . ";
			}
		}
		cout << endl;
	}

}


void CreatSqare()
{
	cout << "���Ͻô� �׸��� ��ǥ�� �Է��� �ּ���. (�»��)" << endl;

	cin >> iSquare[0].iX;
	cin >> iSquare[0].iY;

	cout << "���Ͻô� �׸��� ��ǥ�� �Է��� �ּ���. (�� �ϴ�)" << endl;
	cin >> iSquare[1].iX;
	cin >> iSquare[1].iY;


	// ���� ���� ���ϱ�
	iRight = iSquare[1].iX - iSquare[0].iX + 1;
	iDown = iSquare[1].iY - iSquare[0].iY + 1;

	cout << "���Ͻô� �� ��° �׸��� ��ǥ�� �Է��� �ּ���. (�»��)" << endl;

	cin >> iSquareTwo[0].iX;
	cin >> iSquareTwo[0].iY;

	cout << "���Ͻô� �� ��° �׸��� ��ǥ�� �Է��� �ּ���. (�� �ϴ�)" << endl;
	cin >> iSquareTwo[1].iX;
	cin >> iSquareTwo[1].iY;


	// ���� ���� ���ϱ�
	iRightTwo = iSquareTwo[1].iX - iSquareTwo[0].iX + 1;
	iDownTwo = iSquareTwo[1].iY - iSquareTwo[0].iY + 1;

}


int main()
{
	CreatSqare();

	while (true)
	{
		//system("cls");
		PrintBoard();

		char cCin{};

		cin >> cCin;

		switch (cCin)
		{
		case 'x':
			iSquare[0].iX += 1;
			break;

		case 'X':
			iSquare[0].iX -= 1;
			break;

		case 'y':
			iSquare[0].iY += 1;
			break;

		case 'Y':
			iSquare[0].iY -= 1;
			break;

		case 'w':
			iSquareTwo[0].iX += 1;
			break;

		case 'W':
			iSquareTwo[0].iX -= 1;
			break;

		case 'a':
			iSquareTwo[0].iY += 1;
			break;

		case 'A':
			iSquareTwo[0].iY -= 1;
			break;

		case 's':
			--iRight;
			--iDown;

			break;

		case 'S':
			++iRight;
			++iDown;
			break;

		case 'd':
	
			--iRightTwo;
			--iDownTwo;

			break;

		case 'D':
			++iRightTwo;
			++iDownTwo;
			break;


		case 'i':
			++iRight;
			break;
		case 'I':
			--iRight;
			break;

		case 'j':
			++iDown;
			break;

		case 'J':
			--iDown;
			break;

		case 'm':
			cout << endl << "�׸��� ���� : " << iRight << " * " << iDown << " = " << iRight * iDown << endl;
			system("pause");
			break;


		case 'n':
			cout << endl << "��ü ������ ���� �簢�� ������ ���� : " << ((float)((float)iRight * (float)iDown) / (float)(30.f * 30.f)) * 100.f << "%" << endl;
			system("pause");
			break;


		case 'r':
			system("cls");
			CreatSqare();
			break;

		case 'q':
			return 0;
			break;

		default:
			break;
		}


	}
}