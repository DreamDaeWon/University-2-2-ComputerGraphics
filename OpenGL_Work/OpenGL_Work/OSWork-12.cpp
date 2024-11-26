#include "Define_Work_12.h"



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



void checkFrameBuffer();


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





// 11 번
GLvoid Change_Form_Triangle(DWArt* pArt);

GLvoid Change_Form_Rectangle(DWArt* pArt);

GLvoid Change_Form_Pentagone(DWArt* pArt);

GLvoid Change_Form_Line(DWArt* pArt);

GLvoid Change_Form_Dot(DWArt* pArt);

GLvoid AllChangeForm(DWArt* pArt);

bool AllChange = false;

// 12번



GLvoid SetMode(DrawType Type)
{
	eDrawType = Type;
}



vector<DWArt*> AllArt{};

vector<DWArt*> AllArtTwo{};
vector<DWArt*> AllArtThree{};
vector<DWArt*> AllArtFour{};
vector<DWArt*> AllArt_Light{};

vector<DWArt*>* AllVec[5]{ &AllArt ,&AllArtTwo ,&AllArtThree ,&AllArtFour ,&AllArt_Light };

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
	for (auto& iter : AllArt)
		UpdateBuffer(iter);
	glutPostRedisplay();
	Move_Diagonal();
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

	for (int i = 0; i < AllArtTwo.size(); ++i)
	{
		UpdateBuffer(AllArtTwo[i]);
	}

	for (int i = 0; i < AllArtThree.size(); ++i)
	{
		UpdateBuffer(AllArtThree[i]);
	}

	for (int i = 0; i < AllArtFour.size(); ++i)
	{
		UpdateBuffer(AllArtFour[i]);
	}

	for (int i = 0; i < AllArt_Light.size(); ++i)
	{
		UpdateBuffer(AllArt_Light[i]);
	}

}

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기

	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(WinsizeX, WinsizeY); // 윈도우의 크기 지정
	g_WinID = glutCreateWindow("OGWork-12"); // 윈도우 생성(윈도우 이름)
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

	Create_Line_Pos(&AllArtThree, WinsizeX / 2.f, 0.f, WinsizeX / 2.f, WinsizeY);
	InitBuffers(&AllArtThree);
	Create_Line_Pos(&AllArtThree, 0.f, WinsizeY / 2.f, WinsizeX, WinsizeY / 2.f);
	InitBuffers(&AllArtThree);


	//
	Create_DWArt(&AllArt, DW_PENTAGONTYPE, RandomPosX(mt), RandomPosY(mt), 50.f, 50.f);
	AllArt.back()->eWantType = DWART_TRIANGLE;

	//
	Create_DWArt(&AllArt, DW_PENTAGONTYPE, RandomPosX(mt), RandomPosY(mt), 50.f, 50.f);
	AllArt.back()->eWantType = DWART_RECTANGLE;


	Create_DWArt(&AllArt, DW_PENTAGONTYPE, RandomPosX(mt), RandomPosY(mt), 50.f, 50.f);
	AllArt.back()->eWantType = DWART_PENTAGON;


	Create_DWArt(&AllArt, DW_PENTAGONTYPE, RandomPosX(mt), RandomPosY(mt), 50.f, 50.f);
	AllArt.back()->eWantType = DWART_LINE;


	Create_DWArt(&AllArt, DW_PENTAGONTYPE, RandomPosX(mt), RandomPosY(mt), 50.f, 50.f);
	AllArt.back()->eWantType = DWART_DOT;

	Create_DWArt(&AllArt, DW_PENTAGONTYPE, RandomPosX(mt), RandomPosY(mt), 50.f, 50.f);
	AllArt.back()->eWantType = DWART_DOT;

	Create_DWArt(&AllArt, DW_PENTAGONTYPE, RandomPosX(mt), RandomPosY(mt), 50.f, 50.f);
	AllArt.back()->eWantType = DWART_DOT;

	Create_DWArt(&AllArt, DW_PENTAGONTYPE, RandomPosX(mt), RandomPosY(mt), 50.f, 50.f);
	AllArt.back()->eWantType = DWART_DOT;

	Create_DWArt(&AllArt, DW_PENTAGONTYPE, RandomPosX(mt), RandomPosY(mt), 50.f, 50.f);
	AllArt.back()->eWantType = DWART_DOT;




	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutMotionFunc(MoveMouse);

	glutTimerFunc(10, All_Move_Func, 1);
	glutTimerFunc(10, Timer, 1);


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

			glUniform1f(Shader_Rotate, iter->Rotate);
			glUniform1f(Shader_CenterX, CoordinateChangeX(iter->CenterX));
			glUniform1f(Shader_CenterY, CoordinateChangeY(iter->CenterY));

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

			case DWART_PENTAGON:
				glDrawElements(iter->PrintType, 9, GL_UNSIGNED_INT, 0);
				break;
			}

		}
	}

	checkFrameBuffer();

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


	default:
		break;
	}

	glutPostRedisplay();
}

bool bPush_L_button{ false };

