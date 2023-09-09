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
		Add(
			{	vec3(*(data + (i * stride) + 0), *(data + (i * stride) + 1), *(data + (i * stride) + 2)), 
				vec3(*(data + (i * stride) + 3), *(data + (i * stride) + 4), *(data + (i * stride) + 5)),
				vec2(*(data + (i * stride) + 6), *(data + (i * stride) + 7)),
				* (data + (i * stride) + 8) 
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