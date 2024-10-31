#include "Define_Work_3D.h"
#include "DW_Camera2.h"

uniform_int_distribution<int> RandomIndex(0, 5);

uniform_int_distribution<int> RandomIndexTri(0, 5);


// 카메라 생성
CDW_Camera2 DW_Camera{ glm::vec3(20.f,20.f,15.f),glm::vec3(0.f,0.f,-1.f) };



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
bool bMove_Change{};
bool bMove_Change_Revolution{};
bool bMove_Change_Up_Down{};
bool bMove_Rotate{};


bool bOneChange{};
bool bTwoChange{};


GLint iMove_Sprial{}; // 얼마나 움직였는지?
GLvoid MoveSpiral();


GLvoid MoveChange();

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

GLvoid Change_Move();

GLvoid Change_Draw_Timing_Cube();


bool bMoveAll{};

bool bParallel{};



GLvoid Change_Square_Pyramid();


GLfloat PyramidRotate[4]{};


//////////////////////////// 여기까지 문제관련



vector<DWArt*> AllArt{};

vector<DWArt*> LineArt{};

vector<DWArt*> AllArtTwo{};
vector<DWArt*> AllArtThree{};

vector<DWArt*> AllArtFour{};
vector<DWArt*> RightBottom{};

vector<DWArt*>* AllVec[6]{ &LineArt, &AllArt , &AllArtTwo ,&AllArtThree ,&AllArtFour , &RightBottom };

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
	Change_Move();
	Change_Square_Pyramid();


	RotateAll();
	RavolutionAll();
	MoveSpiral();
	MoveChange();
	Move_Change_Revolution();
	Move_Change_Up_Down();
	Move_Rotate();
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

	for (int i = 0; i < RightBottom.size(); ++i)
	{
		UpdateBuffer(RightBottom[i]);
	}

}

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기

	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(WinsizeX, WinsizeY); // 윈도우의 크기 지정
	g_WinID = glutCreateWindow("OGWork-18"); // 윈도우 생성(윈도우 이름)

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
		//DW_Camera.RotateY_Camera(90.f);
		//DW_Camera.RotateX_Camera(-45.f);
		glutWarpPointer(WinsizeX / 2, WinsizeY / 2);

	}
	else
		std::cout << "GLEW Initialized\n";


	make_shaderProgram();

	Create_Line_Pos(&LineArt, 0.f, 25.f, 0.f, 0.f, -25.f, 0.f, glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 0.f, 0.f));
	InitBuffers(&LineArt);
	Create_Line_Pos(&LineArt, 25.f, 0.f, 0.f, -25.f, 0.f, 0.f, glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 1.f, 0.f));
	InitBuffers(&LineArt);
	Create_Line_Pos(&LineArt, 0.f, 0.f, 25.f, 0.f, 0.f, -25.f, glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 1.f));
	InitBuffers(&LineArt);



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
				gluCylinder(iter->Model, iter->Sylinder_rx_Top, iter->Sylinder_rx_Bottom, iter->Sylinder_ry, iter->Sylinder_Slices, iter->Sylinder_Stacks);
				glBindVertexArray(0);

				break;

			}

			GLenum err;
			while ((err = glGetError()) != GL_NO_ERROR) {
				std::cerr << "OpenGL error: " << err << std::endl;
			}


		}
	}

	//checkFrameBuffer();
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


		// 중심 구
		Create_Sphere_Model(&AllArt, 0.f, 0.f, 0.f, 10.f, 20, 10);
		InitBuffers(&AllArt);


		// 부모 구
		Create_Sphere_Model(&AllArtTwo, -20.f, 20.f, 0.f, 5.f, 20, 10);
		InitBuffers(&AllArtTwo);

		//AllArtTwo.back()->ParentMatrix = &AllArt.back()->transformMatrix;


		Create_Sphere_Model(&AllArtTwo, 20.f * sqrtf(2.f), 0.f, 0.f, 5.f, 20, 10);
		InitBuffers(&AllArtTwo);

		//AllArtTwo.back()->ParentMatrix = &AllArt.back()->transformMatrix;

		Create_Sphere_Model(&AllArtTwo, 20.f, 20.f, 10.f, 5.f, 20, 10);
		InitBuffers(&AllArtTwo);

		//AllArtTwo.back()->ParentMatrix = &AllArt.back()->transformMatrix;


		// 자식 구

		Create_Sphere_Model(&AllArtThree, 10.f, 0.f, 0.f, 2.f, 20, 10);
		InitBuffers(&AllArtThree);
		//AllArtThree.back()->ParentMatrix = &AllArtTwo[0]->transformMatrix;


		Create_Sphere_Model(&AllArtThree, 10.f * sqrtf(2.f), 0.f, 0.f, 2.f, 20, 10);
		InitBuffers(&AllArtThree);
		//AllArtThree.back()->ParentMatrix = &AllArtTwo[1]->transformMatrix;

		Create_Sphere_Model(&AllArtThree, 10.f, 0.f, 0.f, 2.f, 20, 10);
		InitBuffers(&AllArtThree);
		//AllArtThree.back()->ParentMatrix = &AllArtTwo[2]->transformMatrix;


		// 공전궤도

		// 자식꺼

		Create_Circle_Line(&AllArtFour, 0.f,0.f,0.f,10.f * sqrtf(2.f));
		InitBuffers(&AllArtFour);

		Create_Circle_Line(&AllArtFour, 0.f, 0.f, 0.f, 10.f * sqrtf(2.f));
		InitBuffers(&AllArtFour);

		Create_Circle_Line(&AllArtFour, 0.f, 0.f, 0.f, 10.f * sqrtf(2.f));
		InitBuffers(&AllArtFour);

		// 부모꺼
		Create_Circle_Line(&AllArtFour, 0.f, 0.f, 0.f, 20.f * sqrtf(2.f));
		InitBuffers(&AllArtFour);

		Create_Circle_Line(&AllArtFour, 0.f, 0.f, 0.f, 20.f * sqrtf(2.f));
		InitBuffers(&AllArtFour);

		Create_Circle_Line(&AllArtFour, 0.f, 0.f, 0.f, 20.f * sqrtf(2.f));
		InitBuffers(&AllArtFour);

	}


	if (key == 'i')
	{
		for (int i = 1; i < 6; ++i)
		{
			vector<DWArt*>* pVec = AllVec[i];

			for (auto& iter : *pVec)
			{
				iter->vWorldPos[1] += 0.5f;
			}

		}
	}

	if (key == 'j')
	{
		for (int i = 1; i < 6; ++i)
		{
			vector<DWArt*>* pVec = AllVec[i];

			for (auto& iter : *pVec)
			{
				iter->vWorldPos[0] -= 0.5f;
			}

		}
	}

	if (key == 'k')
	{
		for (int i = 1; i < 6; ++i)
		{
			vector<DWArt*>* pVec = AllVec[i];

			for (auto& iter : *pVec)
			{
				iter->vWorldPos[1] -= 0.5f;
			}

		}
	}

	if (key == 'l')
	{
		for (int i = 1; i < 6; ++i)
		{
			vector<DWArt*>* pVec = AllVec[i];

			for (auto& iter : *pVec)
			{
				iter->vWorldPos[0] += 0.5f;
			}

		}
	}

	if (key == '+')
	{
		for (int i = 1; i < 6; ++i)
		{
			vector<DWArt*>* pVec = AllVec[i];

			for (auto& iter : *pVec)
			{
				iter->vWorldPos[2] += 0.5f;
			}

		}
	}

	if (key == '-')
	{
		for (int i = 1; i < 6; ++i)
		{
			vector<DWArt*>* pVec = AllVec[i];

			for (auto& iter : *pVec)
			{
				iter->vWorldPos[2] -= 0.5f;
			}

		}
	}


	if (key == 'r')
	{
		bMoveAll = true;

	}

	if (key == 'R')
	{
		bMoveAll = false;

	}





	if (key == 'z')
	{
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	}
	if (key == 'Z')
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}


	if (key == 'x')
	{

		RavolutionY = 1.f;

	}
	if (key == 'X')
	{
		RavolutionY = -1.f;
	}

	if (key == 'c')
	{

		RavolutionZ = 1.f;

	}
	if (key == 'C')
	{
		RavolutionZ = -1.f;
	}


	if (key == 'v')
	{
		bParallel = true;
	}

	if (key == 'V')
	{
		bParallel = false;
	}



	

}

