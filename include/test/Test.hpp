#pragma once
#include <Renderer.hpp>
#include <vendor/imgui/imgui.h>
#include <event/Event.hpp>
#include <event/Publisher.hpp>
#include <event/KeyPressedEvent.hpp>
#include <functional>
namespace Test {
	class Test {
	public:
		Test(std::string name);
		virtual ~Test();
		virtual void OnKeyPressed(event::Event* event);
		virtual void OnUpdate(float deltaTime);
		virtual void OnRender(Renderer& renderer, float deltaTime);
		virtual void OnImGuiRender();
		virtual void OnStart();
		void AddKeyListenerEvent(event::Publisher* publisher);
		void RemoveKeyListenerEvent(event::Publisher* publisher);
		inline std::string& const GetName() { return name; } 
	private:
		std::string name;
		double lastTime;
	};
}
