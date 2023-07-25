#SHADER VERTEX
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 vexColor;
out vec4 fColor;

void main()
{
	gl_Position = position;
	fColor = vexColor;
};

#SHADER FRAGMENT
#version 330 core

in vec4 fColor;
layout(location = 0) out vec4 color;
uniform vec4 rect_Color;
void main()
{
	color = fColor;
};