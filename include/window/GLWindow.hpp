#pragma once
#include<Renderer.hpp>
#include<vendor/glm/glm.hpp>
#include<vendor/glm/gtc/matrix_transform.hpp>
#include<vendor/imgui/imgui.h>
#include <vendor/imgui/imgui_impl_glfw.h>
#include<vendor/imgui/imgui_impl_opengl3.h>
#include <test/Test.hpp>
#include<test/ClearColor.hpp>
#include<test/TestMenu.hpp>
#include<test/Texture2D.hpp>
#include<test/Scenery.hpp>
#include<test/Cube.hpp>

class GLWindow
{
public:
	GLWindow(std::string title, int width, int height);
	~GLWindow();
	void Show();
protected:
	virtual void OnStart();
	virtual void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
	void Initialize(int width, int height);
	bool initialized;
	GLFWwindow* window;
	Renderer* renderer;
	std::string title;
	Test::TestMenu* menu;
	double lastTime;
};

