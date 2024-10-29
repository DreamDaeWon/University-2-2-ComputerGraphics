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
	//m_vPos = _vPos;
	//m_vLook = _vLook;
	//m_vUp = glm::vec3(0.f, 1.f, 0.f);
	m_Matrix_View = glm::mat4(1.0f);
	m_vPos = _vPos;
	m_Matrix_View = glm::translate(m_Matrix_View, m_vPos);
	//m_Matrix_View = glm::lookAt(m_vPos, m_vLook, m_vUp);

		// �� �� ���͸� �����ϰ� ��ֶ�����
	//m_Matrix_View[0] = glm::normalize(glm::vec4(m_Matrix_View[0]));
	//m_Matrix_View[1] = glm::normalize(glm::vec4(m_Matrix_View[1]));
	//m_Matrix_View[2] = glm::normalize(glm::vec4(m_Matrix_View[2]));
	//m_Matrix_View[3] = m_Matrix_View[3]; // ��ȯ ����̹Ƿ� ������ ���� ����

}

void CDW_Camera2::RotateX_Camera(float Angle)
{
	//angleX -= Angle;

	glm::vec3 rotationAxisX(1.f, 0.f, 0.f); // X�� ����

	m_Matrix_View = glm::rotate(m_Matrix_View, glm::radians(Angle), rotationAxisX);

}

void CDW_Camera2::RotateY_Camera(float Angle)
{
	//angleY -= Angle;
	glm::vec3 rotationAxisY(0.f, 1.f, 0.f); // Y�� ����
	m_Matrix_View = glm::rotate(m_Matrix_View, glm::radians(Angle), rotationAxisY);

}

void CDW_Camera2::RotateZ_Camera(float Angle)
{
	// rotate Z
	float angleZ = glm::radians(Angle); // ȸ�� (���� ����)
	glm::vec3 rotationAxisZ(m_Matrix_View[0][2], m_Matrix_View[1][2], m_Matrix_View[2][2]); // Z�� ����
	m_Matrix_View = glm::rotate(m_Matrix_View, angleZ, rotationAxisZ);
}

void CDW_Camera2::Move_Right_Camera(float _fMove)
{

	m_vPos.x += _fMove;

	glm::vec3 translationVector(_fMove, 0.f, 0.f);
	m_Matrix_View = glm::translate(m_Matrix_View, translationVector);
}

void CDW_Camera2::Move_Left_Camera(float _fMove)
{

	m_vPos.x -= _fMove;

	// translation
	glm::vec3 translationVector(-_fMove, 0.f, 0.f);
	m_Matrix_View = glm::translate(m_Matrix_View, translationVector);
}

void CDW_Camera2::Move_Back_Camera(float _fMove)
{


	m_vPos.z += _fMove;


	// translation
	glm::vec3 translationVector(0.f, 0.f, _fMove);
	m_Matrix_View = glm::translate(m_Matrix_View, translationVector);
}

void CDW_Camera2::Move_Front_Camera(float _fMove)
{

	m_vPos.z -= _fMove;

	// translation
	glm::vec3 translationVector(0.f, 0.f, -_fMove);
	m_Matrix_View = glm::translate(m_Matrix_View, translationVector);
}

void CDW_Camera2::Move_Up_Camera(float _fMove)
{

}

void CDW_Camera2::Move_Down_Camera(float _fMove)
{

}

void CDW_Camera2::MoveCamera(glm::vec3 _Move_Pos)
{
	// translation
	glm::vec3 translationVector(_Move_Pos.x, _Move_Pos.y, _Move_Pos.z);
	m_Matrix_View = glm::translate(m_Matrix_View, translationVector);
}