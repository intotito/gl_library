#pragma once

#include <test/ClearColor.hpp>

namespace Test {
	ClearColor::ClearColor(std::string name) : Test(name), color{ 0.0f, 0.0f, 0.0f, 1.0f } 
	{

	}

	ClearColor::~ClearColor() {

	}

	void ClearColor::OnUpdate(float deltaTime)
	{

	}

	void ClearColor::OnRender(Renderer& renderer)
	{
		glClearColor(color[0], color[1], color[2], color[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void ClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Background Color", color);
	}
}
