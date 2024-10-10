#pragma once
#include <iostream>
#include <gl/glew.h> //--- �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <stdio.h>
#include <iostream>
#include <random>
#include <list>
#include <vector>

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>  
#include <stdio.h>

using namespace std;


GLint WinsizeX{ 800 };
GLint WinsizeY{ 800 };



std::random_device rd{};

std::mt19937 mt(rd());

std::uniform_int_distribution<int> RandomRGB(0, 10);


std::uniform_real_distribution<GLfloat> RandomPosX(0, WinsizeX);
std::uniform_real_distribution<GLfloat> RandomPosY(0, WinsizeY);

uniform_int_distribution<int> RandomSize(50, 100);


uniform_int_distribution<int> RandomMove(1, 4);

uniform_real_distribution<float> RandomAngle(0.f, 360.f);




enum ArtType { DWART_DOT, DWART_LINE, DWART_TRIANGLE, DWART_RECTANGLE };
enum DrawType { DW_DOT, DW_LINE, DW_TRIANGLE, DW_RECT };
enum eMoveType { DIR_RIGHT, DIR_LEFT, DIR_UP, DIR_DOWN, DIR_LU, DIR_RU, DIR_LD, DIR_RD };

struct DWArt
{
	virtual ~DWArt() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(2, VBO);
		glDeleteBuffers(1, &EBO);
	};

	ArtType eType{};

	GLfloat RGB[3]{};

	GLfloat CenterX{};
	GLfloat CenterY{};

	GLfloat rx{};
	GLfloat ry{};

	bool LR{};

	bool ZigZag{};

	GLfloat Rotate{}; // ȸ��


	int Move_Timer{}; // ������ �� ����� ��




	eMoveType eDir{}; // �簢 �����̷� �� ����� ��
	float Wall_Min_X{0}; // �簢 �����̷� �� ����� ��
	float Wall_Max_X{WinsizeX + 50.f}; // �簢 �����̷� �� ����� ��
	float Wall_Min_Y{0}; // �簢 �����̷� �� ����� ��
	float Wall_Max_Y{ float(WinsizeY) }; // �簢 �����̷� �� ����� ��


	GLuint VAO{};
	GLuint VBO[3]{};

	GLuint EBO{};
};



struct DWRect : public DWArt
{
	GLfloat Vertex[6][3]{};
	GLfloat VertexColor[6][3]{};
	GLuint indexVerTex[6]{};
};

struct DWDot : public DWArt
{
	GLfloat Vertex[1][3]{};
	GLfloat VertexColor[1][3]{};

	GLuint indexVerTex[1]{};
};

struct DWTriangle : public DWArt
{
	GLfloat Vertex[3][3]{};
	GLfloat VertexColor[3][3]{};


	GLuint indexVerTex[3]{};
};

struct DWLine : public DWArt
{
	GLfloat Vertex[2][3]{};
	GLfloat VertexColor[2][3]{};

	GLuint indexVerTex[2]{};
};










// �Լ� �����
char* filetobuf(const char* file);
GLvoid Delete_ALL_Art(vector<DWArt*>& pvector); // �ش� ������ ��� ��ü �����
GLvoid DeleteArt(vector<DWArt*>& pvector, DWArt* pArt); // �ش� ���Ϳ��� ���ϴ� ���� �����
GLvoid ReleaseArt(vector<DWArt*>& pvector, DWArt* pArt); // �ش� ���Ϳ��� ���ϴ� ���� delete�� �ϱ�(���Ϳ��� nullptr��)
GLfloat Coordinate_RE_ChangeX(GLfloat Coord); // X�� ��ǥ�� ��ȯ ���� -> ������
GLfloat Coordinate_RE_ChangeY(GLfloat Coord); // Y�� ��ǥ�� ��ȯ ���� -> ������
GLfloat CoordinateChangeX(GLfloat Coord); // X�� ��ǥ�� ��ȯ ������ -> ����
GLfloat CoordinateChangeY(GLfloat Coord); // Y�� ��ǥ�� ��ȯ ������ -> ����
GLint CheckMouseQuadrant(GLfloat X, GLfloat Y); // ���콺�� �� ��и��� �������� �˷��ִ� �Լ� // ��Ȯ�� �����̸� 0
DWArt* Check_Mouse_Rect(vector<DWArt*>& pvector, GLfloat x, GLfloat y); // ���콺�� ��ü üũ
DWArt* Check_Rect_Rect(vector<DWArt*>& pvector, DWArt* _CheckRect); // ��ü�� ��ü üũ
GLvoid MoveArt(DWArt* pArt, ArtType eDraw, eMoveType eMove); // �־��� ��ü �����̱�


