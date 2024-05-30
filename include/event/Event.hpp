#pragma once
#include <functional>
#include<string>
namespace event {
	class Event
	{
	public:
		Event();
		virtual ~Event();
		virtual std::string GetType() = 0;
	private:

	};
	//std::function<void(*)> method;
}