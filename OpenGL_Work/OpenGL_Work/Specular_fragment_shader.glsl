#version 330 core

out vec4 FragColor; // 최종 출력

in vec3 out_Color; //--- 응용 프로그램에서 설정한 객체의 색상
in vec3 FragPos; //--- 위치값
in vec3 Normal; //--- 버텍스 세이더에서 받은 노멀값


uniform vec3 lightPos; //--- 조명의 위치
uniform vec3 lightColor; //--- 조명의 색
//uniform vec3 objectColor; //--- 객체의 색
uniform float lightPower; //--- 조명의 세기

uniform vec3 viewPos; // ---카메라 위치



void main ()
{
	float ambientLight = 0.5; //--- 주변 조명 계수: 0.0 ≤ ambientLight ≤ 1.0

	vec3 ambient = ambientLight * lightColor; //--- 주변 조명값

	vec3 normalVector = normalize(Normal);   //--- 노말값을 정규화한다

	float fDistance = length(lightPos - FragPos);

	vec3 lightDir = normalize(lightPos - FragPos); //--- 표면과 조명의 위치로 조명의 방향을 결정한다.

	//float fDistance = ((lightDir.x * lightDir.x) + (lightDir.y * lightDir.y) + (lightDir.z * lightDir.z));

	float diffuseLight = max(dot(lightDir,normalVector),0.0); //--- N과 L의 내적 값으로 강도 조절 (음의 값을 가질 수 없게 한다.)
	
	vec3 diffuse = diffuseLight * lightColor * lightPower / fDistance;



	// 스페큘러 항

	int shininess = 128; //--- 광택 계수

	vec3 viewDir = normalize (viewPos - FragPos);
	
	vec3 reflectDir = reflect (-lightDir, normalVector); //--- 반사 방향: reflect 함수 - 입사 벡터의 반사 방향 계산
	
	float specularLight = max (dot (viewDir, reflectDir), 0.0); //--- V와 R의 내적값으로 강도 조절: 음수 방지
	
	specularLight = pow(specularLight, shininess); //--- shininess 승을 해주어 하이라이트를 만들어준다.
	
	vec3 specular = specularLight * lightColor; //--- 거울 반사 조명값: 거울반사값 * 조명색상값
	
	vec3 result = (ambient + diffuse + specular) * out_Color; //--- 최종 조명 설정된 픽셀 색상: (주변+산란반사+거울반사조명)*객체 색상
	
	FragColor = vec4 (result, 1.0); 
}