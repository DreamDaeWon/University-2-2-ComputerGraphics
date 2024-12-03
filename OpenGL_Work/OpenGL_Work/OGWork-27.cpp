#include "Define_Work_3D.h"
#include "DW_Camera2.h"

uniform_int_distribution<int> RandomIndex(0, 5);

uniform_real_distribution<float> RandomPos(-10.f, 10.f);

uniform_real_distribution<float> RandomPos_Y(0.f, 10.f);


//uniform_int_distribution<int> RandomIndex(0, 5);


// 카메라 생성
CDW_Camera2 DW_Camera{ glm::vec3(-1.f, 2.f,2.f),glm::vec3(0.f,0.f,-1.f) };



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

	fragmentSource = filetobuf("Specular_fragment_shader.glsl");

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
unsigned int lightPowerLocation{};

float Light_Power{0.5f};


unsigned int CameraPos{};
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

	lightPowerLocation = glGetUniformLocation(shaderProgramID, "lightPower"); //--- lightColor 값 전달: (1.0, 1.0, 1.0) 백색

	CameraPos = glGetUniformLocation(shaderProgramID, "viewPos");
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



//////////////////////////// 여기까지 문제관련


// 24번

bool bLight_Move{};
bool bLight_Move_Up{};
void Light_Move(float fTimer);
void Light_Move_up(float fTimer);

bool bObject_Move{};
bool bObject_Move_Up{};
void Object_Move(float fTimer);


///////////// 27번 //////////////////


bool bSnow{};
void Snow_Move(float fTimer);



void Draw_Pyramid(int n, DWArt* pArt);




