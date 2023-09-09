#SHADER VERTEX
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;


uniform mat4 u_MVP;
uniform mat4 u_MODEL;
uniform mat3 u_TransInv;

out vec3 a_Normal;
out vec3 a_FragPos;
out vec2 a_TexCoords;
void main()
{
	gl_Position = u_MVP * vec4(position, 1.0f);
	a_Normal = u_TransInv * normal;
	a_FragPos = vec3(u_MODEL * vec4(position, 1.0f));
	a_TexCoords = texCoords;
};

#SHADER FRAGMENT
#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct Light {
    vec3 position;
	vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
	float linear;
	float quadratic;

	float cutOff;
	float outerCutOff;
};



layout(location = 0) out vec4 color;
in vec3 a_Normal;
in vec3 a_FragPos;
in vec2 a_TexCoords;

uniform Light light; 
uniform Material material;
uniform vec3 u_CameraPos;
uniform sampler2D u_Texture[2];
uniform mat4 u_MVP;
uniform float u_Time;
void main()
{
	float distance = length(light.position - a_FragPos);
	float attenuation = 1.0 / (light.constant + distance * light.linear + distance * distance * light.quadratic);
	vec3 viewDir = normalize(u_CameraPos - a_FragPos);


	vec3 ambient = light.ambient * vec3(texture(material.diffuse, a_TexCoords));// * material.ambient ;

	vec3 norm = normalize(a_Normal);
//	vec3 lightDir = normalize(light.position - a_FragPos);
	vec3 lightDir = normalize(u_CameraPos - a_FragPos);
	float NdotL = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * NdotL * vec3(texture(material.diffuse, a_TexCoords));

	
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;

	vec3 H = reflect(-lightDir, norm);
	float NdotH = max(dot(viewDir, H),	0);
	vec3 specular = vec3(0.0);

	if (NdotL > 0) {
		specular = light.specular * (pow(NdotH, material.shininess) * vec3(texture(material.specular, a_TexCoords)));
	}

	vec3 emission = vec3(0.0);

	if(texture(material.specular, a_TexCoords).r < 0.1){
		emission = vec3(texture(material.emission, a_TexCoords + vec2(0.0, u_Time)));
	//	emission = emission * (sin(u_Time) * 0.5 + 0.5) * 2.0;
	}

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

//	vec3 result = clamp(diffuse + specular, 0, 1);
//	vec3 result = clamp(ambient + diffuse + specular + emission, 0, 1);
	if(theta > light.cutOff){
		float bias = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
//		ambient *=	bias;
		diffuse *=	bias;
		specular *=	bias;
		color = vec4(clamp(ambient + diffuse + specular + emission, 0, 1), 1);
	}
	else{
		color = vec4(ambient, 1);
	}

//	color = vec4(1, 0, 0, 1);
};