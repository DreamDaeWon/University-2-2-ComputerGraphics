#pragma once

#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

#include <string.h>
#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include <iostream>
#include <random>
#include <list>
#include <vector>
#include <math.h>
#include <corecrt_math_defines.h>





#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE_LENGTH 256
#include <stdlib.h>  
#include <stdio.h>

using namespace std;


GLint WinsizeX{ 1600 };
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




enum ArtType {DWART_LINE, DWART_CIRCLE_SPIRAL, DWART_FACE, DWART_CUBE,DWART_TETRATEDRON, DWART_MODEL_SPHERE,DWART_MODEL_SYLINDER, DWART_END};

enum eMoveType { DIR_RIGHT, DIR_LEFT, DIR_UP, DIR_DOWN, DIR_LU, DIR_RU, DIR_LD, DIR_RD };

struct DWArt
{
	virtual ~DWArt() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(2, VBO);
		glDeleteBuffers(1, &EBO);
	};


	// 모델
	GLUquadric* Model = gluNewQuadric();




	// 구
	GLint Sphere_Slices{};
	GLint Sphere_Stacks{};
	GLfloat Sphere_rx{}; // 반지름


	// 실린더
	GLint Sylinder_Slices{};
	GLint Sylinder_Stacks{};
	GLfloat Sylinder_rx_Bottom{}; // 바닥면 반지름 (빈 면의 반지름)
	GLfloat Sylinder_rx_Top{}; // 윗면 반지름 (빈 면의 반지름)
	GLfloat Sylinder_ry{}; // 실린더의 높이


	// 원 스파이럴
	GLint Spiral_Center{};
	GLint Spiral_radius{};
	GLint Spiral_Now_Angle{};
	GLint Spiral_Now_Center_X{};


	glm::mat4 transformMatrix = glm::mat4(1.0f); // 본인의 매트릭스


	glm::mat4* ParentMatrix = nullptr; // 부모의 매트릭스



	GLfloat vScale[3]{ 1.f,1.f,1.f }; // 객체가 x,y,z 축으로 얼마나 커졌는지?


	GLfloat vOneJomScale[3]{ 1.f,1.f,1.f }; // 객체가 x,y,z 축으로 얼마나 커졌는지?

	GLfloat vRotate[3]{}; // 객체가 x y z 축으로 얼마만큼 회전하였는지?

	GLfloat vPos[3]{}; // 객체가 원점에서 얼마만큼 움직이는지? // 로컬 좌표계임

	GLfloat vRevolution[4]{}; // 객체가 x y z 축으로 얼마만큼 공전하였는지?


	GLfloat vLastMove[3]{}; // 원점에서 얼만큼 갔다가 다시 회전하고 돌아올 것인지? (ex : 박스 문 열기)
	GLfloat vLastRotate[3]{}; // 마지막 회전


	GLfloat vWorldPos[3]{}; // 진짜 월드 좌표계 이걸 건드려야 똑바로 움직임



	// 움직임
	GLfloat vMoveVec[3]{}; // 이동방향 벡터
	GLfloat fSpeed{}; // 이동 속도


	// 회전

	glm::vec3 revolutionAxis_Want = glm::vec3(1.f);



	ArtType eType{};

	GLfloat RGB[3]{};

	GLfloat CenterX{};
	GLfloat CenterY{};
	GLfloat CenterZ{};

	GLfloat rx{};
	GLfloat ry{};
	GLfloat rz{};

	bool LR{};

	bool ZigZag{};

	bool Move{}; // 움직여야 하는가?

	bool LRCenterMove{}; // 좌우 가운데로 움직여야 하는가?
	bool UDCenterMove{}; // 위 아래로 움직여야 하는가?

	int Move_Timer{}; // 움직일 때 사용할 값

	vector<glm::vec3> Vertex{}; // 버텍스

	vector<glm::vec3> VertexColor{}; // 버텍스 색상

	vector<glm::vec3> Vertex_Nomal{}; // 버텍스 노멀 벡터

	vector<GLuint> indexVerTex{}; // 인덱스 정점





	GLuint VAO{};
	GLuint VBO[4]{};

	GLuint EBO{};
};










// 함수 선언부
char* filetobuf(const char* file);
void read_obj_file(const char* filename, DWArt* pArt);

GLvoid Delete_ALL_Art(vector<DWArt*>& pvector); // 해당 벡터의 모든 객체 지우기
GLvoid DeleteArt(vector<DWArt*>& pvector, DWArt* pArt); // 해당 벡터에서 원하는 원소 지우기
GLvoid ReleaseArt(vector<DWArt*>& pvector, DWArt* pArt); // 해당 벡터에서 원하는 원소 delete만 하기(벡터에는 nullptr값)
GLfloat Coordinate_RE_ChangeX(GLfloat Coord); // X축 좌표계 변환 월드 -> 윈도우
GLfloat Coordinate_RE_ChangeY(GLfloat Coord); // Y축 좌표계 변환 월드 -> 윈도우
GLfloat Coordinate_RE_ChangeZ(GLfloat Coord); // Y축 좌표계 변환 월드 -> 윈도우
GLfloat CoordinateChangeX(GLfloat Coord); // X축 좌표계 변환 윈도우 -> 월드
GLfloat CoordinateChangeY(GLfloat Coord); // Y축 좌표계 변환 윈도우 -> 월드
GLfloat CoordinateChangeZ(GLfloat Coord); // Y축 좌표계 변환 윈도우 -> 월드
GLint CheckMouseQuadrant(GLfloat X, GLfloat Y); // 마우스가 몇 사분면을 눌렀는지 알려주는 함수 // 정확히 원점이면 0
DWArt* Check_Mouse_Rect(vector<DWArt*>& pvector, GLfloat x, GLfloat y); // 마우스와 객체 체크
DWArt* Check_Rect_Rect(vector<DWArt*>& pvector, DWArt* _CheckRect); // 객체와 객체 체크
GLvoid MoveArt(DWArt* pArt, ArtType eDraw, eMoveType eMove); // 넣어준 객체 움직이기