GLvoid Create_Dot(vector<DWArt*>* pVec, GLfloat x, GLfloat y); // ���ϴ� ���Ϳ� �� �߰�
GLvoid Create_Line(vector<DWArt*>* pVec, GLfloat x, GLfloat y, GLfloat rx, GLfloat ry); // ���ϴ� ���Ϳ� ���� �߰�
GLvoid Create_Line_Pos(vector<DWArt*>* pVec, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2); // ���ϴ� ���Ϳ� ���ϴ� �� ���� �մ� ���� �߰�
GLvoid Create_Triangle(vector<DWArt*>* pVec, GLfloat x, GLfloat y, GLfloat rx, GLfloat ry); // ���ϴ� ���Ϳ� �ﰢ�� �߰�
GLvoid Create_Rect(vector<DWArt*>* pVec, GLfloat x, GLfloat y, GLfloat rx, GLfloat ry); // ���ϴ� ���Ϳ� �׸� �߰�






GLvoid InitBuffer(DWArt* pArt);
GLvoid UpdateBuffer(DWArt* pArt);


GLvoid ReBindArt(DWArt* pArt, ArtType eDraw);





GLvoid MoveArt(DWArt* pArt, ArtType eDraw, eMoveType eMove)
{
	switch (eMove)
	{
	case DIR_RIGHT:
		pArt->CenterX += 10;
		break;

	case DIR_LEFT:
		pArt->CenterX -= 10;
		break;

	case DIR_UP:
		pArt->CenterY -= 10;
		break;

	case DIR_DOWN:
		pArt->CenterY += 10;
		break;
	}



	ReBindArt(pArt, eDraw);

}

GLvoid UpdateBuffer(DWArt* pArt)
{
	switch (pArt->eType)
	{
	case DWART_DOT:


		glBindVertexArray(pArt->VAO); //--- VAO�� ���ε��ϱ�


		glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[0]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWDot*>(pArt)->Vertex), dynamic_cast<DWDot*>(pArt)->Vertex, GL_STREAM_DRAW);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pArt->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(dynamic_cast<DWDot*>(pArt)->indexVerTex), dynamic_cast<DWDot*>(pArt)->indexVerTex, GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		glEnableVertexAttribArray(0);

		//glEnableVertexAttribArray(0);


		/////////////////////////////////////////
		glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[1]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWDot*>(pArt)->VertexColor), dynamic_cast<DWDot*>(pArt)->VertexColor, GL_STREAM_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		glEnableVertexAttribArray(1);
		/////////////////////////////////////////


		break;

	case DWART_LINE:


		glBindVertexArray(pArt->VAO); //--- VAO�� ���ε��ϱ�


		glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[0]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWLine*>(pArt)->Vertex), dynamic_cast<DWLine*>(pArt)->Vertex, GL_STREAM_DRAW);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pArt->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(dynamic_cast<DWLine*>(pArt)->indexVerTex), dynamic_cast<DWLine*>(pArt)->indexVerTex, GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		glEnableVertexAttribArray(0);

		//glEnableVertexAttribArray(0);


		/////////////////////////////////////////
		glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[1]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWLine*>(pArt)->VertexColor), dynamic_cast<DWLine*>(pArt)->VertexColor, GL_STREAM_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		glEnableVertexAttribArray(1);
		/////////////////////////////////////////


		break;

	case DWART_TRIANGLE:


		glBindVertexArray(pArt->VAO); //--- VAO�� ���ε��ϱ�


		glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[0]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWTriangle*>(pArt)->Vertex), dynamic_cast<DWTriangle*>(pArt)->Vertex, GL_STREAM_DRAW);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pArt->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(dynamic_cast<DWTriangle*>(pArt)->indexVerTex), dynamic_cast<DWTriangle*>(pArt)->indexVerTex, GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		glEnableVertexAttribArray(0);

		//glEnableVertexAttribArray(0);


		/////////////////////////////////////////
		glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[1]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWTriangle*>(pArt)->VertexColor), dynamic_cast<DWTriangle*>(pArt)->VertexColor, GL_STREAM_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		glEnableVertexAttribArray(1);
		/////////////////////////////////////////
		break;

	case DWART_RECTANGLE:


		glBindVertexArray(pArt->VAO); //--- VAO�� ���ε��ϱ�


		glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[0]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWRect*>(pArt)->Vertex), dynamic_cast<DWRect*>(pArt)->Vertex, GL_STREAM_DRAW);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pArt->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(dynamic_cast<DWRect*>(pArt)->indexVerTex), dynamic_cast<DWRect*>(pArt)->indexVerTex, GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		glEnableVertexAttribArray(0);

		//glEnableVertexAttribArray(0);


		/////////////////////////////////////////
		glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[1]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWRect*>(pArt)->VertexColor), dynamic_cast<DWRect*>(pArt)->VertexColor, GL_STREAM_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		glEnableVertexAttribArray(1);
		/////////////////////////////////////////
		break;

	default:
		cout << "Ÿ���� ������ ���� ����." << endl;
		break;
	}
}

