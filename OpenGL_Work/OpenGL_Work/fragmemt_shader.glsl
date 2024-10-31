#version 330 core
//--- out_Color: ���ؽ� ���̴����� �Է¹޴� ���� ��
//--- FragColor: ����� ������ ������ ������ ���۷� ���� ��. 
in vec3 out_Color; //--- ���ؽ� ���̴����Լ� ���� ����
out vec4 FragColor; //--- ���� ���

uniform vec4 vColor;
void main(void)
{
	FragColor = vec4 (out_Color, 1.0);

	if(vColor.a >0.f)
	{
		FragColor = vColor;
	}
}