#version 330 core
layout (location = 0) in vec3 in_Position; //--- 응용 프로그램에서 받아온 도형 좌표값
layout (location = 1) in vec3 in_Color; //--- 컬러 변수: attribute position 1

layout (location = 2) in vec3 vNormal; // --- 노멀벡터 : attribute position 2

out vec3 FragPos; // 객체의 위치값
out vec3 Normal; // 객체의 노말값
out vec3 out_Color; //--- 프래그먼트 세이더에게 전달

uniform mat4 WorldTransform; //--- 모델링 변환 행렬: uniform 변수로 선언
uniform mat4 ViewTransform; //--- 모델링 변환 행렬: uniform 변수로 선언
uniform mat4 ProjectionTransform; //--- 모델링 변환 행렬: uniform 변수로 선언

void main()
{
	//gl_Position = WorldTransform * vec4(in_Position, 1.0); //--- 좌표값에 WorldTransform 변환을 적용한다.

	// 월드
	vec4 Pos = WorldTransform * vec4(in_Position, 1.0);

	// 뷰
	Pos = ViewTransform * vec4(Pos); 

	// 투영
	Pos = ProjectionTransform * vec4(Pos);

	gl_Position = Pos;

	FragPos = vec3(WorldTransform * vec4(in_Position,1.0));


	// 노멀 변환 (정규화) 
	mat3 normalMatrix = mat3(transpose(inverse(WorldTransform)));
	Normal = normalize(normalMatrix * vNormal);

	//Normal = vNormal;

	out_Color = in_Color;
}
