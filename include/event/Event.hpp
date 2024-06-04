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
	enum EventState{
		STATE_INACTIVE,
		STATE_CREATED,
		STATE_PRESSED,
		STATE_CONSUMED
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
		void SetSource(Test::Test* test);
		inline void SetKeyCode(int keyCode) { Event::keyCode = keyCode; }
		inline int GetKeyCode() { return keyCode; }
		inline Test::Test* GetSource() { return source; }
		inline std::function<void()> GetAction() { return method; }
		inline void SetState(EventState state) { State = state; }
		inline EventState GetState() { return State; }
		inline int GetTimeCreated() { return time_created; }
		inline void SetTimeCreated(float time) { time_created = time; }
		inline int GetLastUpdateTime() { return time_last; }
		inline void SetLastUpdateTime(float update) { time_last = update; }
		inline void ResetTime() { time_last = 0; time_created = 0; }
	private:
		std::function<void()> method;
		Test::Test* source;
		int keyCode;
		EventState State;
		float time_created;
		float time_last;
	};
}