inline GLvoid InitBuffer(DWArt* pArt)
{
	switch (pArt->eType)
	{
	case DWART_DOT:
		glGenVertexArrays(1, &pArt->VAO); //--- VAO �� �����ϰ� �Ҵ��ϱ�
		glGenBuffers(2, pArt->VBO);

		glBindVertexArray(pArt->VAO); //--- VAO�� ���ε��ϱ�


		glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[0]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWDot*>(pArt)->Vertex), dynamic_cast<DWDot*>(pArt)->Vertex, GL_STREAM_DRAW);

		glGenBuffers(1, &pArt->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pArt->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(dynamic_cast<DWDot*>(pArt)->indexVerTex), dynamic_cast<DWDot*>(pArt)->indexVerTex, GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		glEnableVertexAttribArray(0);

		//glEnableVertexAttribArray(0);


		/////////////////////////////////////////
		glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[1]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWDot*>(pArt)->VertexColor), dynamic_cast<DWDot*>(pArt)->VertexColor, GL_STREAM_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		glEnableVertexAttribArray(1);
		/////////////////////////////////////////


		break;

	case DWART_LINE:
		glGenVertexArrays(1, &pArt->VAO); //--- VAO �� �����ϰ� �Ҵ��ϱ�
		glGenBuffers(2, pArt->VBO);

		glBindVertexArray(pArt->VAO); //--- VAO�� ���ε��ϱ�


		glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[0]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWLine*>(pArt)->Vertex), dynamic_cast<DWLine*>(pArt)->Vertex, GL_STREAM_DRAW);

		glGenBuffers(1, &pArt->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pArt->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(dynamic_cast<DWLine*>(pArt)->indexVerTex), dynamic_cast<DWLine*>(pArt)->indexVerTex, GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		glEnableVertexAttribArray(0);

		//glEnableVertexAttribArray(0);


		/////////////////////////////////////////
		glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[1]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWLine*>(pArt)->VertexColor), dynamic_cast<DWLine*>(pArt)->VertexColor, GL_STREAM_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		glEnableVertexAttribArray(1);
		/////////////////////////////////////////


		break;

	case DWART_TRIANGLE:
		glGenVertexArrays(1, &pArt->VAO); //--- VAO �� �����ϰ� �Ҵ��ϱ�
		glGenBuffers(2, pArt->VBO);

		glBindVertexArray(pArt->VAO); //--- VAO�� ���ε��ϱ�


		glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[0]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWTriangle*>(pArt)->Vertex), dynamic_cast<DWTriangle*>(pArt)->Vertex, GL_STREAM_DRAW);

		glGenBuffers(1, &pArt->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pArt->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(dynamic_cast<DWTriangle*>(pArt)->indexVerTex), dynamic_cast<DWTriangle*>(pArt)->indexVerTex, GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		glEnableVertexAttribArray(0);

		//glEnableVertexAttribArray(0);


		/////////////////////////////////////////
		glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[1]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWTriangle*>(pArt)->VertexColor), dynamic_cast<DWTriangle*>(pArt)->VertexColor, GL_STREAM_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		glEnableVertexAttribArray(1);
		/////////////////////////////////////////

		break;

	case DWART_RECTANGLE:
		glGenVertexArrays(1, &pArt->VAO); //--- VAO �� �����ϰ� �Ҵ��ϱ�
		glGenBuffers(2, pArt->VBO);

		glBindVertexArray(pArt->VAO); //--- VAO�� ���ε��ϱ�


		glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[0]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWRect*>(pArt)->Vertex), dynamic_cast<DWRect*>(pArt)->Vertex, GL_STREAM_DRAW);

		glGenBuffers(1, &pArt->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pArt->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(dynamic_cast<DWRect*>(pArt)->indexVerTex), dynamic_cast<DWRect*>(pArt)->indexVerTex, GL_STREAM_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		glEnableVertexAttribArray(0);

		//glEnableVertexAttribArray(0);


		/////////////////////////////////////////
		glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[1]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(dynamic_cast<DWRect*>(pArt)->VertexColor), dynamic_cast<DWRect*>(pArt)->VertexColor, GL_STREAM_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		glEnableVertexAttribArray(1);
		/////////////////////////////////////////
		break;

	default:
		cout << "Ÿ���� ������ ���� ����." << endl;
		break;
	}
}


