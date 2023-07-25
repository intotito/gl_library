#include<string>
#include<shader/Shader.hpp>
class VertexShader : public Shader{
private:
public:
	VertexShader(std::string& filePath);
	~VertexShader();
};