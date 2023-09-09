#SHADER VERTEX
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float texIndex;

out vec2 v_TexCoord;
out vec3 v_Normal;
out float v_TexIndex;

uniform mat4 u_MVP;
void main()
{
	gl_Position = u_MVP * vec4(position, 1.0f);
	if(texIndex == 3.0){
	//	gl_Position += vec4(2.5, -1.5, 0, 0);
	} else {
//		gl_Position -= vec4(2.5, 0, 0, 0);
	}
	v_TexCoord = texCoord;
	v_TexIndex = texIndex;
	v_Normal = normal;

};

#SHADER FRAGMENT
#version 330 core

float rand(vec2 co);
layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_TexIndex;


void main()
{
	if(v_TexIndex == 0.0f){
		//color = vec4(0.0, rand(vec2(gl_FragCoord) + vec2(0.3, -0.3)), rand(vec2(gl_FragCoord)), 1.0);
		color = vec4(0.9, 0.9, 0.9, 1);
	} else if(v_TexIndex == 1.0f){
		//color = vec4(rand(vec2(gl_FragCoord) + vec2(0.3, -0.3)), 0.0, rand(vec2(gl_FragCoord)), 1.0);
		color = vec4(0.1, 0.3, 0.8, 1);
	} else {
		color = vec4(0.0, 1.0, 0.0, 1.0);
	}
};

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
};