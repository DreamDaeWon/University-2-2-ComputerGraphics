#include "DW_Camera.h"

CDW_Camera::CDW_Camera(glm::vec3 _vPos, glm::vec3 _vLook)
{
	CreateCamera(_vPos, _vLook);
	
}

CDW_Camera::~CDW_Camera()
{
}

void CDW_Camera::CreateCamera(glm::vec3 _vPos, glm::vec3 _vLook)
{
	//m_vPos = _vPos;
	//m_vLook = _vLook;
	//m_vUp = glm::vec3(0.f, 1.f, 0.f);
	m_Matrix_View = glm::mat4(1.0f);
	//m_Matrix_View = glm::lookAt(m_vPos, m_vLook, m_vUp);

		// 각 축 벡터를 추출하고 노멀라이즈
	//m_Matrix_View[0] = glm::normalize(glm::vec4(m_Matrix_View[0]));
	//m_Matrix_View[1] = glm::normalize(glm::vec4(m_Matrix_View[1]));
	//m_Matrix_View[2] = glm::normalize(glm::vec4(m_Matrix_View[2]));
	//m_Matrix_View[3] = m_Matrix_View[3]; // 변환 행렬이므로 마지막 행은 유지

}

void CDW_Camera::RotateX_Camera(float Angle)
{
	//angleX -= Angle;

	glm::vec3 rotationAxisX(m_Matrix_View[0]); // Y축 기준
	m_Matrix_View = glm::rotate(m_Matrix_View, glm::radians(Angle), rotationAxisX);

}

void CDW_Camera::RotateY_Camera(float Angle)
{
	//angleY -= Angle;
	glm::vec3 rotationAxisY(0.f, 1.f, 0.f); // Y축 기준
	m_Matrix_View = glm::rotate(m_Matrix_View, glm::radians(Angle), rotationAxisY);

}

void CDW_Camera::RotateZ_Camera(float Angle)
{
	// rotate Z
	float angleZ = glm::radians(Angle); // 회전 (라디안 단위)
	glm::vec3 rotationAxisZ(m_Matrix_View[0][2], m_Matrix_View[1][2], m_Matrix_View[2][2]); // Z축 기준
	m_Matrix_View = glm::rotate(m_Matrix_View, angleZ, rotationAxisZ);
}

void CDW_Camera::Move_Right_Camera(float _fMove)
{

	m_vPos.x += _fMove;

	glm::vec3 translationVector(_fMove, 0.f, 0.f);
	m_Matrix_View = glm::translate(m_Matrix_View, translationVector);
}

void CDW_Camera::Move_Left_Camera(float _fMove)
{

	m_vPos.x -= _fMove;

	// translation
	glm::vec3 translationVector(-_fMove, 0.f, 0.f);
	m_Matrix_View = glm::translate(m_Matrix_View, translationVector);
}

void CDW_Camera::Move_Back_Camera(float _fMove)
{


	m_vPos.z += _fMove;


	// translation
	glm::vec3 translationVector(0.f, 0.f, _fMove);
	m_Matrix_View = glm::translate(m_Matrix_View, translationVector);
}

void CDW_Camera::Move_Front_Camera(float _fMove)
{

	m_vPos.z -= _fMove;

	// translation
	glm::vec3 translationVector(0.f, 0.f, -_fMove);
	m_Matrix_View = glm::translate(m_Matrix_View, translationVector);
}

void CDW_Camera::Move_Up_Camera(float _fMove)
{

}

void CDW_Camera::Move_Down_Camera(float _fMove)
{

}

void CDW_Camera::MoveCamera(glm::vec3 _Move_Pos)
{
	// translation
	glm::vec3 translationVector(_Move_Pos.x, _Move_Pos.y, _Move_Pos.z);
	m_Matrix_View = glm::translate(m_Matrix_View, translationVector);
}