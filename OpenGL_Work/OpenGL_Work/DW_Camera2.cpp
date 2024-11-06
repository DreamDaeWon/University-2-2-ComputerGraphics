#include "DW_Camera2.h"

CDW_Camera2::CDW_Camera2(glm::vec3 _vPos, glm::vec3 _vLook)
{
	CreateCamera(_vPos, _vLook);

}

CDW_Camera2::~CDW_Camera2()
{
}

void CDW_Camera2::CreateCamera(glm::vec3 _vPos, glm::vec3 _vLook)
{

	vPos[0] = _vPos.x;
	vPos[1] = _vPos.y;
	vPos[2] = _vPos.z;

	m_Matrix_View = glm::mat4(1.0f);
	//m_vPos = _vPos;
	//m_Matrix_View = glm::translate(m_Matrix_View, m_vPos);

}

void CDW_Camera2::Make_Camera_Matrix()
{
	m_Matrix_View = glm::mat4(1.0f);

	// 공전
	// revolution X
	float revolution_angleX = glm::radians(vRevolution[0]); // 45도 회전 (라디안 단위)
	glm::vec3 revolutionAxisX(1.0f, 0.0f, 0.0f); // X축 기준
	m_Matrix_View = glm::rotate(m_Matrix_View, revolution_angleX, revolutionAxisX);

	// revolution Y
	float revolution_angleY = glm::radians(vRevolution[1]); // 45도 회전 (라디안 단위)
	glm::vec3 revolutionAxisY(0.0f, 1.0f, 0.0f); // Y축 기준
	m_Matrix_View = glm::rotate(m_Matrix_View, revolution_angleY, revolutionAxisY);

	// revolution Z
	float revolution_angleZ = glm::radians(vRevolution[2]); // 45도 회전 (라디안 단위)
	glm::vec3 revolutionAxisZ(0.0f, 0.0f, 1.0f); // Z축 기준
	m_Matrix_View = glm::rotate(m_Matrix_View, revolution_angleZ, revolutionAxisZ);


	// 이동
		// translation
	glm::vec3 translationVector(vPos[0], vPos[1], vPos[2]);
	m_Matrix_View = glm::translate(m_Matrix_View, translationVector);

	// 자전
	// 
	

	// rotate Y
	float angleY = glm::radians(vRotate[1]); // 45도 회전 (라디안 단위)
	glm::vec3 rotationAxisY(0.0f, 1.0f, 0.0f); // Y축 기준
	m_Matrix_View = glm::rotate(m_Matrix_View, angleY, rotationAxisY);

		// rotate X
	float angleX = glm::radians(vRotate[0]); // 45도 회전 (라디안 단위)
	glm::vec3 rotationAxisX(1.0f, 0.0f, 0.0f); // Y축 기준
	m_Matrix_View = glm::rotate(m_Matrix_View, angleX, rotationAxisX);



	// rotate Z
	float angleZ = glm::radians(vRotate[2]); // 45도 회전 (라디안 단위)
	glm::vec3 rotationAxisZ(0.0f, 0.0f, 1.0f); // Y축 기준
	m_Matrix_View = glm::rotate(m_Matrix_View, angleZ, rotationAxisZ);


	// 크기
	// scale
	//glm::vec3 scaleFactor(pArt->vScale[0], pArt->vScale[1], pArt->vScale[2]); // 원하는 크기
	//pArt->transformMatrix = glm::scale(pArt->transformMatrix, scaleFactor);

}

void CDW_Camera2::RotateX_Camera(float Angle)
{
	//angleX -= Angle;
	vRotate[0] += Angle;

	//glm::vec3 rotationAxisX(1.f, 0.f, 0.f); // X축 기준

	//m_Matrix_View = glm::rotate(m_Matrix_View, glm::radians(Angle), rotationAxisX);

}

void CDW_Camera2::RotateY_Camera(float Angle)
{
	//angleY -= Angle;
	vRotate[1] += Angle;

	//glm::vec3 rotationAxisY(0.f, 1.f, 0.f); // Y축 기준
	//m_Matrix_View = glm::rotate(m_Matrix_View, glm::radians(Angle), rotationAxisY);

}

void CDW_Camera2::RotateZ_Camera(float Angle)
{
	// rotate Z
	float angleZ = glm::radians(Angle); // 회전 (라디안 단위)
	glm::vec3 rotationAxisZ(m_Matrix_View[0][2], m_Matrix_View[1][2], m_Matrix_View[2][2]); // Z축 기준
	m_Matrix_View = glm::rotate(m_Matrix_View, angleZ, rotationAxisZ);
}

void CDW_Camera2::RevolutionX_Camera(float Angle)
{
	vRevolution[0] += Angle;
}

void CDW_Camera2::RevolutionY_Camera(float Angle)
{
	vRevolution[1] += Angle;
}

void CDW_Camera2::RevolutionZ_Camera(float Angle)
{
	vRevolution[2] += Angle;
}

void CDW_Camera2::Move_Right_Camera(float _fMove)
{

	vPos[0] += _fMove;

	//glm::vec3 translationVector(_fMove, 0.f, 0.f);
	//m_Matrix_View = glm::translate(m_Matrix_View, translationVector);
}

void CDW_Camera2::Move_Left_Camera(float _fMove)
{

	vPos[0] -= _fMove;

	// translation
	//glm::vec3 translationVector(-_fMove, 0.f, 0.f);
	//m_Matrix_View = glm::translate(m_Matrix_View, translationVector);
}

void CDW_Camera2::Move_Back_Camera(float _fMove)
{


	vPos[2] += _fMove;


	// translation
	//glm::vec3 translationVector(0.f, 0.f, _fMove);
	//m_Matrix_View = glm::translate(m_Matrix_View, translationVector);
}

void CDW_Camera2::Move_Front_Camera(float _fMove)
{

	vPos[2] -= _fMove;

	// translation
	//glm::vec3 translationVector(0.f, 0.f, -_fMove);
	//m_Matrix_View = glm::translate(m_Matrix_View, translationVector);
}

void CDW_Camera2::Move_Up_Camera(float _fMove)
{
	vPos[1] += _fMove;
}

void CDW_Camera2::Move_Down_Camera(float _fMove)
{
	vPos[1] -= _fMove;
}

void CDW_Camera2::MoveCamera(glm::vec3 _Move_Pos)
{
	// translation
	glm::vec3 translationVector(_Move_Pos.x, _Move_Pos.y, _Move_Pos.z);
	m_Matrix_View = glm::translate(m_Matrix_View, translationVector);
}