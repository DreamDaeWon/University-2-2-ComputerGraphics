#include "Define.h"
#include <algorithm>
#include <random>
#include <vector>
#include <Windows.h>


vector<char> vecAllcard{};

char cBoard[5][5]{};

char cStarBoard[5][5]{};

int iPos[2][2]{};

int iAllChance{};

int iChance{12}; // ��ȸ

int iScore{};


random_device rd;
mt19937 mt(rd());
uniform_int_distribution<int> Random_int{ 0,2 };


void Shuffle()
{
	for (int i = 0; i < 12; ++i)
	{
		vecAllcard.push_back('A' + i);
		vecAllcard.push_back('A' + i);
	}
	vecAllcard.push_back('@');

	shuffle(vecAllcard.begin(), vecAllcard.end(),mt);

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			cBoard[i][j] = vecAllcard.back();
			vecAllcard.pop_back();
		}
	}
}


void PrintAll()
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "\ta\tb\tc\td\te" << endl << endl << endl;

	for (int i = 0; i < 5; ++i)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << i <<".\t";
		for (int j = 0; j < 5; ++j)
		{
			if (cStarBoard[i][j] == '*')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else if(cStarBoard[i][j] == '@')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);//--attribute_color; WORD
				
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cStarBoard[i][j]-63);
			}
			cout << cStarBoard[i][j] << "\t";
		}
		cout << endl << endl << endl;
	}
}


bool Reverse(char pCIn[][2], int& iReverseNum)
{
	if (cStarBoard[pCIn[iReverseNum][1] - 48][pCIn[iReverseNum][0] - 97] != '*')
	{
		cout << "�̹� ������ ī���Դϴ�." << endl;
		system("pause");

		if (iReverseNum == 0)
		{
			iReverseNum = 0;
		}
		else
		{
			cStarBoard[pCIn[0][1] - 48][pCIn[0][0] - 97] = '*';
		}



		return false;
	}




	cStarBoard[pCIn[iReverseNum][1] - 48][pCIn[iReverseNum][0] - 97] = cBoard[pCIn[iReverseNum][1] - 48][pCIn[iReverseNum][0] - 97];

	return true;

}

void Compare()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	if (iPos[0][0] == iPos[1][0] && iPos[0][1] == iPos[1][1])
	{
		cout << "���� ��ȣ�� �Է��ϼ̽��ϴ�." << endl;
		cStarBoard[iPos[0][0]][iPos[0][1]] = '*';
		system("pause");
		return;
	}

	PrintAll();
	
	if(cBoard[iPos[0][0]][iPos[0][1]] == '@')
	{
		iScore = iScore + 2;
		cout << "��Ŀ�� ã�ҽ��ϴ�. ���ο� �ݴ��� ī�带 ���ڽ��ϴ�." << endl;
		system("pause");
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (cBoard[iPos[1][0]][iPos[1][1]] == cBoard[i][j])
				{
					cStarBoard[i][j] = cBoard[i][j];
				}
			}
		}
		PrintAll();
		system("pause");
	}
	else if (cBoard[iPos[1][0]][iPos[1][1]] == '@')
	{
		iScore = iScore + 2;
		cout << "��Ŀ�� ã�ҽ��ϴ�. ���ο� �ݴ��� ī�带 ���ڽ��ϴ�." << endl;
		system("pause");
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (cBoard[iPos[0][0]][iPos[0][1]] == cBoard[i][j])
				{
					cStarBoard[i][j] = cBoard[i][j];
				}
			}
		}
		PrintAll();
		system("pause");
	}
	else if (cBoard[iPos[0][0]][iPos[0][1]] != cBoard[iPos[1][0]][iPos[1][1]])
	{
		cout << "Ʋ�Ƚ��ϴ�." << endl;
		system("pause");

		cStarBoard[iPos[0][0]][iPos[0][1]] = '*';
		cStarBoard[iPos[1][0]][iPos[1][1]] = '*';
	}
	else
	{
		iScore = iScore + 2;
		cout << "�¾ҽ��ϴ�." << endl;
		system("pause");
	}
	system("cls");
}

int main()
{
	memset(&cStarBoard, '*', sizeof(cStarBoard));
	Shuffle();

	iAllChance = iChance;

	int iTwoReverse{};

	while (true)
	{
		PrintAll();

		char cCIN[2][2]{};
		cin >> cCIN[iTwoReverse][0] >> cCIN[iTwoReverse][1];

		if (!Reverse(cCIN, iTwoReverse))
		{
			continue;
		}

		iPos[iTwoReverse][0] = cCIN[iTwoReverse][1] - 48;
		iPos[iTwoReverse][1] = cCIN[iTwoReverse][0] - 97;

		++iTwoReverse;
		--iChance;

		if (iTwoReverse == 2)
		{
			// �˻��ϴ� �ڵ� �ۼ�
			Compare();
			iTwoReverse = 0;
		}

		if (iChance == 0)
		{
			cout << "��ȸ " << iAllChance/2 <<"���� �������ϴ�. ����� ������!" << endl;
			cout << iScore << "��" << endl;
			system("pause");
			return 0;
		}


	}

}