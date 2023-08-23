#SHADER VERTEX
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;


uniform mat4 u_MVP;
uniform mat4 u_MODEL;
uniform mat3 u_TransInv;

out vec3 a_Normal;
out vec3 a_FragPos;
void main()
{
	//	gl_Position = vec4(position, 0.0f, 1.0f);
	gl_Position = u_MVP * vec4(position, 1.0f);
//	a_Normal = vec3(u_MVP * vec4(normal, 0));
	a_Normal = u_TransInv * normal;//vec3(u_MODEL * vec4(normal, 0));
	a_FragPos = vec3(u_MODEL * vec4(position, 1.0f));
	//fColor = vexColor;
	//testColor = position;
};

#SHADER FRAGMENT
#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
    vec3 position;
	vec3 color;
    float ambient;
    float diffuse;
    float specular;
};



layout(location = 0) out vec4 color;
in vec3 a_Normal;
in vec3 a_FragPos;

uniform Light light; 
uniform Material material;
uniform vec3 u_CameraPos;
uniform sampler2D u_Texture[2];
//uniform vec3 u_LightPos;
uniform mat4 u_MVP;
void main()
{
	vec4 objectColor = vec4(0.0, 0.0, 1.0, 1);
	vec3 lightColor = vec3(1.0, 1.0, 1.0);
	vec3 viewDir = normalize(u_CameraPos - a_FragPos);


	vec3 ambient = (light.color * light.ambient) * material.ambient ;

	vec3 norm = normalize(a_Normal);
	vec3 lightDir = normalize(light.position - a_FragPos);

	float NdotL = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (light.color * light.diffuse) * (NdotL * material.diffuse);

	

	vec3 H = reflect(-lightDir, norm);
	float NdotH = max(dot(viewDir, H),	0);
	vec3 specular = vec3(0.0);

	if (NdotL > 0) {
		specular = (light.color * light.specular) * (pow(NdotH, material.shininess) * material.specular);
	}


	vec3 result = clamp(ambient + diffuse + specular, 0, 1);
	color = vec4(result, 1.0);

	//color = vec4(1, 0, 0, 1);
};