GLvoid ReBindArt(DWArt* pArt, ArtType eDraw)
{
	switch (eDraw)
	{
	case DWART_DOT:
		dynamic_cast<DWDot*>(pArt)->Vertex[0][0] = CoordinateChangeX(dynamic_cast<DWDot*>(pArt)->CenterX);
		dynamic_cast<DWDot*>(pArt)->Vertex[0][1] = CoordinateChangeY(dynamic_cast<DWDot*>(pArt)->CenterY);

		//pArt->Vertex[0][2] = 0.f;
		break;
	case DWART_LINE:
		// ���� (���� ��)
		dynamic_cast<DWLine*>(pArt)->Vertex[0][0] = CoordinateChangeX(dynamic_cast<DWLine*>(pArt)->CenterX - dynamic_cast<DWLine*>(pArt)->rx);
		dynamic_cast<DWLine*>(pArt)->Vertex[0][1] = CoordinateChangeY(dynamic_cast<DWLine*>(pArt)->CenterY - dynamic_cast<DWLine*>(pArt)->ry);
		//Art->Vertex[0][2] = 0.f;


		// ���� (������ �Ʒ�)
		dynamic_cast<DWLine*>(pArt)->Vertex[1][0] = CoordinateChangeX(dynamic_cast<DWLine*>(pArt)->CenterX + dynamic_cast<DWLine*>(pArt)->rx);
		dynamic_cast<DWLine*>(pArt)->Vertex[1][1] = CoordinateChangeY(dynamic_cast<DWLine*>(pArt)->CenterY + dynamic_cast<DWLine*>(pArt)->ry);
		//Art->Vertex[1][2] = 0.f;
		break;
	case DWART_TRIANGLE:
		// ���� (�߰� ��)
		dynamic_cast<DWTriangle*>(pArt)->Vertex[0][0] = CoordinateChangeX(dynamic_cast<DWTriangle*>(pArt)->CenterX);
		dynamic_cast<DWTriangle*>(pArt)->Vertex[0][1] = CoordinateChangeY(dynamic_cast<DWTriangle*>(pArt)->CenterY - dynamic_cast<DWTriangle*>(pArt)->ry);
		dynamic_cast<DWTriangle*>(pArt)->Vertex[0][2] = 0.f;


		// ���� (������ �Ʒ�)
		dynamic_cast<DWTriangle*>(pArt)->Vertex[1][0] = CoordinateChangeX(dynamic_cast<DWTriangle*>(pArt)->CenterX + dynamic_cast<DWTriangle*>(pArt)->rx);
		dynamic_cast<DWTriangle*>(pArt)->Vertex[1][1] = CoordinateChangeY(dynamic_cast<DWTriangle*>(pArt)->CenterY + dynamic_cast<DWTriangle*>(pArt)->ry);
		dynamic_cast<DWTriangle*>(pArt)->Vertex[1][2] = 0.f;

		// ���� (���� �Ʒ�)
		dynamic_cast<DWTriangle*>(pArt)->Vertex[2][0] = CoordinateChangeX(dynamic_cast<DWTriangle*>(pArt)->CenterX - dynamic_cast<DWTriangle*>(pArt)->rx);
		dynamic_cast<DWTriangle*>(pArt)->Vertex[2][1] = CoordinateChangeY(dynamic_cast<DWTriangle*>(pArt)->CenterY + dynamic_cast<DWTriangle*>(pArt)->ry);
		dynamic_cast<DWTriangle*>(pArt)->Vertex[2][2] = 0.f;
		break;
	case DWART_RECTANGLE:
		// ���� (���� ��)
		dynamic_cast<DWRect*>(pArt)->Vertex[0][0] = CoordinateChangeX(dynamic_cast<DWRect*>(pArt)->CenterX - dynamic_cast<DWRect*>(pArt)->rx);
		dynamic_cast<DWRect*>(pArt)->Vertex[0][1] = CoordinateChangeY(dynamic_cast<DWRect*>(pArt)->CenterY - dynamic_cast<DWRect*>(pArt)->ry);
		dynamic_cast<DWRect*>(pArt)->Vertex[0][2] = 0.f;


		// ���� (������ ��)
		dynamic_cast<DWRect*>(pArt)->Vertex[1][0] = CoordinateChangeX(dynamic_cast<DWRect*>(pArt)->CenterX + dynamic_cast<DWRect*>(pArt)->rx);
		dynamic_cast<DWRect*>(pArt)->Vertex[1][1] = CoordinateChangeY(dynamic_cast<DWRect*>(pArt)->CenterY - dynamic_cast<DWRect*>(pArt)->ry);
		dynamic_cast<DWRect*>(pArt)->Vertex[1][2] = 0.f;

		// ���� (������ �Ʒ�)
		dynamic_cast<DWRect*>(pArt)->Vertex[2][0] = CoordinateChangeX(dynamic_cast<DWRect*>(pArt)->CenterX + dynamic_cast<DWRect*>(pArt)->rx);
		dynamic_cast<DWRect*>(pArt)->Vertex[2][1] = CoordinateChangeY(dynamic_cast<DWRect*>(pArt)->CenterY + dynamic_cast<DWRect*>(pArt)->ry);
		dynamic_cast<DWRect*>(pArt)->Vertex[2][2] = 0.f;

		// ���� (���� �Ʒ�)
		dynamic_cast<DWRect*>(pArt)->Vertex[3][0] = CoordinateChangeX(dynamic_cast<DWRect*>(pArt)->CenterX - dynamic_cast<DWRect*>(pArt)->rx);
		dynamic_cast<DWRect*>(pArt)->Vertex[3][1] = CoordinateChangeY(dynamic_cast<DWRect*>(pArt)->CenterY + dynamic_cast<DWRect*>(pArt)->ry);
		dynamic_cast<DWRect*>(pArt)->Vertex[3][2] = 0.f;
		break;
	}
}


