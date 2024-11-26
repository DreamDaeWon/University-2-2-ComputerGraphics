#include "Define_Work_3D.h"
#include "DW_Camera2.h"
#include "DW_Imgui_Manager.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static int              g_Width;
static int              g_Height;
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


uniform_int_distribution<int> RandomIndex(0, 5);

uniform_int_distribution<int> RandomIndexTri(0, 5);



uniform_int_distribution<int> RandomOnBoxPos(-2, 2);


// 카메라 생성
CDW_Camera2 DW_Camera{ glm::vec3(0.f, 50.f,100.f),glm::vec3(0.f,0.f,-1.f) };

// IMGUI Manager
DW_imgui_Manager* Imgui_Manager{};




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


void Initialize_Imgui_Manager(HWND hWnd)
{
	Imgui_Manager = new DW_imgui_Manager(hWnd, GetDC(GetForegroundWindow())); // 윈도우 핸들로 프로세스 아이디 얻기

	//Imgui_Manager->Imgui_Initialize();

	Imgui_Manager->Tick();

}


void Initialize_Camera()
{
	DW_Camera.RotateX_Camera(-20.f);
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

	Shader_Matrix = glGetUniformLocation(shaderProgramID, "WorldTransform");
	Shader_ViewTransform = glGetUniformLocation(shaderProgramID, "ViewTransform");
	Shader_ProjectionTransform = glGetUniformLocation(shaderProgramID, "ProjectionTransform");
}




GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyInput(unsigned char key, int x, int y);
GLvoid SpecialKeyInput(int key, int x, int y);
GLvoid TimerFunc(int Valule);
GLvoid MouseInput(int button, int state, int x, int y);
GLvoid MoveMouse(int X, int Y);
GLvoid MoveMouse_Tick(int X, int Y);


// 테스트 코드
void checkFrameBuffer();



// 7 번

GLvoid Create_DWArt(vector<DWArt*>* pVec, ArtType eDraw, GLfloat x, GLfloat y, GLfloat z, GLfloat rx, GLfloat ry, GLfloat rz);

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


// 14번
bool bCallMode{};
bool bLeftTrun{ true };
bool bRightTrun{ true };
float RotateX{};
float RotateY{};

GLvoid RotateAll();

bool RotateCamera = false;


// 15번
//bool bLeftRevolution{};
//bool bRightRevolution{};
float RavolutionX{};
float RavolutionY{};
float RavolutionZ{};

GLvoid RavolutionAll();

bool bMove_Sprial{};
bool bOpen_door{};
bool bMove_Change_Revolution{};
bool bMove_Change_Up_Down{};
bool bMove_Rotate{};


bool bOneChange{};
bool bTwoChange{};


GLint iMove_Sprial{}; // 얼마나 움직였는지?
GLvoid MoveSpiral();


GLvoid MoveDoor();

GLvoid Move_Change_Revolution();



GLint iMove_Up_down{}; // 반정도 갔는지?


GLvoid Move_Change_Up_Down();


GLfloat ScaleOne{};
GLfloat ScaleTwo{};

GLvoid Move_Rotate();


GLvoid ChangeMode();

// 18번

bool bOrtho{ false };



bool bRotate_Up = false;

bool bFront_open = false;


bool bUp_LR = false;

bool bBack_Scale = false;


GLfloat fBack_Scale{ 1.f };

GLfloat fUp{};

GLfloat fFront_Angle = 0.f;

GLvoid Ball_Move();

GLvoid Change_Draw_Timing_Cube();


bool bPlayerMove{}; // 몸통 움직이기

bool bMoveDir[4]{}; // 움직이는 방향 0. 왼, 1. 앞, 2. 오, 3. 뒤

float fSpeed = 5.0f;

bool bJump = false;

bool bOnBoxJump = false;



float fJumpTime = 0.f;

float fGravityTime = 0.f;

int iDelete_Tile_PosX = 0;

int iDelete_Tile_PosY = 0;

int iNowChild = 0; // 현재 점프해야할 자식

bool bChildJump = false; // 자식 점프

bool bAllChildJump = false; // 자식들이 점프 해야 하는지?

float fChildJumpTime = 0.f; // 자식 점프 시간

float fChildGravityTime = 0.f; // 자식 중력 시간




bool bDownShootTrun{}; // 아래포신 회전

float fDownShootTrun{}; // 아래포신 회전 각도값


bool bDownShoorMergePlay{}; // 실행 위에것 꺼야함
bool bDownShootMerge{}; // 아래포신 합치기

bool bUpshoot{}; // 위에 포신 움직이기
bool bUpAngle{}; // 위에 포신 움직이기
float fUpshoot{}; // 위에 포신 움직이기



GLvoid Change_Square_Pyramid();


GLfloat PyramidRotate[4]{};



// 19번 카메라


GLvoid Change_Camera_Move();


bool bRotateCamera{};
bool bRevolutionCamera{};


//////////////////////////// 여기까지 문제관련



vector<DWArt*> AllArt{};

vector<DWArt*> LineArt{};

vector<DWArt*> AllArtTwo{};
vector<DWArt*> AllArtThree{};

vector<DWArt*> AllArtFour{};
vector<DWArt*> AllArt_Light{};

vector<DWArt*>* AllVec[6]{ &LineArt, &AllArt , &AllArtTwo ,&AllArtThree ,&AllArtFour , &AllArt_Light };