GLvoid MakeWorldMartrix(DWArt* pArt); // 해당 객체의 최종 변환 행렬 만들어 주기(이 값을 셰이더에 넘겨 줌)


GLvoid Create_Line_Pos(vector<DWArt*>* pVec, GLfloat x1, GLfloat y1, GLfloat z1,  GLfloat x2, GLfloat y2, GLfloat z2); // 원하는 벡터에 원하는 두 점을 잇는 직선 추가

GLvoid Create_Line_Pos(vector<DWArt*>* pVec, GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, glm::vec3 vColor_One, glm::vec3 vColor_Two); // 원하는 벡터에 원하는 두 점을 잇는 직선 추가

GLvoid Create_Face(vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _rx, GLfloat _ry, GLfloat _rz); // 원하는 벡터에 원하는 면 추가

GLvoid Create_Face_Want_Color(vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _rx, GLfloat _ry, GLfloat _rz, glm::vec3 vColor); // 원하는 벡터에 원하는 색상의 면 추가


GLvoid Create_Face_Trangle(vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _rx, GLfloat _ry, GLfloat _rz); // 원하는 벡터에 원하는 면 추가


GLvoid Create_Cube(vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _rx, GLfloat _ry, GLfloat _rz); // 원하는 벡터에 원하는 큐브 추가

GLvoid Create_Obj(const char* filename, vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _rx, GLfloat _ry, GLfloat _rz); // 원하는 벡터에 원하는 큐브 추가

GLvoid Create_Obj_Want_Color(const char* filename, glm::vec3 _color, vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _rx, GLfloat _ry, GLfloat _rz); // 원하는 벡터에 원하는 큐브 추가

GLvoid Create_Circle_Spiral(vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _final_Radius,GLfloat _UPRadius); // 원하는 벡터에 원하는 원 스파이럴 추가


GLvoid Create_Circle_Line(vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _Radius); // 원하는 벡터에 원하는 원 추가

GLvoid Create_Tetrahedron(vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _rx, GLfloat _ry, GLfloat _rz); // 원하는 벡터에 원하는 사면체 출력

GLvoid Create_Sphere_Model(vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _rx, GLfloat _slices, GLfloat _stacks); // 원하는 벡터에 원하는 사면체 출력

GLvoid Create_Sylinder_Model(vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _rxTop, GLfloat _rxBottom, GLfloat _ry, GLfloat _slices, GLfloat _stacks); // 원하는 벡터에 원하는 사면체 출력



GLvoid Rotate_Art(DWArt* pArt, GLfloat fAngle);




GLvoid Set_Draw_Model_Style(DWArt* pArt, int _iStyle); // 도형 스타일);

GLvoid InitBuffer(DWArt* pArt);

GLvoid InitBuffer_Light(DWArt* pArt);


GLvoid UpdateBuffer(DWArt* pArt);
GLvoid Update_light_Buffer(DWArt* pArt);


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
	glBindVertexArray(pArt->VAO); // VAO 바인딩

	// Vertex 버퍼 업데이트
	glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, pArt->Vertex.size() * sizeof(glm::vec3), pArt->Vertex.data(), GL_DYNAMIC_DRAW);

	// Index 버퍼 업데이트
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pArt->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, pArt->indexVerTex.size() * sizeof(unsigned int), pArt->indexVerTex.data(), GL_DYNAMIC_DRAW);

	// VertexColor 버퍼 업데이트
	glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, pArt->VertexColor.size() * sizeof(glm::vec3), pArt->VertexColor.data(), GL_DYNAMIC_DRAW);

	glBindVertexArray(0); // VAO 바인딩 해제

}

GLvoid Update_light_Buffer(DWArt* pArt)
{
	glBindVertexArray(pArt->VAO); // VAO 바인딩

	// Vertex 버퍼 업데이트
	glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, pArt->Vertex.size() * sizeof(glm::vec3), pArt->Vertex.data(), GL_DYNAMIC_DRAW);

	// Index 버퍼 업데이트
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pArt->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, pArt->indexVerTex.size() * sizeof(unsigned int), pArt->indexVerTex.data(), GL_DYNAMIC_DRAW);

	// VertexColor 버퍼 업데이트
	glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, pArt->VertexColor.size() * sizeof(glm::vec3), pArt->VertexColor.data(), GL_DYNAMIC_DRAW);


	// Normal 버퍼
	glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, pArt->Vertex_Nomal.size() * sizeof(glm::vec3), pArt->Vertex_Nomal.data(), GL_STATIC_DRAW);


	glBindVertexArray(0); // VAO 바인딩 해제

}


