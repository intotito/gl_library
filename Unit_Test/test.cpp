#pragma once
#include "pch.h"
//#include <Transform.hpp>
#include <Object.hpp>


class TransformTest : public testing::Test {

protected:
	void SetUp() override {
		rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		scale = glm::vec3(1.0f, 1.0f, 1.0f);
		position = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	glm::vec3 rotation, scale, position;
	glm::mat4 rotation_x, rotation_y, rotation_z;
	Transform transform;
};
TEST_F(TransformTest, DefaultConstructorTest) {
	EXPECT_TRUE(glm::all(glm::equal(transform.GetPosition(), position)));
	EXPECT_TRUE(glm::all(glm::equal(transform.GetRotation(), rotation)));
	EXPECT_TRUE(glm::all(glm::equal(transform.GetScale(), scale)));
}

TEST_F(TransformTest, TestTranslation) {
	position = glm::vec3(1.0f, 2.0f, 3.0f);
	transform.Translate(position);
	EXPECT_TRUE(glm::all(glm::equal(transform.GetPosition(), position)));
	
	transform.TranslateX(30.0f);
	EXPECT_TRUE(glm::all(glm::equal(transform.GetPosition(), glm::vec3(31.0f, 2.0f, 3.0f))));

	transform.TranslateY(28.0f);
	EXPECT_TRUE(glm::all(glm::equal(transform.GetPosition(), glm::vec3(31.0f, 30.0f, 3.0f))));

	transform.TranslateZ(-3.0f);
	EXPECT_TRUE(glm::all(glm::equal(transform.GetPosition(), glm::vec3(31.0f, 30.0f, 0.0f))));
}

TEST_F(TransformTest, TestUpdate) {

}
