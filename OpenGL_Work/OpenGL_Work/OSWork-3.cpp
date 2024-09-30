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

uniform_int_distribution<int> RandomSize(0,300);


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyInput(unsigned char key, int x, int y);
GLvoid TimerFunc(int Valule);
GLvoid MouseInput(int button, int state, int x, int y);
GLvoid MoveMouse(int X, int Y);




struct DWRect
{
	GLfloat RGB[3]{};
	GLfloat CenterX{};
	GLfloat CenterY{};

	GLfloat Cx{};
	GLfloat Cy{};

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
 



GLvoid Set_DWRect()
{

	if (AllRect.size() == 10)
	{
		return;
	}

	GLfloat CenterX = RandomPosX(mt);
	GLfloat CenterY = RandomPosY(mt);
	GLfloat Cx = 50.f;
	GLfloat Cy = 50.f;

	DWRect InRGB{ RandomRGB(mt)/10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f,
	CenterX, CenterY,Cx,Cy };

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
	glClearColor(RGBA[0], RGBA[1], RGBA[2], 1.f); // 바탕색을 ‘blue’ 로 지정
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
	case 'a':
		Set_DWRect();
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

bool bPush_L_button{false};

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

			if (iSqure != nullptr)
			{
				
				


			}
			
			break;

		case GLUT_RIGHT_BUTTON:

			break;
		}
	}
	else if (state == GLUT_UP)
	{
		bPush_L_button = false;
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
		{
			DWRect* pMouseSqare = Check_Mouse_Rect(x, y);

			DWRect* pSqure = Check_Rect_Rect(pMouseSqare);


			if (pSqure != nullptr)
			{
				pMouseSqare->RGB[0] = (RandomRGB(mt) / 10.f);
				pMouseSqare->RGB[1] = (RandomRGB(mt) / 10.f);
				pMouseSqare->RGB[2] = (RandomRGB(mt) / 10.f);


				if ((pSqure->CenterX - pSqure->Cx) > (pMouseSqare->CenterX - pMouseSqare->Cx))
				{
					pMouseSqare->Cx = ((pSqure->CenterX + pSqure->Cx) - (pMouseSqare->CenterX - pMouseSqare->Cx))/2.f;
				}
				else
				{
					pMouseSqare->Cx = ((pMouseSqare->CenterX + pMouseSqare->Cx) - (pSqure->CenterX - pSqure->Cx)) / 2.f;
				}



				if ((pSqure->CenterY + pSqure->Cy) > (pMouseSqare->CenterY + pMouseSqare->Cy))
				{
					pMouseSqare->Cy = ((pSqure->CenterY + pSqure->Cy) - (pMouseSqare->CenterY - pMouseSqare->Cy))/2.f;
				}
				else
				{
					pMouseSqare->Cy = ((pMouseSqare->CenterY + pMouseSqare->Cy) - (pSqure->CenterY - pSqure->Cy)) / 2.f;
				}

				DeleteRect(pSqure);

			}
		}
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
