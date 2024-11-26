#include "Define_Work_3D.h"
#include "DW_Camera2.h"

uniform_int_distribution<int> RandomIndex(0, 5);

uniform_int_distribution<int> RandomIndexTri(0, 5);


// 카메라 생성
CDW_Camera2 DW_Camera{ glm::vec3(0.f,10.f,5.f),glm::vec3(0.f,0.f,-1.f) };



// 셰이더 관련 변수
GLuint shaderProgramID{}; // 셰이더 프로그램 이름

GLuint vertexShader{}; // 버텍스 셰이더 객체
GLuint fragmentShader{}; // 프래그먼트 셰이터 객체


void make_vectexShaders() // 버텍스 셰이터 객체 만들기
{
	GLchar* vertexSource{};

	vertexSource = filetobuf("light_Vertex_shader.glsl");

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

	fragmentSource = filetobuf("Non_distance_fragment_shader.glsl");

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

unsigned int lightPosLocation{};
unsigned int lightColorLocation{};
//unsigned int objColorLocation{};

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

	lightPosLocation = glGetUniformLocation(shaderProgramID, "lightPos"); //--- lightPos 값 전달: (0.0, 0.0, 5.0);
	//glUniform3f(lightPosLocation, 0.0, 0.0, 5.0);
	lightColorLocation = glGetUniformLocation(shaderProgramID, "lightColor"); //--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색
	//glUniform3f(lightColorLocation, 1.0, 1.0, 1.0);
	//objColorLocation = glGetUniformLocation(shaderProgramID, "objectColor"); //--- object Color값 전달: (1.0, 0.5, 0.3)의 색
	//glUniform3f(objColorLocation, 1.0, 0.5, 0.3);

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


bool bMoveAll{}; // 아래 몸통 움직이기

bool bMoveLeft{}; // 아래 몸통 움직이기

bool bParallel{}; // 아래몸통 회전


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



bool bLight_Move{};
bool bLight_Move_Up{};
void Light_Move(float fTimer);
void Light_Move_up(float fTimer);


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

	//17
	Light_Move(0.01f);
	Ball_Move();
	Change_Square_Pyramid();


	//RotateAll();
	//RavolutionAll();
	//MoveSpiral();
	//MoveChange();
	//Move_Change_Revolution();
	//Move_Change_Up_Down();
	//Move_Rotate();


	Change_Camera_Move();
	glutTimerFunc(1, Timer, 1);
}


void InitBuffers(vector<DWArt*>* pVec)
{
	for (int i = (*pVec).size() - 1; i < (*pVec).size(); ++i)
	{

		InitBuffer((*pVec)[i]);
	}
}



