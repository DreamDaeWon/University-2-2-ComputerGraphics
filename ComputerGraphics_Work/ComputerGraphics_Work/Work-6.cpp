#include "Define.h"


random_device rd;
mt19937 mt(rd());
uniform_int_distribution<int> Random_int{ 0,29 };

uniform_int_distribution<int> Random_Dir{ 0,3 };

enum Dir {Dir_Left,Dir_Right, Dir_Up, Dir_Down};

struct Pos // ��ġ ����ü
{
	int iX{};
	int iY{};
};

struct Pos_And_Dir // ��ġ ����ü
{
	int iX{};
	int iY{};
	Dir eDir{};
};

struct Player
{
	int iX{};
	int iY{};
	bool bLive{}; // �����ϴ���? (����ؾ� �ϴ���?)
};

bool bAllRoad[30][30]{}; // ��

bool bNoCanMove[30][30]{}; // �̵��� �� ���� ��ġ True�� �̵� �Ұ�

list<Pos_And_Dir> listAllRoadPos{(0,0,Dir_Down)}; // ��� ������ ���� ��� ����Ʈ

char cAllBoard[30][30]{}; // ��ü ����

bool bAllRoadBoard[30][30]{}; // �游 ���� ǥ��

Pos Wall[30]{}; // ��ֹ�

Player GamePlayer{};

void PtintAll()
{

	memset(&cAllBoard, '1', sizeof(cAllBoard));

	for (int j = 0; j < 30; ++j)
	{
		cAllBoard[Wall[j].iY][Wall[j].iX] = 'X';
	}

	for (auto& iter : listAllRoadPos)
	{
		cAllBoard[iter.iY][iter.iX] = 'O';
	}

	if (GamePlayer.bLive == true)
	{
		cAllBoard[GamePlayer.iY][GamePlayer.iX] = '*';
	}

	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			if (cAllBoard[i][j] == 'O')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				//cout << cAllBoard[i][j] << " ";
			}
			else if (cAllBoard[i][j] == 'X')
			{
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);

				//cout << cAllBoard[i][j] << " ";
			}
			else if (cAllBoard[i][j] == '*')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			/*else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << 'X' << " ";
			}*/
			cout << cAllBoard[i][j] << " ";
			
		}
		cout << endl;
	}


}


void SetWall() // ��ֹ� ����
{
	GamePlayer.bLive = false;

	memset(&bNoCanMove, 0, sizeof(bNoCanMove));
	memset(&bAllRoad, 0, sizeof(bAllRoad));
	listAllRoadPos.clear();
	listAllRoadPos.push_back(Pos_And_Dir{0,0,Dir_Down});
	memset(&cAllBoard, ' ', sizeof(cAllBoard));
	memset(&bAllRoadBoard, 0, sizeof(bAllRoadBoard));
	memset(&Wall, 0, sizeof(Wall));


	bool bOut{};

	for (int i = 0; i < 30; ++i)
	{
		bOut = false;
		while (true)
		{
			Wall[i].iX = Random_int(mt);
			Wall[i].iY = Random_int(mt);
			bOut = true;
			for (int j = 0; j < i; ++j)
			{
				if ((Wall[i].iX == Wall[j].iX) && (Wall[i].iY == Wall[j].iY))
				{
					bOut = false;
					break;
				}
				else if (Wall[i].iX == 29 && Wall[i].iY == 29)
				{
					bOut = false;
					break;
				}
				else if (Wall[i].iX == 0 && Wall[i].iY == 0)
				{
					bOut = false;
					break;
				}
				else
				{
					bOut = true;
				}
			}

			if (bOut == true)
			{
				bNoCanMove[Wall[i].iY][Wall[i].iX] = true;

				break;
			}

		}
	}
}

bool CheckAllMove() // ��� ������ üũ
{
	bool bAllMove[4]{};
	
	for (auto& iter : listAllRoadPos)
	{
		bAllMove[iter.eDir] = true;
	}

	for (int i = 0; i < 4; ++i)
	{
		if (!bAllMove[i])
		{
			return false; // �� ����� ����
		}
	}

	return true; // �� ����� ����

}

Pos BackTracaking()
{
	system("cls");
	bNoCanMove[listAllRoadPos.back().iY][listAllRoadPos.back().iX] = true;

	listAllRoadPos.pop_back();

	Pos RePos{ listAllRoadPos.back().iX, listAllRoadPos.back().iY};
	
	PtintAll(); // �ӽ�
	//system("pause");
	return RePos;
}


