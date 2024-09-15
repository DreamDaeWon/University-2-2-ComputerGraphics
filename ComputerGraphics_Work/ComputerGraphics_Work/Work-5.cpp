#include "Define.h"

struct Pos
{
	int iX{};
	int iY{};
	bool b{ false };
};


Pos MyBorad[30][30]{};

bool AllBoard[30][30]{};

int iRight{}; // 가로
int iDown{}; // 세로


Pos iSqare[2]{}; // 사실상 0만 쓸꺼임


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




	// 나가는 거 처리

	// 내가 bool 값으로 처리하였기 때문에 가능한 것들을 생각해 보자


	for (int i = iSqare[0].iY; i < iSqare[0].iY + iDown; ++i)
	{
		for (int j = iSqare[0].iX; j < iSqare[0].iX + iRight; ++j)
		{
			int iX = j; // 열
			int iY = i; // 행

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
	cout << "원하시는 네모의 좌표를 입력해 주세요. (좌상단)" << endl;

	cin >> iSqare[0].iX;
	cin >> iSqare[0].iY;

	cout << "원하시는 네모의 좌표를 입력해 주세요. (우 하단)" << endl;
	cin >> iSqare[1].iX;
	cin >> iSqare[1].iY;


	// 가로 세로 구하기
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
			cout << endl <<"네모의 면적 : " << iRight << " * " << iDown << " = " << iRight * iDown << endl;
			system("pause");
			break;


		case 'n':
			cout << endl << "전체 면적에 대한 사각형 면적의 비율 : " << ((float)((float)iRight * (float)iDown) / (float)(30.f * 30.f)) * 100.f << "%" << endl;
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