#include "Define.h"

std::random_device rd{};

std::mt19937 mt(rd());

std::uniform_int_distribution<int> RandomRGB(0, 10);


std::uniform_real_distribution<GLfloat> RandomPosX(0, WinsizeX);
std::uniform_real_distribution<GLfloat> RandomPosY(0, WinsizeY);

uniform_int_distribution<int> RandomSize(50, 100);


uniform_int_distribution<int> RandomMove(1, 4);


// ���̴� ���� ����
GLuint shaderProgramID{}; // ���̴� ���α׷� �̸�
GLuint vertexShader{}; // ���ؽ� ���̴� ��ü
GLuint fragmentShader{}; // �����׸�Ʈ ������ ��ü



void make_vectexShaders() // ���ؽ� ������ ��ü �����
{
	GLchar* vertexSource{};

	vertexSource = filetobuf("vertex_shader.glsl");

	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result); 
	if(!result)
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

}




GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyInput(unsigned char key, int x, int y);
GLvoid TimerFunc(int Valule);
GLvoid MouseInput(int button, int state, int x, int y);
GLvoid MoveMouse(int X, int Y);






enum eMoveType { DIR_RIGHT, DIR_LEFT, DIR_UP, DIR_DOWN, DIR_LU, DIR_RU, DIR_LD, DIR_RD };






// 7 ��

DrawType eDrawType{};

GLvoid Create_DWArt(DrawType eDraw, GLfloat x, GLfloat y, GLfloat rx, GLfloat ry);

GLvoid Create_Dot(GLfloat x, GLfloat y);
GLvoid Create_Line(GLfloat x, GLfloat y, GLfloat rx, GLfloat ry);
GLvoid Create_Triangle(GLfloat x, GLfloat y, GLfloat rx, GLfloat ry);
GLvoid Create_Rect(GLfloat x, GLfloat y, GLfloat rx, GLfloat ry);

GLvoid Move(eMoveType Dir);

GLvoid Delete_ALL();



GLvoid SetMode(DrawType Type)
{
	eDrawType = Type;
}



vector<DWArt*> AllArt{};


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


