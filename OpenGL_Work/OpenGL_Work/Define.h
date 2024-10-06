#pragma once
#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
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


GLint WinsizeX{800};
GLint WinsizeY{800};

enum ArtType {DWART_DOT,DWART_LINE, DWART_TRIANGLE,DWART_RECTANGLE};

struct DWArt
{
	virtual ~DWArt() {};

	ArtType eType{};

	GLfloat RGB[3]{};

	GLfloat CenterX{};
	GLfloat CenterY{};

	GLfloat rx{};
	GLfloat ry{};

	GLuint VAO{};
	GLuint VBO[2]{};

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



GLvoid DeleteArt (vector<DWArt*> &pvector, DWArt* pArt)
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

DWArt* Check_Mouse_Rect(vector<DWArt*>& pvector,GLfloat x, GLfloat y)
{
	for (auto iter : pvector)
	{
		if ((iter->CenterX - iter->rx <= x && iter->CenterX + iter->rx >= x) &&
			(iter->CenterY - iter->ry <= y && iter->CenterY + iter->ry >= y))
		{
			return iter; // 마우스의 위치가 사각형과 닿았다면?
		}
	}


	return nullptr; // 마우스의 위치가 사각형과 닿지 않았다면?
}

DWArt* Check_Rect_Rect(vector<DWArt*>& pvector,DWArt* _CheckRect)
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
			continue; // 사각형의 위치가 사각형과 닿지 않았다면?
		}
		if (_CheckRect->CenterY - _CheckRect->ry > iter->CenterY + iter->ry || _CheckRect->CenterY + _CheckRect->ry < iter->CenterY - iter->ry)
		{
			continue; // 사각형의 위치가 사각형과 닿지 않았다면?
		}
		return iter; // 사각형의 위치가 사각형과 닿았다면?
	}
	return nullptr; // 사각형의 위치가 사각형과 닿지 않았다면?
}

char* filetobuf(const char* file)
{
	FILE* fptr;  
	long length; 
	char* buf;

	fopen_s(&fptr,file, "rb");

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