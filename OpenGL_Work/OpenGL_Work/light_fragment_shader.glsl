#version 330 core
out vec4 FragColor;
uniform vec3 objectColor; //--- ���� ���α׷����� ������ ��ü�� ����
uniform vec3 lightColor; //--- ���� ���α׷����� ������ ���� ����
void main ()
{
	float ambientLight = 0.5; //--- �ֺ� ���� ���: 0.0 �� ambientLight �� 1.0
	vec3 ambient = ambientLight * lightColor; //--- �ֺ� ����
	vec3 result = ambient * objectColor; //--- ��ü�� ���� �ֺ������� ���Ͽ� ���� ��ü ���� ����
	FragColor = vec4 (result, 1.0);
}