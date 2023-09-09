#include <Scene.hpp>

Scene::Scene() : vertexArray(new VertexArray()), vertexBuffer(new VertexBuffer()),
	indexBuffer(new IndexBuffer()), bufferOffset(0), indexOffset(0), 
	default_shader(nullptr), default_camera(nullptr), 
	proj_matrix(glm::perspective(glm::radians(45.0f), (640.0f / 480.0f), 1.0f, 100.0f))
{
	vertexArray->Bind();
	vertexBuffer->Bind();
	vertexBuffer->SetData(nullptr, GetBufferByteSize());
	VertexArrayAttribute* posAttr	= new VertexArrayAttribute{0, 3, GL_FLOAT, GL_FALSE, "Position"};
	VertexArrayAttribute* normAttr	= new VertexArrayAttribute{1, 3, GL_FLOAT, GL_FALSE, "Normal"};
	VertexArrayAttribute* tCordAttr = new VertexArrayAttribute{2, 2, GL_FLOAT, GL_FALSE, "TexCoords"};
	VertexArrayAttribute* texIdAttr = new VertexArrayAttribute{3, 1, GL_FLOAT, GL_FALSE, "TexID"};
	VertexBufferLayout* vbl = new VertexBufferLayout();
	vbl->Add(posAttr);
	vbl->Add(normAttr);
	vbl->Add(tCordAttr);
	vbl->Add(texIdAttr);
	vertexArray->AddLayout(vbl, vertexBuffer);
	vertexBuffer->Unbind();
	indexBuffer->Bind();
	indexBuffer->SetData(nullptr, GetIndexByteSize() / sizeof(unsigned int));
	indexBuffer->Unbind();
	std::string fileName = "res/Shaders/default_shader.shader";
	default_shader = new Shader(fileName);
	default_shader->Bind();
	default_camera = new Camera(glm::vec3(0.0f, 10.0f, 25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	std::cout << "Buffer Size: " <<  GetBufferByteSize() << std::endl;
}

Scene::~Scene()
{

	vertexBuffer->Unbind();
	vertexArray->Unbind();
	default_shader->Unbind();

	delete default_shader;
	delete default_camera;
	for (int i = 0; i < objects.size(); i++) {
		delete objects[i];
	}
	delete vertexBuffer;
	delete vertexArray;
}

void Scene::Add(Object* object)
{
	vertexArray->Bind();
	vertexBuffer->Bind();
	assert((bufferOffset + object->GetByteSize()) <= GetBufferByteSize(), "Fatal Error! Scene memory limit Exceeded!!");
	object->SetSceneAddress(bufferOffset);
	auto& v = object->GetMeshes();
	for (int i = 0; i < v.size(); i++) {
		glBufferSubData(GL_ARRAY_BUFFER, bufferOffset, v[i].GetByteSize(), v[i].Data());
		bufferOffset += v[i].GetByteSize();
		std::cout << "Buffer Offset: " << bufferOffset << std::endl;
	}
	object->SetBuffer(vertexBuffer->GetID());
	vertexBuffer->Unbind();
	indexBuffer->Bind();
	unsigned int* indices = object->GetIndices(indexOffset);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, indexOffset, object->GetIndexCount() * sizeof(unsigned int), indices);
	indexOffset += object->GetIndexCount() * sizeof(unsigned int);
	free(indices);
	indexBuffer->SetCount(indexBuffer->GetCount() + object->GetIndexCount());
	indexBuffer->Unbind();
	objects.push_back(object);

	std::cout << "Index Offset: " << indexOffset << std::endl;
}

void Scene::SetCamera(Camera* camera)
{
	if (default_camera != nullptr)
	{
		delete default_camera;
		default_camera = nullptr;
	}
	default_camera = camera;
}

void Scene::LoadUniforms(float deltaTime)
{
	glm::mat4 model_matrix = glm::rotate(glm::mat4(1.0f), deltaTime / 5.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 view_matrix = default_camera->GetMatrix();
	glm::mat4 mvp = GetProjectionMatrix() * view_matrix * model_matrix;
	default_shader->SetUniformMat4f("u_MVP", mvp);
}

void Scene::OnStart()
{
	for (auto a : objects)
	{
		a->OnStart();
	}
}


void Scene::OnUpdate(float deltaTime) {
	for (auto a : objects)
	{
		a->OnUpdate(deltaTime);
	}
}

void Scene::AddLight(Light* light)
{
	lights.push_back(light);
}

void Scene::Remove(Object* obj) {
	objects.erase(std::remove(objects.begin(), objects.end(), obj));
	delete obj;
	// ehm....
}