inline GLvoid InitBuffer(DWArt* pArt)
{
	glGenVertexArrays(1, &pArt->VAO); // VAO 할당
	glGenBuffers(3, pArt->VBO); // VBO 할당
	glGenBuffers(1, &pArt->EBO); // EBO 할당

	glBindVertexArray(pArt->VAO); // VAO 바인딩

	// Vertex 버퍼
	glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, pArt->Vertex.size() * sizeof(glm::vec3), pArt->Vertex.data(), GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Index 버퍼
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pArt->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, pArt->indexVerTex.size() * sizeof(unsigned int), pArt->indexVerTex.data(), GL_STREAM_DRAW);

	// VertexColor 버퍼
	glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, pArt->VertexColor.size() * sizeof(glm::vec3), pArt->VertexColor.data(), GL_STREAM_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);



	glBindVertexArray(0); // VAO 바인딩 해제

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

inline GLvoid InitBuffer_Light(DWArt* pArt)
{
	glGenVertexArrays(1, &pArt->VAO); // VAO 할당
	glGenBuffers(3, pArt->VBO); // VBO 할당
	glGenBuffers(1, &pArt->EBO); // EBO 할당

	glBindVertexArray(pArt->VAO); // VAO 바인딩

	// Vertex 버퍼
	glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, pArt->Vertex.size() * sizeof(glm::vec3), pArt->Vertex.data(), GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Index 버퍼
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pArt->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, pArt->indexVerTex.size() * sizeof(unsigned int), pArt->indexVerTex.data(), GL_STREAM_DRAW);

	// VertexColor 버퍼
	glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, pArt->VertexColor.size() * sizeof(glm::vec3), pArt->VertexColor.data(), GL_STREAM_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	// Normal 버퍼
	glBindBuffer(GL_ARRAY_BUFFER, pArt->VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, pArt->Vertex_Nomal.size() * sizeof(glm::vec3), pArt->Vertex_Nomal.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //--- 노말 속성
	glEnableVertexAttribArray(2); // 이 숫자와 셰이더 간에 숫자를 일치 시켜야 함
									// ex) layout (location = 2) in vec3 vNormal;


	glBindVertexArray(0); // VAO 바인딩 해제

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
	// 월드 좌표(OG 좌표계)로 변환 
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
			return iter; // 마우스의 위치가 사각형과 닿았다면?
		}
	}


	return nullptr; // 마우스의 위치가 사각형과 닿지 않았다면?
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

GLvoid Create_Line_Pos(vector<DWArt*>* pVec, GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2)
{
	DWArt* Art = new DWArt{};

	// 중점
	//Art->CenterX = x;
	//Art->CenterY = y;

	// 색상
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));

	// 반지름
	//Art->rx = rx;
	//Art->ry = ry;


	// 형식
	Art->eType = DWART_LINE;


	Art->Vertex.push_back(glm::vec4(x1, y1, -z1, 1.f));
	Art->Vertex.push_back(glm::vec4(x2, y2, -z2, 1.f));


	// 인덱스
	Art->indexVerTex.push_back(0);
	Art->indexVerTex.push_back(1);


	pVec->push_back(Art);
}

inline GLvoid Create_Line_Pos(vector<DWArt*>* pVec, GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, glm::vec3 vColor_One, glm::vec3 vColor_Two)
{
	DWArt* Art = new DWArt{};

	// 중점
	//Art->CenterX = x;
	//Art->CenterY = y;

	// 색상
	Art->VertexColor.push_back(vColor_One);
	Art->VertexColor.push_back(vColor_Two);

	// 반지름
	//Art->rx = rx;
	//Art->ry = ry;


	// 형식
	Art->eType = DWART_LINE;


	Art->Vertex.push_back(glm::vec4(x1, y1, -z1, 1.f));
	Art->Vertex.push_back(glm::vec4(x2, y2, -z2, 1.f));


	// 인덱스
	Art->indexVerTex.push_back(0);
	Art->indexVerTex.push_back(1);


	pVec->push_back(Art);
}

inline GLvoid Create_Face(vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _rx, GLfloat _ry, GLfloat _rz)
{
	
	DWArt* Art = new DWArt{};

	// 중점
	Art->vPos[0] = _CX;
	Art->vPos[1] = _CY;
	Art->vPos[2] = _CZ;

	// 색상
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));

	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));


	// 반지름
	Art->rx = _rx;
	Art->ry = _ry;
	Art->rz = _rz;

	// 형식
	Art->eType = DWART_FACE;

	// 0 1
	Art->Vertex.push_back(glm::vec3((0 - _rx), (0), (0 + _rz)));



	Art->Vertex.push_back(glm::vec3((0 - _rx), (0), (0 - _rz)));


	// 2 3
	Art->Vertex.push_back(glm::vec3((0 + _rx), (0), (0 - _rz)));


	Art->Vertex.push_back(glm::vec3((0 + _rx), (0), (0 + _rz)));



	// 인덱스

	// 윗면
	Art->indexVerTex.push_back(0);
	Art->indexVerTex.push_back(3);
	Art->indexVerTex.push_back(1);

	Art->indexVerTex.push_back(1);
	Art->indexVerTex.push_back(3);
	Art->indexVerTex.push_back(2);

	pVec->push_back(Art);

}

