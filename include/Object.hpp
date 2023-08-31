#pragma once
#include<vector>
#include<Mesh.hpp>
#include<vendor/glm/glm.hpp>
#include<vendor/glm/ext/matrix_common.hpp>
#include<vendor/glm/gtc/matrix_transform.hpp>

#include <iostream>
using std::vector;

class Object {
public:
	Object();
	virtual ~Object();
	void AddMesh(Mesh mesh);
	int GetCount();
	inline int GetIndexCount() { return indexCount; }
	inline int GetSize() { return GetCount() * sizeof(float); }
	virtual void GenerateIndices();
//	virtual void RotateX(float angleRad);
//	virtual void RotateY(float angleRad);
//	virtual void RotateZ(float angleRad);
	virtual void Translate(glm::vec3 translation);
	virtual void RTranslate(glm::vec3 rTranslation);
	virtual glm::mat4 GetModelMatrix();
	inline glm::mat3 GetTransposeInverseMatrix() { return transpose_inverse_matrix; }

private:
	vector<Mesh> mesh;
	unsigned int* indices;
	int indexCount;
	glm::mat4 model_matrix = glm::mat4(1.0f);
	glm::mat3 transpose_inverse_matrix = glm::mat3(1.0f);
protected:
	bool state_changed = false;
	glm::vec3 translation = glm::vec3(0.0f);
//	glm::vec3 scale;
//	glm::vec3 rotation;

};