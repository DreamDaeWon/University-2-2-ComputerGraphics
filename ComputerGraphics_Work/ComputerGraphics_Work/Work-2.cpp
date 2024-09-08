#include "Define.h"
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <sstream>
#include <Windows.h>
#define strcasecmp _stricmp


string strAll[100]{};
int iStrNum{}; // �� ������ �˷��ִ� ��


void Re_In(char _cWant) // �Ű������� ���� ���ڸ� ������ ������ �������� �� ���� ���� ��
{
	while (true)
	{
		char cIN{};

		cin >> cIN;

		if (cIN == _cWant)
			break;
	}
}

void ReadFile(string _filePath)
{
	ifstream readFile{};
	readFile.open(_filePath);

	

	if (readFile.fail())
	{
		return;
	}

	while (true)
	{

		
		getline(readFile, strAll[iStrNum]);
		
		++iStrNum;

		if (readFile.eof())
		{
			break;
		}
	}

	readFile.close();
}


void ChangeColor()
{
	string strColorAll[100]{};

	int iWordNum{}; //�� ĭ �� ĭ ��ȸ�� �ε��� ��

	int iColorNum{}; // ������ ���� ǥ���� �ܾ��� ��

	unsigned short Color = 12;

	for (int i = 0; i < iStrNum; ++i)
	{
		iWordNum = 0;
		while (true)
		{
			if (strAll[i][iWordNum] >= 'A' && strAll[i][iWordNum] <= 'Z')
			{
				++iColorNum;
				while (true)
				{
					
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);//--attribute_color; WORD Ÿ������ ������ ��Ÿ���� ����

					cout << strAll[i][iWordNum];
					++iWordNum;
					if (iWordNum == strAll[i].size())
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

						break;
					}
					if (strAll[i][iWordNum] == ' ' || strAll[i][iWordNum] == '\n')
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						cout << strAll[i][iWordNum];
						break;
					}
				}
			}
			else
			{
				cout << strAll[i][iWordNum];
			}

			if (iWordNum == strAll[i].size())
			{
				cout << endl;
				iWordNum = 0;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

				break;
			}
			++iWordNum;
		}
	}

	cout << iColorNum << "��" << endl;

	Re_In('c');



}


void BackWards_OneLine()
{
	for (int i = 0; i < iStrNum; ++i)
	{
		for (int j = strAll[i].size()-1; j >= 0; --j)
		{
			cout << strAll[i][j];
		}
		cout << endl;
	}

	Re_In('d');

}

void Three_And_Two()
{

	int iChaeck{};

	for (int i = 0; i < iStrNum; ++i)
	{
		for (int j = 0; j < strAll[i].size(); ++j)
		{
			if (iChaeck == 3)
			{
				cout << "@@";
				iChaeck = 0;
			}
			cout << strAll[i][j];
			++iChaeck;
		}
		cout << endl;
	}

	Re_In('e');

}

void BackWards_Word()
{
	int iWordnum{};

	for (int i = 0; i < iStrNum; ++i)
	{
		for (int j = 0; j < strAll[i].size(); ++j)
		{
			++iWordnum;

			if (strAll[i][j] == ' ')
			{
				for (int k = j; k > j - iWordnum; --k)
				{
					cout << strAll[i][k];
				}
				iWordnum = 0;

			}

			if (j == strAll[i].size()-1)
			{
				cout << " ";

				for (int k = j; k > j - iWordnum; --k)
				{
					cout << strAll[i][k];
				}
				iWordnum = 0;
				break;
			}

			
		}
		cout << endl;
	}

	Re_In('f');

}

void SpecialWord()
{
	string strWord{};

	string strWantWord{};

	string strCheck{};

	int iCheckWord{}; // �ܾ� üũ�� ���� int

	cout << "�ٲٰ� ���� �ܾ �Է��� �ּ���." << endl;

	cin >> strWord;

	cout << "�� �ڸ��� ���� ���� �ܾ �Է��� �ּ���." << endl;
	cin >> strWantWord;

	for (int i = 0; i < iStrNum; ++i)
	{
		for (int j = 0; j < strAll[i].size(); ++j)
		{
			if (strAll[i][j] == ' ')
			{
				if (strCheck == strWord)
				{
					cout << strWantWord;
					cout << " ";
				}
				else
				{
					cout << strCheck;
					cout << " ";
				}
				strCheck.erase();
				iCheckWord = 0;
			}
			else
			{
				strCheck+= strAll[i][j];
				++iCheckWord;
			}
			if (j == strAll[i].size() - 1)
			{
				cout << strCheck;
			}
		
		}
		cout << endl;
	}

	Re_In('g');

}


