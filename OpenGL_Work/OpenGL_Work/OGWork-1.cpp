#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
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

unsigned int g_WinID{};// 윈도우 ID

bool bTimer = false; // 타이머 문제 관련 변수

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기

	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	g_WinID = glutCreateWindow("OGWork-1"); // 윈도우 생성(윈도우 이름)
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(KeyInput);
	glutMainLoop(); // 이벤트 처리 시작
}
GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수 
{
	glClearColor(RGBA[0], RGBA[1], RGBA[2], 1.f); // 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다
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
