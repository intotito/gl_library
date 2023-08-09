#SHADER VERTEX
#version 330 core

layout(location = 0) in vec2 position;
//layout(location = 1) in vec4 vexColor;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texIndex;
out vec2 v_TexCoord;
out float v_TexIndex;
//out vec4 fColor;
//out vec2 testColor;
//uniform vec3 shift_Pos;
uniform mat4 u_MVP;
void main()
{
//	gl_Position = vec4(position, 0.0f, 1.0f);
	gl_Position = u_MVP * vec4(position, 0.0f, 1.0f);
	//fColor = vexColor;
	v_TexCoord = texCoord;
	v_TexIndex = texIndex;
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
	int index = int(v_TexIndex);
	vec4 texColor = texture(u_Texture[index], v_TexCoord);
//	vec4 texColor = vec4(u_Texture[index], u_Texture[index], u_Texture[index], 1);
	color = texColor;
//	color = vec4(index, index, 1, 1);
};