#include <iostream>
#include <gl/glew.h> //--- �ʿ��� ������� include
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

unsigned int g_WinID{};// ������ ID

bool bTimer = false; // Ÿ�̸� ���� ���� ����

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�

	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	g_WinID = glutCreateWindow("OGWork-3"); // ������ ����(������ �̸�)
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{


		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	//Set_DWRect();
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutMotionFunc(MoveMouse);

	glutMainLoop(); // �̺�Ʈ ó�� ����
}

GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
	glClearColor(RGBA[0], RGBA[1], RGBA[2], 1.f); // �������� ��blue�� �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�



	for (auto& iter : AllRect)
	{
		glColor3f(iter->RGB[0], iter->RGB[1], iter->RGB[2]);
		glRectf(CoordinateChangeX(iter->CenterX - iter->Cx), CoordinateChangeY(iter->CenterY - iter->Cy), CoordinateChangeX(iter->CenterX + iter->Cx), CoordinateChangeY(iter->CenterY + iter->Cy));

	}



	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
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
			return iter; // ���콺�� ��ġ�� �簢���� ��Ҵٸ�?
		}
	}


	return nullptr; // ���콺�� ��ġ�� �簢���� ���� �ʾҴٸ�?
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
			continue; // �簢���� ��ġ�� �簢���� ���� �ʾҴٸ�?
		}
		if (_CheckRect->CenterY - _CheckRect->Cy > iter->CenterY + iter->Cy || _CheckRect->CenterY + _CheckRect->Cy < iter->CenterY - iter->Cy)
		{
			continue; // �簢���� ��ġ�� �簢���� ���� �ʾҴٸ�?
		}
		return iter; // �簢���� ��ġ�� �簢���� ��Ҵٸ�?
	}
	return nullptr; // �簢���� ��ġ�� �簢���� ���� �ʾҴٸ�?
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
