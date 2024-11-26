#include "Define_Work_3D.h"
#include "DW_Camera.h"

uniform_int_distribution<int> RandomIndex(0, 5);

uniform_int_distribution<int> RandomIndexTri(0, 5);


// 카메라 생성
CDW_Camera DW_Camera{ glm::vec3(0.f,0.f,1.f),glm::vec3(0.f,0.f,-1.f) };


// 셰이더 관련 변수
GLuint shaderProgramID{}; // 셰이더 프로그램 이름

GLuint vertexShader{}; // 버텍스 셰이더 객체
GLuint fragmentShader{}; // 프래그먼트 셰이터 객체


void make_vectexShaders() // 버텍스 셰이터 객체 만들기
{
	GLchar* vertexSource{};

	vertexSource = filetobuf("Vertex_Shader_Matrix.glsl");

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

int Shader_Matrix{};
int Shader_ViewTransform{};
int Shader_ProjectionTransform{};


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

	Shader_Matrix = glGetUniformLocation(shaderProgramID, "WorldTransform");
	Shader_ViewTransform = glGetUniformLocation(shaderProgramID, "ViewTransform");
	Shader_ProjectionTransform = glGetUniformLocation(shaderProgramID, "ProjectionTransform");
}




GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyInput(unsigned char key, int x, int y);
GLvoid TimerFunc(int Valule);
GLvoid MouseInput(int button, int state, int x, int y);
GLvoid MoveMouse(int X, int Y);


// 테스트 코드
void checkFrameBuffer();



// 7 번

GLvoid Create_DWArt(vector<DWArt*>* pVec, ArtType eDraw, GLfloat x, GLfloat y, GLfloat rx, GLfloat ry);

GLvoid Move(eMoveType Dir);

GLvoid Delete_ALL();

GLvoid UpdateBuffers();

//void InitBuffers();


// 8번

// 13 번

struct Draw_Cube
{
	bool bDraw = false;

	GLuint index[6]{};
};

struct Draw_Tetrahedron
{
	bool bDraw = false;

	GLuint index[3]{};
};

Draw_Cube One_Cube{};
Draw_Cube Two_Cube{};


Draw_Tetrahedron One_Tetrahedron{};
Draw_Tetrahedron Two_Tetrahedron{};

//////////////////////////// 여기까지 문제관련



vector<DWArt*> AllArt{};

vector<DWArt*> LineArt{};

vector<DWArt*> AllArtTwo{};
vector<DWArt*> AllArtThree{};
vector<DWArt*> AllArtFour{};
vector<DWArt*> AllArt_Light{};

vector<DWArt*>* AllVec[6]{ &AllArt ,&LineArt,&AllArtTwo ,&AllArtThree ,&AllArtFour ,&AllArt_Light };

float fSize[4][4]{};

unsigned int g_WinID{};// 윈도우 ID

bool bTimer = false; // 타이머 문제 관련 변수

GLuint iPrintType = GL_TRIANGLES;



// 4번 타이머 관련변수
bool bDiagoanlMoveTimer = false;
bool bZizgZagTimer = false;
bool bSizeRandomTimer = false;
bool bRandomColorTimer = false;


//GLuint vao, vbo[2];

GLuint* vbo{}, * EBO{};


GLvoid Timer(int Value)
{
	for (auto& iter : AllArt)
		UpdateBuffer(iter);
	glutPostRedisplay();
	glutTimerFunc(16, Timer, 1);
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(WinsizeX, WinsizeY); // 윈도우의 크기 지정
	g_WinID = glutCreateWindow("OGWork-13"); // 윈도우 생성(윈도우 이름)

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
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

	Create_Line_Pos(&LineArt, 0.f, 25.f, 0.f, 0.f, -25.f, 0.f);
	InitBuffers(&LineArt);
	Create_Line_Pos(&LineArt, 25.f, 0.f, 0.f, -25.f, 0.f, 0.f);
	InitBuffers(&LineArt);


	Create_Cube(&AllArt, 0.f, 0.f, 0.f, 5.f, 5.f,5.f);
	InitBuffers(&AllArt);

	Create_Tetrahedron(&AllArt, 0.f, 0.f, 0.f, 5.f, 5.f, 5.f);
	InitBuffers(&AllArt);


	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutMotionFunc(MoveMouse);

	glutTimerFunc(16, Timer, 1);


	glutMainLoop(); // 이벤트 처리 시작
}


GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수 
{
	glClearColor(0.f, 0.f, 0.f, 1.f); // 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다


	//int vColorLocation = glGetUniformLocation(shaderProgramID,"vColor");

	glUseProgram(shaderProgramID);

	//glUniform4f(vColorLocation,1.f,0.f,0.f,1.f);

	//glBindVertexArray(vao);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	for (int i = 0; i < 6; ++i)
	{
		vector<DWArt*>* pVec = AllVec[i];

		for (auto& iter : *pVec)
		{
			MakeWorldMartrix(iter);

			// 월드
			glUniformMatrix4fv(Shader_Matrix,1,GL_FALSE, glm::value_ptr(iter->transformMatrix));

			// 뷰
			DW_Camera.Make_view_Matrix();
			glUniformMatrix4fv(Shader_ViewTransform, 1, GL_FALSE, glm::value_ptr(DW_Camera.Get_view_Matrix()));

			// 투영
			glm::mat4 projection = glm::perspective(glm::radians(90.f), (float)WinsizeX/WinsizeY, 0.1f, 100.f);

			glUniformMatrix4fv(Shader_ProjectionTransform, 1, GL_FALSE, glm::value_ptr(projection));

			glBindVertexArray(iter->VAO);



			switch (iter->eType)
			{
			case DWART_LINE:
				glDrawElements(GL_LINE_STRIP, 2, GL_UNSIGNED_INT, 0);
				break;

			case DWART_CUBE:
				//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
				
				if (One_Cube.bDraw)
				{
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, AllArt.front()->EBO);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(One_Cube.index), One_Cube.index, GL_STREAM_DRAW);

					glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				}
				if (Two_Cube.bDraw)
				{
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, AllArt.front()->EBO);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Two_Cube.index), Two_Cube.index, GL_STREAM_DRAW);

					glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				}

				break;

			case DWART_TETRATEDRON:
				//glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

				if (One_Tetrahedron.bDraw)
				{
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, AllArt.front()->EBO);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(One_Tetrahedron.index), One_Tetrahedron.index, GL_STREAM_DRAW);

					glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
				}
				if (Two_Tetrahedron.bDraw)
				{
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, AllArt.front()->EBO);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Two_Tetrahedron.index), Two_Tetrahedron.index, GL_STREAM_DRAW);

					glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
				}
				break;

			}

			GLenum err;
			while ((err = glGetError()) != GL_NO_ERROR) {
				std::cerr << "OpenGL error: " << err << std::endl;
			}


		}
	}

	// checkFrameBuffer();

	glutSwapBuffers(); // 화면에 출력하기
	glutPostRedisplay();
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
		for (int i = 0; i < 6; ++i)
		{
			One_Cube.index[i] = AllArt.front()->indexVerTex[i];
		}
		One_Cube.bDraw = true;
		Two_Cube.bDraw = false;
		break;


	case '2':
		for (int i = 6; i < 12; ++i)
		{
			One_Cube.index[i-6] = AllArt.front()->indexVerTex[i];
		}
		One_Cube.bDraw = true;
		Two_Cube.bDraw = false;

		break;

	case '3':
		for (int i = 12; i < 18; ++i)
		{
			One_Cube.index[i-12] = AllArt.front()->indexVerTex[i];
		}
		One_Cube.bDraw = true;
		Two_Cube.bDraw = false;

		break;

	case '4':
		for (int i = 18; i < 24; ++i)
		{
			One_Cube.index[i-18] = AllArt.front()->indexVerTex[i];
		}
		One_Cube.bDraw = true;
		Two_Cube.bDraw = false;

		break;

	case '5':
		for (int i = 24; i < 30; ++i)
		{
			One_Cube.index[i-24] = AllArt.front()->indexVerTex[i];
		}
		One_Cube.bDraw = true;
		Two_Cube.bDraw = false;

		break;

	case '6':
		for (int i = 30; i < 36; ++i)
		{
			One_Cube.index[i-30] = AllArt.front()->indexVerTex[i];
		}
		One_Cube.bDraw = true;
		Two_Cube.bDraw = false;

		break;

	case '7':
		for (int i = 0; i < 3; ++i)
		{
			One_Tetrahedron.index[i] = AllArt.back()->indexVerTex[i];
		}
		One_Cube.bDraw = false;
		Two_Cube.bDraw = false;
		One_Tetrahedron.bDraw = true;
		Two_Tetrahedron.bDraw = false;
		break;

	case '8':
		for (int i = 3; i < 6; ++i)
		{
			One_Tetrahedron.index[i-3] = AllArt.back()->indexVerTex[i];
		}
		One_Tetrahedron.bDraw = true;
		Two_Tetrahedron.bDraw = false;
		break;

	case '9':
		for (int i = 6; i < 9; ++i)
		{
			One_Tetrahedron.index[i-6] = AllArt.back()->indexVerTex[i];
		}
		One_Tetrahedron.bDraw = true;
		Two_Tetrahedron.bDraw = false;
		break;

	case '0':
		for (int i = 9; i < 12; ++i)
		{
			One_Tetrahedron.index[i-9] = AllArt.back()->indexVerTex[i];
		}
		One_Tetrahedron.bDraw = true;

		break;

	case '.':

		for (int i = 12; i < 15; ++i)
		{
			Two_Tetrahedron.index[i-12] = AllArt.back()->indexVerTex[i];
		}
		Two_Tetrahedron.bDraw = true;

		for (int i = 15; i < 18; ++i)
		{
			One_Tetrahedron.index[i - 15] = AllArt.back()->indexVerTex[i];
		}
		One_Tetrahedron.bDraw = true;

		break;


	case 'c':
	{
		int iRandomOne = RandomIndex(mt);
		int iRandomTwo = RandomIndex(mt);
		while (true)
		{
			if (iRandomTwo == iRandomOne)
			{
				iRandomTwo = RandomIndex(mt);
			}
			else
			{
				break;
			}
		}

		for (int i = iRandomOne * 6; i < iRandomOne * 6 + 6; ++i)
		{
			One_Cube.index[i - iRandomOne * 6] = AllArt.front()->indexVerTex[i];
		}
		One_Cube.bDraw = true;

		for (int i = iRandomTwo * 6; i < iRandomTwo * 6 + 6; ++i)
		{
			Two_Cube.index[i - iRandomTwo * 6] = AllArt.front()->indexVerTex[i];
		}
		Two_Cube.bDraw = true;


	}
		break;

	case 't':
	{
		int iRandomOne = RandomIndexTri(mt);
		int iRandomTwo = RandomIndexTri(mt);
		while (true)
		{
			if (iRandomTwo == iRandomOne)
			{
				iRandomTwo = RandomIndexTri(mt);
			}
			else
			{
				break;
			}
		}

		for (int i = iRandomOne * 3; i < iRandomOne * 3 + 3; ++i)
		{
			One_Tetrahedron.index[i - iRandomOne * 3] = AllArt.back()->indexVerTex[i];
		}
		One_Tetrahedron.bDraw = true;

		for (int i = iRandomTwo * 3; i < iRandomTwo * 3 + 3; ++i)
		{
			Two_Tetrahedron.index[i - iRandomTwo * 3] = AllArt.back()->indexVerTex[i];
		}
		Two_Tetrahedron.bDraw = true;
	}
	break;


	case 'd':
		DW_Camera.MoveCamera(glm::vec3(0.2f));
		break;

	case 'a':
		DW_Camera.MoveCamera(glm::vec3(-0.2f));
		break;

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
		{
			pMouseArt = Check_Mouse_Rect(AllArt, x, y);
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
		{
			
		}
		break;
		}
	}
	glutPostRedisplay();
}

GLvoid Create_DWArt(vector<DWArt*>* pVec, ArtType eDraw, GLfloat x, GLfloat y, GLfloat rx, GLfloat ry)
{


	switch (eDraw)
	{
	case DWART_LINE:
		
		break;
	case DWART_CUBE:
	
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