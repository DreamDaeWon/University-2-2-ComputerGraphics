#include "Define.h"

struct Pos
{
	int iX{};
	int iY{};
	bool b{ false };
};


Pos MyBorad[30][30]{};

bool AllBoard[30][30]{};

int iRight{}; // ����
int iDown{}; // ����


Pos iSqare[2]{}; // ��ǻ� 0�� ������


void PrintBoard()
{
	memset(&AllBoard,false,sizeof(AllBoard));


	Pos pSubPos[2]{};

	if (iSqare[0].iY >= 30 && iSqare[0].iX >= 30)
	{
		iSqare[0].iX = iSqare[0].iX - 30;

		iSqare[0].iY = iSqare[0].iY - 30;
	}
	else if (iSqare[0].iX >= 30)
	{
		iSqare[0].iX = iSqare[0].iX - 30;
	}
	else if (iSqare[0].iY >= 30)
	{
		iSqare[0].iY = iSqare[0].iY - 30;
	}

	

	

	if (iSqare[0].iX < 0 && iSqare[0].iY < 0)
	{
		iSqare[0].iX = iSqare[0].iX + 30;
		iSqare[0].iY = iSqare[0].iY + 30;
	}
	else if (iSqare[0].iX < 0)
	{
		iSqare[0].iX = iSqare[0].iX + 30;
	}
	else if (iSqare[0].iY < 0)
	{
		iSqare[0].iY = iSqare[0].iY + 30;
	}




	// ������ �� ó��

	// ���� bool ������ ó���Ͽ��� ������ ������ �͵��� ������ ����


	for (int i = iSqare[0].iY; i < iSqare[0].iY + iDown; ++i)
	{
		for (int j = iSqare[0].iX; j < iSqare[0].iX + iRight; ++j)
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


	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			if (AllBoard[i][j])
			{
				cout << " 0 ";
			}
			else
			{
				cout << " . ";
			}
		}
		cout << endl;
	}
}


void CreatSqare()
{
	cout << "���Ͻô� �׸��� ��ǥ�� �Է��� �ּ���. (�»��)" << endl;

	cin >> iSqare[0].iX;
	cin >> iSqare[0].iY;

	cout << "���Ͻô� �׸��� ��ǥ�� �Է��� �ּ���. (�� �ϴ�)" << endl;
	cin >> iSqare[1].iX;
	cin >> iSqare[1].iY;


	// ���� ���� ���ϱ�
	iRight = iSqare[1].iX - iSqare[0].iX+1;
	iDown = iSqare[1].iY - iSqare[0].iY+1;

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
			iSqare[0].iX += 1;
			break;

		case 'X':
			iSqare[0].iX -= 1;
			break;

		case 'y':
			iSqare[0].iY += 1;
			break;

		case 'Y':
			iSqare[0].iY -= 1;
			break;

		case 's':
			--iRight;
			--iDown;
			break;

		case 'S':
			++iRight;
			++iDown;
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

		case 'a':
			++iRight;
			--iDown;
			break;

		case 'A':
			--iRight;
			++iDown;
			break;

		case 'm':
			cout << endl <<"�׸��� ���� : " << iRight << " * " << iDown << " = " << iRight * iDown << endl;
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