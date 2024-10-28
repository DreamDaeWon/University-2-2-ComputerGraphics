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
		//m_vLook = m_vPos;
		//m_vLook[2] += 1.f;

		//m_Matrix_View = glm::lookAt(m_vPos, m_vLook, m_vUp);
	}

	glm::mat4 Get_view_Matrix()
	{

		////m_Matrix_View = glm::mat4(1.0f);
		//

		//// 이동
		////m_Matrix_View = glm::translate(m_Matrix_View, m_vPos);


		////m_vLook

		//m_vLook = glm::vec3(0.f,0.f,1.f);
		////m_vPos = glm::vec3(0.f,0.f,0.f );
		//m_vUp = glm::vec3(0.f,1.f,0.f );
		//m_vRight = glm::vec3(1.f,0.f,0.f );



		//glm::mat4 NomalMatrix = glm::mat4(1.f);

		//// 회전
		//glm::vec3 rotationAxisX(1.f,0.f,0.f); // X축 기준
		//glm::mat4 RotateMatrix = glm::rotate(NomalMatrix, glm::radians(angleX), rotationAxisX);


		////m_vLook = RotateMatrix * glm::vec4(m_vLook, 1.f);


		//glm::vec3 rotationAxisY(0.f, 1.f, 0.f); // Y축 기준
		//RotateMatrix = glm::rotate(RotateMatrix, glm::radians(angleY), rotationAxisY);

		//m_vLook = RotateMatrix * glm::vec4(m_vLook, 1.f);


		//m_vRight = glm::cross(m_vUp, m_vLook);

		//m_vUp = glm::cross(m_vLook, m_vRight);
	
		//
		//m_Matrix_View = glm::mat4(m_vRight.x, m_vUp.x, m_vLook.x,0.f, m_vRight.y, m_vUp.y, m_vLook.y, 0.f, m_vRight.z, m_vUp.z, m_vLook.z, 0.f,0,0,0,1);

		//m_Matrix_View = glm::translate(m_Matrix_View, m_vPos);

		//m_Matrix_View = glm::inverse(m_Matrix_View);
		return inverse(m_Matrix_View);
	}

public:

	void RotateX_Camera(float Angle);
	void RotateY_Camera(float Angle);
	void RotateZ_Camera(float Angle);

	void Move_Right_Camera(float _fMove);
	void Move_Left_Camera(float _fMove);
	void Move_Back_Camera(float _fMove);
	void Move_Front_Camera(float _fMove);

	void Move_Up_Camera(float _fMove);

	void Move_Down_Camera(float _fMove);

public:
	void MoveCamera(glm::vec3 _Pos);


private:
	glm::vec3 m_vLook{0.f,0.f,1.f}; // 카메라의 룩벡터
	glm::vec3 m_vPos{0.f,0.f,0.f}; // 카메라의 위치
	glm::vec3 m_vUp{ 0.f,1.f,0.f}; // 카메라 업벡터
	glm::vec3 m_vRight{1.f,0.f,0.f}; // 카메라 라이트 벡터


	glm::mat4 m_Matrix_View{ }; // 뷰변환 행렬

	glm::quat m_Quat_Rotate{};

	float angleX{};
	float angleY{};

	//glm::vec3 m_vLook{}; // 카메라의 룩벡터



};

