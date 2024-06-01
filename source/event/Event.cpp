#include <event/Event.hpp>

namespace event {
	Event::Event(): container(nullptr) {}

	Event::~Event()
	{

	}
	void Event::SetOwner(Test::Test* test) {container = test;}
}