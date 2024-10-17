#include "Define_Work_10.h"



// 셰이더 관련 변수
GLuint shaderProgramID{}; // 셰이더 프로그램 이름
GLuint vertexShader{}; // 버텍스 셰이더 객체
GLuint fragmentShader{}; // 프래그먼트 셰이터 객체



void make_vectexShaders() // 버텍스 셰이터 객체 만들기
{
	GLchar* vertexSource{};

	vertexSource = filetobuf("Vertex_Shader_Rotate.glsl");

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

int Shader_Rotate{};
int Shader_CenterX{};
int Shader_CenterY{};


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

	Shader_Rotate = glGetUniformLocation(shaderProgramID, "Rotate");
	Shader_CenterX = glGetUniformLocation(shaderProgramID, "CenterX");
	Shader_CenterY = glGetUniformLocation(shaderProgramID, "CenterY");
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

GLvoid Move(eMoveType Dir);

GLvoid Delete_ALL();

GLvoid UpdateBuffers();

//void InitBuffers();


// 8 번



// 9 번

GLint Move_Style = 0;

GLvoid All_Move_Func(GLint Value);

GLvoid Move_Diagonal();

GLvoid Move_ZigZig();

GLvoid Move_Squire_Spiral();

GLvoid Move_Circle_spiral();


// 10 번
GLvoid Draw_Spiral(int Value);

GLfloat AllTime[5]{};
GLuint iPrintType = GL_POINTS;


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
	
	//for (auto& iter : AllArt)
		//UpdateBuffer(iter);
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 1);
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
	g_WinID = glutCreateWindow("OGWork-10"); // 윈도우 생성(윈도우 이름)
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


	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutMotionFunc(MoveMouse);

	glutTimerFunc(1, All_Move_Func, 1);
	glutTimerFunc(10, Timer, 1);

	glutMainLoop(); // 이벤트 처리 시작
}


GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수 
{
	glClearColor(0.f, 0.f, 0.f, 1.f); // 바탕색을 ‘blue’ 로 지정
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

			glUniform1f(Shader_Rotate, iter->Rotate);
			glUniform1f(Shader_CenterX, CoordinateChangeX(iter->CenterX));
			glUniform1f(Shader_CenterY, CoordinateChangeY(iter->CenterY));

			glBindVertexArray(iter->VAO);

			switch (iter->eType)
			{
			case DWART_DOT:
				glPointSize(5);
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

			case DWART_SPIRAL:
				glPointSize(10);
				glDrawElements(iPrintType, dynamic_cast<DWSpiral*>(iter)->Vertex.size(), GL_UNSIGNED_INT, 0);
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

	case '1':
		
		glutTimerFunc(100, Draw_Spiral, 1);
		break;

	case '2':
		Create_Circle_Sprial(&AllArt, RandomPosX(mt), RandomPosY(mt));
		Create_Circle_Sprial(&AllArt, RandomPosX(mt), RandomPosY(mt));
		//glutTimerFunc(100, Draw_Spiral, 1);
		break;

	case '3':
		Create_Circle_Sprial(&AllArt, RandomPosX(mt), RandomPosY(mt));
		Create_Circle_Sprial(&AllArt, RandomPosX(mt), RandomPosY(mt));
		Create_Circle_Sprial(&AllArt, RandomPosX(mt), RandomPosY(mt));

		//glutTimerFunc(100, Draw_Spiral, 1);
		break;

	case '4':
		Create_Circle_Sprial(&AllArt, RandomPosX(mt), RandomPosY(mt));
		Create_Circle_Sprial(&AllArt, RandomPosX(mt), RandomPosY(mt));
		Create_Circle_Sprial(&AllArt, RandomPosX(mt), RandomPosY(mt));
		Create_Circle_Sprial(&AllArt, RandomPosX(mt), RandomPosY(mt));

		//glutTimerFunc(100, Draw_Spiral, 1);
		break;

	case '5':
		Create_Circle_Sprial(&AllArt, RandomPosX(mt), RandomPosY(mt));
		Create_Circle_Sprial(&AllArt, RandomPosX(mt), RandomPosY(mt));
		Create_Circle_Sprial(&AllArt, RandomPosX(mt), RandomPosY(mt));
		Create_Circle_Sprial(&AllArt, RandomPosX(mt), RandomPosY(mt));
		Create_Circle_Sprial(&AllArt, RandomPosX(mt), RandomPosY(mt));

		//glutTimerFunc(100, Draw_Spiral, 1);
		break;

	case 'p':
		iPrintType = GL_POINTS;
		break;

	case 'l':
		iPrintType = GL_LINES;
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
			Create_Circle_Sprial(&AllArt,x,y);

			glutTimerFunc(10, Draw_Spiral, 1);
		}
		break;

		case GLUT_RIGHT_BUTTON:
		{

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


GLvoid All_Move_Func(GLint Value)
{
	switch (Move_Style)
	{
	case 1:
		Move_Diagonal();
		break;

	case 2:

		Move_ZigZig();
		break;

	case 3:


		//Move_Squire_Spiral();
		break;

	case 4:
		//Move_Circle_spiral();
		break;

	default:

		break;
	}

	glutTimerFunc(1, All_Move_Func, 1);
}

GLvoid Move_Diagonal()
{
	for (auto& iter : AllArt)
	{
		if (iter->LR) // 오른쪽
		{
			if (iter->CenterX < WinsizeX)
			{
				iter->CenterX += 10;
			}
			else
			{
				iter->LR = !iter->LR;
				iter->Rotate = RandomAngle(mt);
			}
			if (iter->ZigZag) // 아래
			{
				if (iter->CenterY < WinsizeY)
				{
					iter->CenterY += 10;
				}
				else
				{
					iter->ZigZag = !iter->ZigZag;
					iter->Rotate = RandomAngle(mt);
				}
			}
			else // 위
			{
				if (iter->CenterY > 0)
				{
					iter->CenterY -= 10;
				}
				else
				{
					iter->ZigZag = !iter->ZigZag;
					iter->Rotate = RandomAngle(mt);
				}
			}
		}
		if (!iter->LR) // 왼쪽
		{
			if (iter->CenterX > 0)
			{
				iter->CenterX -= 10;
			}
			else
			{
				iter->LR = !iter->LR;
				iter->Rotate = RandomAngle(mt);
			}
			if (iter->ZigZag) // 아래
			{
				if (iter->CenterY < WinsizeY)
				{
					iter->CenterY += 10;
				}
				else
				{
					iter->ZigZag = !iter->ZigZag;
					iter->Rotate = RandomAngle(mt);
				}
			}
			else // 위
			{
				if (iter->CenterY > 0)
				{
					iter->CenterY -= 10;
				}
				else
				{
					iter->ZigZag = !iter->ZigZag;
					iter->Rotate = RandomAngle(mt);
				}
			}
		}
		ReBindArt(iter, DWART_TRIANGLE);
	}

}

GLvoid Move_ZigZig()
{
	for (auto& iter : AllArt)
	{
		// 좌우로 먼저 고
		if (iter->Move_Timer == 0)
		{
			if (iter->LR) // 오른쪽
			{
				iter->CenterX += 10.f;
			}
			else
			{
				iter->CenterX -= 10.f;
			}
		}

		// 왼쪽 또는 오른쪽 벽에 박으면 아래로 고

		if (iter->CenterX <= 0 || iter->CenterX >= WinsizeX)
		{
			if (iter->Move_Timer == 0)
			{
				if (iter->LR)
				{
					iter->CenterX = WinsizeX;
				}
				else
				{
					iter->CenterX = 0;
				}

				iter->LR = !iter->LR;
				iter->Rotate = RandomAngle(mt);

			}

			if (iter->ZigZag) // 아래
			{
				iter->CenterY += 10;
			}
			else
			{
				iter->CenterY -= 10;
			}
			iter->Move_Timer += 1;

			if (iter->Move_Timer >= 10)
			{
				iter->Move_Timer = 0;
			}

		}
		// 아래 벽에 박으면 위로 고
		if (iter->CenterY < 0 || iter->CenterY > WinsizeY)
		{
			if (iter->ZigZag)
			{
				iter->ZigZag = !iter->ZigZag;
				iter->Move_Timer = 0;
				iter->CenterY = WinsizeY;
			}
			else // 위 벽에 박으면 아래로 고
			{
				iter->ZigZag = !iter->ZigZag;
				iter->Move_Timer = 0;
				iter->CenterY = 0;
			}
			iter->Rotate = RandomAngle(mt);
		}
		ReBindArt(iter, DWART_TRIANGLE);
	}
}

GLvoid Move_Squire_Spiral()
{
	int iSmallSize{}; // 줄일 크기

	for (auto& iter : AllArt)
	{
		// 왼쪽 벽에 박으면 아래로 고, 오른쪽 벽을 당김
		switch (iter->eDir)
		{

		case DIR_LEFT:
			if (iter->CenterX > iter->Wall_Min_X)
			{
				iter->CenterX -= 10;

			}
			else
			{
				iter->CenterX = iter->Wall_Min_X;

				iter->eDir = DIR_DOWN; // 아래방향으로 변경

				iter->Wall_Max_X -= 50; // 오른쪽 줄이기
				iter->Rotate = RandomAngle(mt);

			}
			break;

		case DIR_RIGHT:
			if (iter->CenterX < iter->Wall_Max_X)
			{
				iter->CenterX += 10;

			}
			else
			{
				iter->CenterX = iter->Wall_Max_X;

				iter->eDir = DIR_UP; // 위쪽방향 변경

				iter->Wall_Min_X += 50; // 왼쪽 줄이기
				iter->Rotate = RandomAngle(mt);
			}
			break;

		case DIR_DOWN:
			if (iter->CenterY < iter->Wall_Max_Y)
			{
				iter->CenterY += 10;

			}
			else
			{
				iter->CenterY = iter->Wall_Max_Y;

				iter->eDir = DIR_RIGHT; // 오른쪽

				iter->Wall_Min_Y += 50; // 위쪽 줄이기
				iter->Rotate = RandomAngle(mt);
			}
			break;

		case DIR_UP:
			if (iter->CenterY > iter->Wall_Min_Y)
			{
				iter->CenterY -= 10;

			}
			else
			{
				iter->CenterY = iter->Wall_Min_Y;

				iter->eDir = DIR_LEFT; // 왼쪽 방향으로 이동

				iter->Wall_Max_Y -= 50; // 아래쪽 줄이기
				iter->Rotate = RandomAngle(mt);
			}
			break;


		default:
			break;
		}
		ReBindArt(iter, DWART_TRIANGLE);
	}

}

//GLvoid Move_Circle_spiral()
//{
//	// 일단 가운데로 모이게 한다.
//
//	for (auto& iter : AllArt)
//	{
//		if (iter->LRCenterMove)
//		{
//			if (iter->LR) // 오른쪽
//			{
//				if (iter->CenterX > WinsizeX / 2.f)
//				{
//					iter->CenterX -= 10;
//				}
//				else
//				{
//					iter->CenterX = WinsizeX / 2.f;
//					iter->LRCenterMove = false;
//				}
//			}
//			else if (!iter->LR)
//			{
//				if (iter->CenterX < WinsizeX / 2.f)
//				{
//					iter->CenterX += 10;
//				}
//				else
//				{
//					iter->CenterX = WinsizeX / 2.f;
//					iter->LRCenterMove = false;
//				}
//			}
//		}
//		if (iter->UDCenterMove)
//		{
//			if (!iter->ZigZag) // 아래쪽
//			{
//				if (iter->CenterY > WinsizeY / 2.f)
//				{
//					iter->CenterY -= 10;
//				}
//				else
//				{
//					iter->CenterY = WinsizeY / 2.f;
//					iter->UDCenterMove = false;
//				}
//			}
//			else if (iter->ZigZag) // 위쪽
//			{
//				if (iter->CenterY < WinsizeY / 2.f)
//				{
//					iter->CenterY += 10;
//				}
//				else
//				{
//					iter->CenterY = WinsizeY / 2.f;
//					iter->UDCenterMove = false;
//				}
//			}
//		}
//		if (!iter->LRCenterMove and !iter->UDCenterMove)
//		{
//
//
//			iter->CenterX = sinf(iter->Circle_Rotate * (M_PI / 180.0f)) * iter->Rotate_Radius;
//			iter->CenterY = cosf(iter->Circle_Rotate * (M_PI / 180.0f)) * iter->Rotate_Radius;
//
//			iter->CenterX += WinsizeX / 2.f;
//			iter->CenterY += WinsizeY / 2.f + iter->NowCenterY;
//
//			iter->Circle_Rotate += 1.f;
//
//			iter->Rotate += 1.f;
//
//			if ((int)iter->Circle_Rotate % 180 == 0)
//			{
//				iter->Rotate_Radius += 50.f;
//
//				if ((int)iter->Circle_Rotate == 180)
//				{
//					iter->NowCenterY = 50.f;
//				}
//				else if ((int)iter->Circle_Rotate == 360.f)
//				{
//					iter->NowCenterY = 0.f;
//				}
//			}
//
//			if (iter->Circle_Rotate >= 360.f)
//			{
//				iter->Circle_Rotate = 0.f;
//			}
//		}
//
//		ReBindArt(iter, DWART_TRIANGLE);
//
//	}
//}

GLvoid Draw_Spiral(int Value)
{
	Move_Circle_Sprial(&AllArt);
	glutPostRedisplay();
	glutTimerFunc(100,Draw_Spiral,1);
}

