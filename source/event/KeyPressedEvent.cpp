#include <event/KeyPressedEvent.hpp>
namespace event {
	KeyPressedEvent::KeyPressedEvent() : Event()
	{

	}

	KeyPressedEvent::KeyPressedEvent(int keyCode) : Event()
	{
		SetKeyCode(keyCode);
	}

	KeyPressedEvent::~KeyPressedEvent()
	{

	}

	EventType KeyPressedEvent::GetType() {
		return KEY_PRESSED_EVENT;
	}
}