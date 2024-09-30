#include <iostream>
#include <gl/glew.h> //--- �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <iostream>
#include <random>

std::mt19937 mt;

std::uniform_int_distribution<int> RandomRGB(0, 10);


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyInput(unsigned char key, int x, int y);
GLvoid TimerFunc(int Valule);

GLclampf RGBA[4]{ 0.0f, 0.0f, 1.0f, 1.0f };

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

	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(KeyInput);
	glutMainLoop(); // �̺�Ʈ ó�� ����
}
GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
	glClearColor(RGBA[0], RGBA[1], RGBA[2], 1.f); // �������� ��blue�� �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�
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
	case 'c':
		RGBA[0] = 0.f;
		RGBA[1] = 1.f;
		RGBA[2] = 1.f;
		break;

	case 'm':
		RGBA[0] = 1.f;
		RGBA[1] = 0.f;
		RGBA[2] = 1.f;
		break;

	case 'y':
		RGBA[0] = 1.f;
		RGBA[1] = 1.f;
		RGBA[2] = 0.f;
		break;

	case 'a':
		RGBA[0] = (RandomRGB(mt) / 10.f);
		RGBA[1] = (RandomRGB(mt) / 10.f);
		RGBA[2] = (RandomRGB(mt) / 10.f);
		break;

	case 'w':
		RGBA[0] = 1.f;
		RGBA[1] = 1.f;
		RGBA[2] = 1.f;
		break;

	case 'k':
		RGBA[0] = 0.f;
		RGBA[1] = 0.f;
		RGBA[2] = 0.f;
		break;

	case 't':

		bTimer = true;
		glutTimerFunc(100, TimerFunc, 1);

		break;

	case 's':
		bTimer = false;

		break;

	case 'q':
		glutDestroyWindow(g_WinID);
		break;

	default:
		break;
	}
	glutPostRedisplay();
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
