#include <HollowCylinder.hpp>

HollowCylinder::HollowCylinder() : HollowCylinder(16, 0.375f)
{

}

HollowCylinder::HollowCylinder(int segments, float radius)
{
	HollowCylinder::segments = segments;
	HollowCylinder::radius = radius;
	GenerateMesh();
}

HollowCylinder::~HollowCylinder()
{

}

void HollowCylinder::GenerateMesh()
{
	float r = 0.5f;
	float phi = (360.0f / segments);
	float ratio_sum = (90.0f / phi);


	int n_Vertices = segments * 2 * 2;
	int n_Faces = 4 * segments;

	float t = 1.0f;

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.5f;
	float kx = 1.0f / r / 2.0f;
	float ky = 1.0f / r / 2.0f;


	vector<vec3> position(segments * 4);
	vector<vec3> norm(segments * 4);
	vector<vec2> tCoord(segments * 4);

	float Tz = 0.0f;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < segments; j++)
		{
			float theta = j * phi;
			vec3 holePos =	vec3(radius * glm::cos(glm::radians(theta)), radius * glm::sin(glm::radians(theta)), z + Tz);
			vec3 posi =		vec3(r * glm::cos(glm::radians(theta)), r * glm::sin(glm::radians(theta)), z + Tz);
			vec3 nor = glm::rotate(mat4(1.0f), glm::radians(i % 2 == 0 ? 0.0f : 180.0f), vec3(0.0f, 0.0f, 1.0f)) * vec4(0.0f, 0.0f, 1.0f, 1.0f);
			vec2 tCod = glm::rotate(mat4(1.0f), glm::radians(i % 2 == 0 ? 0.0f : 180.0f), vec3(0.0f, 0.0f, 1.0f)) * vec4(kx * (r + posi.x), ky * (r + posi.y), 0.0f, 1.0f);

			position[((2 * i + 0) * segments) + j] = holePos;
			position[((2 * i + 1) * segments) + j] = posi;

			norm[((2 * i + 0) * segments) + j] = nor;
			norm[((2 * i + 1) * segments) + j] = nor;

			tCoord[((2 * i + 0) * segments) + j] = glm::rotate(mat4(1.0f), glm::radians(i % 2 == 0 ? 0.0f : 180.0f), vec3(0.0f, 0.0f, 1.0f)) * vec4(kx * (r + holePos.x), ky * (r + holePos.y), 0.0f, 1.0f);
			tCoord[((2 * i + 1) * segments) + j] = tCod;



		}
		Tz += (-2.0f * z);
	}
	int stride = sizeof(Vertex) / sizeof(float);
	float* data = new float[n_Faces * 4 * stride];

	int pattern[16] = {

							0 * segments + 0,	1 * segments + 0,	1 * segments + 1, 0 * segments + 1,
							2 * segments + 0,	0 * segments + 0,	0 * segments + 1, 2 * segments + 1,
							1 * segments + 0,	3 * segments + 0,	3 * segments + 1, 1 * segments + 1,
							3 * segments + 0,	2 * segments + 0,	2 * segments + 1, 3 * segments + 1,

							/*					 0,  8,  9,  1,
												 0,  1, 17, 16, // 16, 0, 1, 17
												 8, 24, 25,  9,
												16, 17, 25, 24	// 24, 16, 17, 25
							*/ };

	int pointer = 0;
	for (int i = 0; i < 4; i++)
	{
		t = 0.0f;// (i + 3) % 3 == 0 ? 1 : 2;
		float jara = 0.0f;
		for (int j = 0; j < segments; j++)
		{

			for (int k = 0; k < 4; k++) {
				if (j == segments - 1 && (k >= 2)) {
					jara = -segments;
				}
				std::copy(&(position[j + pattern[i * 4 + k] + jara].x), &(position[j + pattern[i * 4 + k] + jara].x) + 3, data + pointer);	pointer += 3;
				std::copy(&(norm[j + pattern[i * 4 + k] + jara].x), &(norm[j + pattern[i * 4 + k] + jara].x) + 3, data + pointer);	pointer += 3;
				std::copy(&(tCoord[j + pattern[i * 4 + k] + jara].x), &(tCoord[j + pattern[i * 4 + k] + jara].x) + 2, data + pointer);	pointer += 2;
				std::copy(&t, &t + 1, data + pointer);	pointer++;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}

	Mesh m = Mesh(data, n_Vertices * stride * 4);
	AddMesh(m);
	GenerateIndices();
	delete[] data;
}