GLvoid Delete_ALL_Art(vector<DWArt*>& pvector)
{
	for (auto& iter : pvector)
	{
		delete iter;
		iter = nullptr;
	}

	pvector.clear();
}


GLvoid DeleteArt(vector<DWArt*>& pvector, DWArt* pArt)
{
	for (vector<DWArt*>::iterator iter = pvector.begin(); iter != pvector.end(); ++iter)
	{
		if ((*iter) == pArt)
		{
			delete pArt;
			pvector.erase(iter);
			return;
		}
	}
}

GLvoid ReleaseArt(vector<DWArt*>& pvector, DWArt* pArt)
{
	for (vector<DWArt*>::iterator iter = pvector.begin(); iter != pvector.end(); ++iter)
	{
		if ((*iter) == pArt)
		{
			delete pArt;
			return;
		}
	}
}

GLfloat Coordinate_RE_ChangeX(GLfloat Coord)
{
	Coord = Coord * (WinsizeX / 2);
	Coord = Coord + (WinsizeX / 2);

	return Coord;
}

GLfloat Coordinate_RE_ChangeY(GLfloat Coord)
{

	Coord = Coord * (WinsizeY / 2);
	Coord = Coord - (WinsizeY / 2);
	Coord = -Coord;

	return Coord;
}

