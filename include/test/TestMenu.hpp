#pragma once
#include <test/Test.hpp>
#include <functional>
namespace Test {

	class TestMenu {
	public:
		TestMenu();
		~TestMenu();
		void OnRender(Renderer& renderer);
		template <typename T>
		void AddTest(std::string testName)
		{
			std::pair<std::string, std::function<Test* ()>>pair;
			pair.first = testName;
			auto func = [=]()->Test* { return new T(testName); };
			pair.second = func;
			tests.push_back(pair);
		}
	private:
		Test* currentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> tests;
	};
}
