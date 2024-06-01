#include <event/KeyPressedEvent.hpp>
namespace event {
	KeyPressedEvent::KeyPressedEvent() : Event()
	{

	}

	KeyPressedEvent::~KeyPressedEvent()
	{

	}

	EventType KeyPressedEvent::GetType() {
		return KEY_PRESSED_EVENT;
	}
}