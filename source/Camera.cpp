#include<Camera.hpp>
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::cos;
using glm::sin;
#include<iostream>
Camera::Camera(vec3 pos, vec3 v) : position(pos), Up(v)
{
	vec3 N = glm::normalize(position - Target);
	vec3 U = glm::normalize(glm::cross(Up , N));
	vec3 V = glm::normalize(glm::cross(N, U));
	std::cout << "U: (" << U.x << ", " << U.y << ", " << U.z << ")" << std::endl;
	std::cout << "V: (" << V.x << ", " << V.y << ", " << V.z << ")" << std::endl;
	std::cout << "N: (" << N.x << ", " << N.y << ", " << N.z << ")" << std::endl;
}

Camera::~Camera() {

}

glm::mat4 Camera::GetMatrix()
{
	vec3 N = glm::normalize(position - Target);
	vec3 U = glm::normalize(glm::cross(Up, N));
	vec3 V = glm::normalize(glm::cross(N, U));
	mat4 mat(
		U.x,	V.x,	N.x,	0.0f, 
		U.y,	V.y,	N.y,	0.0f, 
		U.z,	V.z,	N.z,	0.0f, 
		0.0f,	0.0f,	0.0f,	1.0f
	);

	mat4 pos(
		1.0f,	0.0f,	0.0f,		0.0f,
		0.0f,	1.0f,	0.0f,		0.0f,
		0.0f,	0.0f,	1.0f,		0.0f,
		-position.x, -position.y, -position.z, 1.0f
		
	);	
//	return glm::lookAt(position, Target, glm::vec3(0.0f, 1.0f, 0.0f));
	return mat * pos;
//	return (mat * glm::translate(mat4(1.0f), vec3(-position.x, -position.y, -position.z)));
		//position.z -= 0.-position-position.y.y0005f;
	//	return glm::transl-position-position.z.zate(mat4(1.0f), position);// *GetRotationMatrix();
}



	