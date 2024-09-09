#include "Define.h"

void Re_In(char _cWant) // 매개변수와 같은 문자를 누르기 전까지 빠져나갈 수 없는 루프 문
{
	while (true)
	{
		char cIN{};

		cin >> cIN;

		if (cIN == _cWant)
			break;
	}
}

struct Pos
{
	int x{};
	int y{};
	int z{};
	bool bInPut{}; // 현재 채워져 있는지?
	float fDistance{}; // 원점으로부터의 거리
};


Pos AllPos[20]{};

int iTop{}; // 가장 위+1 을 나타냄 처음에는 0

void AllPrint()
{
	cout << endl;
	for (int i = 19; i >= 0; --i)
	{
		cout << i << ".\t" << AllPos[i].x << " " << AllPos[i].y << " " << AllPos[i].z << endl;
	}
	cout << endl;
}


void InPut()
{
	
	for (int i = 0; i < 20; ++i)
	{
		if (AllPos[i].bInPut == false)
		{
			cout << "좌표를 입력해 주세요" << endl;

			cin >> AllPos[i].x;
			cin >> AllPos[i].y;
			cin >> AllPos[i].z;
			AllPos[i].bInPut = true;
			AllPos[i].fDistance = sqrtf((AllPos[i].x) * (AllPos[i].x) + (AllPos[i].y) * (AllPos[i].y) + (AllPos[i].z) * (AllPos[i].z));
			return;
		}
		
	}

	cout << "모든 좌표가 가득 찼습니다." << endl;
	

}

void DeleteTop()
{
	for (int i = 19; i >= 0; --i)
	{
		if (AllPos[i].bInPut == true)
		{
			AllPos[i].x = 0;
			AllPos[i].y = 0;
			AllPos[i].z = 0;
			AllPos[i].bInPut = false;
			AllPos[i].fDistance = 0.f;
			return;
		}
	}

	cout << "삭제할 데이터가 없습니다." << endl;

}

void InPutBottom()
{
	for (int i = 19; i > 0; --i)
	{
		AllPos[i] = AllPos[i - 1];
	}
	cout << "좌표를 입력해 주세요" << endl;

	cin >> AllPos[0].x;
	cin >> AllPos[0].y;
	cin >> AllPos[0].z;
	AllPos[0].bInPut = true;
}

void DeleteBottom()
{
	for (int i = 0; i < 20; ++i)
	{
		if (AllPos[i].bInPut == true)
		{
			AllPos[i].x = 0;
			AllPos[i].y = 0;
			AllPos[i].z = 0;
			AllPos[i].bInPut = false;
			AllPos[i].fDistance = 0.f;
			return;
		}
	}
	cout << "삭제할 데이터가 없습니다." << endl;
}

void AllNum()
{
	int iAllNum{};

	for (int i = 0; i < 20; ++i)
	{
		if (AllPos[i].bInPut == true)
		{
			++iAllNum;
		}
	}

	cout << "모든 점의 개수는 " << iAllNum << "개 입니다." << endl;

}


void DeleteAll()
{
	for (int i = 0; i < 20; ++i)
	{
		if (AllPos[i].bInPut == true)
		{
			AllPos[i].x = 0;
			AllPos[i].y = 0;
			AllPos[i].z = 0;
			AllPos[i].bInPut = false;
			AllPos[i].fDistance = 0.f;
		}
	}
}


void FarPos()
{
	float fTooFar{};
	int iTooFarIndex{};

	for (int i = 0; i < 20; ++i)
	{
		if (AllPos[i].bInPut == true)
		{
			float fFar = sqrtf((AllPos[i].x) * (AllPos[i].x) + (AllPos[i].y) * (AllPos[i].y) + (AllPos[i].z) * (AllPos[i].z));

			if (fTooFar < fFar)
			{
				fTooFar = fFar;
				iTooFarIndex = i;
			}
		}
	}

	if (fTooFar != 0)
	{
		cout << iTooFarIndex << "." << AllPos[iTooFarIndex].x << " " << AllPos[iTooFarIndex].y<< " " << AllPos[iTooFarIndex].z << endl;

		return;
	}

	cout << "모두 균등하여 가장 먼 점의 좌표가 없습니다." << endl;

}

