#pragma once

#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>


#include <iostream>
#include <gl/glew.h> //--- �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <stdio.h>
#include <iostream>
#include <random>
#include <list>
#include <vector>
#include <math.h>
#include <corecrt_math_defines.h>



#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>  
#include <stdio.h>

using namespace std;


GLint WinsizeX{ 800 };
GLint WinsizeY{ 800 };
GLint WinsizeZ{ 800 };



std::random_device rd{};

std::mt19937 mt(rd());

std::uniform_int_distribution<int> RandomRGB(0, 10);


std::uniform_real_distribution<GLfloat> RandomPosX(0, WinsizeX);
std::uniform_real_distribution<GLfloat> RandomPosY(0, WinsizeY);

uniform_int_distribution<int> RandomSize(50, 100);


uniform_int_distribution<int> RandomMove(1, 4);

uniform_real_distribution<float> RandomAngle(0.f, 360.f);


float Pos_Line[5][2]{ {-1.f,1.f},{1.f,-1.f},{1.f,-1.f},{1.f,-1.f},{1.f,-1.f} };
float Pos_Triangle[5][2]{ {-1.f,1.f },{0.f,-1.f},{0.f,-1.f} ,{0.f,-1.f} ,{1.f,1.f} };

float Pos_Rectangle[5][2]{ {-1.f,1.f },{-1.f,-1.f }, {1.f,-1.f} ,{1.f,-1.f} ,{1.f,1.f} };

float Pos_Pentagon[5][2]{ {-1.f,1.f },{-1.5f,-1.f }, {0.f,-2.f} ,{1.5f,-1.f} ,{1.f,1.f} };
float Pos_Dot[5][2]{ {-0.1f,0.1f },{-0.1f,-0.1f }, {0.1f,-0.1f} ,{0.1f,-0.1f} ,{0.1f,0.1f} };


enum ArtType {DWART_LINE, DWART_CUBE, DWART_END};
enum eMoveType { DIR_RIGHT, DIR_LEFT, DIR_UP, DIR_DOWN, DIR_LU, DIR_RU, DIR_LD, DIR_RD };

struct DWArt
{
	virtual ~DWArt() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(2, VBO);
		glDeleteBuffers(1, &EBO);
	};


	glm::mat4 transformMatrix = glm::mat4(1.0f); // ������ ��Ʈ����

	GLfloat vScale[3]{ 1.f,1.f,1.f }; // ��ü�� x,y,z ������ �󸶳� Ŀ������?

	GLfloat vRotate[3]{}; // ��ü�� x y z ������ �󸶸�ŭ ȸ���Ͽ�����?

	GLfloat vMove[3]{}; // ��ü�� �������� �󸶸�ŭ �����̴���?

	GLfloat vRevolution[3]{}; // ��ü�� x y z ������ �󸶸�ŭ �����Ͽ�����?


	ArtType eType{};

	GLfloat RGB[3]{};

	GLfloat CenterX{};
	GLfloat CenterY{};
	GLfloat CenterZ{};

	GLfloat rx{};
	GLfloat ry{};

	bool LR{};

	bool ZigZag{};

	bool Move{}; // �������� �ϴ°�?

	bool LRCenterMove{}; // �¿� ����� �������� �ϴ°�?
	bool UDCenterMove{}; // �� �Ʒ��� �������� �ϴ°�?

	int Move_Timer{}; // ������ �� ����� ��

	vector<glm::vec3> Vertex{}; // ���ؽ�
	vector<glm::vec3> VertexColor{}; // ���ؽ� ����
	vector<GLuint> indexVerTex{}; // �ε��� ����

	GLuint VAO{};
	GLuint VBO[3]{};

	GLuint EBO{};
};










// �Լ� �����
char* filetobuf(const char* file);
GLvoid Delete_ALL_Art(vector<DWArt*>& pvector); // �ش� ������ ��� ��ü �����
GLvoid DeleteArt(vector<DWArt*>& pvector, DWArt* pArt); // �ش� ���Ϳ��� ���ϴ� ���� �����
GLvoid ReleaseArt(vector<DWArt*>& pvector, DWArt* pArt); // �ش� ���Ϳ��� ���ϴ� ���� delete�� �ϱ�(���Ϳ��� nullptr��)
GLfloat Coordinate_RE_ChangeX(GLfloat Coord); // X�� ��ǥ�� ��ȯ ���� -> ������
GLfloat Coordinate_RE_ChangeY(GLfloat Coord); // Y�� ��ǥ�� ��ȯ ���� -> ������
GLfloat Coordinate_RE_ChangeZ(GLfloat Coord); // Y�� ��ǥ�� ��ȯ ���� -> ������
GLfloat CoordinateChangeX(GLfloat Coord); // X�� ��ǥ�� ��ȯ ������ -> ����
GLfloat CoordinateChangeY(GLfloat Coord); // Y�� ��ǥ�� ��ȯ ������ -> ����
GLfloat CoordinateChangeZ(GLfloat Coord); // Y�� ��ǥ�� ��ȯ ������ -> ����
GLint CheckMouseQuadrant(GLfloat X, GLfloat Y); // ���콺�� �� ��и��� �������� �˷��ִ� �Լ� // ��Ȯ�� �����̸� 0
DWArt* Check_Mouse_Rect(vector<DWArt*>& pvector, GLfloat x, GLfloat y); // ���콺�� ��ü üũ
DWArt* Check_Rect_Rect(vector<DWArt*>& pvector, DWArt* _CheckRect); // ��ü�� ��ü üũ
GLvoid MoveArt(DWArt* pArt, ArtType eDraw, eMoveType eMove); // �־��� ��ü �����̱�

