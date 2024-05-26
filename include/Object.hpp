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

/**
* The base Object class and the base class for every Geometry.
* 
* This class declares and defines all necessary functionality to draw and render vertices. 
*/
class Object {
public:
	/**
	* Default Constructor.
	*/
	Object();
	/**
	* Default Deconstructor.
	*/
	virtual ~Object();
	/**
	* Add a Mesh to this Object.
	* 
	* @param mesh the Mesh to be added to the Object list of Mesh. 
	*/
	void AddMesh(Mesh mesh);
	/**
	* Get the number of Vertices.
	* 
	* @return the total number of vertices in all its constituent Mesh. 
	*/
	unsigned int GetCount();
	/**
	* Get the index count.
	* 
	* @return the number of indices required to draw all its constituent Mesh.
	*/
	inline int GetIndexCount() { return indexCount; }
	/**
	* Get the Size in Byte required to store the vertices in a Buffer.
	* 
	* @return the size in Byte. 
	*/
	inline unsigned int GetByteSize() { return GetCount() * sizeof(float); }
	/** 
	* Get the vertex indices for drawing this Object.
	* 
	* @return a pointer to the indices.
	*/
	virtual const unsigned int* GetIndices() const{ return indices; }
	/**
	* Get a subset of the vertex indices for drawing part of this Object.
	* 
	* @param offset the starting index of the indices.
	* @return a pointer to the indices from an offset.
	* @deprecated This method has since been disused.
	*/
	virtual unsigned int* GetIndices(unsigned int offset) const;
	/**
	* Get vertex data that represents this Geometry.
	* 
	* @return a pointer to the data buffer.
	*/
	float* GetData();
	/**
	* Get a List of the meshes that make up this Geometry.
	* 
	* @return a reference to the list of meshes.
	*/
	inline vector<Mesh>& GetMeshes() { return mesh; }
	/**
	* This method is guaranteed to be called every Frame.
	* 
	* @param deltaTime the time ellapsed before the last call.
	*/
	virtual void OnUpdate(float deltaTime);
	/**
	* This method is called for the very time this Object is rendered.
	*/
	virtual void OnStart();
	/**
	* Set the vertex buffer address for this Object.
	* 
	* @param vb the vertex buffer address.
	*/
	inline void SetBuffer(unsigned int vb) { Object::vb = vb; }
	/**
	* Get the vertex buffer address of this Object.
	* 
	* @return the vertex buffer address
	*/
	inline unsigned int GetBuffer() { return vb; }
	/**
	* Set the scene address of this Object.
	* 
	* @param address the address of the Object in the Scene.
	*/
	inline void SetSceneAddress(unsigned int address) { sceneAddress = address; }

	//inline void setIndexAddress(unsigned int index) { indexAddress = index; }
	/**
	* Set the position of this Object.
	* 
	* This method passes the call to the Transform for this Object.
	* @param position the coordinates.
	*/
	inline void SetPosition(vec3 position) { transform.SetPosition(position); }
	/**
	* Set the rotation of this Object.
	* 
	* This method passes the call to the Transform for this Object.
	* @param rotation the angles in radians.
	*/
	inline void SetRotation(vec3 rotation) { transform.SetRotation(rotation); }
	/**
	* Set the scale of this Object.
	* 
	* This method passes the call to the Transform for this Object.
	* @param scale the x,y,z scale.
	*/
	inline void SetScale(vec3 scale) { transform.SetScale(scale); }
	/**
	* Get the position of this Object. 
	* 
	* This method passes the call to the Transform for this Object.
	* @return the positional coordinates.
	*/
	inline const vec3& GetPosition() const { return transform.GetPosition(); }
	/**
	* Get the assigned scene address of this Object.
	* 
	* @return the sceneAddress.
	*/
	inline unsigned int GetSceneAddress() { return sceneAddress; }
	/**
	* Apply a transform to the Object. 
	* 
	* This method applies a given transform to the individual meshes that make up the 
	* Object. It does not affect the Object's identity matrix, instead it only transforms
	* the vertices of the object.
	* @param matrix the transformational matrix.
	*/
	void TransformObject(glm::mat4 matrix);


private:
	unsigned int* indices;
	int indexCount;
	unsigned int sceneAddress;

protected:
	vector<Mesh> mesh;
	unsigned int vb;
	//unsigned int indexAddress;
	Transform transform;
	virtual void GenerateIndices();

};