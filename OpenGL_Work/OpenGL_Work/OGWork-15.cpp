#include "Define_Work_3D.h"
#include "DW_Camera.h"

uniform_int_distribution<int> RandomIndex(0, 5);

uniform_int_distribution<int> RandomIndexTri(0, 5);


// ī�޶� ����
CDW_Camera DW_Camera{ glm::vec3(0.f,0.f,0.f),glm::vec3(0.f,0.f,-1.f) };


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
bool bLeftTrun{true};
bool bRightTrun{true};
float RotateX{};
float RotateY{};

GLvoid RotateAll();


// 15��
//bool bLeftRevolution{};
//bool bRightRevolution{};
float RavolutionX{};
float RavolutionY{};

GLvoid RavolutionAll();



//////////////////////////// ������� ��������



vector<DWArt*> AllArt{};

vector<DWArt*> LineArt{};

vector<DWArt*> LeftTop{};
vector<DWArt*> RightTop{};
vector<DWArt*> LeftBottom{};
vector<DWArt*> RightBottom{};

vector<DWArt*>* AllVec[6]{ &AllArt ,&LineArt,&LeftTop ,&RightTop ,&LeftBottom ,&RightBottom };

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
	RotateAll();
	RavolutionAll();
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

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�

	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(WinsizeX, WinsizeY); // �������� ũ�� ����
	g_WinID = glutCreateWindow("OGWork-14"); // ������ ����(������ �̸�)

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
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
	Create_Line_Pos(&LineArt, 0.f, 0.f, 25.f, 0.f, 0.f, -25.f);
	InitBuffers(&LineArt);

	Create_Sphere_Model(&AllArt,-15.f,0.f,0.f,5,20,20);
	InitBuffers(&AllArt);
	Set_Draw_Model_Style(AllArt.back(), GLU_LINE);

	Create_Cube(&AllArt, 15.f, 0.f, 0.f, 5.f, 5.f, 5.f);
	InitBuffers(&AllArt);



	//Create_Tetrahedron(&AllArt, 0.f, 0.f, 0.f, 5.f, 5.f, 5.f);
	//InitBuffers(&AllArt);



	glutKeyboardFunc(KeyInput);
	glutSpecialFunc(SpecialKeyInput);
	glutMouseFunc(MouseInput);
	glutMotionFunc(MoveMouse);
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����

	glutTimerFunc(16, Timer, 1);


	glutMainLoop(); // �̺�Ʈ ó�� ����
}


GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
	glClearColor(0.f, 0.f, 0.f, 1.f); // �������� ��blue�� �� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�

	glUseProgram(shaderProgramID);


	for (int i = 0; i < 6; ++i)
	{
		vector<DWArt*>* pVec = AllVec[i];

		for (auto& iter : *pVec)
		{
			MakeWorldMartrix(iter);

			// ����
			glUniformMatrix4fv(Shader_Matrix, 1, GL_FALSE, glm::value_ptr(iter->transformMatrix));

			// ��
			DW_Camera.Make_view_Matrix();
			glUniformMatrix4fv(Shader_ViewTransform, 1, GL_FALSE, glm::value_ptr(DW_Camera.Get_view_Matrix()));

			// ����
			glm::mat4 projection = glm::perspective(glm::radians(90.f), (float)WinsizeX / WinsizeY, 0.1f, 100.f);

			glUniformMatrix4fv(Shader_ProjectionTransform, 1, GL_FALSE, glm::value_ptr(projection));

			glBindVertexArray(iter->VAO);



			switch (iter->eType)
			{
			case DWART_LINE:
				glDrawElements(GL_LINE_STRIP, 2, GL_UNSIGNED_INT, 0);
				break;

			case DWART_CUBE:

				glDrawElements(iPrintType, 36, GL_UNSIGNED_INT, 0);

				break;

			case DWART_TETRATEDRON:
				glDrawElements(iPrintType, 18, GL_UNSIGNED_INT, 0);
				break;


			case DWART_MODEL_SPHERE:
				glBindVertexArray(iter->VAO);
				gluSphere(iter->Model, iter->Sphere_rx, iter->Sphere_Slices, iter->Sphere_Stacks);
				glBindVertexArray(0);

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
	case GLUT_KEY_RIGHT:
		for (auto& iter : AllArt)
		{
			iter->vPos[0] += 1.f;
		}
		break;
	case GLUT_KEY_LEFT:
		for (auto& iter : AllArt)
		{
			iter->vPos[0] -= 1.f;
		}
		break;

	case GLUT_KEY_UP:
		for (auto& iter : AllArt)
		{
			iter->vPos[1] += 1.f;
		}
		break;
	case GLUT_KEY_DOWN:
		for (auto& iter : AllArt)
		{
			iter->vPos[1] -= 1.f;
		}
		break;

	}
	//glutPostRedisplay();
}


GLvoid KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'c':
		Delete_ALL_Art(AllArt);
		Create_Sylinder_Model(&AllArt, -15.f, 0.f, 0.f, 5, 5, 10, 20, 20);
		InitBuffers(&AllArt);
		Set_Draw_Model_Style(AllArt.back(), GLU_LINE);

		Create_Sylinder_Model(&AllArt, 15.f, 0.f, 0.f, 0, 5, 10, 20, 20);
		InitBuffers(&AllArt);
		Set_Draw_Model_Style(AllArt.back(), GLU_LINE);
		break;

	case 'p':
		Delete_ALL_Art(AllArt);
		Create_DWArt(&AllArt, DWART_TETRATEDRON, 0, 0, 0, 5, 5, 5);
		AllArt.back()->vRotate[0] = 90.f;
		AllArt.back()->vRotate[1] = -30.f;
		break;


	case '1':
		bLeftTrun = true;
		bRightTrun = false;
		break;


	case '2':
		bLeftTrun = false;
		bRightTrun = true;
		break;


	case '3':
		bLeftTrun = true;
		bRightTrun = true;
		break;



	case 'h':
		if (!bCallMode)
		{
			glEnable(GL_CULL_FACE);
			bCallMode = !bCallMode;
		}
		else
		{
			glDisable(GL_CULL_FACE);
			bCallMode = !bCallMode;
		}
		break;

	case 'w':
		iPrintType = GL_LINE_STRIP;
		break;

	case 'W':
		iPrintType = GL_TRIANGLES;
		break;

	case 'x':

		RotateX = 1.f;

		break;

	case 'X':
		RotateX = -1.f;
		break;

	case 'y':
		RotateY = 1.f;
		break;

	case 'Y':
		RotateY = -1.f;
		break;

	case 'r':
		RavolutionY = 1.f;
		break;

	case 'R':
		RavolutionY = -1.f;
		break;
		 




	case 's':
		RotateX = 0.f;
		RotateY = 0.f;
		RavolutionX = 0.f;
		RavolutionY = 0.f;
		bLeftTrun = true;
		bRightTrun = true;
		Delete_ALL_Art(AllArt);

		Create_Sphere_Model(&AllArt, -15.f, 0.f, 0.f, 5, 20, 20);
		InitBuffers(&AllArt);
		Set_Draw_Model_Style(AllArt.back(), GLU_LINE);

		Create_Cube(&AllArt, 15.f, 0.f, 0.f, 5.f, 5.f, 5.f);
		InitBuffers(&AllArt);

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

	//glutPostRedisplay();
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
	if (bLeftTrun)
	{
		AllArt.front()->vRotate[0] += RotateX;
		AllArt.front()->vRotate[1] += RotateY;
	}
	if (bRightTrun)
	{
		AllArt.back()->vRotate[0] += RotateX;
		AllArt.back()->vRotate[1] += RotateY;
	}

	/*for (auto& iter : AllArt)
	{
		iter->vRotate[0] += RotateX;
		iter->vRotate[1] += RotateY;
	}*/
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
	for (auto& iter : AllArt)
	{
		iter->vRevolution[0] += RavolutionX;
		iter->vRevolution[1] += RavolutionY;
	}
}