void Init_light_Buffers(vector<DWArt*>* pVec)
{
	for (int i = (*pVec).size() - 1; i < (*pVec).size(); ++i)
	{
		InitBuffer_Light((*pVec)[i]);
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
	g_WinID = glutCreateWindow("OGWork-26"); // 윈도우 생성(윈도우 이름)

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

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

	Initialize_Camera();
	make_shaderProgram();


	Create_Obj_Want_Color("obj_file\\cube3.obj", glm::vec3(1, 1, 1), &AllArt_Light, 0, 15, 3, 1, 1, 1);
	Init_light_Buffers(&AllArt_Light);
	AllArt_Light.back()->vRotate[0] -= 90.f;





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

			// 월드
			glUniformMatrix4fv(Shader_Matrix, 1, GL_FALSE, glm::value_ptr(iter->transformMatrix));

			// 뷰
			DW_Camera.Make_view_Matrix();
			glUniformMatrix4fv(Shader_ViewTransform, 1, GL_FALSE, glm::value_ptr(DW_Camera.Get_view_Matrix()));
			glm::mat4 projection;
			// 투영
			//if (bOrtho)
			//{
				//projection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 200.f);
			//}
			//else
			//{
			projection = glm::perspective(glm::radians(90.f), (float)WinsizeX / WinsizeY, 0.1f, 200.f);
			//}

			glUniformMatrix4fv(Shader_ProjectionTransform, 1, GL_FALSE, glm::value_ptr(projection));


			glm::vec3 Light_Pos = {};
			glm::vec3 Light_Color = {};

			if (AllArt_Light.size() != 0)
			{
				Light_Pos = glm::vec3(AllArt_Light.back()->vPos[0], AllArt_Light.back()->vPos[1], AllArt_Light.back()->vPos[2]);

				//Light_Pos = DW_Camera.Get_view_Matrix() * glm::vec4(Light_Pos, 1.f);


				MakeWorldMartrix(AllArt_Light.back());

				Light_Pos = AllArt_Light.back()->transformMatrix * glm::vec4(Light_Pos, 1.f);

				Light_Color = AllArt_Light.back()->VertexColor.back();
			}

			glUniform3f(lightPosLocation, Light_Pos.x, Light_Pos.y, Light_Pos.z);
			glUniform3f(lightColorLocation, Light_Color.x, Light_Color.y, Light_Color.z);
			//glUniform3f(objColorLocation, 1.0, 0.5, 0.3);


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

				glDrawElements(iPrintType, iter->indexVerTex.size(), GL_UNSIGNED_INT, 0);

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

	// checkFrameBuffer();
	glViewport(0, 0, WinsizeX, WinsizeY);
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


	if (key == 't')
	{
		AllArt_Light.back()->VertexColor.back().x = 0.f;
		AllArt_Light.back()->VertexColor.back().y = 0.f;
		AllArt_Light.back()->VertexColor.back().z = 0.f;
	}

	if (key == 'T')
	{
		AllArt_Light.back()->VertexColor.back().x = 1.f;
		AllArt_Light.back()->VertexColor.back().y = 1.f;
		AllArt_Light.back()->VertexColor.back().z = 1.f;
	}


	if (key == 'y')
	{
		AllArt_Light.back()->VertexColor.back().x = RandomRGB(mt) / 10.f;
		AllArt_Light.back()->VertexColor.back().y = RandomRGB(mt) / 10.f;
		AllArt_Light.back()->VertexColor.back().z = RandomRGB(mt) / 10.f;
	}

	if (key == 'u')
	{
		bLight_Move = true;
		bLight_Move_Up = false;
	}

	if (key == 'U')
	{
		bLight_Move = false;
		bLight_Move_Up = true;
	}


	if (key == 'i')
	{
		bLight_Move = false;
		bLight_Move_Up = false;
	}




	if (key == 'w')
	{
		DW_Camera.Move_Front_Camera(0.5f);
	}

	if (key == 'a')
	{
		DW_Camera.Move_Left_Camera(0.5f);
	}

	if (key == 's')
	{
		DW_Camera.Move_Back_Camera(0.5f);
	}

	if (key == 'd')
	{
		DW_Camera.Move_Right_Camera(0.5f);
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
		glEnable(GL_CULL_FACE);
	}

	if (key == 'O')
	{
		glDisable(GL_CULL_FACE);
	}



	// 18

	if (key == 'g')
	{
		Delete_ALL_Art(AllArt);
		Delete_ALL_Art(AllArtTwo);
		Delete_ALL_Art(AllArtThree);
		Delete_ALL_Art(AllArtFour);

		Create_Face(&LineArt, 0, 0, 0, 100, 100, 100);
		InitBuffers(&LineArt);

		Create_Obj("obj_file\\cube3.obj", &AllArt, 0.f * 0.5f, 5.f * 0.5f, 0.f * 0.5f, 10.f, 5.f, 10.f);
		InitBuffers(&AllArt);
		AllArt.back()->vScale[0] = 0.5f;
		AllArt.back()->vScale[1] = 0.5f;
		AllArt.back()->vScale[2] = 0.5f;

		Create_Obj("obj_file\\cube3.obj", &AllArtTwo, 0.f * 0.5f, 7.5f * 0.5f, 0.f * 0.5f, 5.f, 2.5f, 5.f);
		InitBuffers(&AllArtTwo);
		AllArtTwo.back()->ParentMatrix = &AllArt.back()->transformMatrix;
		AllArt.back()->vScale[0] = 0.5f;
		AllArt.back()->vScale[1] = 0.5f;
		AllArt.back()->vScale[2] = 0.5f;

		// 자식 포신

		// 왼 0
		Create_Obj("obj_file\\cube3.obj", &AllArtThree, 2.f * 0.5f, 5.f * 0.5f, 0.f * 0.5f, 1.f, 5.f, 1.f);
		InitBuffers(&AllArtThree);
		AllArtThree.back()->ParentMatrix = &AllArtTwo.back()->transformMatrix;
		AllArt.back()->vScale[0] = 0.5f;
		AllArt.back()->vScale[1] = 0.5f;
		AllArt.back()->vScale[2] = 0.5f;
		//// 오 1

		Create_Obj("obj_file\\cube3.obj", &AllArtThree, -2.f * 0.5f, 5.f * 0.5f, 0.f * 0.5f, 1.f, 5.f, 1.f);
		InitBuffers(&AllArtThree);
		AllArtThree.back()->ParentMatrix = &AllArtTwo.back()->transformMatrix;
		AllArt.back()->vScale[0] = 0.5f;
		AllArt.back()->vScale[1] = 0.5f;
		AllArt.back()->vScale[2] = 0.5f;
		// 몸통 포신

		////왼 0
		Create_Obj("obj_file\\cube3.obj", &AllArtFour, 5.f * 0.5f, 0.f * 0.5f, 15.f * 0.5f, 1.f, 1.f, 7.f);
		InitBuffers(&AllArtFour);
		AllArtFour.back()->ParentMatrix = &AllArt.back()->transformMatrix;
		AllArt.back()->vScale[0] = 0.5f;
		AllArt.back()->vScale[1] = 0.5f;
		AllArt.back()->vScale[2] = 0.5f;
		//// 오 1
		Create_Obj("obj_file\\cube3.obj", &AllArtFour, -5.f * 0.5f, 0.f * 0.5f, 15.f * 0.5f, 1.f, 1.f, 7.f);
		InitBuffers(&AllArtFour);
		AllArtFour.back()->ParentMatrix = &AllArt.back()->transformMatrix;
		AllArt.back()->vScale[0] = 0.5f;
		AllArt.back()->vScale[1] = 0.5f;
		AllArt.back()->vScale[2] = 0.5f;
	}







	if (key == 'z')
	{

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		bMoveAll = true;


	}
	if (key == 'Z')
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		bMoveAll = false;


	}


	if (key == 'x')
	{

		bParallel = !bParallel;

		RotateY = 1.f;

	}
	if (key == 'X')
	{

		bParallel = !bParallel;
		RotateY = -1.f;
	}

	if (key == 'c')
	{
		bDownShoorMergePlay = false;
		fDownShootTrun = 1.f;
		bDownShootTrun = !bDownShootTrun;
	}
	if (key == 'C')
	{
		bDownShoorMergePlay = false;
		fDownShootTrun = -1.f;
		bDownShootTrun = !bDownShootTrun;
	}

	if (key == 'v')
	{
		bDownShoorMergePlay = true;
		bDownShootMerge = true;
		bDownShootTrun = false;

	}
	if (key == 'V')
	{
		bDownShoorMergePlay = true;
		bDownShootMerge = false;
		bDownShootTrun = false;

	}


	if (key == 'b')
	{
		bUpshoot = true;
	}
	if (key == 'B')
	{
		bUpshoot = false;
	}




	if (key == 'n')
	{
		bMoveAll = false; // 아래 몸통 움직이기

		bMoveLeft = false; // 아래 몸통 움직이기

		bParallel = false; // 아래몸통 회전


		bDownShootTrun = false; // 아래포신 회전


		bDownShoorMergePlay = false; // 실행 위에것 꺼야함
		bDownShootMerge = false; // 아래포신 합치기

		bUpshoot = false; // 위에 포신 움직이기
		bUpAngle = false; // 위에 포신 움직이기

		bRotateCamera = false;
		bRevolutionCamera = false;

	}
	if (key == 'N')
	{

		bMoveAll = false; // 아래 몸통 움직이기

		bMoveLeft = false; // 아래 몸통 움직이기

		bParallel = false; // 아래몸통 회전


		bDownShootTrun = false; // 아래포신 회전


		bDownShoorMergePlay = false; // 실행 위에것 꺼야함
		bDownShootMerge = false; // 아래포신 합치기

		bUpshoot = false; // 위에 포신 움직이기
		bUpAngle = false; // 위에 포신 움직이기

		bRotateCamera = false;
		bRevolutionCamera = false;
	}


	if (key == 'm')
	{

		Delete_ALL_Art(AllArt);
		Delete_ALL_Art(AllArtTwo);
		Delete_ALL_Art(AllArtThree);
		Delete_ALL_Art(AllArtFour);

		Create_Face(&LineArt, 0, 0, 0, 100, 100, 100);
		InitBuffers(&LineArt);

		Create_Obj("obj_file\\cube3.obj", &AllArt, 0.f, 5.f, 0.f, 10.f, 5.f, 10.f);
		InitBuffers(&AllArt);

		Create_Obj("obj_file\\cube3.obj", &AllArtTwo, 0.f, 7.5f, 0.f, 5.f, 2.5f, 5.f);
		InitBuffers(&AllArtTwo);
		AllArtTwo.back()->ParentMatrix = &AllArt.back()->transformMatrix;


		// 자식 포신


		// 왼 0
		Create_Obj("obj_file\\cube3.obj", &AllArtThree, 2.f, 5.f, 0.f, 1.f, 5.f, 1.f);
		InitBuffers(&AllArtThree);
		AllArtThree.back()->ParentMatrix = &AllArtTwo.back()->transformMatrix;

		//// 오 1

		Create_Obj("obj_file\\cube3.obj", &AllArtThree, -2.f, 5.f, 0.f, 1.f, 5.f, 1.f);
		InitBuffers(&AllArtThree);
		AllArtThree.back()->ParentMatrix = &AllArtTwo.back()->transformMatrix;

		// 몸통 포신

		////왼 0
		Create_Obj("obj_file\\cube3.obj", &AllArtFour, 5.f, 0.f, 15.f, 1.f, 1.f, 7.f);
		InitBuffers(&AllArtFour);
		AllArtFour.back()->ParentMatrix = &AllArt.back()->transformMatrix;

		//// 오 1
		Create_Obj("obj_file\\cube3.obj", &AllArtFour, -5.f, 0.f, 15.f, 1.f, 1.f, 7.f);
		InitBuffers(&AllArtFour);
		AllArtFour.back()->ParentMatrix = &AllArt.back()->transformMatrix;

		bMoveAll = false; // 아래 몸통 움직이기

		bMoveLeft = false; // 아래 몸통 움직이기

		bParallel = false; // 아래몸통 회전


		bDownShootTrun = false; // 아래포신 회전
		fDownShootTrun = 0.f;


		bDownShoorMergePlay = false; // 실행 위에것 꺼야함
		bDownShootMerge = false; // 아래포신 합치기

		bUpshoot = false; // 위에 포신 움직이기
		bUpAngle = false; // 위에 포신 움직이기


		bRotateCamera = false;
		bRevolutionCamera = false;

		fUpshoot = 0.f;

		DW_Camera.Get_vPos()[0] = 0.f;
		DW_Camera.Get_vPos()[1] = 30.f;
		DW_Camera.Get_vPos()[2] = 50.f;


		DW_Camera.Get_vRevolution()[0] = 0.f;
		DW_Camera.Get_vRevolution()[1] = 0.f;
		DW_Camera.Get_vRevolution()[2] = 0.f;

		DW_Camera.Get_vRotate()[0] = 0.f;
		DW_Camera.Get_vRotate()[1] = 0.f;
		DW_Camera.Get_vRotate()[2] = 0.f;




		DW_Camera.RotateX_Camera(-45.f);
	}


	if (key == 'h')
	{
		DW_Camera.Move_Front_Camera(0.5f);
	}
	if (key == 'H')
	{
		DW_Camera.Move_Back_Camera(0.5f);
	}

	if (key == 'j')
	{
		DW_Camera.Move_Right_Camera(0.5f);
	}
	if (key == 'J')
	{
		DW_Camera.Move_Left_Camera(0.5f);
	}

	if (key == 'k')
	{
		DW_Camera.Move_Up_Camera(0.5f);
	}
	if (key == 'K')
	{
		DW_Camera.Move_Down_Camera(0.5f);
	}

	if (key == 'l')
	{
		bRotateCamera = true;
	}
	if (key == 'L')
	{
		bRotateCamera = false;
	}

	if (key == ';')
	{
		bRevolutionCamera = true;
	}
	if (key == ':')
	{
		bRevolutionCamera = false;
	}


}

