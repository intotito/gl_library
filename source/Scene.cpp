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
	assert((bufferOffset + object->GetByteSize()) <= GetBufferByteSize(), "Fatal Error! Scene memory limit Exceeded!!");
	object->SetSceneAddress(bufferOffset);
	auto& v = object->GetMeshes();
	vertexArray->Bind();
	for (int z = 0; z < v.size(); z++) {
		std::cout << "Buffer Offset: " << bufferOffset << " Size: " << v[z].GetByteSize() << std::endl;
		vertexBuffer->Bind();
		glBufferSubData(GL_ARRAY_BUFFER, bufferOffset, v[z].GetByteSize(), v[z].Data());
		bufferOffset += v[z].GetByteSize();
		vertexBuffer->Unbind();
/*		for (int i = 0; i < v[z].GetByteSize() / sizeof(float) / (sizeof(Vertex) / sizeof(float)); i++)
		{
			std::cout << "V[" << i << "] : ";
			for (int j = 0; j < (sizeof(Vertex) / sizeof(float)); j++)
			{
				std::cout << *(((float*)v[z].Data()) + (i * (sizeof(Vertex) / sizeof(float)) + j)) << ", ";
			}
			std::cout << std::endl;
		}
*/	}
	object->SetBuffer(vertexBuffer->GetID());
	indexBuffer->Bind();
	// unsigned int* indices = object->GetIndices(indexOffset);
	unsigned int* indices = AppendIndices(object->GetIndices(), object->GetIndexCount());
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, indexOffset, object->GetIndexCount() * sizeof(unsigned int), indices);
	indexOffset += object->GetIndexCount() * sizeof(unsigned int);
	//free(indices);
	delete indices;
	indexBuffer->SetCount(indexBuffer->GetCount() + object->GetIndexCount());
	indexBuffer->Unbind();
	objects.push_back(object);

	std::cout << "Index Offset: " << indexOffset << " Scene address " << object->GetSceneAddress() << std::endl;
}

unsigned int* Scene::AppendIndices(const unsigned int* indices, int size) const
{
	unsigned int* indx = new unsigned int[size];
	for (int i = 0; i < size; i++) {
		indx[i] = indexOffset + *(indices + i);
	}
	return indx;
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

void Scene::LoadDeltaTimeUniform(float deltaTime)
{
	glm::mat4 model_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//	glm::mat4 model_matrix = glm::rotate(glm::mat4(1.0f), deltaTime * 1/ 5.0f, glm::vec3(0.65f, 0.24f, 0.16f));
	glm::mat4 view_matrix = default_camera->GetMatrix();
	glm::mat4 mvp = GetProjectionMatrix() * view_matrix * model_matrix;
	default_shader->SetUniformMat4f("u_MVP", mvp);
}

void Scene::LoadTextures(std::vector<std::string>& tex)
{
	default_shader->Bind();
	std::vector<int> vv;
	for (int i = 0; i < tex.size(); i++)
	{
		GLuint texture = Texture::LoadTexture(tex[i].c_str());
		vv.push_back(i);
	}
	default_shader->SetUniform1iv("u_Texture", vv.size(), (int*)&vv[0]);
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