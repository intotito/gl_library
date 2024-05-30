#include <test/TestMenu.hpp>

namespace Test {
	TestMenu::TestMenu() : currentTest(nullptr), publisher(new event::Publisher())
	{

	}

	TestMenu::~TestMenu()
	{
		currentTest = nullptr;
		for (auto& test : tests)
		{
			delete test.second();
		}
		tests.clear();
	}

	void TestMenu::OnRender(Renderer& renderer)
	{
		renderer.Clear();
		if (currentTest != nullptr) {
			currentTest->OnRender(renderer);
		}
		ImGui::Begin((currentTest == nullptr) ? "Test Menu" : currentTest->GetName().c_str());

		if (currentTest == nullptr) {
			for (auto& test : tests)
			{
				if (ImGui::Button(test.first.c_str())) {
					currentTest = test.second();
					currentTest->OnStart();
				}
			}
		}
		else {
			if (ImGui::Button("<-")) {
				delete currentTest;
				currentTest = nullptr;
			}
			else {
				currentTest->OnImGuiRender();
			}
		}

		ImGui::End();
	}

	void TestMenu::OnKeyPressed(int keycode)
	{
		if (currentTest)
		{
			currentTest->OnKeyPressed(keycode);
		}
	}
}
