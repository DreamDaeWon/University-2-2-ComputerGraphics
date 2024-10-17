#version 330 core
layout (location = 0) in vec3 in_Position; //--- ���� ���α׷����� �޾ƿ� ���� ��ǥ��
layout (location = 1) in vec3 in_Color; //--- �÷� ����: attribute position 1
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

	// ���ٳ�����
	Pos = vec4(Pos[0]/Pos[3],Pos[1]/Pos[3],Pos[2]/Pos[3],Pos[3]/Pos[3]);

	gl_Position[0] = Pos[0];
	gl_Position[1] = Pos[1];
	gl_Position[2] = Pos[2];

	out_Color = in_Color;
}
