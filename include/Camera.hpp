#pragma once
#include<vendor/glm/glm.hpp>
#include<vendor/glm/gtc/matrix_transform.hpp>


class Camera {
public:
	Camera(glm::vec3 position, glm::vec3 V);
	virtual ~Camera();
	glm::mat4 GetMatrix();
	inline float GetX() { return position.x; }
	inline float GetY() { return position.y; }
	inline float GetZ() { return position.z; }
	inline void SetX(float x) { position.x = x; }
	inline void SetY(float y) { position.y = y; }
	inline void SetZ(float z) { position.z = z; }
	inline glm::vec3 GetPosition() { return position; }
	inline void SetLookAt(glm::vec3& la){
		Target.x = la.x;
		Target.y = la.y;
		Target.z = la.z;
	}
private:
	glm::vec3 position;
	glm::vec3 Up;
	glm::vec3 Target = glm::vec3(0.0f, 0.0f, 0.0f);
};