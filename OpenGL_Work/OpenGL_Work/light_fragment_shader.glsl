#version 330 core

out vec4 FragColor; // ���� ���

in vec3 out_Color; //--- ���� ���α׷����� ������ ��ü�� ����
in vec3 FragPos; //--- ��ġ��
in vec3 Normal; //--- ���ؽ� ���̴����� ���� ��ְ�


uniform vec3 lightPos; //--- ������ ��ġ
uniform vec3 lightColor; //--- ������ ��
//uniform vec3 objectColor; //--- ��ü�� ��



void main ()
{
	float ambientLight = 0.5; //--- �ֺ� ���� ���: 0.0 �� ambientLight �� 1.0

	vec3 ambient = ambientLight * lightColor; //--- �ֺ� ����

	vec3 normalVector = normalize(Normal);   //--- �븻���� ����ȭ�Ѵ�

	float fDistance = length(lightPos - FragPos);

	vec3 lightDir = normalize(lightPos - FragPos); //--- ǥ��� ������ ��ġ�� ������ ������ �����Ѵ�.

	//float fDistance = ((lightDir.x * lightDir.x) + (lightDir.y * lightDir.y) + (lightDir.z * lightDir.z));

	float diffuseLight = max(dot(lightDir,normalVector),0.0); //--- N�� L�� ���� ������ ���� ���� (���� ���� ���� �� ���� �Ѵ�.)
	
	vec3 diffuse = diffuseLight * lightColor / fDistance;


	vec3 result = (ambient + diffuse) * out_Color; //--- ��ü�� ���� �ֺ������� ���Ͽ� ���� ��ü ���� ����

	FragColor = vec4 (result, 1.0);
}