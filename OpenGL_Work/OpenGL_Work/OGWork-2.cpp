#include <iostream>
#include <gl/glew.h> //--- �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>
#include <random>

std::mt19937 mt;

std::uniform_int_distribution<int> RandomIntNum(0, 10);


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyInput(unsigned char key, int x, int y);
GLvoid TimerFunc(int Valule);
GLvoid MouseInput(int button, int state, int x, int y);

int CheckRect(GLfloat x, GLfloat y);


struct DWRect
{
	GLfloat RGB[3]{};
	GLfloat Size[4]{};
};


DWRect AllDWRect[4]{};


GLvoid Set_DWRect()
{
	DWRect InRGB{ 0.6f, 0.9f, 0.f,
	0.f, 0.f, 1.f, 1.f };

	memcpy(&AllDWRect[0],&InRGB,sizeof(InRGB));


	DWRect InRGBTwo{ 1.f, 0.7f, 0.f,
	0.f, 0.f, -1.f, 1.f };

	memcpy(&AllDWRect[1], &InRGBTwo, sizeof(InRGBTwo));

	DWRect InRGBThree{ 1.f, 0.3f, 0.f,
	0.f, 0.f, -1.f, -1.f };

	memcpy(&AllDWRect[2], &InRGBThree, sizeof(InRGBThree));


	DWRect InRGBFour{ 0.f, 0.7f, 1.f,
	0.f, 0.f, 1.f, -1.f };

	memcpy(&AllDWRect[3], &InRGBFour, sizeof(InRGBFour));

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
	g_WinID = glutCreateWindow("OGWork-1"); // ������ ����(������ �̸�)
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
	

		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	Set_DWRect();
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);

	glutMainLoop(); // �̺�Ʈ ó�� ����
}
GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
	glClearColor(RGBA[0], RGBA[1], RGBA[2], 1.f); // �������� ��blue�� �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�


	for (int i = 0; i < 4; ++i)
	{
		glColor3f(AllDWRect[i].RGB[0], AllDWRect[i].RGB[1], AllDWRect[i].RGB[2]);
		glRectf(AllDWRect[i].Size[0], AllDWRect[i].Size[1], AllDWRect[i].Size[2], AllDWRect[i].Size[3]);
	}


	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
{
	glViewport(0, 0, w, h);

}

GLvoid KeyInput(unsigned char key, int x, int y)
{
	


	glutPostRedisplay();
}


GLvoid MouseInput(int button, int state, int x, int y)
{
	
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		RGBA[0] = (RandomIntNum(mt) / 10.f);
		RGBA[1] = (RandomIntNum(mt) / 10.f);
		RGBA[2] = (RandomIntNum(mt) / 10.f);
		break;




	default:
		break;
	}


	glutPostRedisplay();
}

int CheckRect(GLfloat x, GLfloat y)
{
	for (int i = 0; i < 4; ++i)
	{
		if ((AllDWRect[i].Size[0] <= x && AllDWRect[i].Size[2] >= x)&&
			(AllDWRect[i].Size[1] <= y && AllDWRect[i].Size[3] >= y))
		{ 
			return i; // ���콺�� ��ġ�� �簢���� ��Ҵٸ�?
		}
	}


	return -1; // ���콺�� ��ġ�� �簢���� ���� �ʾҴٸ�?
}


GLvoid TimerFunc(int Valule)
{

	RGBA[0] = (RandomIntNum(mt) / 10.f);
	RGBA[1] = (RandomIntNum(mt) / 10.f);
	RGBA[2] = (RandomIntNum(mt) / 10.f);

	glutPostRedisplay();
	if (bTimer)
	{
		glutTimerFunc(100, TimerFunc, 1);
	}

}