void InitBuffer()
{
	//glGenVertexArrays(1, &vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�
	//glBindVertexArray(vao); //--- VAO�� ���ε��ϱ�

	//{
	//	glGenBuffers(2, vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
	//	//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
	//	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	//	//--- ���� diamond ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
	//	//--- triShape �迭�� ������: 9 * float
	//	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape, GL_STATIC_DRAW);
	//	//--- ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
	//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//	//--- attribute �ε��� 0���� ��밡���ϰ� ��
	//	glEnableVertexAttribArray(0);
	//	//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
	//	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//	//--- ���� colors���� ���ؽ� ������ �����Ѵ�.
	//	//--- colors �迭�� ������: 9 *float 
	//	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
	//	//--- ������ attribute �ε��� 1���� ����Ѵ�: ���ؽ� �� 3*float
	//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//	//--- attribute �ε��� 1���� ��� �����ϰ� ��.
	//	glEnableVertexAttribArray(1);
	//}


	vbo = new GLuint[AllArt.size()];
	EBO = new GLuint[AllArt.size()];

	
	for (int i = 0; i < AllArt.size(); ++i)
	{
		
		switch (AllArt[i]->eType)
		{
		case DWART_DOT:
			glGenVertexArrays(1, &AllArt[i]->VAO); //--- VAO �� �����ϰ� �Ҵ��ϱ�
			glGenBuffers(2, AllArt[i]->VBO);

			glBindVertexArray(AllArt[i]->VAO); //--- VAO�� ���ε��ϱ�


			glBindBuffer(GL_ARRAY_BUFFER, AllArt[i]->VBO[0]);

			glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWDot*>(AllArt[i])->Vertex), dynamic_cast<DWDot*>(AllArt[i])->Vertex, GL_STREAM_DRAW);

			glGenBuffers(1, &AllArt[i]->EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, AllArt[i]->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(dynamic_cast<DWDot*>(AllArt[i])->indexVerTex), dynamic_cast<DWDot*>(AllArt[i])->indexVerTex, GL_STREAM_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

			glEnableVertexAttribArray(0);

			//glEnableVertexAttribArray(0);


			/////////////////////////////////////////
			glBindBuffer(GL_ARRAY_BUFFER, AllArt[i]->VBO[1]);

			glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWDot*>(AllArt[i])->VertexColor), dynamic_cast<DWDot*>(AllArt[i])->VertexColor, GL_STREAM_DRAW);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

			glEnableVertexAttribArray(1);
			/////////////////////////////////////////


			break;

		case DWART_LINE:
			glGenVertexArrays(1, &AllArt[i]->VAO); //--- VAO �� �����ϰ� �Ҵ��ϱ�
			glGenBuffers(2, AllArt[i]->VBO);

			glBindVertexArray(AllArt[i]->VAO); //--- VAO�� ���ε��ϱ�


			glBindBuffer(GL_ARRAY_BUFFER, AllArt[i]->VBO[0]);

			glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWLine*>(AllArt[i])->Vertex), dynamic_cast<DWLine*>(AllArt[i])->Vertex, GL_STREAM_DRAW);

			glGenBuffers(1, &AllArt[i]->EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, AllArt[i]->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(dynamic_cast<DWLine*>(AllArt[i])->indexVerTex), dynamic_cast<DWLine*>(AllArt[i])->indexVerTex, GL_STREAM_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

			glEnableVertexAttribArray(0);

			//glEnableVertexAttribArray(0);


			/////////////////////////////////////////
			glBindBuffer(GL_ARRAY_BUFFER, AllArt[i]->VBO[1]);

			glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWLine*>(AllArt[i])->VertexColor), dynamic_cast<DWLine*>(AllArt[i])->VertexColor, GL_STREAM_DRAW);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

			glEnableVertexAttribArray(1);
			/////////////////////////////////////////


			break;

		case DWART_TRIANGLE:
			glGenVertexArrays(1, &AllArt[i]->VAO); //--- VAO �� �����ϰ� �Ҵ��ϱ�
			glGenBuffers(2, AllArt[i]->VBO);

			glBindVertexArray(AllArt[i]->VAO); //--- VAO�� ���ε��ϱ�


			glBindBuffer(GL_ARRAY_BUFFER, AllArt[i]->VBO[0]);

			glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWTriangle*>(AllArt[i])->Vertex), dynamic_cast<DWTriangle*>(AllArt[i])->Vertex, GL_STREAM_DRAW);

			glGenBuffers(1, &AllArt[i]->EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, AllArt[i]->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(dynamic_cast<DWTriangle*>(AllArt[i])->indexVerTex), dynamic_cast<DWTriangle*>(AllArt[i])->indexVerTex, GL_STREAM_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

			glEnableVertexAttribArray(0);

			//glEnableVertexAttribArray(0);


			/////////////////////////////////////////
			glBindBuffer(GL_ARRAY_BUFFER, AllArt[i]->VBO[1]);

			glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWTriangle*>(AllArt[i])->VertexColor), dynamic_cast<DWTriangle*>(AllArt[i])->VertexColor, GL_STREAM_DRAW);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

			glEnableVertexAttribArray(1);
			/////////////////////////////////////////
			break;

		case DWART_RECTANGLE:
			glGenVertexArrays(1, &AllArt[i]->VAO); //--- VAO �� �����ϰ� �Ҵ��ϱ�
			glGenBuffers(2, AllArt[i]->VBO);

			glBindVertexArray(AllArt[i]->VAO); //--- VAO�� ���ε��ϱ�


			glBindBuffer(GL_ARRAY_BUFFER, AllArt[i]->VBO[0]);

			glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWRect*>(AllArt[i])->Vertex), dynamic_cast<DWRect*>(AllArt[i])->Vertex, GL_STREAM_DRAW);

			glGenBuffers(1, &AllArt[i]->EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, AllArt[i]->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(dynamic_cast<DWRect*>(AllArt[i])->indexVerTex), dynamic_cast<DWRect*>(AllArt[i])->indexVerTex, GL_STREAM_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

			glEnableVertexAttribArray(0);

			//glEnableVertexAttribArray(0);


			/////////////////////////////////////////
			glBindBuffer(GL_ARRAY_BUFFER, AllArt[i]->VBO[1]);

			glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWRect*>(AllArt[i])->VertexColor), dynamic_cast<DWRect*>(AllArt[i])->VertexColor, GL_STREAM_DRAW);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

			glEnableVertexAttribArray(1);
			/////////////////////////////////////////
			break;

		default:
			cout << "Ÿ���� ������ ���� ����." << endl;
			break;
		}
	}



}