GLvoid MakeWorldMartrix(DWArt* pArt); // �ش� ��ü�� ���� ��ȯ ��� ����� �ֱ�(�� ���� ���̴��� �Ѱ� ��)


GLvoid Create_Line_Pos(vector<DWArt*>* pVec, GLfloat x1, GLfloat y1, GLfloat z1,  GLfloat x2, GLfloat y2, GLfloat z2); // ���ϴ� ���Ϳ� ���ϴ� �� ���� �մ� ���� �߰�

GLvoid Create_Cube(vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _rx, GLfloat _ry, GLfloat _rz); // ���ϴ� ���Ϳ� ���ϴ� �� ���� �մ� ���� �߰�







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
	glBindVertexArray(pArt->VAO); // VAO ���ε�

	// Vertex ���� ������Ʈ
	glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, pArt->Vertex.size() * sizeof(glm::vec3), pArt->Vertex.data(), GL_DYNAMIC_DRAW);

	// Index ���� ������Ʈ
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pArt->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, pArt->indexVerTex.size() * sizeof(unsigned int), pArt->indexVerTex.data(), GL_DYNAMIC_DRAW);

	// VertexColor ���� ������Ʈ
	glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, pArt->VertexColor.size() * sizeof(glm::vec3), pArt->VertexColor.data(), GL_DYNAMIC_DRAW);

	glBindVertexArray(0); // VAO ���ε� ����



}

inline GLvoid InitBuffer(DWArt* pArt)
{
	glGenVertexArrays(1, &pArt->VAO); // VAO �Ҵ�
	glGenBuffers(2, pArt->VBO); // VBO �Ҵ�
	glGenBuffers(1, &pArt->EBO); // EBO �Ҵ�

	glBindVertexArray(pArt->VAO); // VAO ���ε�

	// Vertex ����
	glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, pArt->Vertex.size() * sizeof(glm::vec3), pArt->Vertex.data(), GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Index ����
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pArt->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, pArt->indexVerTex.size() * sizeof(unsigned int), pArt->indexVerTex.data(), GL_STREAM_DRAW);

	// VertexColor ����
	glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, pArt->VertexColor.size() * sizeof(glm::vec3), pArt->VertexColor.data(), GL_STREAM_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // VAO ���ε� ����

}


