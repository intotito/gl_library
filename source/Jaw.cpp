#include <Jaw.hpp>

const float Jaw::MAX_ANGLE_RAD = glm::radians(0.0f);
const float Jaw::MIN_ANGLE_RAD = glm::radians(-90.0f);
Jaw::Jaw() : Object()
{
	float data[432] = {
		//	MESH 1
		//	Position		--			Normal			--			Texture UV			--		Texture ID	--	Label	-- Index
			-0.5f,	 0.0f,	 0.5f,		 0.0f,	 0.0f,	 1.0f,		0.0f,	0.1f,				0.0f,			// A		 0
			-0.5f,	-0.1f,	 0.5f,		 0.0f,	 0.0f,	 1.0f,		0.0f,	0.0f,				0.0f,			// B		 1
			 0.5f,	-0.1f,	 0.5f,		 0.0f,	 0.0f,	 1.0f,		1.0f,	0.0f,				0.0f,			// C		 2
			 0.5f,	 0.0f,	 0.5f,		 0.0f,	 0.0f,	 1.0f,		1.0f,	0.1f,				0.0f,			// D		 3

			-0.5f,	 0.0f,	 0.5f,		-1.0f,	 0.0f,	 0.0f,		1.0f,	0.1f,				0.0f,			// A		 4
			-0.5f,	 0.0f,	-0.5f,		-1.0f,	 0.0f,	 0.0f,		0.0f,	0.1f,				0.0f,			// E		 5
			-0.5f,	-0.1f,	-0.5f,		-1.0f,	 0.0f,	 0.0f,		0.0f,	0.0f,				0.0f,			// F		 6
			-0.5f,	-0.1f,	 0.5f,		-1.0f,	 0.0f,	 0.0f,		1.0f,	0.0f,				0.0f,			// B		 7

			-0.5f,	 0.0f,	-0.5f,		0.0f,	 0.0f,	 -1.0f,		1.0f,	0.1f,				0.0f,			// E		 8
			 0.5f,	 0.0f,	-0.5f,		0.0f,	 0.0f,	 -1.0f,		0.0f,	0.1f,				0.0f,			// G		 9
			 0.5f,	-0.1f,	-0.5f,		0.0f,	 0.0f,	 -1.0f,		0.0f,	0.0f,				0.0f,			// H		10
			-0.5f,	-0.1f,	-0.5f,		0.0f,	 0.0f,	 -1.0f,		1.0f,	0.0f,				0.0f,			// F		11

			 0.5f,	-0.1f,	 0.5f,		1.0f,	 0.0f,	 0.0f,		0.0f,	0.0f,				0.0f,			// C		12
			 0.5f,	-0.1f,	-0.5f,		1.0f,	 0.0f,	 0.0f,		1.0f,	0.0f,				0.0f,			// H		13
			 0.5f,	 0.0f,	-0.5f,		1.0f,	 0.0f,	 0.0f,		1.0f,	0.1f,				0.0f,			// G		14
			 0.5f,	 0.0f,	 0.5f,		1.0f,	 0.0f,	 0.0f,		0.0f,	0.1f,				0.0f,			// D		15

			-0.5f,	 0.0f,	 0.5f,		0.0f,	 1.0f,	 0.0f,		0.0f,	0.0f,				0.0f,			// A		16
			 0.5f,	 0.0f,	 0.5f,		0.0f,	 1.0f,	 0.0f,		1.0f,	0.0f,				0.0f,			// D		17
			 0.5f,	 0.0f,	-0.5f,		0.0f,	 1.0f,	 0.0f,		1.0f,	1.0f,				0.0f,			// G		18
			-0.5f,	 0.0f,	-0.5f,		0.0f,	 1.0f,	 0.0f,		0.0f,	1.0f,				0.0f,			// E		19

			-0.5f,	-0.1f,	 0.5f,		0.0f,	-1.0f,	 0.0f,		1.0f,	0.0f,				0.0f,			// B		20
			-0.5f,	-0.1f,	-0.5f,		0.0f,	-1.0f,	 0.0f,		1.0f,	1.0f,				0.0f,			// F		21
			 0.5f,	-0.1f,	-0.5f,		0.0f,	-1.0f,	 0.0f,		0.0f,	1.0f,				0.0f,			// H		22
			 0.5f,	-0.1f,	 0.5f,		0.0f,	-1.0f,	 0.0f,		0.0f,	0.0f,				0.0f,			// C		23

			  // MESH 2

			-0.5f,	 0.1f,	 0.5f,		 0.0f,	 0.0f,	 1.0f,		0.0f,	0.1f,				1.0f,			// I		24
			-0.5f,	 0.0f,	 0.5f,		 0.0f,	 0.0f,	 1.0f,		0.0f,	0.0f,				1.0f,			// J		25
			 0.5f,	 0.0f,	 0.5f,		 0.0f,	 0.0f,	 1.0f,		1.0f,	0.0f,				1.0f,			// K		26
			 0.5f,	 0.1f,	 0.5f,		 0.0f,	 0.0f,	 1.0f,		1.0f,	0.1f,				1.0f,			// L		27

			-0.5f,	 0.0f,	-0.5f,		-1.0f,	 0.0f,	 0.0f,		1.0f,	0.1f,				1.0f,			// E		28
			-0.5f,	 0.0f,	 0.5f,		-1.0f,	 0.0f,	 0.0f,		0.0f,	0.1f,				1.0f,			// J		29
			-0.5f,	 0.1f,	 0.5f,		-1.0f,	 0.0f,	 0.0f,		0.0f,	0.0f,				1.0f,			// I		30
			-0.5f,	 0.1f,	-0.5f,		-1.0f,	 0.0f,	 0.0f,		1.0f,	0.0f,				1.0f,			// M		31

			-0.5f,	 0.0f,	-0.5f,		0.0f,	 0.0f,	-1.0f,		1.0f,	0.1f,				1.0f,			// E		32
			-0.5f,	 0.1f,	-0.5f,		0.0f,	 0.0f,	-1.0f,		0.0f,	0.1f,				1.0f,			// M		33
			 0.5f,	 0.1f,	-0.5f,		0.0f,	 0.0f,	-1.0f,		0.0f,	0.0f,				1.0f,			// N		34
			 0.5f,	 0.0f,	-0.5f,		0.0f,	 0.0f,	-1.0f,		1.0f,	0.0f,				1.0f,			// G		35

			 0.5f,	 0.0f,	-0.5f,		1.0f,	 0.0f,	 0.0f,		0.0f,	0.0f,				1.0f,			// G		36
			 0.5f,	 0.1f,	-0.5f,		1.0f,	 0.0f,	 0.0f,		1.0f,	0.0f,				1.0f,			// N		37
			 0.5f,	 0.1f,	 0.5f,		1.0f,	 0.0f,	 0.0f,		1.0f,	0.1f,				1.0f,			// L		38
			 0.5f,	 0.0f,	 0.5f,		1.0f,	 0.0f,	 0.0f,		0.0f,	0.1f,				1.0f,			// K		39

			-0.5f,	 0.1f,	 0.5f,		0.0f,	 1.0f,	 0.0f,		0.0f,	0.0f,				1.0f,			// I		40
			 0.5f,	 0.1f,	 0.5f,		0.0f,	 1.0f,	 0.0f,		1.0f,	0.0f,				1.0f,			// L		41
			 0.5f,	 0.1f,	-0.5f,		0.0f,	 1.0f,	 0.0f,		1.0f,	1.0f,				1.0f,			// N		42
			-0.5f,	 0.1f,	-0.5f,		0.0f,	 1.0f,	 0.0f,		0.0f,	1.0f,				1.0f,			// M		43	

			-0.5f,	 0.0f,	-0.5f,		0.0f,	-1.0f,	 0.0f,		0.0f,	0.0f,				1.0f,			// E		44
			 0.5f,	 0.0f,	-0.5f,		0.0f,	-1.0f,	 0.0f,		1.0f,	0.0f,				1.0f,			// G		45
			 0.5f,	 0.0f,	 0.5f,		0.0f,	-1.0f,	 0.0f,		1.0f,	1.0f,				1.0f,			// K		46
			-0.5f,	 0.0f,	 0.5f,		0.0f,	-1.0f,	 0.0f,		0.0f,	1.0f,				1.0f,			// J		47
	};

/*	
	float indices[72] = {
		 0,   1,  2,		 2,  3,  0,
		 4,   5,  6,		 6,  7,  4,
		 8,   9, 10,		10, 11,  8,
		 12, 13, 14,		14, 15, 12,
		 16, 17, 18,		18, 19, 16,
		 20, 21, 22,		22, 23, 20,

		 24, 25, 26,		26, 27, 24,
		 28, 29, 30,		30, 31, 28,
		 32, 33, 34,		34, 35, 32,
		 36, 37, 38,		38, 39, 36,
		 40, 41, 42,		42, 43, 40,
		 44, 45, 46,		46, 47, 44

	};
*/

	Mesh m = Mesh(data, (sizeof(data) / sizeof(float)) / 2);

	Mesh m1 = Mesh(data + (sizeof(data) / sizeof(float)) / 2, (sizeof(data) / sizeof(float)) / 2);

//	m1.Format(glm::radians(90.0f));
//	GenerateMesh();
	AddMesh(m);
	AddMesh(m1);
	GenerateIndices();
}
Jaw::~Jaw()
{

}

void Jaw::OnUpdate(float deltaTime) 
{
	static int sign = -1;
//	float angle = mesh[1].rotation.x;
	float angle = glm::radians(deltaTime);
	
	mesh[1].Format(angle);


//	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	
	float offset = GetSceneAddress() + mesh[0].GetByteSize();
	glBufferSubData(GL_ARRAY_BUFFER, offset, mesh[1].GetByteSize(), mesh[1].Data());


//	std::cout << "Angle: " << glm::degrees(angle) << " Delta " << deltaTime << std::endl;
}