float fSize[4][4]{};

unsigned int g_WinID{};// 윈도우 ID

HWND hwnd{};

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


	//17

	Ball_Move();
	//Change_Square_Pyramid();

	MoveDoor();
	RotateAll();
	//RavolutionAll();
	//MoveSpiral();
	//MoveChange();
	//Move_Change_Revolution();
	//Move_Change_Up_Down();
	//Move_Rotate();




	Change_Camera_Move();


	for (auto& iter : AllArt)
		UpdateBuffer(iter);

	glutPostRedisplay();
	//Imgui_Manager->Tick();



	glutTimerFunc(1, Timer, 1);
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
	

	g_WinID = glutCreateWindow("OGWork-23"); // 윈도우 생성(윈도우 이름)

	//hwnd = ::CreateWindowW(wc.lpszClassName, L"Dear ImGui Win32+OpenGL3 Example", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, nullptr, nullptr, wc.hInstance, nullptr);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_CULL_FACE);

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
		//DW_Camera.RotateY_Camera(90.f);
		//DW_Camera.RotateX_Camera(-90.f);
		glutWarpPointer(WinsizeX / 2, WinsizeY / 2);
	}
	else
		std::cout << "GLEW Initialized\n";




	Initialize_Imgui_Manager(GetForegroundWindow());

	Initialize_Camera();
	make_shaderProgram();

	Create_Line_Pos(&LineArt, 0.f, 25.f, 0.f, 0.f, -25.f, 0.f, glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 0.f, 0.f));
	InitBuffers(&LineArt);
	Create_Line_Pos(&LineArt, 25.f, 0.f, 0.f, -25.f, 0.f, 0.f, glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 1.f, 0.f));
	InitBuffers(&LineArt);
	Create_Line_Pos(&LineArt, 0.f, 0.f, 25.f, 0.f, 0.f, -25.f, glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 1.f));
	InitBuffers(&LineArt);



	// 무대
	Create_Face_Want_Color(&AllArt, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, glm::vec3(1.f, 0.f, 0.f));
	AllArt.back()->vRotate[0] = 0.f;
	InitBuffers(&AllArt);

	for (int i = -40; i < 50; i += 40)
	{
		for (int j = -40; j < 50; j += 40)
		{
			Create_Face_Want_Color(&AllArt, j, 0.f, i, 10.f, 0.f, 10.f, glm::vec3(1.f, 0.f, 0.f));
			AllArt.back()->vRotate[0] = 0.f;
			InitBuffers(&AllArt);
		}
	}

	for (int i = -20; i < 50; i += 40)
	{
		for (int j = -20; j < 50; j += 40)
		{
			Create_Face_Want_Color(&AllArt, j, 0.f, i, 10.f, 0.f, 10.f, glm::vec3(1.f, 0.f, 0.f));
			AllArt.back()->vRotate[0] = 0.f;
			InitBuffers(&AllArt);
		}
	}

	for (int i = -40; i <= 50; i += 40)
	{
		for (int j = -20; j <= 50; j += 40)
		{
			Create_Face_Want_Color(&AllArt, j, 0.f, i, 10.f, 0.f, 10.f, glm::vec3(0.f, 1.f, 0.f));
			AllArt.back()->vRotate[0] = 0.f;
			InitBuffers(&AllArt);
		}
	}

	for (int i = -20; i <= 50; i += 40)
	{
		for (int j = -40; j <= 50; j += 40)
		{
			Create_Face_Want_Color(&AllArt, j, 0.f, i, 10.f, 0.f, 10.f, glm::vec3(0.f, 1.f, 0.f));
			AllArt.back()->vRotate[0] = 0.f;
			InitBuffers(&AllArt);
		}
	}



	//Create_Face(&AllArt, 0.f, 0.f, 0.f, 50.f, 0.f, 50.f); // 아래
	//AllArt.back()->vRotate[0] = 0.f;
	//InitBuffers(&AllArt);

	Create_Face(&AllArt, 0.f, 100.f, 0.f, 50, 0.f, 50.f); // 위
	AllArt.back()->vRotate[0] = 180.f;
	InitBuffers(&AllArt);

	Create_Face(&AllArt, -50.f, 50.f, 0.f, 50, 0.f, 50.f); // 왼쪽
	AllArt.back()->vRotate[2] = -90.f;
	InitBuffers(&AllArt);

	Create_Face(&AllArt, 50.f, 50.f, 0.f, 50, 0.f, 50.f); // 오른쪽
	AllArt.back()->vRotate[2] = 90.f;
	InitBuffers(&AllArt);

	Create_Face(&AllArt, 0.f, 50.f, -50.f, 50, 0.f, 50.f); // 뒤
	AllArt.back()->vRotate[0] = 90.f;
	InitBuffers(&AllArt);


	// 열리는 벽

	Create_Face(&AllArtTwo, -25.f, 50.f, 50.f, 25.f, 0.f, 50.f); // 왼쪽
	AllArtTwo.back()->vRotate[0] = 90.f;
	InitBuffers(&AllArtTwo);

	Create_Face(&AllArtTwo, 25.f, 50.f, 50.f, 25.f, 0.f, 50.f); // 오른쪽
	AllArtTwo.back()->vRotate[0] = 90.f;
	InitBuffers(&AllArtTwo);

	// 장애물

	for (int i = 0; i < 3; ++i)
	{
		int iRandX = RandomOnBoxPos(mt);
		int iRandZ = RandomOnBoxPos(mt);

		while (iRandX == 0)
		{
			iRandX = RandomOnBoxPos(mt);
		}

		while (iRandZ == 0)
		{
			iRandZ = RandomOnBoxPos(mt);
		}

		Create_Cube(&AllArtThree, iRandX * 20.f, 5.f, iRandZ * 20.f, 10.f, 5.f, 10.f);
		InitBuffers(&AllArtThree);
	}

	Create_Sylinder_Model(&AllArtThree, 40.f, 70.f, 75.f, 10.f, 10.f, 70.f, 10, 10);
	InitBuffers(&AllArtThree);
	AllArtThree.back()->vRotate[0] += 90.f;

	Create_Sylinder_Model(&AllArtThree, -40.f, 70.f, 75.f, 10.f, 10.f, 70.f, 10, 10);
	InitBuffers(&AllArtThree);
	AllArtThree.back()->vRotate[0] += 90.f;

	Create_Sylinder_Model(&AllArtThree, -40.f, 70.f, -10.f, 10.f, 10.f, 70.f, 10, 10);
	InitBuffers(&AllArtThree);
	AllArtThree.back()->vRotate[0] += 90.f;

	Create_Sylinder_Model(&AllArtThree, 40.f, 70.f, -10.f, 10.f, 10.f, 70.f, 10, 10);
	InitBuffers(&AllArtThree);
	AllArtThree.back()->vRotate[0] += 90.f;


	// 플레이어 몸통
	Create_Cube(&AllArtFour, 0.f, 15.f, 0.f, 5.f, 5.f, 2.5f);
	InitBuffers(&AllArtFour);

	//	머리
	Create_Cube(&AllArtFour, 0.f, 7.5f, 0.f, 2.5f, 2.5f, 2.5f);
	AllArtFour.back()->ParentMatrix = &AllArtFour.front()->transformMatrix;
	InitBuffers(&AllArtFour);

	//	코
	Create_Cube(&AllArtFour, 0.f, 8.75f, -12.5f, 0.5f, 0.5f, 12.5f);
	AllArtFour.back()->ParentMatrix = &AllArtFour.front()->transformMatrix;
	InitBuffers(&AllArtFour);


	// 다리
		// 왼 3
	Create_Cube(&AllArtFour, -2.f, -10.f, 0.f, 1.f, 5.f, 1.f);
	AllArtFour.back()->ParentMatrix = &AllArtFour.front()->transformMatrix;
	InitBuffers(&AllArtFour);

	// 오 4
	Create_Cube(&AllArtFour, 2.f, -10.f, 0.f, 1.f, 5.f, 1.f);
	AllArtFour.back()->ParentMatrix = &AllArtFour.front()->transformMatrix;
	InitBuffers(&AllArtFour);

	// 팔
		// 왼 5
	Create_Cube(&AllArtFour, -6.f, -2.5f, 0.f, 1.f, 5.f, 1.f);
	AllArtFour.back()->ParentMatrix = &AllArtFour.front()->transformMatrix;
	InitBuffers(&AllArtFour);

	// 오 6
	Create_Cube(&AllArtFour, 6.f, -2.5f, 0.f, 1.f, 5.f, 1.f);
	AllArtFour.back()->ParentMatrix = &AllArtFour.front()->transformMatrix;
	InitBuffers(&AllArtFour);








	glutKeyboardFunc(KeyInput);
	glutSpecialFunc(SpecialKeyInput);
	glutMouseFunc(MouseInput);
	glutMotionFunc(MoveMouse);
	glutPassiveMotionFunc(MoveMouse_Tick);
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정

	glutTimerFunc(16, Timer, 1);


	glutMainLoop(); // 이벤트 처리 시작
}


GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수 
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.f); // 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다
	int ColorLocation = glGetUniformLocation(shaderProgramID, "vColor");
	glUseProgram(shaderProgramID);


	for (int i = 0; i < 6; ++i)
	{
		vector<DWArt*>* pVec = AllVec[i];

		for (auto& iter : *pVec)
		{
			MakeWorldMartrix(iter);

			Change_Draw_Timing_Cube();

			// 월드
			glUniformMatrix4fv(Shader_Matrix, 1, GL_FALSE, glm::value_ptr(iter->transformMatrix));

			// 뷰
			DW_Camera.Make_view_Matrix();
			glUniformMatrix4fv(Shader_ViewTransform, 1, GL_FALSE, glm::value_ptr(DW_Camera.Get_view_Matrix()));
			glm::mat4 projection;
			// 투영
			if (bOrtho)
			{
				projection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 200.f);
			}
			else
			{
				projection = glm::perspective(glm::radians(90.f), (float)WinsizeX / WinsizeY, 0.1f, 200.f);
			}

			glUniformMatrix4fv(Shader_ProjectionTransform, 1, GL_FALSE, glm::value_ptr(projection));

			glBindVertexArray(iter->VAO);



			switch (iter->eType)
			{
			case DWART_LINE:
				glDrawElements(GL_LINE_STRIP, iter->indexVerTex.size(), GL_UNSIGNED_INT, 0);
				break;

			case DWART_CIRCLE_SPIRAL:

				glDrawElements(iPrintType, iter->indexVerTex.size(), GL_UNSIGNED_INT, 0);

				break;

			case DWART_FACE:
				glDrawElements(iPrintType, iter->indexVerTex.size(), GL_UNSIGNED_INT, 0);
				break;

			case DWART_CUBE:

				glDrawElements(iPrintType, 36, GL_UNSIGNED_INT, 0);

				break;

			case DWART_TETRATEDRON:
				glDrawElements(iPrintType, 18, GL_UNSIGNED_INT, 0);
				break;


			case DWART_MODEL_SPHERE:
			{
				glBindVertexArray(iter->VAO);
				glUniform4f(ColorLocation, iter->VertexColor[0].x, iter->VertexColor[0].y, iter->VertexColor[0].z, 1);
				gluSphere(iter->Model, iter->Sphere_rx, iter->Sphere_Slices, iter->Sphere_Stacks);
				glUniform4f(ColorLocation, 0, 0, 0, 0);
				glBindVertexArray(0);
			}

			break;

			case DWART_MODEL_SYLINDER:
				glBindVertexArray(iter->VAO);
				glUniform4f(ColorLocation, iter->VertexColor[0].x, iter->VertexColor[0].y, iter->VertexColor[0].z, 1);
				gluCylinder(iter->Model, iter->Sylinder_rx_Top, iter->Sylinder_rx_Bottom, iter->Sylinder_ry, iter->Sylinder_Slices, iter->Sylinder_Stacks);
				glUniform4f(ColorLocation, 0, 0, 0, 0);
				glBindVertexArray(0);

				break;

			}

			GLenum err;
			while ((err = glGetError()) != GL_NO_ERROR) {
				std::cerr << "OpenGL error: " << err << std::endl;
			}


		}
	}



	Imgui_Manager->Render();
	// checkFrameBuffer();
	glViewport(0, 0, WinsizeX, WinsizeY);
	
	Imgui_Manager->Tick();

	glutSwapBuffers(); // 화면에 출력하기
	glutPostRedisplay();
}
GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수 
{

	glViewport(0, 0, w, h);

}