void ColorWord()
{
	string strWord{};

	string strCheck{};

	int iCheckWord{}; // �ܾ� üũ�� ���� int

	int iChangeNum{};

	cout << "�ٲٰ� ���� �ܾ �Է��� �ּ���." << endl;

	cin >> strWord;


	for (int i = 0; i < iStrNum; ++i)
	{
		for (int j = 0; j < strAll[i].size(); ++j)
		{
			if (strAll[i][j] == ' ')
			{
				if (0 == strcasecmp(strCheck.c_str(), strWord.c_str()))
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
					cout << strCheck;
					cout << " ";
					++iChangeNum;
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					cout << strCheck;
					cout << " ";
				}
				strCheck.erase();
				iCheckWord = 0;
			}
			else
			{
				strCheck += strAll[i][j];
				++iCheckWord;
			}
			if (j == strAll[i].size() - 1)
			{
				cout << strCheck;
			}

		}
		cout << endl;
	}

	cout << iChangeNum << "��" << endl;
}




void WordNum()
{

	int iWordNum{};

	for (int i = 0; i < iStrNum; ++i)
	{
		for (int j = 0; j < strAll[i].size(); ++j)
		{
			if (strAll[i][j] == ' ' && strAll[i][j-1] != ' ')
			{
				++iWordNum;
			}
		}
		++iWordNum;
	}

	cout << iWordNum;
}


struct UpSo
{
	int iAllWordNum{};
	int iLine{};
};

void UpSort()
{

	UpSo* AllLine = new UpSo[iStrNum];


	for (int i = 0; i < iStrNum; ++i)
	{
		AllLine[i].iLine = i;
		for (int j = 0; j < strAll[i].size(); ++j)
		{
			if (strAll[i][j] == ' ' || j== strAll[i].size()-1)
			{
				++AllLine[i].iAllWordNum;
			}
		}
	}

	for(int k = 0; k < iStrNum; ++k)
	{
		for (int i = 0; i < iStrNum - 1; ++i)
		{
			if (AllLine[i].iAllWordNum > AllLine[i + 1].iAllWordNum)
			{
				UpSo Change = AllLine[i];

				AllLine[i] = AllLine[i + 1];

				AllLine[i + 1] = Change;
			}
		}
	}

	for (int i = 0; i < iStrNum; ++i)
	{
		cout << strAll[AllLine[i].iLine] << endl;
	}
	cout << endl;


	Re_In('r');

	for (int k = 0; k < iStrNum; ++k)
	{
		for (int i = 0; i < iStrNum - 1; ++i)
		{
			if (AllLine[i].iAllWordNum < AllLine[i + 1].iAllWordNum)
			{
				UpSo Change = AllLine[i];

				AllLine[i] = AllLine[i + 1];

				AllLine[i + 1] = Change;
			}
		}
	}

	for (int i = 0; i < iStrNum; ++i)
	{
		cout << strAll[AllLine[i].iLine] << endl;
	}
	cout << endl;

	Re_In('r');

}



void PrintAllFile()
{
	cout << endl;
	for (int i = 0; i < iStrNum; ++i)
	{
		cout << strAll[i] << endl;
	}
}


int main()
{
	ReadFile("../data.txt");

	while (true)
	{
		PrintAllFile();

		char ccIn{};

		cin >> ccIn;

		switch (ccIn)
		{
		case 'c':
			ChangeColor();
			break;

		case 'd':
			BackWards_OneLine();
			break;

		case 'e':
			Three_And_Two();
			break;

		case 'f':
			BackWards_Word();
			break;

		case 'g':
			SpecialWord();
			break;

		case 'h':
			WordNum();
			break;

		case 'r':
			UpSort();
			break;

		case 's':
			ColorWord();
			break;

		case 'q':
			return 0;
			break;

		default:

			break;
		}


	}

	return 0;
}