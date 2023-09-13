#include<HollowCube.hpp>

HollowCube::HollowCube() : segments(6)
{
	std::cout << "Hollow Cube Constructor called" << std::endl;
	GenerateMesh();
}

HollowCube::~HollowCube()
{

}

void HollowCube::GenerateMesh()
{
	segments = 8;
	float h = 0.5f;
	float w = 0.5f;
	float z = 0.5f;
	float r = 0.25f;
	float phi = (360.0f / segments);
	float ratio_sum = (90.0f / phi);
	float ratios[2] = { glm::ceil( glm::ceil(ratio_sum) / 2.0f), ratio_sum - glm::ceil(glm::ceil(ratio_sum) / 2.0f) };
	std::cout << "Ratios: {" << ratios[0] << ", " << ratios[1] << "}" << std::endl;




	int n_Vertices = segments * 2 * 2;
	int n_Faces = 4 * segments;

	std::vector<vec3> pos;
	std::vector<vec3> normal;
	std::vector<vec2> texCoord;
	float t = 0.0f;

	float A[] = {
		 w,		 0.0f,	
		 0.0f,	 h,
		-w,		 0.0f,
		 0.0f,	 -h
	};

	glm::vec2 P[] = {
		glm::vec2( w,	  0.0f	),	glm::vec2( w,		 h		),	
		glm::vec2( 0.0f,  h		),	glm::vec2(-w,		 h		),
		glm::vec2(-w,	  0.0f	),	glm::vec2(-w,		-h		),
		glm::vec2( 0.0f, -h		),	glm::vec2( w,		-h		)
	};

	glm::vec2 T[] = {
		glm::vec2( 0.0f,  h		),	glm::vec2(-w,		 0.0f	), 
		glm::vec2(-w,	  0.0f	),	glm::vec2( 0.0f,	-h		), 
		glm::vec2( 0.0f, -h		),	glm::vec2( w,		 0.0f	), 
		glm::vec2( w,	  0.0f	),	glm::vec2( 0.0f,	 h		)
	};
	float x = 0.0f;
	float y = 0.0f;

	for (int i = 0; i < segments; i++)
	{
		
		float theta = i * phi;
		int quadrant = glm::floor(theta / 90.0f) + 1;
		float target = 0.0f;
		float start = 0.0f;// 90.0f * quadrant - 90.0f;
		float ratio = 0.0f;

		int branch = 0;
		if (theta < (quadrant - 1) * 90.0f + (ratios[(quadrant + 1) % 2] / ratio_sum) * 90.0f)
		{
			start = 90.0f * (quadrant - 1);
			target = start + ((ratios[(quadrant + 1) % 2] / ratio_sum) * 90.0f);
			ratio = (theta - start) / (target - start);
			branch = 0;
			x = P[(quadrant - 1) * 2].x + T[(quadrant - 1) * 2].x * ratio;
			y = P[(quadrant - 1) * 2].y	+ T[(quadrant - 1) * 2].y * ratio;
		}
		else {
			start = 90.0f * (quadrant - 1) + (ratios[(quadrant + 1) % 2] / ratio_sum * 90.0f);
			target = start + ((ratios[quadrant % 2] / ratio_sum) * 90.0f);// 90.0f * quadrant;
			ratio = (theta - start) / (target - start);
			branch = 1;
			x = P[(quadrant - 1) * 2 + 1].x		+ T[(quadrant - 1) * 2 + 1].x * ratio;
			y = P[(quadrant - 1) * 2 + 1].y		+ T[(quadrant - 1) * 2 + 1].y * ratio;
		}
		float kx = 1.0f / w / 2.0f;
		float ky = 1.0f / h / 2.0f;

		pos.push_back(vec3(x, y, z));
		normal.push_back(vec3(0.0f, 0.0f, 1.0f));
		texCoord.push_back(vec2(kx * (w + x), ky * (h + y)));
		t = 0.0f;

		std::cout << "i : " << i << " phi:" << phi << " quadrant: " << quadrant << " Theta: " << theta << "\tStart: " << 
			start << "\tTarget: " << target << "\tRatio: " << ratio << "\tBranch: " << branch
			<< "\tx: " << x << "\ty: " << y << std::endl;
	}
	vector<vec3> position(pos.size() * 4);
	vector<vec3> norm(segments * 4);
	
	float angle = 0.0f;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < segments; j++)
		{
			float theta = j * phi;
			x = r * glm::cos(glm::radians(theta));
			y = r * glm::sin(glm::radians(theta));
			vec3 coord = glm::rotate(mat4(1.0f), glm::radians(angle), vec3(1.0f, 0.0f, 0.0f)) * vec4(x, y, z, 1.0f);
			vec3 posi = glm::rotate(mat4(1.0f), glm::radians(angle), vec3(1.0f, 0.0f, 0.0f)) * vec4(pos[j], 1.0f);
			vec3 nor = glm::rotate(mat4(1.0f), glm::radians(angle), vec3(1.0f, 0.0f, 0.0f)) * vec4(normal[j], 1.0f);
			position[(i * segments * 2) + j] = coord;
			position[((i + 1) * segments) + j]	= posi;
			norm[(i * segments * 2) + j] = nor;
			norm[((i + 1) * segments) + j] = nor;
		}
		angle += 180.0f;
	}
	int stride = sizeof(Vertex) / sizeof(float);
	float* data = new float[n_Faces * 4];

	for (int i = 0; i < segments; i++)
	{
		for (int j = 0; j < 4; j++)
		{

		}
	}
}