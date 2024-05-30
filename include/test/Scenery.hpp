#pragma once
#include<test/Test.hpp>
#include<Scene.hpp>
namespace Test {
	class Scenery : public Test
	{
	public:
		Scenery(std::string testName);
		~Scenery();
		void OnUpdate(float deltaTime);
		void OnRender(Renderer& renderer);
		void OnImGuiRender();
		void OnStart() override;
		void OnKeyPressed(int keycode) override;
	private:
		Scene* scene;
	};
}