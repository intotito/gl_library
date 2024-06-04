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

	void TestMenu::OnRender(Renderer& renderer, float deltaTime)
	{
		renderer.Clear();
		if (currentTest != nullptr) {
			currentTest->OnRender(renderer, deltaTime);
			UpdateEvent(deltaTime);
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
				// publisher->Unsubscribe();
				currentTest->RemoveKeyListenerEvent(publisher);
				delete currentTest;
				currentTest = nullptr;
			}
			else {
				currentTest->OnImGuiRender();
			}
		}

		ImGui::End();
	}

	void TestMenu::UpdateEvent(float time)
	{
		// search for all registered events
		publisher->Update(time);
	}

	void TestMenu::RegisterKeyEvent(int keycode)
	{
		if (currentTest)
		{
			publisher->ActivateKey(keycode);
		}
	}

	void TestMenu::UnRegisterKeyEvent(int keycode)
	{
		if (currentTest)
		{
			publisher->DeactivateKey(keycode);
		}
	}

	void TestMenu::FireKeyPressedEvent(int keycode)
	{
		
		if (currentTest)
		{
		//	currentTest->OnKeyPressed(keycode);
			publisher->Notify(event::KEY_PRESSED_EVENT, keycode);
			std::cout << "Weting Happen" << std::endl;
		}
	}
}
