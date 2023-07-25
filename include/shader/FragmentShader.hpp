#include<string>
#include<shader/Shader.hpp>
class FragmentShader : public Shader {
private:
public:
	FragmentShader(std::string& filePath);
	~FragmentShader();
};