#pragma once
#include<vendor/glm/glm.hpp>
#include<vendor/glm/ext/matrix_common.hpp>

using glm::vec4;
using glm::mat4;
using glm::vec3;
using glm::cos;
using glm::sin;
class Object;
class Transform
{
public:
	Transform();
	~Transform();
	void Translate(vec3 translation);
	void TranslateX(float dx);
	void TranslateY(float dy);
	void TranslateZ(float dz);
	void SetPosition(vec3 position);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	void SetRotation(vec3 rotation);
	void SetRotationX(float rotationX);
	void SetRotationY(float rotationY);
	void SetRotationZ(float rotationZ);
	void SetScale(vec3 scale);
	void SetScale(float scale);
	void SetScaleX(float scaleX);
	void SetScaleY(float scaleY);
	void SetScaleZ(float scaleZ);
	void SetContainer(Object* Container);

	vec3 const& GetPosition() const;
	vec3 const& GetScale() const;
	vec3 const& GetRotation() const;


	void Update();
	inline mat4& GetMatrix() { return identity; }

	static void PrintMatrix(mat4 matrix);

private:
		vec3 rotation;
		vec3 scale;
		vec3 position;
		mat4 rotation_x;
		mat4 rotation_y;
		mat4 rotation_z;
		mat4 scaling;
		mat4 translate;
		mat4 identity;
		bool isDirty;
		Object* Container;
};