#pragma once
#include <Renderer.hpp>
#include <vendor/imgui/imgui.h>
namespace Test {
	class Test {
	public:
		Test(std::string name);
		virtual ~Test();
		virtual void OnUpdate(float deltaTime);
		virtual void OnRender(Renderer& renderer);
		virtual void OnImGuiRender();
		virtual void OnStart();
		inline std::string& const GetName() { return name; } 
	private:
		std::string name;
	};
}