bool bPush_L_button{ false };

DWArt* pMouseArt{};

GLvoid MoveMouse(int X, int Y)
{

	DW_Camera.RotateY_Camera((WinsizeX / 2 - X) * 0.5f);
	DW_Camera.RotateX_Camera((WinsizeY / 2 - Y) * 0.5f);


	glutWarpPointer(WinsizeX / 2, WinsizeY / 2);

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
		Create_Obj("obj_file\\cube3.obj", pVec, x, y, z, rx, ry, rx);
		break;
	case DWART_TETRATEDRON:
		Create_Tetrahedron(pVec, x, y, z, rx, ry, rx);
		break;
	}
	InitBuffers(pVec);
}

GLvoid RotateAll()
{
	//if (AllArt.size() == 0)
	//{
	//	return;
	//}

	//if (bLeftTrun)
	//{
	//	AllArt.front()->vRotate[0] += RotateX;
	//	AllArt.front()->vRotate[1] += RotateY;
	//}
	//if (bRightTrun)
	//{
	//	AllArt.back()->vRotate[0] += RotateX;
	//	AllArt.back()->vRotate[1] += RotateY;
	//}

	//for (auto& iter : AllArt)
	//{
	//	iter->vRotate[0] += RotateX * 0.01f;
	//	iter->vRotate[1] += RotateY * 0.01f;
	//}
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

	if (iMove_Sprial < 400)
	{
		float t = (float)iMove_Sprial / 400.f;

		AllArt.front()->vPos[2] = -20.f * (1.f - t) + 20.f * t;
		AllArt.back()->vPos[2] = -20.f * t + 20.f * (1.f - t);
		++iMove_Sprial;
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

	if (iMove_Up_down == 0)
	{
		float t = (float)iMove_Sprial / 200.f;

		AllArt.front()->vPos[2] = -20.f * (1.f - t) + 0.f * t;
		AllArt.front()->vPos[1] = 0.f * (1.f - t) + 10.f * t;

		AllArt.back()->vPos[2] = 0.f * t + 20.f * (1.f - t);
		AllArt.back()->vPos[1] = 0.f * (1.f - t) - 10.f * t;


		++iMove_Sprial;
	}
	else if (iMove_Up_down == 1)
	{
		float t = (float)iMove_Sprial / 200.f;

		AllArt.front()->vPos[2] = 0.f * (1.f - t) + 20.f * t;
		AllArt.front()->vPos[1] = 10.f * (1.f - t) + 0.f * t;



		AllArt.back()->vPos[2] = 0.f * (1.f - t) + -20.f * t;
		AllArt.back()->vPos[1] = -10.f * (1.f - t) - 0.f * t;

		++iMove_Sprial;
	}

	if (iMove_Sprial > 200)
	{
		iMove_Up_down += 1;
		iMove_Sprial = 0;
	}

}

GLvoid Move_Rotate()
{
	if (!bMove_Rotate)
	{
		return;
	}
	else
	{
		RavolutionY = -1.f;
		RotateX = -1.f;
		RotateY = -1.f;

		if (AllArt.back()->vScale[0] < 3.f)
		{
			AllArt.back()->vScale[0] += 0.01f;
			AllArt.back()->vScale[1] += 0.01f;
			AllArt.back()->vScale[2] += 0.01f;
		}

		if (AllArt.front()->vScale[0] > 1.f)
		{
			AllArt.front()->vScale[0] -= 0.01f;
			AllArt.front()->vScale[1] -= 0.01f;
			AllArt.front()->vScale[2] -= 0.01f;
		}

	}

}

GLvoid ChangeMode()
{
	if (LineArt.size() == 4)
	{
		DeleteArt(LineArt, LineArt.back());
	}

	bMove_Sprial = false;
	bOpen_door = false;
	bMove_Change_Revolution = false;
	bMove_Change_Up_Down = false;
	bMove_Rotate = false;

	RavolutionX = 0.f;
	RavolutionY = 0.f;

	RotateX = 0.f;
	RotateY = 0.f;

	iMove_Sprial = 0;
	iMove_Up_down = 0;

	AllArt.front()->vRotate[0] = 0.f;
	AllArt.front()->vRotate[1] = 0.f;
	AllArt.front()->vRotate[2] = 0.f;

	AllArt.back()->vRotate[0] = 0.f;
	AllArt.back()->vRotate[1] = 0.f;
	AllArt.back()->vRotate[2] = 0.f;


	ScaleOne = 0.f;
	ScaleTwo = 0.f;

	AllArt.front()->vRevolution[1] = 0.f;
	AllArt.back()->vRevolution[1] = 0.f;

	AllArt.front()->vPos[0] = 0.f;
	AllArt.front()->vPos[1] = 0.f;
	AllArt.front()->vPos[2] = 20.f;

	AllArt.back()->vPos[0] = 0.f;
	AllArt.back()->vPos[1] = 0.f;
	AllArt.back()->vPos[2] = -20.f;

}

GLvoid Ball_Move()
{

	if (AllArt.size() == 0)
	{
		return;
	}

	if (bMoveAll)
	{
		if (bMoveLeft)
		{
			if (AllArt.back()->vPos[0] <= 50.f)
			{
				AllArt.back()->vPos[0] += 0.25f;
			}
			else
			{
				bMoveLeft = false;
			}

		}
		else
		{
			if (AllArt.back()->vPos[0] >= -50.f)
			{
				AllArt.back()->vPos[0] -= 0.25f;
			}
			else
			{
				bMoveLeft = true;
			}
		}

	}


	if (bParallel)
	{
		AllArt.back()->vRotate[1] += RotateY * 0.5f;
	}
	else
	{

	}

	if (bDownShootTrun)
	{
		AllArtFour[0]->vRevolution[1] += fDownShootTrun * 0.5f;
		AllArtFour[1]->vRevolution[1] -= fDownShootTrun * 0.5f;
	}
	else
	{

	}

	if (bDownShoorMergePlay)
	{
		if (bDownShootMerge)
		{
			if (AllArtFour[0]->vRevolution[1] < 0)
			{
				AllArtFour[0]->vRevolution[1] += 0.5f;
			}
			else if (AllArtFour[0]->vRevolution[1] > 0)
			{
				AllArtFour[0]->vRevolution[1] -= 0.5f;
			}

			if (AllArtFour[1]->vRevolution[1] < 0)
			{
				AllArtFour[1]->vRevolution[1] += 0.5f;
			}
			else if (AllArtFour[1]->vRevolution[1] > 0)
			{
				AllArtFour[1]->vRevolution[1] -= 0.5f;
			}

			if (AllArtFour[0]->vRevolution[0] == 0 && AllArtFour[1]->vRevolution[1] == 0)
			{
				if (AllArtFour[0]->vPos[0] != 0.f)
				{
					AllArtFour[0]->vPos[0] -= 0.5f;
				}
				if (AllArtFour[1]->vPos[0] != 0.f)
				{
					AllArtFour[1]->vPos[0] += 0.5f;
				}
			}
			if (AllArtFour[0]->vPos[0] == 0 && AllArtFour[1]->vPos[0] == 0)
			{
				bDownShoorMergePlay = false;
			}

		}
		else
		{

			if (AllArtFour[0]->vRevolution[1] < 0)
			{
				AllArtFour[0]->vRevolution[1] += 0.5f;
			}
			else if (AllArtFour[0]->vRevolution[1] > 0)
			{
				AllArtFour[0]->vRevolution[1] -= 0.5f;
			}

			if (AllArtFour[1]->vRevolution[1] < 0)
			{
				AllArtFour[1]->vRevolution[1] += 0.5f;
			}
			else if (AllArtFour[1]->vRevolution[1] > 0)
			{
				AllArtFour[1]->vRevolution[1] -= 0.5f;
			}

			if (AllArtFour[0]->vRevolution[0] == 0 && AllArtFour[1]->vRevolution[1] == 0)
			{
				if (AllArtFour[0]->vPos[0] != 5.f)
				{
					AllArtFour[0]->vPos[0] += 0.5f;
				}
				if (AllArtFour[1]->vPos[0] != -5.f)
				{
					AllArtFour[1]->vPos[0] -= 0.5f;
				}
			}

			if (AllArtFour[0]->vPos[0] == 5.f && AllArtFour[1]->vPos[0] == -5.f)
			{
				bDownShoorMergePlay = false;
			}
		}
	}

	if (bUpshoot)
	{
		if (bUpAngle)
		{
			if (fUpshoot < 90.f)
			{
				fUpshoot += 0.5f;
			}
			else
			{
				bUpAngle = false;
			}
		}
		else
		{
			if (fUpshoot > -90.f)
			{
				fUpshoot -= 0.5f;
			}
			else
			{
				bUpAngle = true;
			}
		}

		AllArtThree[0]->vRevolution[0] = fUpshoot;
		AllArtThree[1]->vRevolution[0] = -fUpshoot;
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


void Light_Move(float fTimer)
{

	if (AllArt_Light.size() == 0)
	{
		return;
	}

	if (bLight_Move)
	{
		AllArt_Light.back()->vRevolution[1] += 20.f * fTimer;

	}

	if (bLight_Move_Up)
	{
		AllArt_Light.back()->vRevolution[1] -= 20.f * fTimer;

	}


}