inline GLvoid Create_Face_Want_Color(vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _rx, GLfloat _ry, GLfloat _rz, glm::vec3 vColor)
{
	DWArt* Art = new DWArt{};

	// 중점
	Art->vPos[0] = _CX;
	Art->vPos[1] = _CY;
	Art->vPos[2] = _CZ;

	// 색상
	Art->VertexColor.push_back(vColor);
	Art->VertexColor.push_back(vColor);

	Art->VertexColor.push_back(vColor);
	Art->VertexColor.push_back(vColor);

	Art->VertexColor.push_back(vColor);
	Art->VertexColor.push_back(vColor);

	// 반지름
	Art->rx = _rx;
	Art->ry = _ry;


	// 형식
	Art->eType = DWART_FACE;

	// 0 1
	Art->Vertex.push_back(glm::vec3((0 - _rx), (0), (0 + _rz)));



	Art->Vertex.push_back(glm::vec3((0 - _rx), (0), (0 - _rz)));


	// 2 3
	Art->Vertex.push_back(glm::vec3((0 + _rx), (0), (0 - _rz)));


	Art->Vertex.push_back(glm::vec3((0 + _rx), (0), (0 + _rz)));

	
	Art->Vertex_Nomal.push_back(glm::vec3(0.f, 1.f, 0.f));
	Art->Vertex_Nomal.push_back(glm::vec3(0.f, 1.f, 0.f));
	Art->Vertex_Nomal.push_back(glm::vec3(0.f, 1.f, 0.f));
	Art->Vertex_Nomal.push_back(glm::vec3(0.f, 1.f, 0.f));
	Art->Vertex_Nomal.push_back(glm::vec3(0.f, 1.f, 0.f));
	Art->Vertex_Nomal.push_back(glm::vec3(0.f, 1.f, 0.f));


	// 인덱스

	// 윗면
	Art->indexVerTex.push_back(0);
	Art->indexVerTex.push_back(3);
	Art->indexVerTex.push_back(1);

	Art->indexVerTex.push_back(1);
	Art->indexVerTex.push_back(3);
	Art->indexVerTex.push_back(2);

	pVec->push_back(Art);
}

inline GLvoid Create_Face_Trangle(vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _rx, GLfloat _ry, GLfloat _rz)
{
	DWArt* Art = new DWArt{};

	// 중점
	Art->vPos[0] = _CX;
	Art->vPos[1] = _CY;
	Art->vPos[2] = _CZ;

	// 색상
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
	
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));

	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));


	// 반지름
	Art->rx = _rx;
	Art->ry = _ry;


	// 형식
	Art->eType = DWART_FACE;

	// 0 1
	Art->Vertex.push_back(glm::vec3((0 - _rx), (0 - _ry), (0)));


	Art->Vertex.push_back(glm::vec3((0), (0 + _ry), (0)));

	// 2 3
	Art->Vertex.push_back(glm::vec3((0 + _rx), (0 - _ry), (0)));



	// 인덱스

	// 윗면
	Art->indexVerTex.push_back(0);
	Art->indexVerTex.push_back(2);
	Art->indexVerTex.push_back(1);

	pVec->push_back(Art);
}




inline GLvoid Create_Cube(vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _rx, GLfloat _ry, GLfloat _rz)
{

	DWArt* Art = new DWArt{};

	// 중점
	Art->vPos[0] = _CX;
	Art->vPos[1] = _CY;
	Art->vPos[2] = _CZ;

	// 색상
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));

	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));

	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));

	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));

	// 반지름
	Art->rx = _rx;
	Art->ry = _ry;
	Art->rz = _rz;


	// 형식
	Art->eType = DWART_CUBE;

	// 0 1
	Art->Vertex.push_back(glm::vec3((0 - _rx), (0 + _ry), (0 + _rz)));
	Art->Vertex.push_back(glm::vec3((0 - _rx), (0 + _ry), (0 - _rz)));


	// 2 3
	Art->Vertex.push_back(glm::vec3((0 + _rx), (0 + _ry), (0 - _rz)));
	Art->Vertex.push_back(glm::vec3((0 + _rx), (0 + _ry), (0 + _rz)));


	// 4 5
	Art->Vertex.push_back(glm::vec3((0 - _rx), (0 - _ry), (0 + _rz)));
	Art->Vertex.push_back(glm::vec3((0 - _rx), (0 - _ry), (0 - _rz)));


	// 6 7
	Art->Vertex.push_back(glm::vec3((0 + _rx), (0 - _ry), (0 - _rz)));
	Art->Vertex.push_back(glm::vec3((0 + _rx), (0 - _ry), (0 + _rz)));


	// 인덱스

	// 윗면
	Art->indexVerTex.push_back(0);
	Art->indexVerTex.push_back(3);
	Art->indexVerTex.push_back(1);

	Art->indexVerTex.push_back(1);
	Art->indexVerTex.push_back(3);
	Art->indexVerTex.push_back(2);


	// 왼쪽면
	Art->indexVerTex.push_back(1);
	Art->indexVerTex.push_back(4);
	Art->indexVerTex.push_back(0);

	Art->indexVerTex.push_back(1);
	Art->indexVerTex.push_back(5);
	Art->indexVerTex.push_back(4);

	// 앞면
	Art->indexVerTex.push_back(0);
	Art->indexVerTex.push_back(4);
	Art->indexVerTex.push_back(7);

	Art->indexVerTex.push_back(0);
	Art->indexVerTex.push_back(7);
	Art->indexVerTex.push_back(3);

	// 오른쪽
	Art->indexVerTex.push_back(7);
	Art->indexVerTex.push_back(6);
	Art->indexVerTex.push_back(3);

	Art->indexVerTex.push_back(3);
	Art->indexVerTex.push_back(6);
	Art->indexVerTex.push_back(2);

	// 뒷면
	Art->indexVerTex.push_back(6);
	Art->indexVerTex.push_back(5);
	Art->indexVerTex.push_back(2);

	Art->indexVerTex.push_back(2);
	Art->indexVerTex.push_back(5);
	Art->indexVerTex.push_back(1);

	// 아래면
	Art->indexVerTex.push_back(5);
	Art->indexVerTex.push_back(6);
	Art->indexVerTex.push_back(4);

	Art->indexVerTex.push_back(4);
	Art->indexVerTex.push_back(6);
	Art->indexVerTex.push_back(7);

	pVec->push_back(Art);


	
}

