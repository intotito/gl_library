#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <event/Event.hpp>
namespace event {
	class Publisher
	{
	public:
		Publisher();
		~Publisher();
		void Subscribe(Event* event);
		void Unsubscribe(EventType type, Test::Test* subscriber);
		void Notify(EventType type, int keyCode);
		void NotifyAll();
		void Update(float time);
		void ActivateKey(int keyCode);
		void DeactivateKey(int keyCode);
		static constexpr float POLL_INTERVAL = 25.0f;
		static constexpr float ACTIVATE_PRESS_INTERVAL = 200.0f;
		static constexpr float PRESS_REPEAT_INTERVAL = 125.0f;
	private:
		std::map<int, std::vector<Event*>> events;
		float time;
	};
}

