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
			events.insert(std::map<std::string, std::vector<Event*>>::value_type(event->GetType(), vec));
		}
		else {
			std::cout << "Key-value pair present : ";
			auto& vec = it->second;
			vec.push_back(event);
		}
	}

	void Publisher::Unsubscribe(Event* event)
	{
		auto it = events.find(event->GetType());

		if (it == events.end())
		{
			std::cout << "Event Never Subscribed!!!";
		}
		else {
			std::cout << "Event Unsubscribed!";
			auto& vec = it->second;
			auto it = std::find(vec.begin(), vec.end(), event);
			if (it != vec.end()) {
				vec.erase(it);
			}
		}
	}

	void Publisher::Notify(std::string type)
	{
		auto it = events.find(type);
		if (it == events.end())
		{
			return;
		}
		for (const Event* event : it->second)
		{
			
		}
	}
	void Publisher::NotifyAll()
	{

	}
}
