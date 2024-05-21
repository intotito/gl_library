#pragma once
#include<vector>
#include<Mesh.hpp>
#include<vendor/glm/glm.hpp>
#include<vendor/glm/ext/matrix_common.hpp>
#include<vendor/glm/gtc/matrix_transform.hpp>
#include<GL/glew.h>
#include <iostream>
#include<Transform.hpp>
#include<texture/Texture.hpp>
using std::vector;


/// The base Object class where every Geometry inherits from.

class Object {
public:
	Object();
	virtual ~Object();
	void AddMesh(Mesh mesh);
	unsigned int GetCount();
	inline int GetIndexCount() { return indexCount; }
	inline unsigned int GetByteSize() { return GetCount() * sizeof(float); }
	virtual unsigned int* GetIndices() { return indices; }
	virtual unsigned int* GetIndices(unsigned int offset);
	float* GetData();
	inline vector<Mesh>& GetMeshes() { return mesh; }
	virtual void OnUpdate(float deltaTime);
	virtual void OnStart();
	inline void SetBuffer(unsigned int vb) { Object::vb = vb; }
	inline unsigned int GetBuffer() { return vb; }
	inline void SetSceneAddress(unsigned int address) { sceneAddress = address; }
	inline void setIndexAddress(unsigned int index) { indexAddress = index; }
	inline void SetPosition(vec3 position) { transform.SetPosition(position); }
	inline void SetRotation(vec3 rotation) { transform.SetRotation(rotation); }
	inline void SetScale(vec3 scale) { transform.SetScale(scale); }
	inline const vec3& GetPosition() const { return transform.GetPosition(); }
	inline unsigned int GetSceneAddress() { return sceneAddress; }
	void TransformObject(glm::mat4 matrix);


private:
	unsigned int* indices;
	int indexCount;
	unsigned int sceneAddress;

protected:
	vector<Mesh> mesh;
	unsigned int vb;
	unsigned int indexAddress;
	Transform transform;
	virtual void GenerateIndices();

};