#include "Define_Work_3D.h"
#include "DW_Camera2.h"

uniform_int_distribution<int> RandomIndex(1, 3);

uniform_int_distribution<int> RandomIndexTri(0, 5);



uniform_int_distribution<int> RandomOnBoxPos(-45, 45);

uniform_real_distribution<float> RandomMoveVec(-1.f, 1.f);


// ī�޶� ����
CDW_Camera2 DW_Camera{ glm::vec3(0.f, 0.f,150.f),glm::vec3(0.f,0.f,-1.f) };



// ���̴� ���� ����
GLuint shaderProgramID{}; // ���̴� ���α׷� �̸�

GLuint vertexShader{}; // ���ؽ� ���̴� ��ü
GLuint fragmentShader{}; // �����׸�Ʈ ������ ��ü


void make_vectexShaders() // ���ؽ� ������ ��ü �����
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
		std::cerr << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}

void make_fragmenetShaders() // ���ؽ� ������ ��ü �����
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
		std::cerr << "ERROR: fragment shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}

int Shader_Matrix{};
int Shader_ViewTransform{};
int Shader_ProjectionTransform{};

void Initialize_Camera()
{
	DW_Camera.RotateX_Camera(0.f);
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


// �׽�Ʈ �ڵ�
void checkFrameBuffer();



// 7 ��

GLvoid Create_DWArt(vector<DWArt*>* pVec, ArtType eDraw, GLfloat x, GLfloat y, GLfloat z, GLfloat rx, GLfloat ry, GLfloat rz);

GLvoid Move(eMoveType Dir);

GLvoid Delete_ALL();

GLvoid UpdateBuffers();

//void InitBuffers();


// 8��

// 13 ��

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


// 14��
bool bCallMode{};
bool bLeftTrun{ false };
bool bRightTrun{ false };
float RotateX{};
float RotateY{};

GLvoid RotateAll();

bool RotateCamera = false;


// 15��
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


GLint iMove_Sprial{}; // �󸶳� ����������?
GLvoid MoveSpiral();


GLvoid MoveDoor();

GLvoid Move_Change_Revolution();



GLint iMove_Up_down{}; // ������ ������?


GLvoid Move_Change_Up_Down();


GLfloat ScaleOne{};
GLfloat ScaleTwo{};

GLvoid Move_Rotate();


GLvoid ChangeMode();

// 18��

bool bOrtho{ false };



bool bRotate_Up = false;

bool bFront_open = false;


bool bUp_LR = false;

bool bBack_Scale = false;


GLfloat fBack_Scale{ 1.f };

GLfloat fUp{};

GLfloat fFront_Angle = 0.f;

GLvoid Ball_Move();

GLvoid Box_Move();

GLvoid Change_Draw_Timing_Cube();


bool bBall_Move{}; // ���� �����̱�

bool bMoveDir[4]{}; // �����̴� ���� 0. ��, 1. ��, 2. ��, 3. ��

float fSpeed = 5.0f;

bool bJump = false;

bool bOnBoxJump = false;

float fJumpTime = 0.f;

float fGravityTime = 0.f;





bool bDownShootTrun{}; // �Ʒ����� ȸ��

float fDownShootTrun{}; // �Ʒ����� ȸ�� ������


bool bDownShoorMergePlay{}; // ���� ������ ������
bool bDownShootMerge{}; // �Ʒ����� ��ġ��

bool bUpshoot{}; // ���� ���� �����̱�
bool bUpAngle{}; // ���� ���� �����̱�
float fUpshoot{}; // ���� ���� �����̱�



GLvoid Change_Square_Pyramid();


GLfloat PyramidRotate[4]{};



// 19�� ī�޶�


GLvoid Change_Camera_Move();


bool bRotateCamera{};
bool bRevolutionCamera{};


// 22 ��

float fAngleMouse = 0.f;


//////////////////////////// ������� ��������



vector<DWArt*> AllArt{};

vector<DWArt*> LineArt{};

vector<DWArt*> AllArtTwo{};
vector<DWArt*> AllArtThree{};

vector<DWArt*> AllArtFour{};
vector<DWArt*> RightBottom{};

vector<DWArt*>* AllVec[6]{ &LineArt, &AllArt , &AllArtTwo ,&AllArtThree ,&AllArtFour , &RightBottom };

float fSize[4][4]{};

unsigned int g_WinID{};// ������ ID

bool bTimer = false; // Ÿ�̸� ���� ���� ����

GLuint iPrintType = GL_TRIANGLES;



// 4�� Ÿ�̸� ���ú���
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

	Ball_Move();
	Box_Move();
	//Change_Square_Pyramid();

	MoveDoor();
	RotateAll();
	RavolutionAll();
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

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�

	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(WinsizeX, WinsizeY); // �������� ũ�� ����
	g_WinID = glutCreateWindow("OGWork-22"); // ������ ����(������ �̸�)

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
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

	//Create_Line_Pos(&LineArt, 0.f, 25.f, 0.f, 0.f, -25.f, 0.f, glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 0.f, 0.f));
	//InitBuffers(&LineArt);
	//Create_Line_Pos(&LineArt, 25.f, 0.f, 0.f, -25.f, 0.f, 0.f, glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 1.f, 0.f));
	//InitBuffers(&LineArt);
	//Create_Line_Pos(&LineArt, 0.f, 0.f, 25.f, 0.f, 0.f, -25.f, glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 1.f));
	//InitBuffers(&LineArt);



	// ����
	Create_Face(&AllArt, 0.f, -50.f, 0.f, 50, 0.f, 50.f); // �Ʒ�
	AllArt.back()->vRotate[0] = 0.f;
	InitBuffers(&AllArt);

	Create_Face(&AllArt, 0.f, 50.f, 0.f, 50, 0.f, 50.f); // ��
	AllArt.back()->vRotate[0] = 180.f;
	InitBuffers(&AllArt);

	Create_Face(&AllArt, -50.f, 0.f, 0.f, 50, 0.f, 50.f); // ����
	AllArt.back()->vRotate[2] = -90.f;
	InitBuffers(&AllArt);

	Create_Face(&AllArt, 50.f, 0.f, 0.f, 50, 0.f, 50.f); // ������
	AllArt.back()->vRotate[2] = 90.f;
	InitBuffers(&AllArt);

	Create_Face(&AllArt, 0.f, 0.f, -50.f, 50, 0.f, 50.f); // ��
	AllArt.back()->vRotate[0] = 90.f;
	InitBuffers(&AllArt);



	// �ڽ�

	Create_Cube(&AllArtThree,0.f,0.f,10.f,20.f,20.f,5.f);
	InitBuffers(&AllArtThree);

	Create_Cube(&AllArtThree, 0.f, 0.f, 25.f, 10.f, 10.f, 5.f);
	InitBuffers(&AllArtThree);

	Create_Cube(&AllArtThree, 0.f, 0.f, 40.f, 5.f, 5.f, 5.f);
	InitBuffers(&AllArtThree);





	glutKeyboardFunc(KeyInput);
	glutSpecialFunc(SpecialKeyInput);
	glutMouseFunc(MouseInput);
	glutMotionFunc(MoveMouse);
	glutPassiveMotionFunc(MoveMouse_Tick);
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����

	glutTimerFunc(16, Timer, 1);


	glutMainLoop(); // �̺�Ʈ ó�� ����
}


GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.f); // �������� ��blue�� �� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�
	int ColorLocation = glGetUniformLocation(shaderProgramID, "vColor");
	glUseProgram(shaderProgramID);


	for (int i = 0; i < 6; ++i)
	{
		vector<DWArt*>* pVec = AllVec[i];

		for (auto& iter : *pVec)
		{
			MakeWorldMartrix(iter);

			Change_Draw_Timing_Cube();

			// ����
			glUniformMatrix4fv(Shader_Matrix, 1, GL_FALSE, glm::value_ptr(iter->transformMatrix));

			// ��
			DW_Camera.Make_view_Matrix();
			glUniformMatrix4fv(Shader_ViewTransform, 1, GL_FALSE, glm::value_ptr(DW_Camera.Get_view_Matrix()));
			glm::mat4 projection;
			// ����
			if (bOrtho)
			{
				projection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 200.f);
			}
			else
			{
				projection = glm::perspective(glm::radians(90.f), (float)WinsizeX / WinsizeY, 0.1f, 400.f);
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

	// checkFrameBuffer();
	glViewport(0, 0, WinsizeX, WinsizeY);
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
	glutPostRedisplay();
}
GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
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
		DW_Camera.Move_Front_Camera(2.f);
	}

	if (key == 'Z')
	{
		DW_Camera.Move_Back_Camera(2.f);
	}

	if (key == 'y')
	{
		for (int i = 1; i < 6; ++i)
		{
			for (auto& iter : *AllVec[i])
			{
				iter->vRevolution[1] += 1.f;

			}
		}
	}

	if (key == 'Y')
	{
		for (int i = 1; i < 6; ++i)
		{
			for (auto& iter : *AllVec[i])
			{
				iter->vRevolution[1] -= 1.f;
				
			}
		}
	}

	if (key == 'b')
	{
		Create_Sphere_Model(&AllArtTwo,0.f,0.f,25.f,5.f,10,10);
		glm::vec3 Invec(RandomMoveVec(mt), RandomMoveVec(mt), 0.f);

		Invec = normalize(Invec);

		AllArtTwo.back()->vMoveVec[0] = Invec.x;
		AllArtTwo.back()->vMoveVec[1] = Invec.y;
		AllArtTwo.back()->vMoveVec[2] = Invec.z;

		AllArtTwo.back()->fSpeed = RandomIndex(mt);




		InitBuffers(&AllArtTwo);
	}

	



	if (key == 'o')
	{
		// glEnable(GL_CULL_FACE);

		bOpen_door = true;

	}

	if (key == 'O')
	{
		// glDisable(GL_CULL_FACE);
		bOpen_door = false;
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

	static float Before_MouseX = 0.f;

	
	// ���϶� ���������� ����.
	fAngleMouse = (Before_MouseX - X) * 0.2f;

	Before_MouseX = X;

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
	static float fAllAngle = 0.f;

	fAllAngle += fAngleMouse;

	for (int i = 1; i < 6; ++i)
	{
		for (auto& iter : *AllVec[i])
		{
			if (bLeftTrun)
			{
				iter->vRevolution[1] += 0.001f;
			}
			else
			{
				iter->vRevolution[1] += 0.001f;
			}
		}
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

	// ������ ���� �����͸� Ȯ��
	bool hasData = false;
	for (size_t i = 0; i < pixels.size(); ++i) {
		if (pixels[i] != 0) {
			hasData = true;
			break;
		}
	}

	if (hasData) {
		std::cout << "������ ���ۿ� �����Ͱ� �ֽ��ϴ�." << std::endl;
	}
	else {
		std::cout << "������ ���۰� ��� �ֽ��ϴ�." << std::endl;
	}
}

GLvoid RavolutionAll()
{

	static float fAllAngle = 0.f;

	fAllAngle += fAngleMouse;

	if (abs(fAllAngle) >= 360.f)
	{
		if (fAllAngle > 0)
		{
			fAllAngle -= 360.f;
		}
		else
		{
			fAllAngle += 360.f;
		}
	}



	for (int i = 1; i < 6; ++i)
	{
		for (auto& iter : *AllVec[i])
		{

			if (iter->vPos[1] <= -45.f && i>=2)
			{
				continue;
			}
			iter->vRevolution[2] = fAllAngle;
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
float fLastAngle{};

GLvoid MoveDoor()
{



	if (!bOpen_door)
	{

		if (fLastAngle > 0)
		{
			fLastAngle -= 0.5f;

			AllArt.front()->vLastRotate[0] = fLastAngle;

			AllArt.front()->vLastMove[0] = AllArt.front()->rz;

		}


		return;
	}

	else
	{	
		if (fLastAngle < 90)
		{
			fLastAngle += 0.5f;

			AllArt.front()->vLastRotate[0] = fLastAngle;

			AllArt.front()->vLastMove[2] = -AllArt.front()->rz;

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

GLvoid Ball_Move()
{
	if (AllArtTwo.size() == 0)
	{
		return;
	}


	for (int i = 0; i < AllArtTwo.size(); ++i)
	{
		// xy �� �����̱�
		AllArtTwo[i]->vPos[0] += AllArtTwo[i]->vMoveVec[0] * AllArtTwo[i]->fSpeed * 0.3;
		AllArtTwo[i]->vPos[1] += AllArtTwo[i]->vMoveVec[1] * AllArtTwo[i]->fSpeed * 0.3;
	}


	// �浹ó�� �ϱ�
	for (int i = 0; i < AllArtTwo.size(); ++i)
	{

		if (AllArtTwo[i]->vPos[1] < -43.5f)
		{
			continue;
		}


			if (AllArtTwo[i]->vPos[0] < -42.5f)
			{
				AllArtTwo[i]->vMoveVec[0] = -AllArtTwo[i]->vMoveVec[0];

				AllArtTwo[i]->vPos[0] = -42.5f;
			}

			if (AllArtTwo[i]->vPos[0] > 42.5f)
			{
				AllArtTwo[i]->vMoveVec[0] = -AllArtTwo[i]->vMoveVec[0];

				AllArtTwo[i]->vPos[0] = 42.5f;
			}

			if (AllArtTwo[i]->vPos[1] > 42.5f)
			{
				AllArtTwo[i]->vMoveVec[1] = -AllArtTwo[i]->vMoveVec[1];

				AllArtTwo[i]->vPos[1] = 42.5f;
			}

			if (fLastAngle < 90.f)
			{
				if (AllArtTwo[i]->vPos[1] < -42.5f)
				{
					AllArtTwo[i]->vMoveVec[1] = -AllArtTwo[i]->vMoveVec[1];

					AllArtTwo[i]->vPos[1] = -42.5f;
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

GLvoid Box_Move()
{
	if (AllArtThree.size() == 0)
	{
		return;
	}


	for (int i = 0; i < AllArtThree.size(); ++i)
	{
		// xy �� �����̱�



		if (AllArtThree[i]->vRevolution[2] >= 0.f && AllArtThree[i]->vRevolution[2] < 90.f)
		{
			AllArtThree[i]->vPos[1] -= 0.1f;
			AllArtThree[i]->vPos[0] -= 0.1f;
		}

		if (AllArtThree[i]->vRevolution[2] >= 90.f && AllArtThree[i]->vRevolution[2] < 180.f)
		{
			if (AllArtThree[i]->vPos[1] < -43.5f + AllArtThree[i]->ry)
			{
				AllArtThree[i]->vPos[1] -= 0.1f;
				continue;
			}
			AllArtThree[i]->vPos[1] += 0.1f;
			AllArtThree[i]->vPos[0] -= 0.1f;
		}

		if (AllArtThree[i]->vRevolution[2] >= 180 && AllArtThree[i]->vRevolution[2] < 270.f)
		{
			if (AllArtThree[i]->vPos[1] < -43.5f + AllArtThree[i]->ry)
			{
				AllArtThree[i]->vPos[1] -= 0.1f;
				continue;
			}
			AllArtThree[i]->vPos[1] += 0.1f;
			AllArtThree[i]->vPos[0] += 0.1f;
		}

		if (AllArtThree[i]->vRevolution[2] >= 270 && AllArtThree[i]->vRevolution[2] < 360.f)
		{
			AllArtThree[i]->vPos[1] -= 0.1f;
			AllArtThree[i]->vPos[0] += 0.1f;
		}






		if (AllArtThree[i]->vRevolution[2] < 0.f && AllArtThree[i]->vRevolution[2] > -90.f)
		{
			AllArtThree[i]->vPos[1] -= 0.1f;
			AllArtThree[i]->vPos[0] += 0.1f;
		}

		if (AllArtThree[i]->vRevolution[2] <= -90.f && AllArtThree[i]->vRevolution[2] > -180.f)
		{
			if (AllArtThree[i]->vPos[1] < -43.5f + AllArtThree[i]->ry)
			{
				AllArtThree[i]->vPos[1] -= 0.1f;
				continue;
			}
			AllArtThree[i]->vPos[1] += 0.1f;
			AllArtThree[i]->vPos[0] += 0.1f;
		}

		if (AllArtThree[i]->vRevolution[2] <= -180 && AllArtThree[i]->vRevolution[2] > -270.f)
		{
			if (AllArtThree[i]->vPos[1] < -43.5f + AllArtThree[i]->ry)
			{
				AllArtThree[i]->vPos[1] -= 0.1f;
				continue;
			}
			AllArtThree[i]->vPos[1] += 0.1f;
			AllArtThree[i]->vPos[0] -= 0.1f;
		}

		if (AllArtThree[i]->vRevolution[2] <= -270 && AllArtThree[i]->vRevolution[2] > -360.f)
		{
			AllArtThree[i]->vPos[1] -= 0.1f;
			AllArtThree[i]->vPos[0] -= 0.1f;
		}

	}


	// �浹ó�� �ϱ�
	for (int i = 0; i < AllArtThree.size(); ++i)
	{

		if (AllArtThree[i]->vPos[1] < -43.5f + AllArtThree[i]->ry)
		{
			continue;
		}


		if (AllArtThree[i]->vPos[0] < -42.5f + AllArtThree[i]->rx)
		{

			AllArtThree[i]->vPos[0] = -42.5f + AllArtThree[i]->rx;
		}

		if (AllArtThree[i]->vPos[0] > 42.5f - AllArtThree[i]->rx)
		{

			AllArtThree[i]->vPos[0] = 42.5f - AllArtThree[i]->rx;
		}

		if (AllArtThree[i]->vPos[1] > 42.5f - AllArtThree[i]->ry)
		{

			AllArtThree[i]->vPos[1] = 42.5f - AllArtThree[i]->ry;
		}

		if (fLastAngle < 90.f)
		{
			if (AllArtThree[i]->vPos[1] < -42.5f + AllArtThree[i]->ry)
			{


				AllArtThree[i]->vPos[1] = -42.5f + AllArtThree[i]->ry;
			}
		}
	}
}