GLvoid SpecialKeyInput(int key, int x, int y)
{
	switch (key)
	{

	}
	//glutPostRedisplay();
}


GLvoid KeyInput(unsigned char key, int x, int y)
{
	if (key == 'q')
	{
		glutDestroyWindow(g_WinID);
	}



	if (key == 'z')
	{
		DW_Camera.Move_Front_Camera(0.5f);
	}

	if (key == 'x')
	{
		DW_Camera.Move_Left_Camera(0.5f);
	}

	if (key == 'Z')
	{
		DW_Camera.Move_Back_Camera(0.5f);
	}

	if (key == 'X')
	{
		DW_Camera.Move_Right_Camera(0.5f);
	}

	if (key == 'y')
	{
		RotateCamera = true;
	}

	if (key == 'Y')
	{
		RotateCamera = false;
	}

	if (key == 'w')
	{
		bPlayerMove = true;
		memset(bMoveDir, 0, sizeof(bMoveDir));
		bMoveDir[1] = true;

	}

	if (key == 'a')
	{
		bPlayerMove = true;
		memset(bMoveDir, 0, sizeof(bMoveDir));
		bMoveDir[0] = true;
	}

	if (key == 's')
	{
		bPlayerMove = true;
		memset(bMoveDir, 0, sizeof(bMoveDir));
		bMoveDir[3] = true;
	}

	if (key == 'd')
	{
		bPlayerMove = true;
		memset(bMoveDir, 0, sizeof(bMoveDir));
		bMoveDir[2] = true;
	}


	if (key == '+')
	{
		fSpeed += 1.f;
	}

	if (key == '-')
	{
		fSpeed -= 1.f;
	}

	if (key == 'j')
	{
		bJump = true;
		bOnBoxJump = true;
	}

	if (key == 'f')
	{
		bChildJump = true;
	}


	if (key == 'i')
	{
		bJump = false;
		bOnBoxJump = false;
		RotateCamera = false;

		bPlayerMove = false;
		memset(bMoveDir, 0, sizeof(bMoveDir));

		DW_Camera.Get_vPos()[0] = 0.f;
		DW_Camera.Get_vPos()[1] = 50.f;
		DW_Camera.Get_vPos()[2] = 100.f;

		DW_Camera.Get_vRevolution()[1] = 0.f;

		AllArtFour.front()->vRotate[1] = 0.f;

		AllArtFour.front()->vPos[0] = 0.f;
		AllArtFour.front()->vPos[1] = 15.f;
		AllArtFour.front()->vPos[2] = 0.f;

		AllArtFour[3]->vRevolution[0] = 0.f;
		AllArtFour[6]->vRevolution[0] = 0.f;

		AllArtFour[4]->vRevolution[0] = 0.f;
		AllArtFour[5]->vRevolution[0] = 0.f;


		bOpen_door = false;

		AllArtTwo[0]->vPos[0] = -25;
		AllArtTwo[1]->vPos[0] = 25;

		fSpeed = 5.f;

	}

	if (key == 't')
	{
		static bool bSpawn = false;

		bSpawn = !bSpawn;

		if (bSpawn)
		{
			{ // 1 번째 아이 사이즈 * 0.8f
				float fSize = 0.8f;

				// 플레이어 몸통 7
				Create_Cube(&AllArtFour, 0.f * fSize, 15.f * fSize, 0.f * fSize, 5.f * fSize, 5.f * fSize, 2.5f * fSize);
				InitBuffers(&AllArtFour);

				//	머리
				Create_Cube(&AllArtFour, 0.f * fSize, 7.5f * fSize, 0.f * fSize, 2.5f * fSize, 2.5f * fSize, 2.5f * fSize);
				AllArtFour.back()->ParentMatrix = &AllArtFour[7]->transformMatrix;
				InitBuffers(&AllArtFour);

				//	코
				Create_Cube(&AllArtFour, 0.f * fSize, 8.75f * fSize, -12.5f * fSize, 0.5f * fSize, 0.5f * fSize, 12.5f * fSize);
				AllArtFour.back()->ParentMatrix = &AllArtFour[7]->transformMatrix;
				InitBuffers(&AllArtFour);


				// 다리
					// 왼 3
				Create_Cube(&AllArtFour, -2.f * fSize, -10.f * fSize, 0.f * fSize, 1.f * fSize, 5.f * fSize, 1.f * fSize);
				AllArtFour.back()->ParentMatrix = &AllArtFour[7]->transformMatrix;
				InitBuffers(&AllArtFour);

				// 오 4
				Create_Cube(&AllArtFour, 2.f * fSize, -10.f * fSize, 0.f * fSize, 1.f * fSize, 5.f * fSize, 1.f * fSize);
				AllArtFour.back()->ParentMatrix = &AllArtFour[7]->transformMatrix;
				InitBuffers(&AllArtFour);

				// 팔
					// 왼 5
				Create_Cube(&AllArtFour, -6.f * fSize, -2.5f * fSize, 0.f * fSize, 1.f * fSize, 5.f * fSize, 1.f * fSize);
				AllArtFour.back()->ParentMatrix = &AllArtFour[7]->transformMatrix;
				InitBuffers(&AllArtFour);

				// 오 6
				Create_Cube(&AllArtFour, 6.f * fSize, -2.5f * fSize, 0.f * fSize, 1.f * fSize, 5.f * fSize, 1.f * fSize);
				AllArtFour.back()->ParentMatrix = &AllArtFour[7]->transformMatrix;
				InitBuffers(&AllArtFour);
			}

			{ // 2 번째 아이 사이즈 * 0.5f
				float fSize = 0.5f;

				// 플레이어 몸통 14
				Create_Cube(&AllArtFour, 0.f * fSize, 15.f * fSize, 0.f * fSize, 5.f * fSize, 5.f * fSize, 2.5f * fSize);
				InitBuffers(&AllArtFour);

				//	머리
				Create_Cube(&AllArtFour, 0.f * fSize, 7.5f * fSize, 0.f * fSize, 2.5f * fSize, 2.5f * fSize, 2.5f * fSize);
				AllArtFour.back()->ParentMatrix = &AllArtFour[14]->transformMatrix;
				InitBuffers(&AllArtFour);

				//	코
				Create_Cube(&AllArtFour, 0.f * fSize, 8.75f * fSize, -12.5f * fSize, 0.5f * fSize, 0.5f * fSize, 12.5f * fSize);
				AllArtFour.back()->ParentMatrix = &AllArtFour[14]->transformMatrix;
				InitBuffers(&AllArtFour);


				// 다리
					// 왼 3
				Create_Cube(&AllArtFour, -2.f * fSize, -10.f * fSize, 0.f * fSize, 1.f * fSize, 5.f * fSize, 1.f * fSize);
				AllArtFour.back()->ParentMatrix = &AllArtFour[14]->transformMatrix;
				InitBuffers(&AllArtFour);

				// 오 4
				Create_Cube(&AllArtFour, 2.f * fSize, -10.f * fSize, 0.f * fSize, 1.f * fSize, 5.f * fSize, 1.f * fSize);
				AllArtFour.back()->ParentMatrix = &AllArtFour[14]->transformMatrix;
				InitBuffers(&AllArtFour);

				// 팔
					// 왼 5
				Create_Cube(&AllArtFour, -6.f * fSize, -2.5f * fSize, 0.f * fSize, 1.f * fSize, 5.f * fSize, 1.f * fSize);
				AllArtFour.back()->ParentMatrix = &AllArtFour[14]->transformMatrix;
				InitBuffers(&AllArtFour);

				// 오 6
				Create_Cube(&AllArtFour, 6.f * fSize, -2.5f * fSize, 0.f * fSize, 1.f * fSize, 5.f * fSize, 1.f * fSize);
				AllArtFour.back()->ParentMatrix = &AllArtFour[14]->transformMatrix;
				InitBuffers(&AllArtFour);
			}

			{ // 3 번째 아이 사이즈 * 0.3f
				float fSize = 0.3f;

				// 플레이어 몸통 21
				Create_Cube(&AllArtFour, 0.f * fSize, 15.f * fSize, 0.f * fSize, 5.f * fSize, 5.f * fSize, 2.5f * fSize);
				InitBuffers(&AllArtFour);

				//	머리
				Create_Cube(&AllArtFour, 0.f * fSize, 7.5f * fSize, 0.f * fSize, 2.5f * fSize, 2.5f * fSize, 2.5f * fSize);
				AllArtFour.back()->ParentMatrix = &AllArtFour[21]->transformMatrix;
				InitBuffers(&AllArtFour);

				//	코
				Create_Cube(&AllArtFour, 0.f * fSize, 8.75f * fSize, -12.5f * fSize, 0.5f * fSize, 0.5f * fSize, 12.5f * fSize);
				AllArtFour.back()->ParentMatrix = &AllArtFour[21]->transformMatrix;
				InitBuffers(&AllArtFour);


				// 다리
					// 왼 3
				Create_Cube(&AllArtFour, -2.f * fSize, -10.f * fSize, 0.f * fSize, 1.f * fSize, 5.f * fSize, 1.f * fSize);
				AllArtFour.back()->ParentMatrix = &AllArtFour[21]->transformMatrix;
				InitBuffers(&AllArtFour);

				// 오 4
				Create_Cube(&AllArtFour, 2.f * fSize, -10.f * fSize, 0.f * fSize, 1.f * fSize, 5.f * fSize, 1.f * fSize);
				AllArtFour.back()->ParentMatrix = &AllArtFour[21]->transformMatrix;
				InitBuffers(&AllArtFour);

				// 팔
					// 왼 5
				Create_Cube(&AllArtFour, -6.f * fSize, -2.5f * fSize, 0.f * fSize, 1.f * fSize, 5.f * fSize, 1.f * fSize);
				AllArtFour.back()->ParentMatrix = &AllArtFour[21]->transformMatrix;
				InitBuffers(&AllArtFour);

				// 오 6
				Create_Cube(&AllArtFour, 6.f * fSize, -2.5f * fSize, 0.f * fSize, 1.f * fSize, 5.f * fSize, 1.f * fSize);
				AllArtFour.back()->ParentMatrix = &AllArtFour[21]->transformMatrix;
				InitBuffers(&AllArtFour);
			}
		}
		else
		{
			int iAllSize = AllArtFour.size();

			for (int i = 0; i < iAllSize; ++i)
			{
				AllArtFour.erase(AllArtFour.begin() + 7, AllArtFour.end());
			}

		}

	}



	if (key == 'p')
	{
		bOrtho = true;
	}

	if (key == 'P')
	{
		bOrtho = false;
	}

	if (key == 'o')
	{
		// glEnable(GL_CULL_FACE);

		bOpen_door = true;

	}

	if (key == 'O')
	{
		// glDisable(GL_CULL_FACE);
		bOpen_door = true;
	}


}

