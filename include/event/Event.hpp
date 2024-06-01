#pragma once
#include <functional>
#include<string>
namespace Test {
	class Test;
}
namespace event {
	enum EventType { 
		KEY_PRESSED_EVENT 
	};
	class Event
	{
	public:
		Event();
		virtual ~Event();
		virtual EventType GetType() = 0;
	//	template<typename T>
		void SetAction(std::function<void()> method) {
			Event::method = method;
		}
		void SetOwner(Test::Test* test);
		inline void SetKeyCode(int keyCode) { Event::keyCode = keyCode; }
		inline int GetKeyCode() { return keyCode; }
		inline Test::Test* GetOwner() { return container; }
		inline std::function<void()> GetAction() { return method; }
	private:
		std::function<void()> method;
		Test::Test* container;
		int keyCode;
	};
}