inline GLvoid Create_Obj(const char* filename,vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _rx, GLfloat _ry, GLfloat _rz)
{
	DWArt* Art = new DWArt{};

	// 중점
	Art->vPos[0] = _CX;
	Art->vPos[1] = _CY;
	Art->vPos[2] = _CZ;



	// 크기 설정
	Art->rx = _rx;
	Art->ry = _ry;
	Art->rz = _rz;

	Art->vScale[0] = _rx * 0.5f;
	Art->vScale[1] = _ry * 0.5f;
	Art->vScale[2] = _rz * 0.5f;

	
	// 형식
	Art->eType = DWART_CUBE;

	read_obj_file(filename, Art);


	// 색상

	for (int i = 0; i < Art->indexVerTex.size(); ++i)
	{
		Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
		//Art->VertexColor.push_back(glm::vec3(0.2f,0.5f,0.7f));
	}

	pVec->push_back(Art);

}

inline GLvoid Create_Obj_Want_Color(const char* filename, glm::vec3 _color, vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _rx, GLfloat _ry, GLfloat _rz)
{
	DWArt* Art = new DWArt{};

	// 중점
	Art->vPos[0] = _CX;
	Art->vPos[1] = _CY;
	Art->vPos[2] = _CZ;



	// 크기 설정
	Art->rx = _rx;
	Art->ry = _ry;
	Art->rz = _rz;

	Art->vScale[0] = _rx * 0.5f;
	Art->vScale[1] = _ry * 0.5f;
	Art->vScale[2] = _rz * 0.5f;


	// 형식
	Art->eType = DWART_CUBE;

	read_obj_file(filename, Art);


	// 색상

	for (int i = 0; i < Art->indexVerTex.size(); ++i)
	{
		//Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
		Art->VertexColor.push_back(_color);
	}

	pVec->push_back(Art);
}

inline GLvoid Create_Circle_Spiral(vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _final_Radius, GLfloat _UPRadius)
{
	DWArt* Art = new DWArt{};

	// 중점
	Art->vPos[0] = _CX;
	Art->vPos[1] = _CY;
	Art->vPos[2] = _CY;

	Art->CenterX = _CX;
	Art->CenterY = _CY;

	int iIndex{};


	while(Art->Spiral_radius <= _final_Radius + _UPRadius)
	{
		Art->CenterX = sinf(Art->Spiral_Now_Angle * (M_PI / 180.0f)) * Art->Spiral_radius;
		Art->CenterZ = cosf(Art->Spiral_Now_Angle * (M_PI / 180.0f)) * Art->Spiral_radius;

		Art->CenterX += Art->vPos[0];
		Art->CenterZ += Art->vPos[2] + Art->Spiral_Now_Center_X;

		Art->Spiral_Now_Angle += 1.f;

		if ((int)Art->Spiral_Now_Angle % 180 == 0)
		{
			Art->Spiral_radius += _UPRadius;

			if ((int)Art->Spiral_Now_Angle == 180)
			{
				Art->Spiral_Now_Center_X = _UPRadius;
			}
			else if ((int)Art->Spiral_Now_Angle == 360.f)
			{
				Art->Spiral_Now_Center_X = 0.f;
			}
		}

		if (Art->Spiral_Now_Angle >= 360.f)
		{
			Art->Spiral_Now_Angle = 0.f;
		}

		Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
		Art->Vertex.push_back(glm::vec3((Art->CenterX), (0.f), (Art->CenterZ)));
		Art->indexVerTex.push_back(iIndex);
		++iIndex;
	}


	// 반지름
	//Art->rx = _rx;
	//Art->ry = _ry;


	// 형식
	Art->eType = DWART_CIRCLE_SPIRAL;


	pVec->push_back(Art);
}

