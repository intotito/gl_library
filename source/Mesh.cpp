#include <Mesh.hpp>

Mesh::Mesh(float* data, int size) {
	Parse(data, size);
}

Mesh::~Mesh(){

}


void Mesh::Parse(float* data, int size)
{
	int stride = sizeof(Vertex) / sizeof(float);
	std::cout << "Stride: " << stride << std::endl;
	for (int i = 0; i < size / stride; i++)
	{
		Add(																								// Vertex Struct
			{	vec3(*(data + (i * stride) + 0), *(data + (i * stride) + 1), *(data + (i * stride) + 2)),	// Position Coordinate
				vec3(*(data + (i * stride) + 3), *(data + (i * stride) + 4), *(data + (i * stride) + 5)),	// Normal Coordinate
				vec2(*(data + (i * stride) + 6), *(data + (i * stride) + 7)),								// Texture UV Coordinate
				* (data + (i * stride) + 8)																	// Texture ID
			});
	}
//	Format();
}

float* Mesh::Data()
{
	return (float*)( & (vertices[0].position));
}

void Mesh::Transform(mat4 matrix)
{
//	matrix = glm::mat4(1.0f);
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].position = matrix * vec4(vertices[i].position, 1.0f);
		vertices[i].normal = matrix * vec4(vertices[i].position, 1.0f);
	}
	origin = matrix * vec4(origin, 1.0f);
}

void Mesh::Format(float angle)
{
	rotation.x += angle;
	for (int i = 0; i < vertices.size(); i++) {
		//	std::cout << "Position = (" << vertices[i].position.x << ", " << vertices[i].position.y
		//		<< ", " << vertices[i].position.z << ")" << std::endl;

		mat4 translate1 = mat4(
			vec4(1.0f, 0.0f, 0.0f, 0.0f), 
			vec4(0.0f, 1.0f, 0.0f, 0.0f),
			vec4(0.0f, 0.0f, 1.0f, 0.0f), 
			vec4(	-origin.x, 
					-origin.y, 
					-origin.z, 1.0f)
		);
		mat4 rotate = mat4(
			vec4(1.0f,	 0.0f,				0.0f,				0.0f),
			vec4(0.0f,	 cos(angle),		sin(angle),			0.0f),
			vec4(0.0f,	-sin(angle),		cos(angle),			0.0f),
			vec4(0.0f,	 0.0f,				0.0f,				1.0f)
		);
		mat4 translate2 = mat4(
			vec4(1.0f, 0.0f, 0.0f, 0.0f),
			vec4(0.0f, 1.0f, 0.0f, 0.0f),
			vec4(0.0f, 0.0f, 1.0f, 0.0f),
			vec4(	origin.x,
					origin.y,
					origin.z, 
				1.0f)
		);
	
		vertices[i].position = translate2 * rotate * translate1 * vec4(vertices[i].position, 1.0f);
		vertices[i].normal = translate2 * rotate * translate1 * vec4(vertices[i].normal, 1.0f);
	//	std::cout << "'Position = (" << vertices[i].position.x << ", " << vertices[i].position.y
	//		<< ", " << vertices[i].position.z << ")" << std::endl;
	}
}

void Mesh::RotateJoint(float angle, Axis axis)
{
	switch (axis) 
	{
	case X_AXIS: 
		rotation.x += angle;
		break;
	case Y_AXIS:
		rotation.y += angle;
		break;
	case Z_AXIS:
		rotation.z += angle;
		break;
	}
	mat4 translate1 = mat4(
		vec4(1.0f, 0.0f, 0.0f, 0.0f),
		vec4(0.0f, 1.0f, 0.0f, 0.0f),
		vec4(0.0f, 0.0f, 1.0f, 0.0f),
		vec4(-origin.x,
			-origin.y,
			-origin.z, 1.0f)
	);
	mat4 rotate[3] = {
		mat4(
			vec4(1.0f, 0.0f, 0.0f, 0.0f),
			vec4(0.0f, cos(angle), sin(angle), 0.0f),
			vec4(0.0f, -sin(angle), cos(angle), 0.0f),
			vec4(0.0f, 0.0f, 0.0f, 1.0f)
		),
		mat4(
			vec4(cos(angle), 0.0f, -sin(angle), 0.0f),
			vec4(0.0f, 1.0f, 0.0f, 0.0f),
			vec4(sin(angle), 0.0f, cos(angle), 0.0f),
			vec4(0.0f, 0.0f, 0.0f, 1.0f)
		),
		mat4(
			vec4(cos(angle), -sin(angle), 0.0f, 0.0f),
			vec4(sin(angle), cos(angle), 0.0f, 0.0f),
			vec4(0.0f, 0.0f, 1.0f, 0.0f),
			vec4(0.0f, 0.0f, 0.0f, 1.0f)
		)
	};
	mat4 translate2 = mat4(
		vec4(1.0f, 0.0f, 0.0f, 0.0f),
		vec4(0.0f, 1.0f, 0.0f, 0.0f),
		vec4(0.0f, 0.0f, 1.0f, 0.0f),
		vec4(origin.x,
			origin.y,
			origin.z,
			1.0f)
	);
	mat4 transformation = translate2 * rotate[axis] * translate1;
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].position = transformation * vec4(vertices[i].position, 1.0f);
		vertices[i].normal = transformation * vec4(vertices[i].normal, 1.0f);
	}
}