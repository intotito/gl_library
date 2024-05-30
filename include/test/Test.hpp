#pragma once
#include <Renderer.hpp>
#include <vendor/imgui/imgui.h>
#include <event/Event.hpp>
namespace Test {
	class Test {
	public:
		Test(std::string name);
		virtual ~Test();
		virtual void OnKeyPressed(int keycode);
		virtual void OnUpdate(float deltaTime);
		virtual void OnRender(Renderer& renderer);
		virtual void OnImGuiRender();
		virtual void OnStart();
		template<typename T>
		void AddEvent(event::Event event) {
		//	event.SetAction();
		}
		inline std::string& const GetName() { return name; } 
	private:
		std::string name;
	};
}
