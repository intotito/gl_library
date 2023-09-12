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
	float h = 0.5f;
	float w = 0.5f;
	float z = 0.0f;
	float phi = (360.0f / segments);
	float ratio_sum = (90.0f / phi);
	float ratios[2] = {glm::ceil(ratio_sum / 2.0f), ratio_sum - glm::ceil(ratio_sum / 2.0f)};
	std::cout << "Ratios: {" << ratios[0] << ", " << ratios[1] << "}" << std::endl;
	float A[] = {
		w, z, 
		z, h,
		-w, z,
		z, -h
	};

	glm::vec2 T[] = {
		glm::vec2(0.0f, 1.0f), glm::vec2(-1.0f, 0.0f), 
		glm::vec2(-1.0f, 0.0f), glm::vec2(0.0f, -1.0f), 
		glm::vec2(0.0f, -1.0f), glm::vec2(1.0f, 0.0f), 
		glm::vec2(1.0f, 0.0f), glm::vec2(0.0f, 1.0f)
	};
	
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
		}
		else {
			start = 90.0f * (quadrant - 1) + (ratios[(quadrant + 1) % 2] / ratio_sum * 90.0f);
			target = start + ((ratios[quadrant % 2] / ratio_sum) * 90.0f);// 90.0f * quadrant;
			ratio = (theta - start) / (target - start);
			branch = 1;
		}

		std::cout << "i : " << i << " phi:" << phi << " quadrant: " << quadrant << " Theta: " << theta << "\tStart: " << 
			start << "\tTarget: " << target << "\tBranch: " << branch << std::endl;
	}
}