#version 330 core
layout (location = 0) in vec3 in_Position; //--- ���� ���α׷����� �޾ƿ� ���� ��ǥ��
layout (location = 1) in vec3 in_Color; //--- �÷� ����: attribute position 1

layout (location = 2) in vec3 vNormal; // --- ��ֺ��� : attribute position 2

out vec3 FragPos; // ��ü�� ��ġ��
out vec3 Normal; // ��ü�� �븻��
out vec3 out_Color; //--- �����׸�Ʈ ���̴����� ����

uniform mat4 WorldTransform; //--- �𵨸� ��ȯ ���: uniform ������ ����
uniform mat4 ViewTransform; //--- �𵨸� ��ȯ ���: uniform ������ ����
uniform mat4 ProjectionTransform; //--- �𵨸� ��ȯ ���: uniform ������ ����

void main()
{
	//gl_Position = WorldTransform * vec4(in_Position, 1.0); //--- ��ǥ���� WorldTransform ��ȯ�� �����Ѵ�.

	// ����
	vec4 Pos = WorldTransform * vec4(in_Position, 1.0);

	// ��
	Pos = ViewTransform * vec4(Pos); 

	// ����
	Pos = ProjectionTransform * vec4(Pos);

	gl_Position = Pos;

	FragPos = vec3(WorldTransform * vec4(in_Position,1.0));


	// ��� ��ȯ (����ȭ) 
	mat3 normalMatrix = mat3(transpose(inverse(WorldTransform)));
	Normal = normalize(normalMatrix * vNormal);

	//Normal = vNormal;

	out_Color = in_Color;
}
