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
	segments = 24;
	float h = 0.5f;
	float w = 0.5f;
	float z = 0.5f;
	float r = 0.375f;
	float phi = (360.0f / segments);
	float ratio_sum = (90.0f / phi);
	float ratios[2] = { glm::ceil( glm::ceil(ratio_sum) / 2.0f), ratio_sum - glm::ceil(glm::ceil(ratio_sum) / 2.0f) };
	std::cout << "Ratios: {" << ratios[0] << ", " << ratios[1] << "}" << std::endl;




	int n_Vertices = segments * 2 * 2;
	int n_Faces = 4 * segments;

	std::vector<vec3> pos;
	std::vector<vec3> normal;
	std::vector<vec2> texCoord;
	float t = 1.0f;

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
	float kx = 1.0f / w / 2.0f;
	float ky = 1.0f / h / 2.0f;

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
		

		pos.push_back(vec3(x, y, z));
		normal.push_back(vec3(0.0f, 0.0f, 1.0f));
		texCoord.push_back(vec2(kx * (w + x), ky * (h + y)));
		

		std::cout << "i : " << i << " phi:" << phi << " quadrant: " << quadrant << " Theta: " << theta << "\tStart: " << 
			start << "\tTarget: " << target << "\tRatio: " << ratio << "\tBranch: " << branch
			<< "\tx: " << x << "\ty: " << y << std::endl;
	}
	vector<vec3> position(pos.size() * 4);
	vector<vec3> norm(segments * 4);
	vector<vec2> tCoord(segments * 4);
	
	float Tz = 0.0f;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < segments; j++)
		{
			float theta = j * phi;
			x = r * glm::cos(glm::radians(theta));
			y = r * glm::sin(glm::radians(theta));
			vec3 holePos = vec3(x, y, z + Tz);// glm::rotate(mat4(1.0f), glm::radians(Tz), vec3(1.0f, 0.0f, 0.0f))* vec4(x, y, z, 1.0f);
			vec3 posi = pos[j] + vec3(0.0f, 0.0f, Tz);
			vec3 nor = glm::rotate(mat4(1.0f), glm::radians(i % 2 == 0 ? 0.0f : 180.0f), vec3(0.0f, 0.0f, 1.0f)) * vec4(normal[j], 1.0f);
			vec2 tCod = glm::rotate(mat4(1.0f), glm::radians(i % 2 == 0 ? 0.0f : 180.0f), vec3(0.0f, 0.0f, 1.0f)) * vec4(texCoord[j], 0.0f, 1.0f);
			
			position[((2 * i + 0) * segments) + j] = holePos;
			position[((2 * i + 1) * segments) + j] = posi;
			
			std::cout << "Trial: --- " << ((2 * i + 0) * segments) + j << " )( " << ((2 * i + 1) * segments) + j << std::endl;
			norm[((2 * i + 0) * segments) + j] = nor;
			norm[((2 * i + 1) * segments) + j] = nor;
			
	//		tCoord[(i * segments * 2) + j] = tCod; // wrong 
			tCoord[((2 * i + 0) * segments) + j] = glm::rotate(mat4(1.0f), glm::radians(i % 2 == 0 ? 0.0f : 180.0f), vec3(0.0f, 0.0f, 1.0f)) * vec4(kx * (w + x), ky * (h + y), 0.0f, 1.0f);
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
		*/				};

	int pointer = 0;
	for (int i = 0; i < 4; i++)
	{
		t = (i + 3) % 3 == 0 ? 1 : 2;
		float jara = 0.0f;
		for (int j = 0; j < segments; j++)
		{
			
			for (int k = 0; k < 4; k++) {
				if (j == segments - 1 && (k >= 2)) {
					jara = -segments;
				}
				std::copy(&(position[j	+ pattern[i * 4 + k] + jara].x), &(position[j	+ pattern[i * 4 + k] + jara].x) + 3, data + pointer);	pointer += 3;
				std::copy(&(norm[j		+ pattern[i * 4 + k] + jara].x), &(norm[j		+ pattern[i * 4 + k] + jara].x) + 3, data + pointer);	pointer += 3;
				std::copy(&(tCoord[j	+ pattern[i * 4 + k] + jara].x), &(tCoord[j		+ pattern[i * 4 + k] + jara].x) + 2, data + pointer);	pointer += 2;
				std::copy(&t,									  &t + 1,									  data + pointer);	pointer++;

				std::cout << "t: " << t << "\ti: " << i << "\tj: " << j << "\tk : " << k << "\tPosition = (" << position[j + pattern[i * 4 + k] + jara].x << ", "
					<< position[j + pattern[i * 4 + k] + jara].y << ", " << position[j + pattern[i * 4 + k] + jara].z << std::endl;
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