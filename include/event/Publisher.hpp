#pragma once
#include<event/Event.hpp>
#include <map>
#include <vector>
#include <string>
#include <iostream>
namespace event {
	class Publisher
	{
	public:
		Publisher();
		~Publisher();
		void Subscribe(Event* event);
		void Unsubscribe(Event* event);
		void Notify(std::string type);
		void NotifyAll();

	private:
		std::map<std::string, std::vector<Event*>> events;
	};

}

