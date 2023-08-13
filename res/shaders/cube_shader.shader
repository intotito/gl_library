#SHADER VERTEX
#version 330 core

layout(location = 0) in vec2 position;


uniform mat4 u_MVP;
void main()
{
	//	gl_Position = vec4(position, 0.0f, 1.0f);
	gl_Position = u_MVP * vec4(position, 0.0f, 1.0f);
	//fColor = vexColor;
	//testColor = position;
};

#SHADER FRAGMENT
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_TexIndex;
//in vec4 fColor;
//in vec2 testColor;

//uniform vec4 rect_Color;
uniform sampler2D u_Texture[2];

void main()
{

	color = vec4(1, 0, 0, 1);
};