#include<Object.hpp>

class HollowCube : public Object{
public:
	HollowCube();
	~HollowCube();

private:
	void GenerateMesh();
	int segments;
};