#pragma once
#include<Object.hpp>
#include<Camera.hpp>
#include<Light.hpp>
#include<vector>

class Scene {
public:
	Scene();
	~Scene();
	void Add(Object* obj);
	void Remove(Object* obj);
	void SetCamera(Camera* camera);
	void AddLight(Light* light);
	inline Camera* GetCamera() { return default_camera; }
	inline GLsizeiptr GetBufferByteSize() { return sizeof(Vertex) * MAX_BUFFER; }
	inline GLsizeiptr GetIndexByteSize() { 
		return sizeof(unsigned int) * (3 * MAX_BUFFER / 2);
	}
	inline GLsizeiptr GetIndexCount() { return indexOffset / (sizeof(unsigned int)); }
	inline glm::mat4& GetProjectionMatrix() { return proj_matrix; }
	inline glm::mat4& GetViewMatrix() { 
		glm::mat4 aa = default_camera->GetMatrix(); 
		return aa; 
	}
	inline VertexArray* GetVertexArray() { return vertexArray; }
	inline IndexBuffer* GetIndexBuffer() { return indexBuffer; }
	inline Shader* GetShader() { return default_shader; }
	void LoadUniforms(float deltaTime);
	void OnUpdate(float deltaTime);
	void OnStart();
	void AddTexture(unsigned int);

private: 
	std::vector<Object*> objects;
	std::vector<Light*> lights;
	VertexArray* vertexArray;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	GLsizeiptr bufferOffset;
	GLsizeiptr indexOffset;
	Shader* default_shader;
	Camera* default_camera;
	glm::mat4 proj_matrix;
	int MAX_BUFFER = 12000;
};