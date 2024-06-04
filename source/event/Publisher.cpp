#include <event/Publisher.hpp>

namespace event
{
	Publisher::Publisher(): time(0)
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
			std::cout << "Key-value pair present : " << std::endl;
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
				[subscriber](Event* event) -> bool{
					std::cout << "Checking: " << event->GetSource() << " VS " << subscriber << std::endl;
					return event->GetSource() == subscriber; 
				}
			);
			if (it != vec.end()) {
				std::cout << "Found the villian" << std::endl;
				delete* it;
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

	void Publisher::Update(float time)
	{
		if (time - Publisher::time < POLL_INTERVAL)
		{
			return;
		}
		Publisher::time = time;
		// search through all registered events
		std::map<int, std::vector<Event*>>::iterator it = events.begin();
		while (it != events.end())
		{
			int eventType = it->first;
			auto& vec = it->second;
			for (auto& ev : vec)
			{
				if (ev->GetState() == STATE_CREATED || ev->GetState() == STATE_PRESSED)
				{
					if (ev->GetState() == STATE_CREATED) {
						if (time - ev->GetTimeCreated() > ACTIVATE_PRESS_INTERVAL)
						{
							ev->SetState(STATE_PRESSED);
							ev->GetAction()();
							ev->SetLastUpdateTime(time);
							std::cout << "Event Fired after ACTIVATE_INTERVAL" << std::endl;
						}
					}
					else if (ev->GetState() == STATE_PRESSED && (time - ev->GetLastUpdateTime() > PRESS_REPEAT_INTERVAL))
					{
						ev->GetAction()();
						ev->SetLastUpdateTime(time);
						std::cout << "Event Fired after PRESS_REPEAT " << std::endl;
					}
					std::cout << "Something to Update ..." << std::endl;
				}
				// do something with individual events
				
	//			std::cout << ev->GetSource() << std::endl;
			}
			it++;
		}
	}

	void Publisher::DeactivateKey(int keyCode)
	{
		std::cout << "DeactivateKey called" << std::endl;
		std::map<int, std::vector<Event*>>::iterator it = events.begin();
		while (it != events.end()) {
			if (it->first == KEY_PRESSED_EVENT) {
				std::vector<Event*>::iterator evts = it->second.begin();
				while (evts != it->second.end())
				{
					Event* event = *evts;
					if (event->GetState() == STATE_CREATED)
					{
						event->GetAction()();
						std::cout << "Event Fired after RELEASE_KEY" << std::endl;
					}
					event->SetState(event::STATE_CONSUMED);
//					event->SetKeyCode(keyCode);
					event->ResetTime();
					std::cout << "Deactivating " << event->GetType() << std::endl;
					evts++;
				}
			}
			it++;
		}
		std::cout << "ActivateKey Exiting... " << std::endl;
	}

	void Publisher::ActivateKey(int keyCode)
	{
		std::cout << "ActivateKey called" << std::endl;
		std::map<int, std::vector<Event*>>::iterator it = events.begin();
		while (it != events.end()) {
			if (it->first == KEY_PRESSED_EVENT) {
				std::vector<Event*>::iterator evts = it->second.begin();
				while (evts != it->second.end())
				{
					Event* event = *evts;
					event->SetState(event::STATE_CREATED);
					event->SetKeyCode(keyCode);
					event->SetTimeCreated(time);
					std::cout << "Activating " << event->GetType() << std::endl;
					evts++;
				}
			}
			it++;
		}
		std::cout << "ActivateKey Exiting... " << std::endl;
	}
	void Publisher::NotifyAll()
	{

	}
}