Pos SetNextRoad(Pos NowPos)
{
	Pos NextPos = NowPos;

	bool CanMoveDir[4]{};

	memset(&CanMoveDir,true,sizeof(CanMoveDir));

	while (true)
	{
		Dir eNextDir = (Dir)Random_Dir(mt); // ������ ���ϱ�

		switch (eNextDir)
		{
		case Dir_Left:
			if ((NowPos.iX - 1 >= 0) &&
				(bNoCanMove[NowPos.iY][NowPos.iX - 1] != true))
			{
				Pos_And_Dir Input_Pos{ (NowPos.iX - 1),(NowPos.iY), (Dir_Left) };
				listAllRoadPos.push_back(Input_Pos);
				Pos RePos{ (NowPos.iX - 1),(NowPos.iY) };

				bNoCanMove[NowPos.iY][NowPos.iX - 1] = true;

				return RePos;

				
			}
			CanMoveDir[Dir_Left] = false;
			break;

		case Dir_Right:
			if ((NowPos.iX + 1 <= 29) &&
				(bNoCanMove[NowPos.iY][NowPos.iX + 1] != true))
			{
				Pos_And_Dir Input_Pos{ (NowPos.iX + 1),(NowPos.iY), (Dir_Right) };
				listAllRoadPos.push_back(Input_Pos);

				Pos RePos{ (NowPos.iX + 1),(NowPos.iY) };
				bNoCanMove[NowPos.iY][NowPos.iX + 1] = true;
				return RePos;

		
			}

			CanMoveDir[Dir_Right] = false;
			break;

		case Dir_Up:
			if ((NowPos.iY - 1 >= 0) &&
				(bNoCanMove[NowPos.iY - 1][NowPos.iX] != true))
			{
				Pos_And_Dir Input_Pos{ (NowPos.iX),(NowPos.iY - 1), (Dir_Up) };
				listAllRoadPos.push_back(Input_Pos);


				Pos RePos{ (NowPos.iX),(NowPos.iY - 1) };
				
				bNoCanMove[NowPos.iY - 1][NowPos.iX] = true;
				
				return RePos;

				

			}

			CanMoveDir[Dir_Up] = false;
			break;

		case Dir_Down:
			if ((NowPos.iY + 1 <= 29) &&
				(bNoCanMove[NowPos.iY + 1][NowPos.iX] != true))
			{
				Pos_And_Dir Input_Pos{ (NowPos.iX),(NowPos.iY + 1), (Dir_Down) };
				listAllRoadPos.push_back(Input_Pos);


				Pos RePos{ (NowPos.iX),(NowPos.iY + 1) };

				bNoCanMove[NowPos.iY + 1][NowPos.iX] = true;

				return RePos;

				

			}

			CanMoveDir[Dir_Down] = false;
			break;
		}

		int iFalse{};

		for (int i = 0; i < 4; ++i)
		{
			if (CanMoveDir[i] == false)
			{
				++iFalse;
			}
		}

		if (iFalse == 4)
		{
			NowPos = BackTracaking();
			memset(&CanMoveDir, true, sizeof(CanMoveDir));
		}
		//system("cls");
		//PtintAll(); // �ӽ�
		//system("pause");

	}

}

void SetRoad()
{

	Pos NowHeadPos{}; // ���� �Ӹ��� ��ġ


	bool bAllDirMove{}; // ��� �������� ����������?

	while (NowHeadPos.iX != 29 || NowHeadPos.iY != 29) // ���� ������ ���ߴٸ�?
	{
		system("cls");
		SetNextRoad(NowHeadPos);
		
		NowHeadPos.iX = listAllRoadPos.back().iX;

		NowHeadPos.iY = listAllRoadPos.back().iY;

		
		PtintAll(); // �ӽ�
		//system("pause");

	}

	// ������ ��
	if (!CheckAllMove())
	{
		SetRoad();

	}
	else
	{
		for (auto iter : listAllRoadPos)
		{
			bAllRoadBoard[iter.iY][iter.iX] = true;
		}
	}


}


void PlayerMove(Dir InDir)
{
	if (GamePlayer.bLive == false)
	{
		return;
	}


	switch (InDir)
	{
	case Dir_Left:
		if (GamePlayer.iX - 1 >= 0 && bAllRoadBoard[GamePlayer.iY][GamePlayer.iX-1] == true)
		{
			GamePlayer.iX = GamePlayer.iX - 1;
		}
		break;
	case Dir_Right:
		if (GamePlayer.iX + 1 <= 29 && bAllRoadBoard[GamePlayer.iY][GamePlayer.iX + 1] == true)
		{
			GamePlayer.iX = GamePlayer.iX + 1;
		}
		break;
	case Dir_Up:
		if (GamePlayer.iY - 1 >= 0 && bAllRoadBoard[GamePlayer.iY-1][GamePlayer.iX] == true)
		{
			GamePlayer.iY = GamePlayer.iY - 1;
		}
		break;
	case Dir_Down:
		if (GamePlayer.iY + 1 <= 29 && bAllRoadBoard[GamePlayer.iY+1][GamePlayer.iX] == true)
		{
			GamePlayer.iY = GamePlayer.iY + 1;
		}
		break;
	}


}


int main()
{
	SetWall(); // ��ֹ� ��ġ
	SetRoad();

	system("cls");
	PtintAll();


	while (true)
	{
		system("cls");
		PtintAll();
		char cInput{};
		cInput = _getch();
		switch (cInput)
		{

		case 'r':
			if (GamePlayer.bLive == false)
			{
				GamePlayer.iX = 0;
				GamePlayer.iY = 0;
				GamePlayer.bLive = true;
			}
			break;

		case 'p':
			SetWall(); // ��ֹ� ��ġ
			SetRoad();
			break;

		case 'w':
			PlayerMove(Dir_Up);
			break;

		case 'a':
			PlayerMove(Dir_Left);
			break;

		case 's':
			PlayerMove(Dir_Down);
			break;

		case 'd':
			PlayerMove(Dir_Right);
			break;

		case 'q':

			return 0;

			break;
		}

	}
	

	return 0;
}