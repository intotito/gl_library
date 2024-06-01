#pragma once
#include <test/Test.hpp>
#include <functional>
#include<event/Publisher.hpp>
#include <event/Event.hpp>
namespace Test {

	class TestMenu {
	public:
		TestMenu();
		~TestMenu();
		void OnRender(Renderer& renderer);
		virtual void OnKeyPressed(int keycode);

		template <typename T>
		void AddTest(std::string testName)
		{
			std::pair<std::string, std::function<Test* ()>>pair;
			pair.first = testName;
			auto func = [=]()->Test* {
				T* t = new T(testName);
				t->AddKeyListenerEvent(publisher);
				return t;
			};
			pair.second = func;
			tests.push_back(pair);
		}

	private:
		Test* currentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> tests;
		event::Publisher* publisher;
	};
}