GLvoid ReBindArt(DWArt* pArt, ArtType eDraw)
{

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

GLfloat Coordinate_RE_ChangeZ(GLfloat Coord)
{

	Coord = Coord * (WinsizeZ / 2);
	Coord = Coord - (WinsizeZ / 2);
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

GLfloat CoordinateChangeZ(GLfloat Coord)
{
	Coord = -Coord;
	Coord = Coord + (WinsizeZ / 2);
	Coord = Coord / (WinsizeZ / 2);
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

GLvoid Create_Line_Pos(vector<DWArt*>* pVec, GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2)
{
	DWArt* Art = new DWArt{};

	// ����
	//Art->CenterX = x;
	//Art->CenterY = y;

	// ����
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));

	// ������
	//Art->rx = rx;
	//Art->ry = ry;


	// ����
	Art->eType = DWART_LINE;


	Art->Vertex.push_back(glm::vec4(x1, y1, -z1, 1.f));
	Art->Vertex.push_back(glm::vec4(x2, y2, -z2, 1.f));


	// �ε���
	Art->indexVerTex.push_back(0);
	Art->indexVerTex.push_back(1);


	pVec->push_back(Art);
}


inline GLvoid Create_Cube(vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _rx, GLfloat _ry, GLfloat _rz)
{

	DWArt* Art = new DWArt{};

	// ����
	Art->CenterX = _CX;
	Art->CenterY = _CY;
	Art->CenterZ = _CY;

	// ����
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));

	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));

	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));

	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));

	// ������
	Art->rx = _rx;
	Art->ry = _ry;


	// ����
	Art->eType = DWART_CUBE;

	// 0 1
	Art->Vertex.push_back(glm::vec3((_CX - _rx), (_CY + _ry), (_CZ + _rz)));
	Art->Vertex.push_back(glm::vec3((_CX - _rx), (_CY + _ry), (_CZ - _rz)));


	// 2 3
	Art->Vertex.push_back(glm::vec3((_CX + _rx), (_CY + _ry), (_CZ - _rz)));
	Art->Vertex.push_back(glm::vec3((_CX + _rx), (_CY + _ry), (_CZ + _rz)));


	// 4 5
	Art->Vertex.push_back(glm::vec3((_CX - _rx), (_CY - _ry), (_CZ + _rz)));
	Art->Vertex.push_back(glm::vec3((_CX - _rx), (_CY - _ry), (_CZ - _rz)));


	// 6 7
	Art->Vertex.push_back(glm::vec3((_CX + _rx), (_CY - _ry), (_CZ - _rz)));
	Art->Vertex.push_back(glm::vec3((_CX + _rx), (_CY - _ry), (_CZ + _rz)));


	// �ε���

	// ����
	Art->indexVerTex.push_back(0);
	Art->indexVerTex.push_back(3);
	Art->indexVerTex.push_back(1);

	Art->indexVerTex.push_back(1);
	Art->indexVerTex.push_back(3);
	Art->indexVerTex.push_back(2);


	// ���ʸ�
	Art->indexVerTex.push_back(1);
	Art->indexVerTex.push_back(4);
	Art->indexVerTex.push_back(0);

	Art->indexVerTex.push_back(1);
	Art->indexVerTex.push_back(5);
	Art->indexVerTex.push_back(4);

	// �ո�
	Art->indexVerTex.push_back(0);
	Art->indexVerTex.push_back(4);
	Art->indexVerTex.push_back(7);

	Art->indexVerTex.push_back(0);
	Art->indexVerTex.push_back(7);
	Art->indexVerTex.push_back(3);

	// ������
	Art->indexVerTex.push_back(7);
	Art->indexVerTex.push_back(6);
	Art->indexVerTex.push_back(3);

	Art->indexVerTex.push_back(3);
	Art->indexVerTex.push_back(6);
	Art->indexVerTex.push_back(2);

	// �޸�
	Art->indexVerTex.push_back(6);
	Art->indexVerTex.push_back(5);
	Art->indexVerTex.push_back(2);

	Art->indexVerTex.push_back(2);
	Art->indexVerTex.push_back(5);
	Art->indexVerTex.push_back(1);

	// �Ʒ���
	Art->indexVerTex.push_back(5);
	Art->indexVerTex.push_back(6);
	Art->indexVerTex.push_back(4);

	Art->indexVerTex.push_back(4);
	Art->indexVerTex.push_back(6);
	Art->indexVerTex.push_back(7);

	pVec->push_back(Art);


	
}






GLvoid MakeWorldMartrix(DWArt* pArt)
{

// ũ��
	// scale
	glm::vec3 scaleFactor(pArt->vScale[0], pArt->vScale[1], pArt->vScale[2]); // ���ϴ� ũ��
	pArt->transformMatrix = glm::scale(pArt->transformMatrix, scaleFactor);

// ����
	// rotate X
	float angleX = glm::radians(pArt->vRotate[0]); // 45�� ȸ�� (���� ����)
	glm::vec3 rotationAxisX(1.0f, 0.0f, 0.0f); // Y�� ����
	pArt->transformMatrix = glm::rotate(pArt->transformMatrix, angleX, rotationAxisX);

	// rotate Y
	float angleY = glm::radians(pArt->vRotate[1]); // 45�� ȸ�� (���� ����)
	glm::vec3 rotationAxisY(0.0f, 1.0f, 0.0f); // Y�� ����
	pArt->transformMatrix = glm::rotate(pArt->transformMatrix, angleY, rotationAxisY);

	// rotate Z
	float angleZ = glm::radians(pArt->vRotate[2]); // 45�� ȸ�� (���� ����)
	glm::vec3 rotationAxisZ(0.0f, 0.0f, 1.0f); // Y�� ����
	pArt->transformMatrix = glm::rotate(pArt->transformMatrix, angleZ, rotationAxisZ);


// �̵�
	// translation
	glm::vec3 translationVector(pArt->CenterX, pArt->CenterY, pArt->CenterZ);
	pArt->transformMatrix = glm::translate(pArt->transformMatrix, translationVector);
	

// ����
	// revolution X
	float revolution_angleX = glm::radians(pArt->vRevolution[0]); // 45�� ȸ�� (���� ����)
	glm::vec3 revolutionAxisX(1.0f, 0.0f, 0.0f); // Y�� ����
	pArt->transformMatrix = glm::rotate(pArt->transformMatrix, revolution_angleX, revolutionAxisX);

	// revolution Y
	float revolution_angleY = glm::radians(pArt->vRevolution[1]); // 45�� ȸ�� (���� ����)
	glm::vec3 revolutionAxisY(0.0f, 1.0f, 0.0f); // Y�� ����
	pArt->transformMatrix = glm::rotate(pArt->transformMatrix, revolution_angleY, revolutionAxisY);

	// revolution Z
	float revolution_angleZ = glm::radians(pArt->vRevolution[2]); // 45�� ȸ�� (���� ����)
	glm::vec3 revolutionAxisZ(0.0f, 0.0f, 1.0f); // Y�� ����
	pArt->transformMatrix = glm::rotate(pArt->transformMatrix, revolution_angleZ, revolutionAxisZ);



// �θ�


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