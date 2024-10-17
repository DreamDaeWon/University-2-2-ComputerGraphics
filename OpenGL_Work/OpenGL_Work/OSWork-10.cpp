#include "Define_Work_10.h"



// ���̴� ���� ����
GLuint shaderProgramID{}; // ���̴� ���α׷� �̸�
GLuint vertexShader{}; // ���ؽ� ���̴� ��ü
GLuint fragmentShader{}; // �����׸�Ʈ ������ ��ü



void make_vectexShaders() // ���ؽ� ������ ��ü �����
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




// 7 ��

DrawType eDrawType{};

GLvoid Create_DWArt(vector<DWArt*>* pVec, DrawType eDraw, GLfloat x, GLfloat y, GLfloat rx, GLfloat ry);

GLvoid Move(eMoveType Dir);

GLvoid Delete_ALL();

GLvoid UpdateBuffers();

//void InitBuffers();


// 8 ��



// 9 ��

GLint Move_Style = 0;

GLvoid All_Move_Func(GLint Value);

GLvoid Move_Diagonal();

GLvoid Move_ZigZig();

GLvoid Move_Squire_Spiral();

GLvoid Move_Circle_spiral();


// 10 ��
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

unsigned int g_WinID{};// ������ ID

bool bTimer = false; // Ÿ�̸� ���� ���� ����


// 4�� Ÿ�̸� ���ú���
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

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�

	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(WinsizeX, WinsizeY); // �������� ũ�� ����
	g_WinID = glutCreateWindow("OGWork-10"); // ������ ����(������ �̸�)
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


	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutMotionFunc(MoveMouse);

	glutTimerFunc(1, All_Move_Func, 1);
	glutTimerFunc(10, Timer, 1);

	glutMainLoop(); // �̺�Ʈ ó�� ����
}


GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
	glClearColor(0.f, 0.f, 0.f, 1.f); // �������� ��blue�� �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�


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



	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
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
			// ���콺 ��и� üũ
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
		if (iter->LR) // ������
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
			if (iter->ZigZag) // �Ʒ�
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
			else // ��
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
		if (!iter->LR) // ����
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
			if (iter->ZigZag) // �Ʒ�
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
			else // ��
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
		// �¿�� ���� ��
		if (iter->Move_Timer == 0)
		{
			if (iter->LR) // ������
			{
				iter->CenterX += 10.f;
			}
			else
			{
				iter->CenterX -= 10.f;
			}
		}

		// ���� �Ǵ� ������ ���� ������ �Ʒ��� ��

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

			if (iter->ZigZag) // �Ʒ�
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
		// �Ʒ� ���� ������ ���� ��
		if (iter->CenterY < 0 || iter->CenterY > WinsizeY)
		{
			if (iter->ZigZag)
			{
				iter->ZigZag = !iter->ZigZag;
				iter->Move_Timer = 0;
				iter->CenterY = WinsizeY;
			}
			else // �� ���� ������ �Ʒ��� ��
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
	int iSmallSize{}; // ���� ũ��

	for (auto& iter : AllArt)
	{
		// ���� ���� ������ �Ʒ��� ��, ������ ���� ���
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

				iter->eDir = DIR_DOWN; // �Ʒ��������� ����

				iter->Wall_Max_X -= 50; // ������ ���̱�
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

				iter->eDir = DIR_UP; // ���ʹ��� ����

				iter->Wall_Min_X += 50; // ���� ���̱�
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

				iter->eDir = DIR_RIGHT; // ������

				iter->Wall_Min_Y += 50; // ���� ���̱�
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

				iter->eDir = DIR_LEFT; // ���� �������� �̵�

				iter->Wall_Max_Y -= 50; // �Ʒ��� ���̱�
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
//	// �ϴ� ����� ���̰� �Ѵ�.
//
//	for (auto& iter : AllArt)
//	{
//		if (iter->LRCenterMove)
//		{
//			if (iter->LR) // ������
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
//			if (!iter->ZigZag) // �Ʒ���
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
//			else if (iter->ZigZag) // ����
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

