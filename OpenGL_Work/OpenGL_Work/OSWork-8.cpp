#include "Define.h"



// 셰이더 관련 변수
GLuint shaderProgramID{}; // 셰이더 프로그램 이름
GLuint vertexShader{}; // 버텍스 셰이더 객체
GLuint fragmentShader{}; // 프래그먼트 셰이터 객체



void make_vectexShaders() // 버텍스 셰이터 객체 만들기
{
	GLchar* vertexSource{};

	vertexSource = filetobuf("vertex_shader.glsl");

	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}

}

void make_fragmenetShaders() // 버텍스 셰이터 객체 만들기
{
	GLchar* fragmentSource{};

	fragmentSource = filetobuf("fragmemt_shader.glsl");

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

void make_shaderProgram()
{
	make_vectexShaders();
	make_fragmenetShaders();


	shaderProgramID = glCreateProgram();

	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);

	glLinkProgram(shaderProgramID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderProgramID);

}




GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyInput(unsigned char key, int x, int y);
GLvoid TimerFunc(int Valule);
GLvoid MouseInput(int button, int state, int x, int y);
GLvoid MoveMouse(int X, int Y);




// 7 번

DrawType eDrawType{};

GLvoid Create_DWArt(vector<DWArt*>* pVec, DrawType eDraw, GLfloat x, GLfloat y, GLfloat rx, GLfloat ry);

GLvoid Create_Dot(vector<DWArt*>* pVec, GLfloat x, GLfloat y);
GLvoid Create_Line(vector<DWArt*>* pVec, GLfloat x, GLfloat y, GLfloat rx, GLfloat ry);
GLvoid Create_Line_Pos(vector<DWArt*>* pVec, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
GLvoid Create_Triangle(vector<DWArt*>* pVec, GLfloat x, GLfloat y, GLfloat rx, GLfloat ry);
GLvoid Create_Rect(vector<DWArt*>* pVec, GLfloat x, GLfloat y, GLfloat rx, GLfloat ry);

GLvoid Move(eMoveType Dir);

GLvoid Delete_ALL();

GLvoid UpdateBuffers();

//void InitBuffers();


// 8 번



GLvoid SetMode(DrawType Type)
{
	eDrawType = Type;
}



vector<DWArt*> AllArt{};

vector<DWArt*> LeftTop{};
vector<DWArt*> RightTop{};
vector<DWArt*> LeftBottom{};
vector<DWArt*> RightBottom{};

vector<DWArt*>* AllVec[5]{ &AllArt ,&LeftTop ,&RightTop ,&LeftBottom ,&RightBottom };

float fSize[4][4]{};

unsigned int g_WinID{};// 윈도우 ID

bool bTimer = false; // 타이머 문제 관련 변수

GLuint iPrintType = GL_TRIANGLES;


// 4번 타이머 관련변수
bool bDiagoanlMoveTimer = false;
bool bZizgZagTimer = false;
bool bSizeRandomTimer = false;
bool bRandomColorTimer = false;

const GLfloat triShape[3][3] = { { -0.5, -0.5, 0.0 }, { 0.5, -0.5, 0.0 }, { 0.0, 0.5, 0.0} };

const GLfloat colors[3][3] = { {  1.0,  0.0,  0.0  }, {  0.0,  1.0,  0.0  }, {  0.0,  0.0,  1.0  } };

//GLuint vao, vbo[2];

GLuint* vbo{}, * EBO{};


GLvoid Timer(int Value)
{
	for(auto& iter : AllArt)
		UpdateBuffer(iter);
	glutTimerFunc(100, Timer, 1);
}


void InitBuffers(vector<DWArt*>* pVec)
{
	for (int i = (*pVec).size() - 1; i < (*pVec).size(); ++i)
	{
		InitBuffer((*pVec)[i]);
	}
}


void UpdateBuffers()
{
	for (int i = 0; i < AllArt.size(); ++i)
	{
		UpdateBuffer(AllArt[i]);
	}

	for (int i = 0; i < LeftTop.size(); ++i)
	{
		UpdateBuffer(LeftTop[i]);
	}

	for (int i = 0; i < RightTop.size(); ++i)
	{
		UpdateBuffer(RightTop[i]);
	}

	for (int i = 0; i < LeftBottom.size(); ++i)
	{
		UpdateBuffer(LeftBottom[i]);
	}

	for (int i = 0; i < RightBottom.size(); ++i)
	{
		UpdateBuffer(RightBottom[i]);
	}

}

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기

	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(WinsizeX, WinsizeY); // 윈도우의 크기 지정
	g_WinID = glutCreateWindow("OGWork-8"); // 윈도우 생성(윈도우 이름)
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";


	make_shaderProgram();

	Create_Line_Pos(&AllArt, WinsizeX/2.f,0.f, WinsizeX / 2.f, WinsizeY);
	InitBuffers(&AllArt);
	Create_Line_Pos(&AllArt, 0.f,WinsizeY/2.f, WinsizeX, WinsizeY / 2.f);
	InitBuffers(&AllArt);
	Create_Triangle(&RightTop,WinsizeX / 4.f * 3.f, WinsizeY / 4.f, 50.f, 100.f); // 1사분면
	InitBuffers(&RightTop);
	Create_Triangle(&LeftTop,WinsizeX/4.f, WinsizeY / 4.f,50.f,100.f); // 2 사분면
	InitBuffers(&LeftTop);
	Create_Triangle(&LeftBottom,WinsizeX/4.f, WinsizeY / 4.f*3.f,50.f,100.f); // 3사분면
	InitBuffers(&LeftBottom);
	Create_Triangle(&RightBottom,WinsizeX/4.f*3.f, WinsizeY / 4.f*3.f,50.f,100.f); // 4사분면
	InitBuffers(&RightBottom);


	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutMotionFunc(MoveMouse);


	glutMainLoop(); // 이벤트 처리 시작
}


GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수 
{
	glClearColor(1.f, 1.f, 1.f, 1.f); // 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다


	//int vColorLocation = glGetUniformLocation(shaderProgramID,"vColor");

	glUseProgram(shaderProgramID);

	//glUniform4f(vColorLocation,1.f,0.f,0.f,1.f);

	//glBindVertexArray(vao);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	for (int i = 0; i < 5; ++i)
	{
		vector<DWArt*>* pVec = AllVec[i];

		for (auto& iter : *pVec)
		{
			glBindVertexArray(iter->VAO);

			switch (iter->eType)
			{
			case DWART_DOT:
				glPointSize(10);
				glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, 0);
				break;

			case DWART_LINE:
				glDrawElements(GL_LINE_STRIP, 2, GL_UNSIGNED_INT, 0);
				break;

			case DWART_TRIANGLE:
				glDrawElements(iPrintType, 3, GL_UNSIGNED_INT, 0);
				break;

			case DWART_RECTANGLE:
				glDrawElements(iPrintType, 6, GL_UNSIGNED_INT, 0);
				break;
			}

		}
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

	case 'c':
		Delete_ALL();
		break;

	case 'q':
		glutDestroyWindow(g_WinID);
		break;

	case 'a':
		iPrintType = GL_TRIANGLES;
		break;

	case 'b':
		iPrintType = GL_LINE_LOOP;
		break;


	default:
		break;
	}

	glutPostRedisplay();
}

bool bPush_L_button{ false };

DWArt* iSqure{};
GLvoid MoveMouse(int X, int Y)
{

	glutPostRedisplay();
}


GLvoid MouseInput(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		bPush_L_button = true;
		switch (button)
		{
			case GLUT_LEFT_BUTTON:
				// 마우스 사분면 체크
			{
				int iQuadrant = CheckMouseQuadrant(x, y); // 사분면
				float fSize = RandomSize(mt);
				switch (iQuadrant)
				{
				case 1:
					Delete_ALL_Art(RightTop);
					Create_DWArt(&RightTop, DW_TRIANGLE, x, y, fSize, fSize * 2.f);
					break;

				case 2:
					Delete_ALL_Art(LeftTop);
					Create_DWArt(&LeftTop, DW_TRIANGLE, x, y, fSize, fSize * 2.f);
					break;

				case 3:
					Delete_ALL_Art(LeftBottom);
					Create_DWArt(&LeftBottom, DW_TRIANGLE, x, y, fSize, fSize * 2.f);
					break;

				case 4:
					Delete_ALL_Art(RightBottom);
					Create_DWArt(&RightBottom, DW_TRIANGLE, x, y, fSize, fSize * 2.f);
					break;

				default:
					break;
				}
			}
			break;

			case GLUT_RIGHT_BUTTON:
			{
				int iQuadrant = CheckMouseQuadrant(x, y); // 사분면
				float fSize = RandomSize(mt);
				switch (iQuadrant)
				{
				case 1:

					
					Create_DWArt(&RightTop, DW_TRIANGLE, x, y, fSize, fSize * 2.f);
					break;

				case 2:

					
					Create_DWArt(&LeftTop, DW_TRIANGLE, x, y, fSize, fSize * 2.f);
					break;

				case 3:

				
					Create_DWArt(&LeftBottom, DW_TRIANGLE, x, y, fSize, fSize * 2.f);
					break;

				case 4:

					
					Create_DWArt(&RightBottom, DW_TRIANGLE, x, y, fSize, fSize * 2.f);
					break;

				}
			}
			break;
		}
	}
	glutPostRedisplay();
}

GLvoid Create_DWArt(vector<DWArt*>* pVec, DrawType eDraw, GLfloat x, GLfloat y, GLfloat rx, GLfloat ry)
{

	if (pVec->size() >= 3)
	{
		return;
	}

	switch (eDraw)
	{
	case DW_DOT:
		Create_Dot(pVec, x, y);
		break;
	case DW_LINE:
		Create_Line(pVec, x, y, rx, ry);
		break;
	case DW_TRIANGLE:
		Create_Triangle(pVec, x, y, rx, ry);
		break;
	case DW_RECT:
		Create_Rect(pVec, x, y, rx, ry);
		break;
	}
	InitBuffers(pVec);
}



GLvoid Move(eMoveType Dir)
{

	if (AllArt.empty())
	{
		return;
	}

	uniform_int_distribution<int> AllArtRandom(0, AllArt.size() - 1);

	int index = AllArtRandom(mt);

	MoveArt(AllArt[index], AllArt[index]->eType, Dir);

	
	glutPostRedisplay();

}

GLvoid Delete_ALL()
{
	Delete_ALL_Art(AllArt);
}
