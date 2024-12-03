#version 330 core

out vec4 FragColor; // ���� ���

in vec3 out_Color; //--- ���� ���α׷����� ������ ��ü�� ����
in vec3 FragPos; //--- ��ġ��
in vec3 Normal; //--- ���ؽ� ���̴����� ���� ��ְ�


uniform vec3 lightPos; //--- ������ ��ġ
uniform vec3 lightColor; //--- ������ ��
//uniform vec3 objectColor; //--- ��ü�� ��
uniform float lightPower; //--- ������ ����

uniform vec3 viewPos; // ---ī�޶� ��ġ



void main ()
{
	float ambientLight = 0.5; //--- �ֺ� ���� ���: 0.0 �� ambientLight �� 1.0

	vec3 ambient = ambientLight * lightColor; //--- �ֺ� ����

	vec3 normalVector = normalize(Normal);   //--- �븻���� ����ȭ�Ѵ�

	float fDistance = length(lightPos - FragPos);

	vec3 lightDir = normalize(lightPos - FragPos); //--- ǥ��� ������ ��ġ�� ������ ������ �����Ѵ�.

	//float fDistance = ((lightDir.x * lightDir.x) + (lightDir.y * lightDir.y) + (lightDir.z * lightDir.z));

	float diffuseLight = max(dot(lightDir,normalVector),0.0); //--- N�� L�� ���� ������ ���� ���� (���� ���� ���� �� ���� �Ѵ�.)
	
	vec3 diffuse = diffuseLight * lightColor * lightPower / fDistance;



	// ����ŧ�� ��

	int shininess = 128; //--- ���� ���

	vec3 viewDir = normalize (viewPos - FragPos);
	
	vec3 reflectDir = reflect (-lightDir, normalVector); //--- �ݻ� ����: reflect �Լ� - �Ի� ������ �ݻ� ���� ���
	
	float specularLight = max (dot (viewDir, reflectDir), 0.0); //--- V�� R�� ���������� ���� ����: ���� ����
	
	specularLight = pow(specularLight, shininess); //--- shininess ���� ���־� ���̶���Ʈ�� ������ش�.
	
	vec3 specular = specularLight * lightColor; //--- �ſ� �ݻ� ����: �ſ�ݻ簪 * �������
	
	vec3 result = (ambient + diffuse + specular) * out_Color; //--- ���� ���� ������ �ȼ� ����: (�ֺ�+����ݻ�+�ſ�ݻ�����)*��ü ����
	
	FragColor = vec4 (result, 1.0); 
}