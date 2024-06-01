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

	private:
		std::map<int, std::vector<Event*>> events;
	};

}