////////////////







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
	Light_Move(0.01f);
	Light_Move_up(0.01f);
	Object_Move(0.01f);
	Snow_Move(0.01f);

	for (auto& iter : AllArt)
		Update_light_Buffer(iter);
	glutPostRedisplay();

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
	g_WinID = glutCreateWindow("OGWork-27"); // 윈도우 생성(윈도우 이름)

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
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

	Initialize_Camera();
	make_shaderProgram();

	Create_Obj_Want_Color("obj_file\\cube.obj", glm::vec3(1, 1, 1), &AllArt_Light, 0, 2,2, 1, 1, 1);
	Init_light_Buffers(&AllArt_Light);

	Create_Face_Want_Color(&AllArt,0,0,0,10,10,10,glm::vec3(0.5,0.5,0.5));
	Init_light_Buffers(&AllArt);

	Create_Obj_Want_Color("obj_file\\low_cone.obj", glm::vec3(0.4,0.6,0.9), &AllArtTwo, 0, 0.5, 0, 1, 1, 1);
	Init_light_Buffers(&AllArtTwo);







	Create_Circle_Line(&AllArt,0,0,0,5);
	Init_light_Buffers(&AllArt);
	
	AllArt.back()->vRotate[0] += 25.f;
	
	
	Create_Circle_Line(&AllArt,0,0,0,5);
	Init_light_Buffers(&AllArt);
	AllArt.back()->vRotate[0] += 90.f;
	
	Create_Circle_Line(&AllArt,0,0,0,5);
	Init_light_Buffers(&AllArt);
	AllArt.back()->vRotate[0] -= 25.f;



	glm::vec3 revolutionAxisX(1.0f, 0.0f, 0.0f); // X축 기준

	glm::vec3 Want_Spin = glm::vec3(0.f, 0.f, 1.f);
	glm::mat4 Matrix = glm::mat4(1.f);
	Create_Obj_Want_Color("obj_file\\high_sphere.obj", glm::vec3(1.f, 0.f, 0.f), &AllArtFour, 5, 0, 0, 1, 1, 1);
	Init_light_Buffers(&AllArtFour);
	float revolution_angleX = glm::radians(65.f); // 45도 회전 (라디안 단위)



	Matrix = glm::rotate(Matrix, revolution_angleX, revolutionAxisX);


	Want_Spin = Matrix * glm::vec4(Want_Spin, 1.f);
	AllArtFour.back()->revolutionAxis_Want = Want_Spin;




	Want_Spin = glm::vec3(1.f, 0.f, 0.f);
	Matrix = glm::mat4(1.f);
	Create_Obj_Want_Color("obj_file\\high_sphere.obj", glm::vec3(0, 1, 0), &AllArtFour, 0, 5, 0, 2, 2, 2);
	Init_light_Buffers(&AllArtFour);
	revolution_angleX = glm::radians(90.f); // 45도 회전 (라디안 단위)

	Matrix = glm::rotate(Matrix, revolution_angleX, revolutionAxisX);
	Matrix = glm::rotate(Matrix, revolution_angleX, glm::vec3(0.f,0.f,1.f));

	Want_Spin = Matrix * glm::vec4(Want_Spin, 1.f);
	AllArtFour.back()->revolutionAxis_Want = Want_Spin;




	Want_Spin = glm::vec3(0.f, 0.f, 1.f);
	Matrix = glm::mat4(1.f);
	Create_Obj_Want_Color("obj_file\\high_sphere.obj", glm::vec3(0, 0, 1), &AllArtFour, -5, 0, 0, 3, 3, 3);
	Init_light_Buffers(&AllArtFour);
	revolution_angleX = glm::radians(-65.f); // 45도 회전 (라디안 단위)

	Matrix = glm::rotate(Matrix, revolution_angleX, revolutionAxisX);
	Want_Spin = Matrix * glm::vec4(Want_Spin, 1.f);
	AllArtFour.back()->revolutionAxis_Want = Want_Spin;





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

			glUniform3f(CameraPos, DW_Camera.Get_vPos().x, DW_Camera.Get_vPos().y, DW_Camera.Get_vPos().z);
			//glUniform3f(objColorLocation, 1.0, 0.5, 0.3);

			glUniform1f(lightPowerLocation, Light_Power);


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

	if (key == 'w')
	{
		DW_Camera.Move_Front_Camera(0.1f);
	}

	if (key == 'a')
	{
		DW_Camera.Move_Left_Camera(0.1f);
	}

	if (key == 's')
	{
		DW_Camera.Move_Back_Camera(0.1f);
	}

	if (key == 'd')
	{
		DW_Camera.Move_Right_Camera(0.1f);
	}

	if (key == 'c')
	{
		DW_Camera.Move_Down_Camera(0.1f);
	}

	if (key == 'v')
	{
		DW_Camera.Move_Up_Camera(0.1f);
	}


	if (key == 'b')
	{
		bLight_Move = true;
	}

	if (key == 'B')
	{
		bLight_Move = false;
	}

	if (key == 'n')
	{
		AllArt_Light.back()->vPos[2] -= 0.1f;
	}

	if (key == 'f')
	{
		AllArt_Light.back()->vPos[2] += 0.1f;
	}


	if (key == 't')
	{
		bSnow = true;
		if (AllArtThree.size() == 0)
		{
			for (int i = 0; i < 300; ++i)
			{
				Create_Obj_Want_Color("obj_file\\sphere.obj",glm::vec3(1.f,1.f,1.f), &AllArtThree , RandomPos(mt), RandomPos_Y(mt), RandomPos(mt),1.f,1.f,1.f);
				Init_light_Buffers(&AllArtThree);
			}
		}
	}


	if (key == 'T')
	{
		bSnow = false;
	}

	if (key == '+')
	{
		if (Light_Power <= 1.0)
		{
			Light_Power += 0.1f;
		}
	}

	if (key == '-')
	{
		if (Light_Power >= 0)
		{
			Light_Power -= 0.1f;
		}
	}

	if (key == '1')
	{
		Delete_ALL_Art(AllArtTwo);
		Create_Obj_Want_Color("obj_file\\low_cone.obj", glm::vec3(0.4, 0.6, 0.9), &AllArtTwo, 0, 0.5, 0, 1, 1, 1);
		Init_light_Buffers(&AllArtTwo);

		Draw_Pyramid(1, AllArtTwo.back());
	}

	if (key == '2')
	{
		Delete_ALL_Art(AllArtTwo);
		Create_Obj_Want_Color("obj_file\\low_cone.obj", glm::vec3(0.4, 0.6, 0.9), &AllArtTwo, 0, 0.5, 0, 1, 1, 1);
		Init_light_Buffers(&AllArtTwo);

		Draw_Pyramid(2, AllArtTwo.back());
	}

	if (key == '3')
	{
		Delete_ALL_Art(AllArtTwo);
		Create_Obj_Want_Color("obj_file\\low_cone.obj", glm::vec3(0.4, 0.6, 0.9), &AllArtTwo, 0, 0.5, 0, 1, 1, 1);
		Init_light_Buffers(&AllArtTwo);

		Draw_Pyramid(3, AllArtTwo.back());
	}

	if (key == '4')
	{
		Delete_ALL_Art(AllArtTwo);
		Create_Obj_Want_Color("obj_file\\low_cone.obj", glm::vec3(0.4, 0.6, 0.9), &AllArtTwo, 0, 0.5, 0, 1, 1, 1);
		Init_light_Buffers(&AllArtTwo);

		Draw_Pyramid(4, AllArtTwo.back());
	}

	if (key == '5')
	{
		Delete_ALL_Art(AllArtTwo);
		Create_Obj_Want_Color("obj_file\\low_cone.obj", glm::vec3(0.4, 0.6, 0.9), &AllArtTwo, 0, 0.5, 0, 1, 1, 1);
		Init_light_Buffers(&AllArtTwo);

		Draw_Pyramid(5, AllArtTwo.back());
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

void Light_Move(float fTimer)
{

	if (AllArt_Light.size() == 0)
	{
		return;
	}

	if (bLight_Move)
	{
		AllArt_Light.back()->vRevolution[1] += 20.f * fTimer;
		//AllArt_Light.back()->vRotate[1] += 20.f * fTimer;
	}


}

void Light_Move_up(float fTimer)
{


	if (AllArt_Light.size() == 0)
	{
		return;
	}

	if (bLight_Move_Up)
	{
		AllArt_Light.back()->vRevolution[0] += 20.f * fTimer;
	}


}

void Object_Move(float fTimer)
{
	if (AllArt.size() == 0)
	{
		return;
	}
	if (AllArtFour.size() == 0)
	{
		return;
	}
	for (int i = 0; i < AllArtFour.size(); ++i)
	{
		AllArtFour[i]->vRevolution[3] += 5.f * fTimer;
	}
}

void Snow_Move(float fTimer)
{
	if (bSnow)
	{
		for (int i = 0; i < AllArtThree.size(); ++i)
		{
			AllArtThree[i]->vPos[1] -= fTimer * 2.5f;

			if (AllArtThree[i]->vPos[1] <= 0.f)
			{
				AllArtThree[i]->vPos[1] = 10.f;
			}
		}
	}
}

void Draw_Pyramid(int n, DWArt* pArt)
{

	if (n == 1)
	{
		//Delete_ALL_Art(AllArtTwo);
		//Create_Obj_Want_Color("obj_file\\low_cone.obj", glm::vec3(0.4, 0.6, 0.9), &AllArtTwo, 0, 0.5, 0, 1, 1, 1);
		//Init_light_Buffers(&AllArtTwo);
		return;
	}

	float fSize = pArt->vScale[0] / 2;
	float fPos[3] = { pArt->vPos[0],pArt->vPos[1],pArt->vPos[2] };


	// 위
	Create_Obj_Want_Color("obj_file\\low_cone.obj", glm::vec3(0.4, 0.6, 0.9), &AllArtTwo, fPos[0], fPos[1] + fSize * 1.f, fPos[2], fSize * 2.f, fSize * 2.f, fSize * 2.f);
	Init_light_Buffers(&AllArtTwo);
	Draw_Pyramid(n - 1 , AllArtTwo.back());

	// 왼쪽 앞
	Create_Obj_Want_Color("obj_file\\low_cone.obj", glm::vec3(0.4, 0.6, 0.9), &AllArtTwo, fPos[0] -fSize * 0.7f, fPos[1] - fSize * 1.f, fPos[2] -fSize * 0.7f, fSize * 2.f, fSize * 2.f, fSize * 2.f);
	Init_light_Buffers(&AllArtTwo);
	Draw_Pyramid(n - 1, AllArtTwo.back());

	// 오른쪽 앞 
	Create_Obj_Want_Color("obj_file\\low_cone.obj", glm::vec3(0.4, 0.6, 0.9), &AllArtTwo, fPos[0] + fSize * 0.7f, fPos[1] - fSize * 1.f, fPos[2] -fSize * 0.7f, fSize * 2.f, fSize * 2.f, fSize * 2.f);
	Init_light_Buffers(&AllArtTwo);
	Draw_Pyramid(n - 1, AllArtTwo.back());

	// 왼쪽 뒤
	Create_Obj_Want_Color("obj_file\\low_cone.obj", glm::vec3(0.4, 0.6, 0.9), &AllArtTwo, fPos[0] -fSize * 0.7f, fPos[1] - fSize * 1.f, fPos[2] + fSize * 0.7f, fSize * 2.f, fSize * 2.f, fSize * 2.f);
	Init_light_Buffers(&AllArtTwo);
	Draw_Pyramid(n - 1, AllArtTwo.back());

	// 오른쪽 뒤 
	Create_Obj_Want_Color("obj_file\\low_cone.obj", glm::vec3(0.4, 0.6, 0.9), &AllArtTwo, fPos[0] + fSize * 0.7f, fPos[1] - fSize * 1.f, fPos[2] + fSize * 0.7f, fSize * 2.f, fSize * 2.f, fSize * 2.f);
	Init_light_Buffers(&AllArtTwo);
	Draw_Pyramid(n - 1, AllArtTwo.back());


	DeleteArt(AllArtTwo,pArt);


}