DWArt* pMouseArt{};
GLvoid MoveMouse(int X, int Y)
{
	if (pMouseArt == nullptr)
	{
		return;
	}

	pMouseArt->CenterX = X;
	pMouseArt->CenterY = Y;
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
			pMouseArt = Check_Mouse_Rect(AllArt,x,y);
		}
		break;

		case GLUT_RIGHT_BUTTON:
		{

		}
		break;
		}
	}
	else if (state == GLUT_UP)
	{
		switch (button)
		{
			case GLUT_LEFT_BUTTON:
				// 마우스 사분면 체크
			{
				if (pMouseArt != nullptr)
				{
					DWArt* Check_Art = Check_Rect_Rect(AllArt, pMouseArt);

					if (Check_Art == nullptr)
					{
						break;
					}

					int PlusType = int(pMouseArt->eWantType + Check_Art->eWantType);

					if (PlusType > (int)(DWART_PENTAGON))
					{
						PlusType = (int)(PlusType % (int)(DWART_END));

						pMouseArt->eWantType = (ArtType)(PlusType + 1);

						pMouseArt->Move = true;

						DeleteArt(AllArt, Check_Art);
						
					}
					else
					{
						pMouseArt->eWantType = (ArtType)(PlusType);

						pMouseArt->Move = true;

						DeleteArt(AllArt, Check_Art);
					}
				}
			}
			break;
		}
	}
	glutPostRedisplay();
}

GLvoid Create_DWArt(vector<DWArt*>* pVec, DrawType eDraw, GLfloat x, GLfloat y, GLfloat rx, GLfloat ry)
{


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
	case DW_PENTAGONTYPE:
		Create_Pentagon(pVec, x, y, rx, ry);
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
	for (auto& iter : AllArt)
	{
		switch (iter->eWantType)
		{
		case DWART_LINE:
			Change_Form_Line(iter);
			break;

		case DWART_TRIANGLE:
			Change_Form_Triangle(iter);
			break;

		case DWART_RECTANGLE:
			Change_Form_Rectangle(iter);
			break;

		case DWART_PENTAGON:
			Change_Form_Pentagone(iter);
			break;

		case DWART_DOT:
			Change_Form_Dot(iter);
			break;
		}
		AllChangeForm(iter);
	}
	glutTimerFunc(10, All_Move_Func, 1);
}


GLvoid AllChangeForm(DWArt* pArt)
{
	if (!AllChange)
	{
		return;
	}


	if (pArt->Move_Timer < 100)
	{

	}
	else
	{
		pArt->eWantType = (ArtType)(pArt->eWantType + 1);
		if (pArt->eWantType == DWART_END)
		{
			pArt->eWantType = DWART_DOT;
		}
		pArt->Move_Timer = 0;
	}
}



GLvoid Change_Form_Triangle(DWArt* pArt)
{
	if (pArt->Move_Timer < 100)
	{
		if (pArt->Move_Timer == 0) // 이전 정점 값 저장
		{
			memcpy(&dynamic_cast<DWPentagon*>(pArt)->BeforeVertex, &dynamic_cast<DWPentagon*>(pArt)->Vertex, sizeof(dynamic_cast<DWPentagon*>(pArt)->Vertex));
		}
		pArt->PrintType = GL_TRIANGLES;

		float t = pArt->Move_Timer / 100.f;

		for (int i = 0; i < 5; ++i) // 정점 보간
		{
			// x
			dynamic_cast<DWPentagon*>(pArt)->Vertex[i][0] = CoordinateChangeX(pArt->CenterX + pArt->rx * Pos_Triangle[i][0]);

			// y 
			dynamic_cast<DWPentagon*>(pArt)->Vertex[i][1] = CoordinateChangeY(pArt->CenterY + pArt->ry * Pos_Triangle[i][1]);
		}
	}
}

GLvoid Change_Form_Rectangle(DWArt* pArt)
{
	if (pArt->Move_Timer <= 100)
	{
		if (pArt->Move_Timer == 0) // 이전 정점 값 저장
		{
			memcpy(&dynamic_cast<DWPentagon*>(pArt)->BeforeVertex, &dynamic_cast<DWPentagon*>(pArt)->Vertex, sizeof(dynamic_cast<DWPentagon*>(pArt)->Vertex));
		}
		pArt->PrintType = GL_TRIANGLES;


		for (int i = 0; i < 5; ++i) // 정점 보간
		{
			// x
			dynamic_cast<DWPentagon*>(pArt)->Vertex[i][0] =  CoordinateChangeX(pArt->CenterX + pArt->rx * Pos_Rectangle[i][0]);

			// y 
			dynamic_cast<DWPentagon*>(pArt)->Vertex[i][1] = CoordinateChangeY(pArt->CenterY + pArt->ry * Pos_Rectangle[i][1]);
		}
	}
}

