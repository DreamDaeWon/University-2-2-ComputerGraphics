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

}

void CDW_Camera::MoveCamera(glm::vec3 _Move_Pos)
{
	m_vPos += _Move_Pos;
}