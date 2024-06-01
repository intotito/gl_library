#include <event/Publisher.hpp>

namespace event
{
	Publisher::Publisher()
	{

	}

	Publisher::~Publisher()
	{

	}

	void Publisher::Subscribe(Event* event)
	{
		auto it = events.find(event->GetType());

		if (it == events.end())
		{
			std::cout << "Key-value pair not present in map";
			std::vector<Event*> vec;
			vec.push_back(event);
			events.insert(std::map<int, std::vector<Event*>>::value_type(event->GetType(), vec));
		}
		else {
			std::cout << "Key-value pair present : ";
			auto& vec = it->second;
			vec.push_back(event);
		}
	}

	void Publisher::Unsubscribe(EventType type, Test::Test* subscriber)
	{
		auto it = events.find(type);

		if (it == events.end())
		{
			std::cout << "Event Never Subscribed!!!";
		}
		else {
			std::cout << "Event Unsubscribed!";
			auto& vec = it->second;
			auto it = std::find_if(vec.begin(), vec.end(), 
				[subscriber](Event* event) {
					std::cout << "Checking: " << event->GetOwner() << " VS " << subscriber << std::endl;
					return event->GetOwner() == subscriber; 
				}
			);
			if (it != vec.end()) {
				std::cout << "Found the villian" << std::endl;
				vec.erase(it);
			}
			std::cout << vec.size() << std::endl;
		}
	}

	void Publisher::Notify(EventType type, int keyCode)
	{
		auto it = events.find(type);
		if (it == events.end())
		{
			std::cout << "We no find anything O" << std::endl;
			return;
		}
		for (Event* event : it->second)
		{
			std::cout << "Something about to happen" << std::endl;
			event->SetKeyCode(keyCode);
			event->GetAction()();
		}
	}
	void Publisher::NotifyAll()
	{

	}
}
