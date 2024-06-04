#pragma once
#include <event/Event.hpp>
namespace event {
	class KeyPressedEvent : public Event
	{

	public:
		KeyPressedEvent();
		KeyPressedEvent(int keyCode);
		~KeyPressedEvent();
		EventType GetType() override;
	};
}
