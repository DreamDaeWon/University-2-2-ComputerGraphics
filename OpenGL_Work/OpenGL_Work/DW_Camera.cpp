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
	m_vPos = _vPos;
	m_vLook = _vLook;
	m_vUp = glm::vec3(0.f, 1.f, 0.f);

	m_Matrix_View = glm::lookAt(m_vPos, m_vLook, m_vUp);

}

void CDW_Camera::RotateY_Camera(float Angle)
{

}

void CDW_Camera::RotateZ_Camera(float Angle)
{

}

void CDW_Camera::MoveX_Camera(glm::vec3 Move)
{

}

void CDW_Camera::MoveCamera(glm::vec3 _Move_Pos)
{
	m_vPos += _Move_Pos;
}