void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�

	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ ����
	glutInitWindowSize(WinsizeX, WinsizeY); // �������� ũ�� ����
	g_WinID = glutCreateWindow("OGWork-7"); // ������ ����(������ �̸�)
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
	InitBuffer();

	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutMotionFunc(MoveMouse);


	glutMainLoop(); // �̺�Ʈ ó�� ����
}

GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
	glClearColor(1.f, 1.f, 1.f, 1.f); // �������� ��blue�� �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�


	//int vColorLocation = glGetUniformLocation(shaderProgramID,"vColor");

	glUseProgram(shaderProgramID);

	//glUniform4f(vColorLocation,1.f,0.f,0.f,1.f);

	//glBindVertexArray(vao);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	for (auto& iter : AllArt)
	{
		glBindVertexArray(iter->VAO);

		switch (iter->eType)
		{
		case DWART_DOT:
			glPointSize(10);
			glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT,0);
			break;

		case DWART_LINE:
			glDrawElements(GL_LINE_STRIP, 2, GL_UNSIGNED_INT, 0);
			break;

		case DWART_TRIANGLE:
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
			break;

		case DWART_RECTANGLE:
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			break;
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
	case 'p':
		SetMode(DW_DOT);
		break;

	case 'l':
		SetMode(DW_LINE);
		break;

	case 't':
		SetMode(DW_TRIANGLE);
		break;

	case 'r':
		SetMode(DW_RECT);
		break;


	case 'w':
		Move(DIR_UP);
		break;
	case 'a':
		Move(DIR_LEFT);
		break;
	case 's':
		Move(DIR_DOWN);
		break;
	case 'd':
		Move(DIR_RIGHT);
		break;

	case 'c':
		Delete_ALL();
		break;



	case 'q':
		glutDestroyWindow(g_WinID);
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
			Create_DWArt(eDrawType, x, y, 50, 50);
			InitBuffer();

			break;

		case GLUT_RIGHT_BUTTON:

			break;
		}
	}
	glutPostRedisplay();
}

GLvoid Create_DWArt(DrawType eDraw ,GLfloat x, GLfloat y, GLfloat rx, GLfloat ry)
{

	if (AllArt.size() >= 10)
	{
		return;
	}

	switch (eDraw)
	{
	case DW_DOT:
		Create_Dot(x,y);
		break;
	case DW_LINE:
		Create_Line(x,y,rx,ry);
		break;
	case DW_TRIANGLE:
		Create_Triangle(x, y, rx, ry);
		break;
	case DW_RECT:
		Create_Rect(x, y, rx, ry);
		break;
	}
}

