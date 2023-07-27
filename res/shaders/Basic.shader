#SHADER VERTEX
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 vexColor;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoord;
out vec4 fColor;

uniform vec3 shift_Pos;
uniform mat4 u_MVP;
void main()
{
	gl_Position = u_MVP * (position + vec4(shift_Pos, 0));
	fColor = vexColor;
	v_TexCoord = texCoord;
};

#SHADER FRAGMENT
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 fColor;

uniform vec4 rect_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor;
};