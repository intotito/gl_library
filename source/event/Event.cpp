#include <event/Event.hpp>

namespace event {
	Event::Event(): source(nullptr), State(STATE_INACTIVE), keyCode(0), time_created(0), time_last(0)
	{
	}

	Event::~Event()
	{

	}
	void Event::SetSource(Test::Test* test) {source = test;}
}