GLfloat CoordinateChangeX(GLfloat Coord)
{
	Coord = Coord - (WinsizeX / 2);
	Coord = Coord / (WinsizeX / 2);
	return Coord;
}

GLfloat CoordinateChangeY(GLfloat Coord)
{
	Coord = -Coord;
	Coord = Coord + (WinsizeY / 2);
	Coord = Coord / (WinsizeY / 2);
	return Coord;
}

GLint CheckMouseQuadrant(GLfloat X, GLfloat Y)
{
	// ���� ��ǥ(OG ��ǥ��)�� ��ȯ 
	GLfloat fX = CoordinateChangeX(X);
	GLfloat fY = CoordinateChangeY(Y);

	if (fX > 0 && fY > 0)
	{
		return 1;
	}

	if (fX < 0 && fY > 0)
	{
		return 2;
	}

	if (fX < 0 && fY < 0)
	{
		return 3;
	}

	if (fX > 0 && fY < 0)
	{
		return 4;
	}


	return 0;
}

DWArt* Check_Mouse_Rect(vector<DWArt*>& pvector, GLfloat x, GLfloat y)
{
	for (auto iter : pvector)
	{
		if ((iter->CenterX - iter->rx <= x && iter->CenterX + iter->rx >= x) &&
			(iter->CenterY - iter->ry <= y && iter->CenterY + iter->ry >= y))
		{
			return iter; // ���콺�� ��ġ�� �簢���� ��Ҵٸ�?
		}
	}


	return nullptr; // ���콺�� ��ġ�� �簢���� ���� �ʾҴٸ�?
}

DWArt* Check_Rect_Rect(vector<DWArt*>& pvector, DWArt* _CheckRect)
{
	if (_CheckRect == nullptr)
		return nullptr;

	for (auto& iter : pvector)
	{
		if (iter == _CheckRect)
		{
			continue;
		}
		if (_CheckRect->CenterX - _CheckRect->rx > iter->CenterX + iter->rx || _CheckRect->CenterX + _CheckRect->rx < iter->CenterX - iter->rx)
		{
			continue; // �簢���� ��ġ�� �簢���� ���� �ʾҴٸ�?
		}
		if (_CheckRect->CenterY - _CheckRect->ry > iter->CenterY + iter->ry || _CheckRect->CenterY + _CheckRect->ry < iter->CenterY - iter->ry)
		{
			continue; // �簢���� ��ġ�� �簢���� ���� �ʾҴٸ�?
		}
		return iter; // �簢���� ��ġ�� �簢���� ��Ҵٸ�?
	}
	return nullptr; // �簢���� ��ġ�� �簢���� ���� �ʾҴٸ�?
}


GLvoid Create_Dot(vector<DWArt*>* pVec, GLfloat x, GLfloat y)
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

	Art->VertexColor[0][0] = RandomRGB(mt) / 10.f;
	Art->VertexColor[0][1] = RandomRGB(mt) / 10.f;
	Art->VertexColor[0][2] = RandomRGB(mt) / 10.f;

	// �ε���
	Art->indexVerTex[0] = 0;

	pVec->push_back(Art);

}

