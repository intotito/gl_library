#SHADER VERTEX
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 vexColor;
out vec4 fColor;
uniform vec3 shift_Pos;

void main()
{
	gl_Position = position + vec4(shift_Pos, 0);
	fColor = vexColor;
};

#SHADER FRAGMENT
#version 330 core

in vec4 fColor;
layout(location = 0) out vec4 color;
uniform vec4 rect_Color;
void main()
{
	color = rect_Color;
};