GLvoid Create_Dot(GLfloat x, GLfloat y)
{
	DWDot* Art = new DWDot{};

	Art->CenterX = x;
	Art->CenterY = y;

	Art->eType = DWART_DOT;

	//dynamic_cast<DWDot*>(Dot);
	

	Art->RGB[0] = 1.f;

	Art->Vertex[0][0] = CoordinateChangeX(x);
	Art->Vertex[0][1] = CoordinateChangeY(y);
	Art->Vertex[0][2] = 0.f;

	Art->VertexColor[0][0] = RandomRGB(mt)/10.f;
	Art->VertexColor[0][1] = RandomRGB(mt) / 10.f;
	Art->VertexColor[0][2] = RandomRGB(mt) / 10.f;

	// �ε���
	Art->indexVerTex[0] = 0;

	AllArt.push_back(Art);

}

GLvoid Create_Line(GLfloat x, GLfloat y, GLfloat rx, GLfloat ry)
{
	DWLine* Art = new DWLine{};

	// ����
	Art->CenterX = x;
	Art->CenterY = y;
	

	// ����
	Art->RGB[0] = 1.f;

	// ������
	Art->rx = rx;
	Art->ry = ry;


	// ����
	Art->eType = DWART_LINE;


	// ���� (���� ��)
	Art->Vertex[0][0] = CoordinateChangeX(x - rx);
	Art->Vertex[0][1] = CoordinateChangeY(y - ry);
	Art->Vertex[0][2] = 0.f;


	// ���� (������ �Ʒ�)
	Art->Vertex[1][0] = CoordinateChangeX(x + rx);
	Art->Vertex[1][1] = CoordinateChangeY(y + ry);
	Art->Vertex[1][2] = 0.f;


	// ���� (���� ��)
	Art->VertexColor[0][0] = RandomRGB(mt) / 10.f;
	Art->VertexColor[0][1] = RandomRGB(mt) / 10.f;
	Art->VertexColor[0][2] = RandomRGB(mt) / 10.f;


	// ���� (������ �Ʒ�)
	Art->VertexColor[1][0] = RandomRGB(mt) / 10.f;
	Art->VertexColor[1][1] = RandomRGB(mt) / 10.f;
	Art->VertexColor[1][2] = RandomRGB(mt) / 10.f;


	// �ε���
	Art->indexVerTex[0] = 0;
	Art->indexVerTex[1] = 1;


	AllArt.push_back(Art);
}

GLvoid Create_Triangle(GLfloat x, GLfloat y, GLfloat rx, GLfloat ry)
{
	DWTriangle* Art = new DWTriangle{};

	// ����
	Art->CenterX = x;
	Art->CenterY = y;


	// ����
	Art->RGB[0] = 1.f;

	// ������
	Art->rx = rx;
	Art->ry = ry;


	// ����
	Art->eType = DWART_TRIANGLE;


	// ���� (�߰� ��)
	Art->Vertex[0][0] = CoordinateChangeX(x);
	Art->Vertex[0][1] = CoordinateChangeY(y - ry);
	Art->Vertex[0][2] = 0.f;


	// ���� (������ �Ʒ�)
	Art->Vertex[1][0] = CoordinateChangeX(x + rx);
	Art->Vertex[1][1] = CoordinateChangeY(y + ry);
	Art->Vertex[1][2] = 0.f;

	// ���� (���� �Ʒ�)
	Art->Vertex[2][0] = CoordinateChangeX(x - rx);
	Art->Vertex[2][1] = CoordinateChangeY(y + ry);
	Art->Vertex[2][2] = 0.f;





	// ���� (�߰� ��)
	Art->VertexColor[0][0] = RandomRGB(mt) / 10.f;
	Art->VertexColor[0][1] = RandomRGB(mt) / 10.f;
	Art->VertexColor[0][2] = RandomRGB(mt) / 10.f;


	// ���� (������ �Ʒ�)
	Art->VertexColor[1][0] = RandomRGB(mt)/10.f;
	Art->VertexColor[1][1] = RandomRGB(mt)/10.f;
	Art->VertexColor[1][2] = RandomRGB(mt)/10.f;

	// ���� (���� �Ʒ�)
	Art->VertexColor[2][0] =  RandomRGB(mt)/10.f;
	Art->VertexColor[2][1] =  RandomRGB(mt)/10.f;
	Art->VertexColor[2][2] =  RandomRGB(mt)/10.f;




	// �ε���
	Art->indexVerTex[0] = 0;
	Art->indexVerTex[1] = 2;
	Art->indexVerTex[2] = 1;


	AllArt.push_back(Art);
}

