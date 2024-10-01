#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>
#include <random>
#include <list>
#include <vector>
using namespace std;

std::mt19937 mt;

std::uniform_int_distribution<int> RandomRGB(0, 10);

int WinsizeX = 800;
int WinsizeY = 600;

std::uniform_real_distribution<GLfloat> RandomPosX(0, WinsizeX);
std::uniform_real_distribution<GLfloat> RandomPosY(0, WinsizeY);

uniform_int_distribution<int> RandomSize(50, 100);


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyInput(unsigned char key, int x, int y);
GLvoid TimerFunc(int Valule);
GLvoid MouseInput(int button, int state, int x, int y);
GLvoid MoveMouse(int X, int Y);


// 4번
GLvoid RectMoveDiagonal(int Value); // 대각선 이동
GLvoid RectZigZag(int Value);
GLvoid SizeChange(int Value);
GLvoid RandomColor(int Value);



struct DWRect
{
	GLfloat RGB[3]{};
	GLfloat CenterX{};
	GLfloat CenterY{};

	GLfloat Cx{};
	GLfloat Cy{};

	
	GLfloat Origin_CenterX{};
	GLfloat Origin_CenterY{};

	bool LR{};
	bool ZigZag{};

};

DWRect* Check_Mouse_Rect(GLfloat x, GLfloat y);
DWRect* Check_Rect_Rect(DWRect* CheckRect);

GLfloat CoordinateChangeX(GLfloat Coord)
{
	Coord = Coord - (WinsizeX / 2);
	Coord = Coord / (WinsizeX / 2);
	return Coord;
}

GLfloat CoordinateChangeY(GLfloat Coord)
{
	Coord = -Coord;
	Coord = Coord + (WinsizeY / 2);
	Coord = Coord / (WinsizeY / 2);
	return Coord;
}

GLvoid RectUpScale(GLfloat x, GLfloat y, DWRect* Rect)
{
	Rect->Cx += x;
	Rect->Cy += y;
}

GLvoid RectDownScale(GLfloat x, GLfloat y, DWRect* Rect, GLfloat Minsize)
{
	if (Rect->Cx < x && Rect->Cy < y)
	{
		return;
	}

	Rect->Cx -= x;
	Rect->Cy -= y;
}



vector<DWRect*> AllRect{};




GLvoid Set_DWRect(GLfloat x, GLfloat y)
{
	static bool bZigZag{true};
	static bool bLR{};

	bZigZag = !bZigZag;
	bLR = !bLR;


	if (AllRect.size() == 5)
	{
		return;
	}

	GLfloat CenterX = x;
	GLfloat CenterY = y;
	GLfloat Cx = 50.f;
	GLfloat Cy = 50.f;

	DWRect InRGB{ RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f,
	CenterX, CenterY,Cx,Cy };

	InRGB.Origin_CenterX = CenterX;
	InRGB.Origin_CenterY = CenterY;

	InRGB.LR = bLR;
	InRGB.ZigZag = bZigZag;

	AllRect.push_back(new DWRect(InRGB));

}

GLvoid DeleteRect(DWRect* Rect)
{
	for (vector<DWRect*>::iterator iter = AllRect.begin(); iter != AllRect.end(); ++iter)
	{
		if ((*iter) == Rect)
		{
			delete Rect;
			AllRect.erase(iter);
			return;
		}
	}
}


GLclampf RGBA[4]{ 0.0f, 0.0f, 1.0f, 1.0f };

float fSize[4][4]{};

unsigned int g_WinID{};// 윈도우 ID

bool bTimer = false; // 타이머 문제 관련 변수


