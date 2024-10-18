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

class CDW_Camera
{
public:
	CDW_Camera(glm::vec3 _vPos, glm::vec3 _vLook);
	~CDW_Camera();


public:
	void CreateCamera(glm::vec3 _vPos, glm::vec3 _vLook);

	void Make_view_Matrix()
	{
		//m_vLook = m_vPos;
		//m_vLook[2] += 1.f;

		m_Matrix_View = glm::lookAt(m_vPos, m_vLook, m_vUp);
	}

	glm::mat4 Get_view_Matrix()
	{
		return m_Matrix_View;
	}

public:
	void RotateX_Camera(float Angle);
	void RotateY_Camera(float Angle);
	void RotateZ_Camera(float Angle);

	void MoveX_Camera(glm::vec3 Move);


public:
	void MoveCamera(glm::vec3 _Pos);


private:
	glm::vec3 m_vLook{}; // 카메라의 룩벡터
	glm::vec3 m_vPos{}; // 카메라의 위치
	glm::vec3 m_vUp{}; // 카메라 업벡터

	glm::mat4 m_Matrix_View{ }; // 뷰변환 행렬

	//glm::vec3 m_vLook{}; // 카메라의 룩벡터



};