bool bPush_L_button{ false };

DWArt* pMouseArt{};

GLvoid MoveMouse(int X, int Y)
{

	//DW_Camera.RotateY_Camera((WinsizeX / 2 - X) * 0.5f);
	//DW_Camera.RotateX_Camera((WinsizeY / 2 - Y) * 0.5f);


	//glutWarpPointer(WinsizeX / 2, WinsizeY / 2);

	//glutPostRedisplay();
}

GLvoid MoveMouse_Tick(int X, int Y)
{

	//DW_Camera.RotateX_Camera((WinsizeY / 2 - Y) * 0.5f);

	//DW_Camera.RotateY_Camera((WinsizeX / 2 - X) * 0.5f);


	//glutWarpPointer(WinsizeX / 2, WinsizeY / 2);

	//glutPostRedisplay();
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
	//glutPostRedisplay();
}

GLvoid Create_DWArt(vector<DWArt*>* pVec, ArtType eDraw, GLfloat x, GLfloat y, GLfloat z, GLfloat rx, GLfloat ry, GLfloat rz)
{
	if (pVec->size() >= 2)
	{
		return;
	}

	switch (eDraw)
	{
	case DWART_LINE:

		break;
	case DWART_CUBE:
		Create_Cube(pVec, x, y, z, rx, ry, rx);
		break;
	case DWART_TETRATEDRON:
		Create_Tetrahedron(pVec, x, y, z, rx, ry, rx);
		break;
	}
	InitBuffers(pVec);
}

