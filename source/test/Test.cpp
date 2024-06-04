#include<test/Test.hpp>

namespace Test {
	Test::Test(std::string name): lastTime(0)
	{
		Test::name = name;
	}

	Test::~Test()
	{

	}

	void Test::OnUpdate(float deltaTime)
	{

	}

	void Test::OnRender(Renderer& renderer, float deltaTime)
	{

	}

	void Test::OnImGuiRender()
	{

	}

	void Test::OnStart()
	{

	}

	void Test::OnKeyPressed(event::Event* event)
	{

	}
	void Test::AddKeyListenerEvent(event::Publisher* publisher) {
		event::KeyPressedEvent* event = new event::KeyPressedEvent();
		std::function<void()> action = [=]() -> void {
			OnKeyPressed(event);
			std::cout << "Did we" << std::endl;
			};
		event->SetSource(this);
		event->SetAction(action);
//		event->SetState(event::STATE_CREATED);
		publisher->Subscribe(event);
	}
	void Test::RemoveKeyListenerEvent(event::Publisher* publisher) {
		publisher->Unsubscribe(event::KEY_PRESSED_EVENT, this);
	}
}
