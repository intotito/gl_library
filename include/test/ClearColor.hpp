#pragma once
#include <test/Test.hpp>

namespace Test {
	class ClearColor : public Test {
	public:
		ClearColor(std::string name);
		~ClearColor();
		void OnUpdate(float deltaTime) override;
		void OnRender(Renderer& renderer) override;
		void OnImGuiRender() override;

	private:
		float color[4];
	};
}