GLvoid RotateAll()
{
	if (RotateCamera)
	{
		DW_Camera.Get_vRotate()[1] += 0.1f;

	}
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


	//glutPostRedisplay();

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

GLvoid RavolutionAll()
{
	for (int i = 1; i < 6; ++i)
	{
		for (auto& iter : *AllVec[i])
		{
			iter->vRevolution[0] += RavolutionX * 0.1f;
			iter->vRevolution[1] += RavolutionY * 0.1f;

		}
	}

	for (int i = 2; i < 6; ++i)
	{
		for (auto& iter : *AllVec[i])
		{
			iter->vRevolution[2] += RavolutionZ * 0.1f;
		}

	}

}

GLvoid MoveSpiral()
{
	if (!bMove_Sprial)
	{
		return;
	}

	for (auto& iter : AllArt)
	{
		if (iMove_Sprial < LineArt.back()->Vertex.size())
		{
			iter->vPos[0] = LineArt.back()->Vertex[iMove_Sprial][0];
			iter->vPos[1] = LineArt.back()->Vertex[iMove_Sprial][1];
			iter->vPos[2] = LineArt.back()->Vertex[iMove_Sprial][2];
			iMove_Sprial += 1;
		}
	}



}

GLvoid MoveDoor()
{
	if (!bOpen_door)
	{
		return;
	}

	else
	{
		if (abs(AllArtTwo.back()->vPos[0]) < 75.f)
		{
			AllArtTwo[0]->vPos[0] -= 0.1f;
			AllArtTwo[1]->vPos[0] += 0.1f;
		}
	}


}

GLvoid Move_Change_Revolution()
{
	if (!bMove_Change_Revolution)
	{
		return;
	}

	if (iMove_Sprial <= 180)
	{
		AllArt.front()->vRevolution[1] = (float)iMove_Sprial;
		AllArt.back()->vRevolution[1] = (float)iMove_Sprial;
		++iMove_Sprial;
	}
}

GLvoid Move_Change_Up_Down()
{

	if (!bMove_Change_Up_Down)
	{
		return;
	}


}

GLvoid Move_Rotate()
{
	if (!bMove_Rotate)
	{
		return;
	}

}

GLvoid ChangeMode()
{

}

GLvoid ChildJump()
{
	if (AllArtFour.size() < 10)
	{
		return;
	}

	if (!bChildJump)
	{
		return;
	}

	static float fOriPos[4] = { AllArtFour[7]->vPos[1], AllArtFour[14]->vPos[1], AllArtFour[21]->vPos[1] };


	fChildGravityTime += 0.01f;

	AllArtFour[iNowChild * 7 + 7]->vPos[1] -= 5.8f * fChildGravityTime;

	if (bChildJump)
	{
		if (fChildJumpTime == 0.f)
		{
			AllArtFour[iNowChild * 7 + 7]->vPos[1] += 0.5f;
		}

		fChildJumpTime += 0.001f;
		AllArtFour[iNowChild * 7 + 7]->vPos[1] += 5.8f * fChildGravityTime;

		AllArtFour[iNowChild * 7 + 7]->vPos[1] += (sinf(fChildJumpTime * 3.141592f / 180.f) * 50.f - 9.8f * fChildJumpTime * fChildJumpTime) * fSpeed;

	}

	if (AllArtFour[iNowChild * 7 + 7]->vPos[1] < fOriPos[iNowChild])
	{
		AllArtFour[iNowChild * 7 + 7]->vPos[1] = fOriPos[iNowChild];
		fChildJumpTime = 0.f;
		fChildGravityTime = 0.f;
		if (iNowChild * 7 + 7 < 21)
		{
			iNowChild++;
		}
		else
		{
			iNowChild = 0;
			bChildJump = false;
		}
	}
}


GLvoid Ball_Move()
{

	static float fAngle = 0.5f;

	static int LiDir = 1.f;
	static int RiDir = -1.f;

	if (bPlayerMove)
	{
		if (fAngle <= 40.f + fSpeed && fAngle >= -40.f - fSpeed)
		{
			fAngle += 0.05f * LiDir * fSpeed;

			AllArtFour[3]->vRevolution[0] += 0.05f * LiDir * fSpeed;
			AllArtFour[6]->vRevolution[0] += 0.05f * LiDir * fSpeed;

			AllArtFour[4]->vRevolution[0] += 0.05f * RiDir * fSpeed;
			AllArtFour[5]->vRevolution[0] += 0.05f * RiDir * fSpeed;

			if (AllArtFour.size() > 10)
			{
				for (int i = 7; i < 22; i += 7)
				{
					AllArtFour[3 + i]->vRevolution[0] += 0.05f * LiDir * fSpeed;
					AllArtFour[6 + i]->vRevolution[0] += 0.05f * LiDir * fSpeed;

					AllArtFour[4 + i]->vRevolution[0] += 0.05f * RiDir * fSpeed;
					AllArtFour[5 + i]->vRevolution[0] += 0.05f * RiDir * fSpeed;
				}


			}

		}
		else
		{

			fAngle = (40.f + fSpeed) * LiDir;

			LiDir = -1 * LiDir;
			RiDir = -1 * RiDir;

			AllArtFour[3]->vRevolution[0] = fAngle;
			AllArtFour[6]->vRevolution[0] = fAngle;

			AllArtFour[4]->vRevolution[0] = -fAngle;
			AllArtFour[5]->vRevolution[0] = -fAngle;

			if (AllArtFour.size() > 10)
			{
				for (int i = 7; i < 22; i += 7)
				{
					AllArtFour[3 + i]->vRevolution[0] = fAngle;
					AllArtFour[6 + i]->vRevolution[0] = fAngle;

					AllArtFour[4 + i]->vRevolution[0] = -fAngle;
					AllArtFour[5 + i]->vRevolution[0] = -fAngle;
				}
			}

		}


		if (AllArtFour.front()->vPos[0] < -50.f)
		{
			memset(bMoveDir, 0, sizeof(bMoveDir));
			bMoveDir[2] = true;
		}

		if (AllArtFour.front()->vPos[0] > 50.f)
		{
			memset(bMoveDir, 0, sizeof(bMoveDir));
			bMoveDir[0] = true;
		}

		if (AllArtFour.front()->vPos[2] < -50.f)
		{
			memset(bMoveDir, 0, sizeof(bMoveDir));
			bMoveDir[3] = true;
		}

		if (AllArtFour.front()->vPos[2] > 50.f)
		{
			memset(bMoveDir, 0, sizeof(bMoveDir));
			bMoveDir[1] = true;
		}


		fGravityTime += 0.01f;

		AllArtFour.front()->vPos[1] -= 5.8f * fGravityTime;

		if (bJump && bOnBoxJump)
		{
			if (fJumpTime == 0.f)
			{
				AllArtFour.front()->vPos[1] += 0.5f;
			}

			fJumpTime += 0.001f;
			AllArtFour.front()->vPos[1] += 5.8f * fGravityTime;

			AllArtFour.front()->vPos[1] += (sinf(fJumpTime * 3.141592f / 180.f) * 50.f - 9.8f * fJumpTime * fJumpTime) * fSpeed;

		}




		// 박스들과 충돌처리

		for (int i = 0; i < AllArtThree.size(); ++i)
		{


			if (AllArtFour.front()->vPos[0] + AllArtFour.front()->rx > AllArtThree[i]->vPos[0] - AllArtThree[i]->rx &&
				AllArtFour.front()->vPos[0] - AllArtFour.front()->rx < AllArtThree[i]->vPos[0] + AllArtThree[i]->rx &&
				AllArtFour.front()->vPos[2] + AllArtFour.front()->rz > AllArtThree[i]->vPos[2] - AllArtThree[i]->rz &&
				AllArtFour.front()->vPos[2] - AllArtFour.front()->rz < AllArtThree[i]->vPos[2] + AllArtThree[i]->rz)
			{

				if (bJump)
				{
					if (AllArtFour.front()->vPos[1] < 20.f + AllArtThree[i]->vPos[1])
					{
						AllArtThree[i]->vPos[1] -= 0.01f;

						fJumpTime = 0.f;
						fGravityTime = 0.f;
						AllArtFour.front()->vPos[1] = 20.f + AllArtThree[i]->vPos[1];
						bOnBoxJump = false;
					}

					break;
				}
				else if (AllArtFour.front()->vPos[1] > 15.f)
				{
					break;
				}
				else
				{
					for (int i = 0; i < 4; ++i)
					{
						if (bMoveDir[i])
						{
							memset(bMoveDir, 0, sizeof(bMoveDir));
							bMoveDir[(i + 2) % 4] = true;
							break;
						}
					}
				}
			}
		}

		for (vector<DWArt*>::iterator iter = AllArtThree.begin(); iter != AllArtThree.end();)
		{
			if ((*iter)->vPos[1] < -5.f)
			{
				iter = AllArtThree.erase(iter);
			}
			else
			{
				iter++;
			}

		}



		if (AllArtFour.front()->vPos[1] < 15.f)
		{
			AllArtFour.front()->vPos[1] = 15.f;
			fJumpTime = 0.f;
			fGravityTime = 0.f;
			bJump = false;
			bOnBoxJump = true;
		}

		ChildJump();




		if (bMoveDir[0]) // 왼
		{
			AllArtFour.front()->vRotate[1] = 90.f;
			AllArtFour.front()->vPos[0] -= fSpeed * 0.01f;


			if (AllArtFour.size() >= 10)
			{
				for (int i = 7; i < AllArtFour.size(); i += 7)
				{
					AllArtFour[i]->vRotate[1] = AllArtFour.front()->vRotate[1] = 90.f;


					AllArtFour[i]->vPos[0] = AllArtFour.front()->vPos[0] + i;
					AllArtFour[i]->vPos[2] = AllArtFour.front()->vPos[2];


				}
			}

		}

		if (bMoveDir[1]) // 앞
		{
			AllArtFour.front()->vRotate[1] = 0.f;
			AllArtFour.front()->vPos[2] -= fSpeed * 0.01f;

			if (AllArtFour.size() >= 10)
			{
				for (int i = 7; i < AllArtFour.size(); i += 7)
				{
					AllArtFour[i]->vRotate[1] = AllArtFour.front()->vRotate[1] = 0.f;


					AllArtFour[i]->vPos[0] = AllArtFour.front()->vPos[0];
					AllArtFour[i]->vPos[2] = AllArtFour.front()->vPos[2] + i;


				}
			}

		}

		if (bMoveDir[2]) // 오
		{
			AllArtFour.front()->vRotate[1] = -90.f;
			AllArtFour.front()->vPos[0] += fSpeed * 0.01f;

			if (AllArtFour.size() >= 10)
			{
				for (int i = 7; i < AllArtFour.size(); i += 7)
				{
					AllArtFour[i]->vRotate[1] = AllArtFour.front()->vRotate[1] = -90.f;


					AllArtFour[i]->vPos[0] = AllArtFour.front()->vPos[0] - i;
					AllArtFour[i]->vPos[2] = AllArtFour.front()->vPos[2];


				}
			}

		}

		if (bMoveDir[3]) // 뒤
		{
			AllArtFour.front()->vRotate[1] = 180.f;
			AllArtFour.front()->vPos[2] += fSpeed * 0.01f;

			if (AllArtFour.size() >= 10)
			{
				for (int i = 7; i < AllArtFour.size(); i += 7)
				{
					AllArtFour[i]->vRotate[1] = AllArtFour.front()->vRotate[1] = 180.f;


					AllArtFour[i]->vPos[0] = AllArtFour.front()->vPos[0];
					AllArtFour[i]->vPos[2] = AllArtFour.front()->vPos[2] - i;


				}
			}

		}
	}

}

GLvoid Change_Draw_Timing_Cube()
{
	static GLfloat fAngle{ };


	if (AllArt.size() == 0)
	{
		return;
	}

	if (AllArtTwo.size() != 0)
	{


	}
}

GLvoid Change_Square_Pyramid()
{

}

GLvoid Change_Camera_Move()
{
	if (bRotateCamera)
	{
		DW_Camera.RotateY_Camera(0.1f);
	}

	if (bRevolutionCamera)
	{
		DW_Camera.RevolutionY_Camera(0.1f);
	}
}



LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED)
		{
			glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