GLvoid Create_Line(vector<DWArt*>* pVec, GLfloat x, GLfloat y, GLfloat rx, GLfloat ry)
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


	pVec->push_back(Art);
}


GLvoid Create_Line_Pos(vector<DWArt*>* pVec, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
	DWLine* Art = new DWLine{};

	// ����
	//Art->CenterX = x;
	//Art->CenterY = y;


	// ����
	Art->RGB[0] = 1.f;

	// ������
	//Art->rx = rx;
	//Art->ry = ry;


	// ����
	Art->eType = DWART_LINE;


	// ���� (���� ��)
	Art->Vertex[0][0] = CoordinateChangeX(x1);
	Art->Vertex[0][1] = CoordinateChangeY(y1);
	Art->Vertex[0][2] = 0.f;


	// ���� (������ �Ʒ�)
	Art->Vertex[1][0] = CoordinateChangeX(x2);
	Art->Vertex[1][1] = CoordinateChangeY(y2);
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


	pVec->push_back(Art);
}




GLvoid Create_Triangle(vector<DWArt*>* pVec, GLfloat x, GLfloat y, GLfloat rx, GLfloat ry)
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
	Art->VertexColor[1][0] = RandomRGB(mt) / 10.f;
	Art->VertexColor[1][1] = RandomRGB(mt) / 10.f;
	Art->VertexColor[1][2] = RandomRGB(mt) / 10.f;

	// ���� (���� �Ʒ�)
	Art->VertexColor[2][0] = RandomRGB(mt) / 10.f;
	Art->VertexColor[2][1] = RandomRGB(mt) / 10.f;
	Art->VertexColor[2][2] = RandomRGB(mt) / 10.f;




	// �ε���
	Art->indexVerTex[0] = 0;
	Art->indexVerTex[1] = 2;
	Art->indexVerTex[2] = 1;


	pVec->push_back(Art);
}

GLvoid Create_Rect(vector<DWArt*>* pVec, GLfloat x, GLfloat y, GLfloat rx, GLfloat ry)
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
	Art->VertexColor[0][0] = RandomRGB(mt) / 10.f;
	Art->VertexColor[0][1] = RandomRGB(mt) / 10.f;
	Art->VertexColor[0][2] = RandomRGB(mt) / 10.f;


	// ���� (������ ��)
	Art->VertexColor[1][0] = RandomRGB(mt) / 10.f;
	Art->VertexColor[1][1] = RandomRGB(mt) / 10.f;
	Art->VertexColor[1][2] = RandomRGB(mt) / 10.f;

	// ���� (������ �Ʒ�)
	Art->VertexColor[2][0] = RandomRGB(mt) / 10.f;
	Art->VertexColor[2][1] = RandomRGB(mt) / 10.f;
	Art->VertexColor[2][2] = RandomRGB(mt) / 10.f;

	// ���� (���� �Ʒ�)
	Art->VertexColor[3][0] = RandomRGB(mt) / 10.f;
	Art->VertexColor[3][1] = RandomRGB(mt) / 10.f;
	Art->VertexColor[3][2] = RandomRGB(mt) / 10.f;



	// �ε���
	Art->indexVerTex[0] = 0;
	Art->indexVerTex[1] = 3;
	Art->indexVerTex[2] = 1;

	Art->indexVerTex[3] = 1;
	Art->indexVerTex[4] = 3;
	Art->indexVerTex[5] = 2;


	pVec->push_back(Art);
}




char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;

	fopen_s(&fptr, file, "rb");

	if (!fptr)
		return NULL;

	fseek(fptr, 0, SEEK_END);

	length = ftell(fptr);

	buf = (char*)malloc(length + 1);

	fseek(fptr, 0, SEEK_SET);

	fread(buf, length, 1, fptr);

	fclose(fptr);

	buf[length] = 0;

	return buf;
}