GLvoid Create_Rect(GLfloat x, GLfloat y, GLfloat rx, GLfloat ry)
{
	DWRect* Art = new DWRect{};

	// ����
	Art->CenterX = x;
	Art->CenterY = y;


	// ����
	Art->RGB[0] = 1.f;

	// ������
	Art->rx = rx;
	Art->ry = ry;


	// ����
	Art->eType = DWART_RECTANGLE;


	// ���� (���� ��)
	Art->Vertex[0][0] = CoordinateChangeX(x - rx);
	Art->Vertex[0][1] = CoordinateChangeY(y - ry);
	Art->Vertex[0][2] = 0.f;


	// ���� (������ ��)
	Art->Vertex[1][0] = CoordinateChangeX(x + rx);
	Art->Vertex[1][1] = CoordinateChangeY(y - ry);
	Art->Vertex[1][2] = 0.f;

	// ���� (������ �Ʒ�)
	Art->Vertex[2][0] = CoordinateChangeX(x + rx);
	Art->Vertex[2][1] = CoordinateChangeY(y + ry);
	Art->Vertex[2][2] = 0.f;

	// ���� (���� �Ʒ�)
	Art->Vertex[3][0] = CoordinateChangeX(x - rx);
	Art->Vertex[3][1] = CoordinateChangeY(y + ry);
	Art->Vertex[3][2] = 0.f;


	// ���� (���� ��)
	Art->VertexColor[0][0] = RandomRGB(mt)/10.f;
	Art->VertexColor[0][1] = RandomRGB(mt)/10.f;
	Art->VertexColor[0][2] = RandomRGB(mt)/10.f;


	// ���� (������ ��)
	Art->VertexColor[1][0] = RandomRGB(mt)/10.f;
	Art->VertexColor[1][1] = RandomRGB(mt)/10.f;
	Art->VertexColor[1][2] = RandomRGB(mt)/10.f;

	// ���� (������ �Ʒ�)
	Art->VertexColor[2][0] = RandomRGB(mt)/10.f;
	Art->VertexColor[2][1] = RandomRGB(mt)/10.f;
	Art->VertexColor[2][2] = RandomRGB(mt)/10.f;

	// ���� (���� �Ʒ�)
	Art->VertexColor[3][0] = RandomRGB(mt)/10.f;
	Art->VertexColor[3][1] = RandomRGB(mt)/10.f;
	Art->VertexColor[3][2] = RandomRGB(mt)/10.f;



	// �ε���
	Art->indexVerTex[0] = 0;
	Art->indexVerTex[1] = 3;
	Art->indexVerTex[2] = 1;

	Art->indexVerTex[3] = 1;
	Art->indexVerTex[4] = 3;
	Art->indexVerTex[5] = 2;


	AllArt.push_back(Art);
}

GLvoid Move(eMoveType Dir)
{

	if (AllArt.empty())
	{
		return;
	}

	uniform_int_distribution<int> AllArtRandom(0, AllArt.size() - 1);
	
	int index = AllArtRandom(mt);

	switch (Dir)
	{
	case DIR_RIGHT:
		AllArt[index]->CenterX += CoordinateChangeX(10);

		break;
	case DIR_LEFT:
		AllArt[index]->CenterX -= CoordinateChangeX(10);
		break;
	case DIR_UP:
		AllArt[index]->CenterY -= CoordinateChangeY(10);
		break;
	case DIR_DOWN:
		AllArt[index]->CenterY += CoordinateChangeY(10);

		break;
	}


}

GLvoid Delete_ALL()
{
	Delete_ALL_Art(AllArt);
	InitBuffer();
}
