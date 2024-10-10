#version 330 core
//--- in_Position: attribute index 0 
//--- in_Color: attribute index 1
layout (location = 0) in vec3 in_Position; //--- 위치 변수: attribute position 0
layout (location = 1) in vec3 in_Color; //--- 컬러 변수: attribute position 1
out vec3 out_Color; //--- 프래그먼트 세이더에게 전달

uniform float Rotate;
uniform float CenterX;
uniform float CenterY;

void main(void) 
{
	vec3 Pos = {in_Position.x, in_Position.y, in_Position.z};

	float rad = radians(Rotate);

	mat3 Mat = mat3(cos(rad),sin(rad),0,-sin(rad),cos(rad),0,0,0,1);

	vec3 Move = {in_Position.x - CenterX,in_Position.y - CenterY,in_Position.z};

	Move = Mat * Move;

	gl_Position = vec4 (Move.x + CenterX, Move.y + CenterY, Pos.z, 1.0);

	out_Color = in_Color;
}