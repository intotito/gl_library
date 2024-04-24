#include<Cylinder.hpp>

Cylinder::Cylinder() : Cylinder(8)
{
}

Cylinder::Cylinder(int seg): segments(seg), radius(0.5f), stacks(4)
{
	GenerateMesh();
}

Cylinder::~Cylinder()
{

}

void Cylinder::GenerateMesh()
{
	float h = 0.5f;
	int n_Faces = (stacks - 1) * segments;
	int s_Vertices = n_Faces * 4;
	std::vector<glm::vec3> pos;
	std::vector<glm::vec3> normal;


	float longitude = glm::radians(360.0f / segments);
//	float latitude = glm::atan(h / radius);// glm::radians(180.0f / stacks);
	float x = 0, y = 0, z = 0;

	for (int i = 0; i < stacks; i++)
	{
		y = i < 2 ? h : -h;
		for (int j = 0; j < segments; j++)
		{
			float beta = j * longitude;
			x = (i == 0 || i == (stacks - 1)) ? (0.0f) : (radius * glm::cos(beta));
			z = (i == 0 || i == (stacks - 1)) ? (0.0f) : (radius * glm::sin(beta));
			glm::vec3 vv = vec3(x, y, z);
			pos.push_back(vv);
			normal.push_back(glm::vec3(x / radius, y / radius, z / radius));
			//		std::cout.precision(2);
			//		std::cout << "(" << vv.x << ", " << vv.y << ", " << vv.z << ")" << std::endl;
		}
	}
	int stride = sizeof(Vertex) / sizeof(float);
	float* data = new float[s_Vertices * stride];
	int pointer = 0;
	for (int i = 0; i < stacks - 1; i++) {
		float jara = 0.0f;
		float top = 1.0f - (i / (float)stacks);
		float bottom = 1.0f - ((i + 1.0f) / (float)stacks);
		for (int j = 0; j < segments; j++) {
			if (j == segments - 1) {
				jara = -segments;
			}
			float left = j / (float)segments;
			float right = (j + 1.0f) / (float)segments;
			int fourth = i * segments + j;
			int third = (i + 1) * segments + j;
			int second = (i + 1) * segments + j + 1 + jara;
			int first = i * segments + j + 1 + jara;

			float texId = 0.0f;// ((i % 2 == 0) ^ (j % 2 == 0));

			glm::vec2 uv_fourth = glm::vec2(left, top);
			glm::vec2 uv_third = glm::vec2(left, bottom);
			glm::vec2 uv_second = glm::vec2(right, bottom);
			glm::vec2 uv_first = glm::vec2(right, top);


			pointer = 4 * stride * (i * segments + j);

			std::copy(&(pos[first].x), &(pos[first].x) + 3, data + pointer); pointer += 3;
			std::copy(&(normal[first].x), &(normal[first].x) + 3, data + pointer); pointer += 3;
			std::copy(&(uv_first.x), &(uv_first.x) + 2, data + pointer); pointer += 2;
			std::copy(&texId, &texId + 1, data + pointer); pointer += 1;

			std::copy(&(pos[second].x), &(pos[second].x) + 3, data + pointer); pointer += 3;
			std::copy(&(normal[second].x), &(normal[second].x) + 3, data + pointer); pointer += 3;
			std::copy(&(uv_second.x), &(uv_second.x) + 2, data + pointer); pointer += 2;
			std::copy(&texId, &texId + 1, data + pointer); pointer += 1;

			std::copy(&(pos[third].x), &(pos[third].x) + 3, data + pointer); pointer += 3;
			std::copy(&(normal[third].x), &(normal[third].x) + 3, data + pointer); pointer += 3;
			std::copy(&(uv_third.x), &(uv_third.x) + 2, data + pointer); pointer += 2;
			std::copy(&texId, &texId + 1, data + pointer); pointer += 1;

			std::copy(&(pos[fourth].x), &(pos[fourth].x) + 3, data + pointer); pointer += 3;
			std::copy(&(normal[fourth].x), &(normal[fourth].x) + 3, data + pointer); pointer += 3;
			std::copy(&(uv_fourth.x), &(uv_fourth.x) + 2, data + pointer); pointer += 2;
			std::copy(&texId, &texId + 1, data + pointer); pointer += 1;



			//		std::copy(&(_A.x), &(_A.x) + 3, dataSet + index);




		//		std::cout << "(" << first << "-" << second << "-" << third << "-" << fourth << ")" << std::endl;
		}
	}
	std::cout << "Stride: " << stride << " s_Vertices: " << s_Vertices << " pos.size(): " << pos.size() << std::endl;
	Mesh m = Mesh(data, s_Vertices * stride);
	AddMesh(m);
	GenerateIndices();
	delete[] data;
}