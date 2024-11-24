#version 330 core
out vec4 FragColor;
uniform vec3 objectColor; //--- 응용 프로그램에서 설정한 객체의 색상
uniform vec3 lightColor; //--- 응용 프로그램에서 설정한 조명 색상
void main ()
{
	float ambientLight = 0.5; //--- 주변 조명 계수: 0.0 ≤ ambientLight ≤ 1.0
	vec3 ambient = ambientLight * lightColor; //--- 주변 조명값
	vec3 result = ambient * objectColor; //--- 객체의 색과 주변조명값을 곱하여 최종 객체 색상 설정
	FragColor = vec4 (result, 1.0);
}