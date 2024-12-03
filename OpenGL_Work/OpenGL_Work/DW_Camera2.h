#pragma once
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>


#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
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

class CDW_Camera2
{
public:
	CDW_Camera2(glm::vec3 _vPos, glm::vec3 _vLook);
	~CDW_Camera2();


public:
	void CreateCamera(glm::vec3 _vPos, glm::vec3 _vLook);

	void Make_view_Matrix()
	{

	}

	glm::mat4 Get_view_Matrix()
	{

		Make_Camera_Matrix();
		return inverse(m_Matrix_View);
	}

	glm::mat4* Get_view_Matrix_Pointer()
	{


		return &m_Matrix_View;
	}


public:

	void Make_Camera_Matrix();

	GLfloat* Get_vRotate()
	{
		return vRotate;
	}

	glm::vec3 Get_vPos()
	{
		return vPos;
	}

	GLfloat* Get_vRevolution()
	{
		return vRevolution;
	}



	void RotateX_Camera(float Angle);
	void RotateY_Camera(float Angle);
	void RotateZ_Camera(float Angle);

	void RevolutionX_Camera(float Angle);
	void RevolutionY_Camera(float Angle);
	void RevolutionZ_Camera(float Angle);

	void Move_Right_Camera(float _fMove);
	void Move_Left_Camera(float _fMove);
	void Move_Back_Camera(float _fMove);
	void Move_Front_Camera(float _fMove);

	void Move_Up_Camera(float _fMove);

	void Move_Down_Camera(float _fMove);


public:
	void MoveCamera(glm::vec3 _Pos);


private:
	//glm::vec3 m_vLook{0.f,0.f,1.f}; // 카메라의 룩벡터
	//glm::vec3 m_vPos{0.f,0.f,0.f}; // 카메라의 위치
	//glm::vec3 m_vUp{ 0.f,1.f,0.f}; // 카메라 업벡터
	//glm::vec3 m_vRight{1.f,0.f,0.f}; // 카메라 라이트 벡터


	glm::mat4 m_Matrix_View{ }; // 뷰변환 행렬

	glm::quat m_Quat_Rotate{};

	float angleX{};
	float angleY{};

	GLfloat vRotate[3]{}; // 객체가 x y z 축으로 얼마만큼 회전하였는지?

	glm::vec3 vPos{}; // 객체가 원점에서 얼마만큼 움직이는지? // 로컬 좌표계임

	GLfloat vRevolution[4]{}; // 객체가 x y z 축으로 얼마만큼 공전하였는지?

	//glm::vec3 m_vLook{}; // 카메라의 룩벡터



};

