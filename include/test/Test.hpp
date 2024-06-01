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
		virtual void OnKeyPressed(int keycode);
		virtual void OnUpdate(float deltaTime);
		virtual void OnRender(Renderer& renderer);
		virtual void OnImGuiRender();
		virtual void OnStart();
		//	template<typename T>
		void AddKeyListenerEvent(event::Publisher* publisher) {
			event::KeyPressedEvent* event = new event::KeyPressedEvent();
			std::function<void()> action = [=]() -> void {
				OnKeyPressed(event->GetKeyCode());
				std::cout << "Did we" << std::endl;
				};
			event->SetOwner(this);
			event->SetAction(action);
			publisher->Subscribe(event);
		}
		void RemoveKeyListenerEvent(event::Publisher* publisher) {
			publisher->Unsubscribe(event::KEY_PRESSED_EVENT, this);
		}
		inline std::string& const GetName() { return name; } 
	private:
		std::string name;
	};
}