void NearPos()
{
	float fTooNear{999999};
	int iTooNearIndex{};

	for (int i = 0; i < 20; ++i)
	{
		if (AllPos[i].bInPut == true)
		{
			float fNear = sqrtf((AllPos[i].x) * (AllPos[i].x) + (AllPos[i].y) * (AllPos[i].y) + (AllPos[i].z) * (AllPos[i].z));

			if (fTooNear > fNear)
			{
				fTooNear = fNear;
				iTooNearIndex = i;
			}
		}
	}

	if (fTooNear != 999999)
	{
		cout << iTooNearIndex << "." << AllPos[iTooNearIndex].x<< " " << AllPos[iTooNearIndex].y<< " " << AllPos[iTooNearIndex].z << endl;

		return;
	}

	cout << "모두 균등하여 가장 가까운 점의 좌표가 없습니다." << endl;

}

void UpSort()
{
	float fAllDistance[20]{};

	int iAllTruePos{};

	

	for (int i = 0; i < 20; ++i)
	{
		if (AllPos[i].bInPut == true)
		{
			++iAllTruePos;
		}
	}

	Pos* SmallAllPos = new Pos[iAllTruePos]{};

	int iSmallnum{};

	for (int i = 0; i < 20; ++i)
	{
		if (AllPos[i].bInPut == true)
		{
			SmallAllPos[iSmallnum] = AllPos[i];
			++iSmallnum;
		}
	}

	for (int i = 0; i < iSmallnum; ++i)
	{
		for (int j = 0; j < iSmallnum - 1; ++j)
		{
			if (SmallAllPos[j].fDistance > SmallAllPos[j + 1].fDistance)
			{
				Pos Change = SmallAllPos[j];
				SmallAllPos[j] = SmallAllPos[j + 1];
				SmallAllPos[j + 1] = Change;
			}
		}
	}

	//memset(&AllPos,0,sizeof(AllPos));

	Pos Temporary[20]{};

	for (int i = 0; i < iSmallnum; ++i)
	{
		Temporary[i] = SmallAllPos[i];
	}

	cout << endl;
	for (int i = 19; i >= 0; --i)
	{
		cout << i << ".\t" << Temporary[i].x << " " << Temporary[i].y << " " << Temporary[i].z << endl;
	}
	cout << endl;

	Re_In('a');
}

void DownSort()
{
	float fAllDistance[20]{};

	int iAllTruePos{};



	for (int i = 0; i < 20; ++i)
	{
		if (AllPos[i].bInPut == true)
		{
			++iAllTruePos;
		}
	}

	Pos* SmallAllPos = new Pos[iAllTruePos]{};

	int iSmallnum{};

	for (int i = 0; i < 20; ++i)
	{
		if (AllPos[i].bInPut == true)
		{
			SmallAllPos[iSmallnum] = AllPos[i];
			++iSmallnum;
		}
	}

	for (int i = 0; i < iSmallnum; ++i)
	{
		for (int j = 0; j < iSmallnum - 1; ++j)
		{
			if (SmallAllPos[j].fDistance < SmallAllPos[j + 1].fDistance)
			{
				Pos Change = SmallAllPos[j];
				SmallAllPos[j] = SmallAllPos[j + 1];
				SmallAllPos[j + 1] = Change;
			}
		}
	}

	//memset(&AllPos, 0, sizeof(AllPos));

	Pos Temporary[20]{};

	for (int i = 0; i < iSmallnum; ++i)
	{
		Temporary[i] = SmallAllPos[i];
	}

	cout << endl;
	for (int i = 19; i >= 0; --i)
	{
		cout << i << ".\t" << Temporary[i].x << " " << Temporary[i].y << " " << Temporary[i].z << endl;
	}
	cout << endl;

	Re_In('s');
}


int main()
{
	while (true)
	{
		AllPrint();

		char cIN{};

		cin >> cIN;

		switch (cIN)
		{
		case '+':
			InPut();
			break;

		case '-':
			DeleteTop();
			break;

		case 'e':
			InPutBottom();
			break;

		case 'd':
			DeleteBottom();
			break;

		case 'i':
			AllNum();
			break;

		case 'c':
			DeleteAll();
			break;

		case 'm':
			FarPos();
			break;

		case 'n':
			NearPos();
			break;

		case 'a':
			UpSort();
			break;

		case 's':
			DownSort();
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