// 4번 타이머 관련변수
bool bDiagoanlMoveTimer = false;
bool bZizgZagTimer = false;
bool bSizeRandomTimer = false;
bool bRandomColorTimer = false;

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기

	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	g_WinID = glutCreateWindow("OGWork-3"); // 윈도우 생성(윈도우 이름)
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) // glew 초기화
	{


		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	//Set_DWRect();
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutMotionFunc(MoveMouse);

	glutMainLoop(); // 이벤트 처리 시작
}

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수 
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.f); // 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다


	for (auto& iter : AllRect)
	{
		glColor3f(iter->RGB[0], iter->RGB[1], iter->RGB[2]);
		glRectf(CoordinateChangeX(iter->CenterX - iter->Cx), CoordinateChangeY(iter->CenterY - iter->Cy), CoordinateChangeX(iter->CenterX + iter->Cx), CoordinateChangeY(iter->CenterY + iter->Cy));

	}



	glutSwapBuffers(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수 
{
	glViewport(0, 0, w, h);

}

GLvoid KeyInput(unsigned char key, int x, int y)
{
	
	switch (key)
	{
	case '1':
		bDiagoanlMoveTimer = !bDiagoanlMoveTimer;
		glutTimerFunc(100, RectMoveDiagonal, 1);
		break;

	case '2':
		bZizgZagTimer = !bZizgZagTimer;
		glutTimerFunc(100, RectZigZag, 1);
		break;

	case '3':
		bSizeRandomTimer = !bSizeRandomTimer;
		glutTimerFunc(100, SizeChange, 1);
		break;

	case '4':
		bRandomColorTimer = !bRandomColorTimer;
		glutTimerFunc(100, RandomColor, 1);
		break;

	case 's':
		bDiagoanlMoveTimer = false;
		bZizgZagTimer = false;
		bSizeRandomTimer = false;
		bRandomColorTimer = false;
		break;

	case 'm':
		for (auto& iter : AllRect)
		{
			iter->CenterX = iter->Origin_CenterX;
			iter->CenterY = iter->Origin_CenterY;
		}
		break;

	case 'r':
		bDiagoanlMoveTimer = false;
		bZizgZagTimer = false;
		bSizeRandomTimer = false;
		bRandomColorTimer = false;
		for (auto& iter : AllRect)
		{
			delete iter;
		}

		AllRect.clear();

		break;

	case 'q':
		glutDestroyWindow(g_WinID);
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

bool bPush_L_button{ false };

DWRect* iSqure{};
GLvoid MoveMouse(int X, int Y)
{
	if (iSqure != nullptr)
	{
		iSqure->CenterX = X;
		iSqure->CenterY = Y;
	}
	glutPostRedisplay();
}


GLvoid MouseInput(int button, int state, int x, int y)
{
	iSqure = Check_Mouse_Rect(x, y);
	if (state == GLUT_DOWN)
	{
		bPush_L_button = true;
		switch (button)
		{
		case GLUT_LEFT_BUTTON:

			Set_DWRect(x, y);


			break;

		case GLUT_RIGHT_BUTTON:

			break;
		}
	}
	glutPostRedisplay();
}

DWRect* Check_Mouse_Rect(GLfloat x, GLfloat y)
{
	for (auto iter : AllRect)
	{
		if ((iter->CenterX - iter->Cx <= x && iter->CenterX + iter->Cx >= x) &&
			(iter->CenterY - iter->Cy <= y && iter->CenterY + iter->Cy >= y))
		{
			return iter; // 마우스의 위치가 사각형과 닿았다면?
		}
	}


	return nullptr; // 마우스의 위치가 사각형과 닿지 않았다면?
}

DWRect* Check_Rect_Rect(DWRect* _CheckRect)
{
	if (_CheckRect == nullptr)
		return nullptr;

	for (auto& iter : AllRect)
	{
		if (iter == _CheckRect)
		{
			continue;
		}
		if (_CheckRect->CenterX - _CheckRect->Cx > iter->CenterX + iter->Cx || _CheckRect->CenterX + _CheckRect->Cx < iter->CenterX - iter->Cx)
		{
			continue; // 사각형의 위치가 사각형과 닿지 않았다면?
		}
		if (_CheckRect->CenterY - _CheckRect->Cy > iter->CenterY + iter->Cy || _CheckRect->CenterY + _CheckRect->Cy < iter->CenterY - iter->Cy)
		{
			continue; // 사각형의 위치가 사각형과 닿지 않았다면?
		}
		return iter; // 사각형의 위치가 사각형과 닿았다면?
	}
	return nullptr; // 사각형의 위치가 사각형과 닿지 않았다면?
}


GLvoid TimerFunc(int Valule)
{

	RGBA[0] = (RandomRGB(mt) / 10.f);
	RGBA[1] = (RandomRGB(mt) / 10.f);
	RGBA[2] = (RandomRGB(mt) / 10.f);

	glutPostRedisplay();
	if (bTimer)
	{
		glutTimerFunc(100, TimerFunc, 1);
	}

}


GLvoid RectMoveDiagonal(int Value)
{
	for (auto& iter : AllRect)
	{
		if (iter->LR) // 오른쪽
		{
			if (iter->CenterX + iter->Cx < WinsizeX)
			{
				iter->CenterX += 5;
			}
			else
			{
				iter->LR = !iter->LR;
			}
			if (iter->ZigZag) // 아래
			{
				if (iter->CenterY + iter->Cy < WinsizeY)
				{
					iter->CenterY += 5;
				}
				else
				{
					iter->ZigZag = !iter->ZigZag;
				}
			}
			else // 위
			{
				if (iter->CenterY - iter->Cy > 0)
				{
					iter->CenterY -= 5;
				}
				else
				{
					iter->ZigZag = !iter->ZigZag;
				}
			}
		}
		if (!iter->LR) // 왼쪽
		{
			if (iter->CenterX - iter->Cx > 0)
			{
				iter->CenterX -= 5;
			}
			else
			{
				iter->LR = !iter->LR;
			}
			if (iter->ZigZag) // 아래
			{
				if (iter->CenterY + iter->Cy < WinsizeY)
				{
					iter->CenterY += 5;
				}
				else
				{
					iter->ZigZag = !iter->ZigZag;
				}
			}
			else // 위
			{
				if (iter->CenterY - iter->Cy > 0)
				{
					iter->CenterY -= 5;
				}
				else
				{
					iter->ZigZag = !iter->ZigZag;
				}
			}
		}
	}
	glutPostRedisplay();
	if (bDiagoanlMoveTimer)
	{
		glutTimerFunc(10, RectMoveDiagonal, 1);
	}

}

GLvoid RectZigZag(int Value)
{
	static bool ZigZag{}; // true면 가로 이동

	static int iZigZag{};

	iZigZag += 1;
	if (iZigZag >= 10)
	{
		ZigZag = !ZigZag;
		iZigZag = 0;
	}

	for (auto& iter : AllRect)
	{
		if (ZigZag)
		{
			if (iter->LR) // 오른쪽
			{
				if (iter->CenterX + iter->Cx < WinsizeX)
				{
					iter->CenterX += 5;
				}
				else
				{
					iter->LR = !iter->LR;
				}
			}
			if (!iter->LR) // 왼쪽
			{
				if (iter->CenterX - iter->Cx > 0)
				{
					iter->CenterX -= 5;
				}
				else
				{
					iter->LR = !iter->LR;
				}
			}
		}
		else
		{


			if (iter->ZigZag) // 아래
			{
				if (iter->CenterY + iter->Cy < WinsizeY)
				{
					iter->CenterY += 5;
				}
				else
				{
					iter->ZigZag = !iter->ZigZag;
				}
			}
			else // 위
			{
				if (iter->CenterY - iter->Cy > 0)
				{
					iter->CenterY -= 5;
				}
				else
				{
					iter->ZigZag = !iter->ZigZag;
				}
			}
		}
	}
	glutPostRedisplay();
	if (bZizgZagTimer)
	{
		glutTimerFunc(10, RectZigZag, 1);
	}

	
}

GLvoid SizeChange(int Value)
{
	for (auto iter : AllRect)
	{
		iter->Cx = RandomSize(mt);
		iter->Cy = RandomSize(mt);
	}
	glutPostRedisplay();
	if (bSizeRandomTimer)
	{
		glutTimerFunc(100, SizeChange, 1);
	}

}

GLvoid RandomColor(int Value)
{
	for (auto iter : AllRect)
	{
		iter->RGB[0] = RandomRGB(mt) / 10.f;
		iter->RGB[1] = RandomRGB(mt) / 10.f;
		iter->RGB[2] = RandomRGB(mt) / 10.f;
	}
	glutPostRedisplay();
	if (bRandomColorTimer)
	{
		glutTimerFunc(100, RandomColor, 1);
	}

}