inline GLvoid Create_Circle_Line(vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _Radius)
{
	DWArt* Art = new DWArt{};

	// 중점
	Art->vPos[0] = _CX;
	Art->vPos[1] = _CY;
	Art->vPos[2] = _CY;

	Art->CenterX = _CX;
	Art->CenterY = _CY;

	int iIndex{};

	Art->Spiral_radius = _Radius;

	while (Art->Spiral_Now_Angle <= 360.f)
	{
		Art->CenterX = sinf(Art->Spiral_Now_Angle * (M_PI / 180.0f)) * Art->Spiral_radius;
		Art->CenterZ = cosf(Art->Spiral_Now_Angle * (M_PI / 180.0f)) * Art->Spiral_radius;

		Art->CenterX += Art->vPos[0];
		Art->CenterZ += Art->vPos[2] + Art->Spiral_Now_Center_X;

		Art->Spiral_Now_Angle += 1.f;


		Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
		Art->Vertex.push_back(glm::vec3((Art->CenterX), (0.f), (Art->CenterZ)));
		Art->indexVerTex.push_back(iIndex);

		Art->Vertex_Nomal.push_back(glm::vec3(0.f,0.f,0.f));

		++iIndex;
	}


	// 반지름
	//Art->rx = _rx;
	//Art->ry = _ry;


	// 형식
	Art->eType = DWART_LINE;


	pVec->push_back(Art);
}

inline GLvoid Create_Tetrahedron(vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _rx, GLfloat _ry, GLfloat _rz)
{
	DWArt* Art = new DWArt{};

	// 중점
	Art->vPos[0] = _CX;
	Art->vPos[1] = _CY;
	Art->vPos[2] = _CY;

	// 색상
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));

	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));

	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));

	// 반지름
	Art->rx = _rx;
	Art->ry = _ry;


	// 형식
	Art->eType = DWART_TETRATEDRON;

	// 0
	Art->Vertex.push_back(glm::vec3((0), (0 + _ry), (0)));

	// 1
	Art->Vertex.push_back(glm::vec3((0 - _rx), (0 - _ry), (0 + _rz)));

	// 2
	Art->Vertex.push_back(glm::vec3((0 + _rx), (0 - _ry), (0 + _rz)));

	// 3
	Art->Vertex.push_back(glm::vec3((0 + _rx), (0 - _ry), (0 - _rz)));

	// 4
	Art->Vertex.push_back(glm::vec3((0 - _rx), (0 - _ry), (0 - _rz)));





	// 인덱스

	// 앞면
	Art->indexVerTex.push_back(0);
	Art->indexVerTex.push_back(1);
	Art->indexVerTex.push_back(2);


	// 오른쪽
	Art->indexVerTex.push_back(0);
	Art->indexVerTex.push_back(2);
	Art->indexVerTex.push_back(3);


	// 뒷면
	Art->indexVerTex.push_back(0);
	Art->indexVerTex.push_back(3);
	Art->indexVerTex.push_back(4);

	// 왼쪽면
	Art->indexVerTex.push_back(0);
	Art->indexVerTex.push_back(4);
	Art->indexVerTex.push_back(1);



	// 아래면
	Art->indexVerTex.push_back(2);
	Art->indexVerTex.push_back(1);
	Art->indexVerTex.push_back(3);

	Art->indexVerTex.push_back(3);
	Art->indexVerTex.push_back(1);
	Art->indexVerTex.push_back(4);

	pVec->push_back(Art);
}

inline GLvoid Create_Sphere_Model(vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _rx, GLfloat _slices, GLfloat _stacks)
{
	DWArt* Art = new DWArt{};

	Art->eType = DWART_MODEL_SPHERE;

	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));
	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));

	Art->vPos[0] = _CX;
	Art->vPos[1] = _CY;
	Art->vPos[2] = _CZ;

	Art->Sphere_rx = _rx;

	Art->Sphere_Slices = _slices;
	Art->Sphere_Stacks = _stacks;
	
	gluSphere(Art->Model,_rx, _slices, _stacks);

	pVec->push_back(Art);
}

inline GLvoid Create_Sylinder_Model(vector<DWArt*>* pVec, GLfloat _CX, GLfloat _CY, GLfloat _CZ, GLfloat _rxTop, GLfloat _rxBottom, GLfloat _ry, GLfloat _slices, GLfloat _stacks)
{
	DWArt* Art = new DWArt{};

	Art->eType = DWART_MODEL_SYLINDER;

	Art->VertexColor.push_back(glm::vec3(RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f, RandomRGB(mt) / 10.f));

	Art->vPos[0] = _CX;
	Art->vPos[1] = _CY;
	Art->vPos[2] = _CZ - _ry/2.f;

	Art->Sylinder_rx_Top = _rxTop;
	Art->Sylinder_rx_Bottom = _rxBottom;

	Art->rx = _rxTop;
	Art->rz = _rxBottom;
	Art->ry = _ry;

	Art->Sylinder_ry = _ry;

	Art->Sylinder_Slices = _slices;
	Art->Sylinder_Stacks= _stacks;

	gluCylinder(Art->Model, Art->Sylinder_rx_Top, Art->Sylinder_rx_Bottom, Art->Sylinder_ry, Art->Sylinder_Slices, Art->Sylinder_Stacks);

	pVec->push_back(Art);
}

inline GLvoid Rotate_Art(DWArt* pArt, GLfloat fAngle)
{
	
}

inline GLvoid Set_Draw_Model_Style(DWArt* pArt, int _iStyle)
{
	gluQuadricDrawStyle(pArt->Model, _iStyle); // 도형 스타일
	
}






