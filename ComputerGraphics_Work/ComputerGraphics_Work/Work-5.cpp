#include "Define.h"

struct Pos
{
	int iX{};
	int iY{};
	bool b{ false };
};


Pos MyBorad[30][30]{};

bool AllBoard[30][30]{};


Pos iSqare[2]{};


void PrintBoard()
{
	memset(&AllBoard,false,sizeof(AllBoard));

	Pos pSubPos[2]{};

	memcpy(&pSubPos,&iSqare,sizeof(iSqare));

	//{ // 나가는거 처리
	//	if (iSqare[0].iX < 0)
	//	{
	//		pSubPos[0].iX = iSqare[0].iX + 30;

	//		iSqare[0].iX = 0;
	//	}
	//	if (iSqare[0].iX >= 30)
	//	{
	//		pSubPos[0].iX = iSqare[0].iX - 30;

	//		iSqare[0].iX = 29;
	//	}

	//	if (iSqare[1].iX < 0)
	//	{
	//		pSubPos[1].iX = iSqare[1].iX + 30;

	//		iSqare[1].iX = 0;
	//	}
	//	if (iSqare[1].iX >= 30)
	//	{
	//		pSubPos[1].iX = iSqare[1].iX - 30;

	//		iSqare[1].iX = 29;
	//	}

	//	if (iSqare[0].iY < 0)
	//	{
	//		pSubPos[0].iY = iSqare[0].iY + 30;

	//		iSqare[0].iY = 0;
	//	}
	//	if (iSqare[0].iY >= 30)
	//	{
	//		pSubPos[0].iY = iSqare[0].iY - 30;

	//		iSqare[0].iY = 29;
	//	}

	//	if (iSqare[1].iY < 0)
	//	{
	//		pSubPos[1].iY = iSqare[1].iY + 30;

	//		iSqare[1].iY = 0;
	//	}
	//	if (iSqare[1].iY >= 30)
	//	{
	//		pSubPos[1].iY = iSqare[1].iY - 30;

	//		iSqare[1].iY = 29;
	//	}
	//}

	if(pSubPos[0].iX > pSubPos[0].iY)


	for (int i = iSqare[0].iY; i < iSqare[1].iY + 1; ++i)
	{
		for (int j = iSqare[0].iX; j < iSqare[1].iX + 1; ++j)
		{
			AllBoard[i][j] = true;
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
	cout << "원하시는 네모의 좌표를 입력해 주세요." << endl;

	cin >> iSqare[0].iX;
	cin >> iSqare[0].iY;

	cin >> iSqare[1].iX;
	cin >> iSqare[1].iY;
}


int main()
{
	CreatSqare();

	while (true)
	{
		PrintBoard();

		char cCin{};

		cin >> cCin;

		switch (cCin)
		{
		case 'x':

			break;

		case 'y':

			break;

		case 's':

			break;

		case 'j':

			break;

		case 'a':

			break;

		case 'm':

			break;


		case 'n':

			break;


		case 'r':

			break;

		case 'q':
			return 0;
			break;

		default:
			break;
		}
		

	}
}