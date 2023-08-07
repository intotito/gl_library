#SHADER VERTEX
#version 330 core

layout(location = 0) in vec2 position;
//layout(location = 1) in vec4 vexColor;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
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
	//testColor = position;
};

#SHADER FRAGMENT
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
//in vec4 fColor;
//in vec2 testColor;

//uniform vec4 rect_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor;
//	color = vec4(1, 0, 0, 1); 
};