bool bPush_L_button{ false };

DWArt* pMouseArt{};
GLvoid MoveMouse(int X, int Y)
{

	DW_Camera.RotateY_Camera(-(WinsizeX / 2 - X));
	DW_Camera.RotateX_Camera(-(WinsizeY / 2 - Y));


	glutWarpPointer(WinsizeX / 2, WinsizeY / 2);

	//glutPostRedisplay();
}

GLvoid MoveMouse_Tick(int X, int Y)
{

	DW_Camera.RotateX_Camera((WinsizeY / 2 - Y) * 0.5f);

	DW_Camera.RotateY_Camera((WinsizeX / 2 - X) * 0.5f);


	glutWarpPointer(WinsizeX / 2, WinsizeY / 2);

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

	for (auto& iter : AllArt)
	{
		iter->vRotate[0] += RotateX * 0.01f;
		iter->vRotate[1] += RotateY * 0.01f;
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

GLvoid MoveChange()
{
	if (!bMove_Change)
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
	bMove_Change = false;
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

GLvoid Change_Move()
{
	if (bMoveAll)
	{
		AllArtFour[3]->vRotate[2] = -45;
		AllArtFour[4]->vRotate[2] = 0;
		AllArtFour[5]->vRotate[2] = 45;



		AllArtTwo[0]->revolutionAxis_Want = glm::vec3(1.f, 1.f, 0.f);
		AllArtTwo[0]->vRevolution[3] += 0.1f;


		AllArtTwo[1]->revolutionAxis_Want = glm::vec3(0.f, 1.f, 0.f);
		AllArtTwo[1]->vRevolution[3] += 0.1f; 

		AllArtTwo[2]->revolutionAxis_Want = glm::vec3(-1.f, 1.f, 0.f);
		AllArtTwo[2]->vRevolution[3] += 0.1f;



		if(bParallel)
		{
			AllArtFour[0]->vRotate[2] = 0.f;
			AllArtFour[1]->vRotate[2] = 0.f;
			AllArtFour[2]->vRotate[2] = 0.f;

			for (int i = 0; i < 3; ++i)
			{
				AllArtFour[i]->vRotate[2] = 0;

				AllArtThree[i]->vPos[0] = 10.f * sqrtf(2.f);
				AllArtThree[i]->vPos[1] = 0.f;
				AllArtThree[i]->vPos[2] = 0.f;


				AllArtThree[i]->vRevolution[1] += 0.1f;
				AllArtThree[i]->vRevolution[1] += 0.1f;
				AllArtThree[i]->vRevolution[1] += 0.1f;

				AllArtThree[i]->vRevolution[3] = 0.f;
				AllArtThree[i]->vRevolution[3] = 0.f;
				AllArtThree[i]->vRevolution[3] = 0.f;

			}
		}
		else
		{

			AllArtFour[0]->vRotate[2] = -45;
			AllArtFour[1]->vRotate[2] = 0;
			AllArtFour[2]->vRotate[2] = 45;


			AllArtThree[0]->vRevolution[1] = 0.f;
			AllArtThree[1]->vRevolution[1] = 0.f;
			AllArtThree[2]->vRevolution[1] = 0.f;


			//for (int i = 0; i < 3; ++i)
			{

				AllArtThree[0]->vPos[0] = -10.f;
				AllArtThree[0]->vPos[1] = 10.f;
				AllArtThree[0]->vPos[2] = 0.f;

				AllArtThree[0]->revolutionAxis_Want = glm::vec3(1.f, 1.f, 0.f);
				AllArtThree[0]->vRevolution[3] += 0.1f;


				AllArtThree[1]->vPos[0] = 10.f;
				AllArtThree[1]->vPos[1] = 0.f;
				AllArtThree[1]->vPos[2] = 0.f;

				AllArtThree[1]->revolutionAxis_Want = glm::vec3(0.f, 1.f, 0.f);
				AllArtThree[1]->vRevolution[3] += 0.1f;


				AllArtThree[2]->vPos[0] = 10.f;
				AllArtThree[2]->vPos[1] = 10.f;
				AllArtThree[2]->vPos[2] = 0.f;

				AllArtThree[2]->revolutionAxis_Want = glm::vec3(-1.f, 1.f, 0.f);
				AllArtThree[2]->vRevolution[3] += 0.1f;

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
		fAngle += 0.01f;
	
		// 이동
		for (int i = 1; i < 3; ++i)
		{
			vector<DWArt*>* pVec = AllVec[i];

			for (auto& iter : *pVec)
			{
				iter->transformMatrix[3][0] = iter->transformMatrix[3][0] + iter->vWorldPos[0];
				iter->transformMatrix[3][1] = iter->transformMatrix[3][1] + iter->vWorldPos[1];
				iter->transformMatrix[3][2] = iter->transformMatrix[3][2] + iter->vWorldPos[2];
			}
		}



		for (int i = 0; i < 3; ++i)
		{
			AllArtThree[i]->transformMatrix[3][0] = AllArtThree[i]->transformMatrix[3][0] + AllArtTwo[i]->transformMatrix[3][0] - AllArtThree[i]->vWorldPos[0] * 3.f;
			AllArtThree[i]->transformMatrix[3][1] = AllArtThree[i]->transformMatrix[3][1] + AllArtTwo[i]->transformMatrix[3][1] - AllArtThree[i]->vWorldPos[1] * 3.f;
			AllArtThree[i]->transformMatrix[3][2] = AllArtThree[i]->transformMatrix[3][2] + AllArtTwo[i]->transformMatrix[3][2] - AllArtThree[i]->vWorldPos[2] * 3.f;
		}



		for (int i = 0; i < 3; ++i)
		{
			AllArtFour[i]->transformMatrix[3][0] = AllArtFour[i]->transformMatrix[3][0] + AllArtTwo[i]->transformMatrix[3][0] - AllArtFour[i]->vWorldPos[0] * 6.f;
			AllArtFour[i]->transformMatrix[3][1] = AllArtFour[i]->transformMatrix[3][1] + AllArtTwo[i]->transformMatrix[3][1] - AllArtFour[i]->vWorldPos[1] * 6.f;
			AllArtFour[i]->transformMatrix[3][2] = AllArtFour[i]->transformMatrix[3][2] + AllArtTwo[i]->transformMatrix[3][2] - AllArtFour[i]->vWorldPos[2] * 6.f;
		}

	/*	for (int i = 3; i < 6; ++i)
		{
			AllArtFour[i]->transformMatrix[3][0] = AllArtFour[i]->transformMatrix[3][0] + AllArt[0]->transformMatrix[3][0] - AllArtFour[i]->vWorldPos[0] * 12.f;
			AllArtFour[i]->transformMatrix[3][1] = AllArtFour[i]->transformMatrix[3][1] + AllArt[0]->transformMatrix[3][1] - AllArtFour[i]->vWorldPos[1] * 6.f;
			AllArtFour[i]->transformMatrix[3][2] = AllArtFour[i]->transformMatrix[3][2] + AllArt[0]->transformMatrix[3][2] - AllArtFour[i]->vWorldPos[2] * 12.f;
		}*/

		AllArtFour[3]->transformMatrix[3][0] = AllArtFour[3]->transformMatrix[3][0] + AllArt[0]->transformMatrix[3][0] - AllArtFour[3]->vWorldPos[0] *10.f;
		AllArtFour[3]->transformMatrix[3][1] = AllArtFour[3]->transformMatrix[3][1] + AllArt[0]->transformMatrix[3][1] - AllArtFour[3]->vWorldPos[1] *10.f;
		AllArtFour[3]->transformMatrix[3][2] = AllArtFour[3]->transformMatrix[3][2] + AllArt[0]->transformMatrix[3][2] - AllArtFour[3]->vWorldPos[2] *10.f;

		AllArtFour[4]->transformMatrix[3][0] = AllArtFour[4]->transformMatrix[3][0] + AllArt[0]->transformMatrix[3][0] - AllArtFour[4]->vWorldPos[0] * 11.f;
		AllArtFour[4]->transformMatrix[3][1] = AllArtFour[4]->transformMatrix[3][1] + AllArt[0]->transformMatrix[3][1] - AllArtFour[4]->vWorldPos[1] * 11.f;
		AllArtFour[4]->transformMatrix[3][2] = AllArtFour[4]->transformMatrix[3][2] + AllArt[0]->transformMatrix[3][2] - AllArtFour[4]->vWorldPos[2] * 11.f;

		AllArtFour[5]->transformMatrix[3][0] = AllArtFour[5]->transformMatrix[3][0] + AllArt[0]->transformMatrix[3][0] - AllArtFour[5]->vWorldPos[0] * 12.f;
		AllArtFour[5]->transformMatrix[3][1] = AllArtFour[5]->transformMatrix[3][1] + AllArt[0]->transformMatrix[3][1] - AllArtFour[5]->vWorldPos[1] * 12.f;
		AllArtFour[5]->transformMatrix[3][2] = AllArtFour[5]->transformMatrix[3][2] + AllArt[0]->transformMatrix[3][2] - AllArtFour[5]->vWorldPos[2] * 12.f;



	}
}

GLvoid Change_Square_Pyramid()
{

}