GLvoid MakeWorldMartrix(DWArt* pArt)
{

	pArt->transformMatrix = glm::mat4(1.0f);




	if(pArt->ParentMatrix != nullptr)
	// 부모
	pArt->transformMatrix = *pArt->ParentMatrix * pArt->transformMatrix;


	// 신축 (커지면 원점에서도 같이 멀어지기)
// scale
	glm::vec3 OneJomScaleFactor(pArt->vOneJomScale[0], pArt->vOneJomScale[1], pArt->vOneJomScale[2]); // 원하는 크기
	pArt->transformMatrix = glm::scale(pArt->transformMatrix, OneJomScaleFactor);

// 공전
	// revolution X
	float revolution_angleX = glm::radians(pArt->vRevolution[0]); // 45도 회전 (라디안 단위)
	glm::vec3 revolutionAxisX(1.0f, 0.0f, 0.0f); // X축 기준
	pArt->transformMatrix = glm::rotate(pArt->transformMatrix, revolution_angleX, revolutionAxisX);

	// revolution Y
	float revolution_angleY = glm::radians(pArt->vRevolution[1]); // 45도 회전 (라디안 단위)
	glm::vec3 revolutionAxisY(0.0f, 1.0f, 0.0f); // Y축 기준
	pArt->transformMatrix = glm::rotate(pArt->transformMatrix, revolution_angleY, revolutionAxisY);

	// revolution Z
	float revolution_angleZ = glm::radians(pArt->vRevolution[2]); // 45도 회전 (라디안 단위)
	glm::vec3 revolutionAxisZ(0.0f, 0.0f, 1.0f); // Z축 기준
	pArt->transformMatrix = glm::rotate(pArt->transformMatrix, revolution_angleZ, revolutionAxisZ);

	// revolution Want 원하는 축으로 회전
	float revolution_angle_Want = glm::radians(pArt->vRevolution[3]); // 45도 회전 (라디안 단위)
	//glm::vec3 revolutionAxis_Want(0.0f, 0.0f, 1.0f); // Z축 기준
	pArt->transformMatrix = glm::rotate(pArt->transformMatrix, revolution_angle_Want, pArt->revolutionAxis_Want);


// 이동
	// translation
	glm::vec3 translationVector(pArt->vPos[0], pArt->vPos[1], pArt->vPos[2]);
	pArt->transformMatrix = glm::translate(pArt->transformMatrix, translationVector);

// 자전
	// rotate X
	float angleX = glm::radians(pArt->vRotate[0]); // 45도 회전 (라디안 단위)
	glm::vec3 rotationAxisX(1.0f, 0.0f, 0.0f); // Y축 기준
	pArt->transformMatrix = glm::rotate(pArt->transformMatrix, angleX, rotationAxisX);

	// rotate Y
	float angleY = glm::radians(pArt->vRotate[1]); // 45도 회전 (라디안 단위)
	glm::vec3 rotationAxisY(0.0f, 1.0f, 0.0f); // Y축 기준
	pArt->transformMatrix = glm::rotate(pArt->transformMatrix, angleY, rotationAxisY);

	// rotate Z
	float angleZ = glm::radians(pArt->vRotate[2]); // 45도 회전 (라디안 단위)
	glm::vec3 rotationAxisZ(0.0f, 0.0f, 1.0f); // Y축 기준
	pArt->transformMatrix = glm::rotate(pArt->transformMatrix, angleZ, rotationAxisZ);
	

	// 크기
	// scale
	glm::vec3 scaleFactor(pArt->vScale[0], pArt->vScale[1], pArt->vScale[2]); // 원하는 크기
	pArt->transformMatrix = glm::scale(pArt->transformMatrix, scaleFactor);



	// 이동
// translation
	glm::vec3 Last_translationVector(pArt->vLastMove[0], pArt->vLastMove[1], pArt->vLastMove[2]);
	pArt->transformMatrix = glm::translate(pArt->transformMatrix, Last_translationVector);


	// 자전
	// rotate X
	float Last_angleX = glm::radians(pArt->vLastRotate[0]); // 45도 회전 (라디안 단위)
	glm::vec3 Last_rotationAxisX(1.0f, 0.0f, 0.0f); // X축 기준
	pArt->transformMatrix = glm::rotate(pArt->transformMatrix, Last_angleX, Last_rotationAxisX);

	// rotate Y
	float Last_angleY = glm::radians(pArt->vLastRotate[1]); // 45도 회전 (라디안 단위)
	glm::vec3 Last_rotationAxisY(0.0f, 1.0f, 0.0f); // Y축 기준
	pArt->transformMatrix = glm::rotate(pArt->transformMatrix, Last_angleY, Last_rotationAxisY);

	// rotate Z
	float Last_angleZ = glm::radians(pArt->vLastRotate[2]); // 45도 회전 (라디안 단위)
	glm::vec3 Last_rotationAxisZ(0.0f, 0.0f, 1.0f); // Z축 기준
	pArt->transformMatrix = glm::rotate(pArt->transformMatrix, Last_angleZ, Last_rotationAxisZ);

	// 이동
// translation
	glm::vec3 Last_OneJeom_translationVector(-pArt->vLastMove[0], -pArt->vLastMove[1], -pArt->vLastMove[2]);
	pArt->transformMatrix = glm::translate(pArt->transformMatrix, Last_OneJeom_translationVector);



	

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


typedef struct 
{
	float x, y, z;
} Vertex;
typedef struct 
{
	unsigned int v1, v2, v3;
} Face;
typedef struct 
{
	Vertex* vertices;
	size_t vertex_count;
	Face* faces;
	size_t face_count;
} Model;
void read_newline(char* str) 
{
	char* pos;
	if ((pos = strchr(str, '\n')) != NULL)
		*pos = '\0';
}

struct DW_Model 
{
	unsigned int iVertexNum{};
	unsigned int iNormalNum{};
	unsigned int iIndexNum{};
};

void read_obj_file(const char* filename, DWArt* pArt) 
{
	int iVerNum{};

	int iIndexNum{};

	int iNormalNum{};

	vector<DW_Model> vecIndex_Index{}; // 모든 인덱스 값

	vector<glm::vec3> vec_All_Normal{}; // 모든 노멀벡터의 값

	vector<glm::vec3> vec_All_Vertex{}; // 모든 정점벡터의 값

	FILE* file;
	fopen_s(&file, filename, "r");
	if (!file) 
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	char line[MAX_LINE_LENGTH];
	while (fgets(line, sizeof(line), file))
	{
		read_newline(line);
		if (line[0] == 'v' && line[1] == ' ')
		{
			iVerNum++;
		}
		else if (line[0] == 'f' && line[1] == ' ')
		{
			iIndexNum += 3;
		}
		else if (line[0] == 'v' && line[1] == 'n')
		{
			iNormalNum++;
		}


	}
	fseek(file, 0, SEEK_SET);


	// 벡터 공간 만들기
	for (int i = 0; i < iVerNum; ++i)
	{
		vec_All_Vertex.push_back(glm::vec3());
	}

	for (int i = 0; i < iIndexNum; ++i)
	{
		vecIndex_Index.push_back(DW_Model{}); // 해당 인덱스에 어떤 노멀값이 들어가는지에 대한 값
	}

	for (int i = 0; i < iNormalNum; ++i)
	{
		vec_All_Normal.push_back(glm::vec3());
	}

	size_t vertex_index = 0; size_t face_index = 0;
	size_t Normal_index = 0;
	while (fgets(line, sizeof(line), file))
	{
		read_newline(line);
		if (line[0] == 'v' && line[1] == ' ')
		{
			int result = sscanf_s(line + 2, "%f %f %f",
				&vec_All_Vertex[vertex_index].x,
				&vec_All_Vertex[vertex_index].y,
				&vec_All_Vertex[vertex_index].z
			);
			//vec_All_Vertex[vertex_index].z = -vec_All_Vertex[vertex_index].z;

			vertex_index++;
		}
		else if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
		{
			int result = sscanf_s(line + 3, "%f %f %f",
				&vec_All_Normal[Normal_index].x,
				&vec_All_Normal[Normal_index].y,
				&vec_All_Normal[Normal_index].z);
			//vec_All_Normal[Normal_index].z = -vec_All_Normal[Normal_index].z;
			Normal_index++;
			
		}
		else if (line[0] == 'f' && line[1] == ' ')
		{
			unsigned int v1, v2, v3, v4, v5, v6;
			int result = sscanf_s(line + 2, "%u//%u %u//%u %u//%u", &v1, &v2, &v3, &v4, &v5, &v6);

			// f 4//4 8//4 5//4



			vecIndex_Index[face_index].iNormalNum = v2 - 1;
			vecIndex_Index[face_index++].iVertexNum = v1 - 1; // OBJ indices start at 1

			vecIndex_Index[face_index].iNormalNum = v4 - 1;
			vecIndex_Index[face_index++].iVertexNum = v3 - 1;

			vecIndex_Index[face_index].iNormalNum = v6 - 1;
			vecIndex_Index[face_index++].iVertexNum = v5 - 1;
			//face_index++;
		}
	}

	for (int i = 0; i < iIndexNum; ++i)
	{
		pArt->Vertex.push_back(vec_All_Vertex[vecIndex_Index[i].iVertexNum]);

		pArt->Vertex_Nomal.push_back(vec_All_Normal[vecIndex_Index[i].iNormalNum]);

		pArt->indexVerTex.push_back(i);
	}

	fclose(file);
}

ULONG ProcIDFromWnd(HWND hwnd) // 윈도우 핸들로 프로세스 아이디 얻기  
{
	ULONG idProc;
	GetWindowThreadProcessId(hwnd, &idProc);
	return idProc;
}

HWND GetWinHandle(ULONG pid) // 프로세스 아이디로 윈도우 핸들 얻기  
{
	HWND tempHwnd = FindWindow(NULL, NULL); // 최상위 윈도우 핸들 찾기

	while (tempHwnd != NULL)
	{
		if (GetParent(tempHwnd) == NULL) // 최상위 핸들인지 체크, 버튼 등도 핸들을 가질 수 있으므로 무시하기 위해  
			if (pid == 1)
				return tempHwnd;
		tempHwnd = GetWindow(tempHwnd, GW_HWNDNEXT); // 다음 윈도우 핸들 찾기  
	}
	return NULL;
}

// GLUT 윈도우 핸들 얻기 
HWND GetGLUTWindowHandle() 
{ 
	// 활성화된 윈도우 핸들 가져오기 
	return GetForegroundWindow(); 
}