GLvoid Change_Form_Pentagone(DWArt* pArt)
{
	if (pArt->Move_Timer <= 100)
	{
		//if (pArt->Move_Timer == 0) // 이전 정점 값 저장
		//{
		//	memcpy(&dynamic_cast<DWPentagon*>(pArt)->BeforeVertex, &dynamic_cast<DWPentagon*>(pArt)->Vertex, sizeof(dynamic_cast<DWPentagon*>(pArt)->Vertex));
		//}
		
		pArt->PrintType = GL_TRIANGLES;
		float t = pArt->Move_Timer / 100.f;

		for (int i = 0; i < 5; ++i) // 정점 보간
		{
			// x
			dynamic_cast<DWPentagon*>(pArt)->Vertex[i][0] = CoordinateChangeX(pArt->CenterX + pArt->rx * Pos_Pentagon[i][0]);

			// y 
			dynamic_cast<DWPentagon*>(pArt)->Vertex[i][1] = CoordinateChangeY(pArt->CenterY + pArt->ry * Pos_Pentagon[i][1]);
		}

	}
}

GLvoid Change_Form_Line(DWArt* pArt)
{
	if (pArt->Move_Timer <= 100)
	{
		if (pArt->Move_Timer == 0) // 이전 정점 값 저장
		{
			memcpy(&dynamic_cast<DWPentagon*>(pArt)->BeforeVertex, &dynamic_cast<DWPentagon*>(pArt)->Vertex, sizeof(dynamic_cast<DWPentagon*>(pArt)->Vertex));
		}
		pArt->PrintType = GL_LINE_STRIP;
		
		float t = pArt->Move_Timer / 100.f;

		for (int i = 0; i < 5; ++i) // 정점 보간
		{
			// x
			dynamic_cast<DWPentagon*>(pArt)->Vertex[i][0] = CoordinateChangeX(pArt->CenterX + pArt->rx * Pos_Line[i][0]);

			// y 
			dynamic_cast<DWPentagon*>(pArt)->Vertex[i][1] = CoordinateChangeY(pArt->CenterY + pArt->ry * Pos_Line[i][1]);
		}
	}
}

GLvoid Change_Form_Dot(DWArt* pArt)
{
	if (pArt->Move_Timer <= 100)
	{
		if (pArt->Move_Timer == 0) // 이전 정점 값 저장
		{
			memcpy(&dynamic_cast<DWPentagon*>(pArt)->BeforeVertex, &dynamic_cast<DWPentagon*>(pArt)->Vertex, sizeof(dynamic_cast<DWPentagon*>(pArt)->Vertex));
		}
		else
		{
			//pArt->PrintType = GL_LINE_STRIP;
			
		}
		pArt->PrintType = GL_TRIANGLES;

	
		float t = pArt->Move_Timer / 100.f;

		for (int i = 0; i < 5; ++i) // 정점 보간
		{
			// x
			dynamic_cast<DWPentagon*>(pArt)->Vertex[i][0] = CoordinateChangeX(pArt->CenterX + pArt->rx * Pos_Dot[i][0]);

			// y 
			dynamic_cast<DWPentagon*>(pArt)->Vertex[i][1] = CoordinateChangeY(pArt->CenterY + pArt->ry * Pos_Dot[i][1]);

		}
	}
}

GLvoid Move_Diagonal()
{

	for (auto& iter : AllArt)
	{
		int iMoveSize{5};
		if (!iter->Move)
		{
			continue;
		}
		if (iter->LR) // 오른쪽
		{
			if (iter->CenterX < WinsizeX)
			{
				iter->CenterX += iMoveSize;
			}
			else
			{
				iter->LR = !iter->LR;
				
			}
			if (iter->ZigZag) // 아래
			{
				if (iter->CenterY < WinsizeY)
				{
					iter->CenterY += iMoveSize;
				}
				else
				{
					iter->ZigZag = !iter->ZigZag;
					
				}
			}
			else // 위
			{
				if (iter->CenterY > 0)
				{
					iter->CenterY -= iMoveSize;
				}
				else
				{
					iter->ZigZag = !iter->ZigZag;
					
				}
			}
		}
		if (!iter->LR) // 왼쪽
		{
			if (iter->CenterX > 0)
			{
				iter->CenterX -= iMoveSize;
			}
			else
			{
				iter->LR = !iter->LR;
				
			}
			if (iter->ZigZag) // 아래
			{
				if (iter->CenterY < WinsizeY)
				{
					iter->CenterY += iMoveSize;
				}
				else
				{
					iter->ZigZag = !iter->ZigZag;
					
				}
			}
			else // 위
			{
				if (iter->CenterY > 0)
				{
					iter->CenterY -= iMoveSize;
				}
				else
				{
					iter->ZigZag = !iter->ZigZag;
					
				}
			}
		}
		ReBindArt(iter, DWART_PENTAGON);
	}

}

void checkFrameBuffer() {
	int width = WinsizeX;
	int height = WinsizeY;
	std::vector<unsigned char> pixels(3 * width * height);
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

	// 프레임 버퍼 데이터를 확인
	bool hasData = false;
	for (size_t i = 0; i < pixels.size(); ++i) {
		if (pixels[i] != 0) {
			hasData = true;
			break;
		}
	}

	if (hasData) {
		std::cout << "프레임 버퍼에 데이터가 있습니다." << std::endl;
	}
	else {
		std::cout << "프레임 버퍼가 비어 있습니다." << std::endl;
	}
}