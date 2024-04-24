#include <Cubex.hpp>

Cubex::Cubex()
{
	GenerateMesh();
}

Cubex::~Cubex()
{

}

void Cubex::GenerateMesh()
{
	
	int faces = 6;
	int vertexPerFace = 4;
	int sides = 2;
	glm::vec3 axis = glm::vec3(0.0f, 0.0f, 0.5f);

	int vertexCount = faces * vertexPerFace;
	int stride = sizeof(Vertex) / sizeof(float);
	float* dataSet = new float[vertexCount * stride];

	glm::vec3 A[4] = {
		glm::vec3( 0.5f,  0.5f,  0.5f),
		glm::vec3(-0.5f,  0.5f,  0.5f),
		glm::vec3(-0.5f, -0.5f,  0.5f),
		glm::vec3( 0.5f, -0.5f,  0.5f)
	};

	glm::vec2 T[4] = {
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f)
	};

	glm::vec3 N = glm::vec3(0.0f, 0.0f, 1.0f);


	int index = 0;

	float angle = glm::radians(-90.0f);
	for (int i = 0; i < faces - 2; i++)
	{
		for (int j = 0; j < vertexPerFace; j++) {
			glm::vec3 _A = glm::rotate(glm::mat4(1.0f), i * angle, vec3(0.0f, 1.0f, 0.0f)) * vec4(A[j], 1.0f);
			glm::vec3 _N = glm::rotate(glm::mat4(1.0f), i * angle, vec3(0.0f, 1.0f, 0.0f)) * vec4(N, 1.0f);
			glm::vec2 _T = T[j];
			float t = 2.0f;
		//	std::cout << "_A: (" << _A.x << ", " << _A.y << ", " << _A.z << ")" << " \t- _N: (" << _N.x << ", " << _N.y << ", " << _N.z << ")" << std::endl;
			std::copy(&(_A.x), &(_A.x) + 3, dataSet + index);
			index += 3;
			std::copy(&(_N.x), &(_N.x) + 3, dataSet + index);
			index += 3;
			std::copy(&(_T.x), &(_T.x) + 2, dataSet + index);
			index += 2;
			*(dataSet + index) = t;
			index++;
		}
	}
	for (int k = 0; k < 2; k++) {
		for (int l = 0; l < vertexPerFace; l++) {
			glm::vec3 _B = glm::rotate(glm::mat4(1.0f), (k * 2 + 1) * angle, vec3(1.0f, 0.0f, 0.0f)) * vec4(A[l], 1.0f);
			glm::vec3 _N = glm::rotate(glm::mat4(1.0f), (k * 2 + 1) * angle, vec3(1.0f, 0.0f, 0.0f)) * vec4(N, 1.0f);
			glm::vec2 _T = T[l];
			float t = 1.0f;
	//		std::cout << "_B: (" << _B.x << ", " << _B.y << ", " << _B.z << ")" << " \t- _N: (" << _N.x << ", " << _N.y << ", " << _N.z << ")" << std::endl;
			std::copy(&(_B.x), &(_B.x) + 3, dataSet + index);
			index += 3;
			std::copy(&(_N.x), &(_N.x) + 3, dataSet + index);
			index += 3;
			std::copy(&(_T.x), &(_T.x) + 2, dataSet + index);
			index += 2;
			std::copy(&t, &t + 1, dataSet + index);
		//	std::cout << "Check " << *(dataSet + index) << " Stride: " << stride << std::endl;
			index++;
		}
	}

/*	for (int i = 0; i < vertexCount * stride; i++) {
		if (i % stride == 0) {
			std::cout << std::endl;
		}
		std::cout << dataSet[i] << ", ";
	}
*/
	Mesh m = Mesh(dataSet, vertexCount * stride);
	AddMesh(m);
	GenerateIndices();
	delete[] dataSet;
}