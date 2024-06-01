#pragma once
#include <event/Event.hpp>
namespace event {
	class KeyPressedEvent : public Event
	{

	public:
		KeyPressedEvent();
		~KeyPressedEvent();
		EventType GetType() override;
	};
}
