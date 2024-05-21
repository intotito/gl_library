#pragma once
#include<vendor/glm/glm.hpp>
#include<vendor/glm/ext/matrix_common.hpp>
using glm::vec4;
using glm::mat4;
using glm::vec3;
using glm::cos;
using glm::sin;
class Object;

/**
* Transform represents the Positional, Rotational and Scaling state of an Object.
* 
* Every Object has a transform and manipulation of an object position, rotation and
* scaling is done through the Transform. 
*/
class Transform
{
public:
	/** 
	* Default Constructor.
	*
	* Creates a transform with default initial position, rotation and scale. 
	* Initial position is (1.0, 1.0, 1.0), rotation is (0.0, 0.0, 0.0) and scale is
	* (1.0, 1.0, 1.0).
	*/
	Transform();
	/** 
	* Default Deconstructor.
	*  
	* Cleans up all resource before deleting an instance. 
	*/
	~Transform();
	/** Translate on all axis. 
	*
	* Translate by *translation*.
	* @param translation the translation magnitude on all directions. 
	*/
	void Translate(vec3 translation);
	/** Translate on the X axis.
	*
	* Translate the x-axis by *dx*.
	* @param dx the distance to translate.
	*/
	void TranslateX(float dx);
	/** 
	* Translate on the Y axis.
	* 
	* Translate on the y-axis by *dy*.
	* @param dy the distanct to translate. 
	*/
	void TranslateY(float dy);
	/** 
	* Translate on the Z axis.
	* 
	* Translate on the z-axis by *dz*.
	* @param dz the distance to translate.
	*/
	void TranslateZ(float dz);
	/** 
	* Set the position.
	*
	* Set the position on all axis to *position*.
	* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
	* Transform::position.x = position.x;
	* Transform::position.y = position.y;
	* Transform::position.z = position.z;
	* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	* @param position the cordinate of the new position.
	*/
	void SetPosition(vec3 position);
	/** Rotate on the X axis.
	* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
	* rotation.x += angle;
	* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	* Rotate on the X by *angle*.
	* @param angle the magnitude to rotate in radians. 
	*/
	void RotateX(float angle);
	/** 
	* Rotate on the Y axis.
	* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
	* rotation.y += angle;
	* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	*
	* Rotate on the Y axis by *angle*.
	* @param angle the magnitude to rotate in radians. 
	*/
	void RotateY(float angle);
	/** 
	* Rotate on the Z axis. 
	*
	* Rotate on the Z axis by *angle* in radians.
	* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
	* rotation.z += angle;
	* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\
	* @param angle the magnitude to rotate in radians.
	*/
	void RotateZ(float angle);
	/** 
	* Set the Rotation to *rotation*.
	*
	* Set the Euler angle rotation for *x, y, z*.
	* @param rotation the rotation angles in radians. 
	*/
	void SetRotation(vec3 rotation);
	/** 
	* Set the X rotation to *rotationX*.
	* 
	* Set the Euler angle rotation for X to *rotationX*.
	* @param rotationX the X rotation in radians. 
	*/
	void SetRotationX(float rotationX);
	/** 
	* Set the Y rotation to *rotationX*.
	* 
	* Set the Euler angle rotation for Y to *rotationY*.
	* @param rotationY the Y rotation in radians.
	*/
	void SetRotationY(float rotationY);
	/** 
	* Set the X rotation to *rotationZ*.
	* 
	* Set the Euler angle rotation for Z to *rotationZ*.
	* @param rotationZ the Z rotation in radians. 
	*/
	void SetRotationZ(float rotationZ);
	/** 
	* Set Scale to **scale**.
	*
	* Set the Scale along *x, y,* & *z* axis.
	* ~~~~~~~~~~~~~~~~~~~~~~~.cpp
	* Transform::scale.x = scale.x;
	* Transform::scale.y = scale.y;
	* Transform::scale.z = scale.z;
	* ~~~~~~~~~~~~~~~~~~~~~~~
	* @param scale the magnitude to scale.
	*/
	void SetScale(vec3 scale);
	/** Scale uniformly to *scale*.
	*
	* Set the Scale along *x, y,* & *z* axis.
	* ~~~~~~~~~~~~~~~~~~~~~~~.cpp
	* Transform::scale.x = scale;
	* Transform::scale.y = scale;
	* Transform::scale.z = scale;
	* ~~~~~~~~~~~~~~~~~~~~~~~
	* @param scale the magnitude to scale across all axis.
	*/
	void SetScale(float scale);
	/** 
	* Set the scale on X to *scaleX*.
	*
	* Set the scale along the X axis to *scaleX*.
	* @param scaleX the magnitude to scale along X.
	*/
	void SetScaleX(float scaleX);
	/** Set the scale on Y to *scaleY*.
	*
	* Set the scale along the Y axis to *scaleY*.
	* @param scaleY the magnitude to scale along Y.
	*/
	void SetScaleY(float scaleY);
	/** 
	* Set the scale on Z to *scaleZ*.
	*
	* Set the scale along the Z axis to *scaleZ*.
	* @param scaleZ the magnitude to scale along Z.
	*/
	void SetScaleZ(float scaleZ);
	/** 
	* Set the owner of this transform.
	*
	* Set the pointer to the Object that shis transform represents. 
	* @param Container the owner of this Transform.
	*/
	void SetContainer(Object* Container);
	/** 
	* Get the current position.
	*
	* Get the current position of this Transform. 
	* @return the current position.
	*/
	vec3 const& GetPosition() const;
	/** 
	* Get the scale.
	*
	* Get a reference to the scale of this Transform. 
	* @return the current scale.
	*/
	vec3 const& GetScale() const;
	/**
	* Get the current rotation. 
	* 
	* Get a reference to the rotation of this Transform. 
	* @return the current rotation. 
	*/
	vec3 const& GetRotation() const;

	/**
	* Update the current state of the Transform.
	* 
	* This method updates the identity matrix of this transform as the
	* product of the translation, rotations and scaling matrices and finally sends
	* the update to the vertex buffer where the vertices are stored for GPU access.
	* This method has no effect if neither of the matrices has changed since 
	* the last call.
	*/
	void Update();
	/**
	* Get the identity matrix of this Transform. 
	* 
	* Get the matrix representing the translational, rotational and scaling state of the Transform.
	* @return the transformational matrix.
	*/
	inline mat4& GetMatrix() { return identity; }

	static void PrintMatrix(mat4 matrix);

private:
		/**
		* The current Rotation.
		*/
		vec3 rotation;
		/**
		* The current Scale.
		*/
		vec3 scale;
		/**
		* The current Position.
		*/
		vec3 position;
		/**
		* The X Rotation Matrix.
		* 
		* ~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
		* rotation_x = mat4(
		*		vec4(1.0f,	0.0f,				0.0f,				0.0f),
		*		vec4(0.0f,	cos(rotation.x),	sin(rotation.x),	0.0f),
		*		vec4(0.0f,	-sin(rotation.x),	cos(rotation.x),	0.0f),
		*		vec4(0.0f,	0.0f,				0.0f,				1.0f)
		* );
		* ~~~~~~~~~~~~~~~~~~~~~~~~~~
		* @note This Matrix is a Transpose Matrix.
		*/
		mat4 rotation_x;
		/**
		* The Y Rotation Matrix.
		* 
		* ~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
		* rotation_y = mat4(
		* 	vec4(cos(rotation.y),	0.0f,	-sin(rotation.y),	0.0f),
		* 	vec4(0.0f,				1.0f,	0.0f,				0.0f),
		* 	vec4(sin(rotation.y),	0.0f,	cos(rotation.y),	0.0f),
		* 	vec4(0.0f,				0.0f,	0.0f,				1.0f)
		* );
		* ~~~~~~~~~~~~~~~~~~~~~~~~~~
		* @note This Matrix is a Transpose Matrix.
		*/
		mat4 rotation_y;
		/**
		* The Z Rotation Matrix.
		* 
		* ~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
		* rotation_z = mat4(	
		*	vec4(cos(rotation.z),	sin(rotation.z),	0.0f,	0.0f),
		*	vec4(-sin(rotation.z),	cos(rotation.z),	0.0f,	0.0f),
		*	vec4(0.0f,				0.0f,				1.0f,	0.0f),
		*	vec4(0.0f,				0.0f,				0.0f,	1.0f)
		* );
		* ~~~~~~~~~~~~~~~~~~~~~~~~~~
		* @note This Matrix is a Transpose Matrix.
		*/
		mat4 rotation_z;
		/**
		* The Scaling Matrix.
		* 
		* ~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
		* scaling = mat4(
		* 	vec4(scale.x,	0.0f,		0.0f,		0.0f),
		* 	vec4(0.0f,		scale.y,	0.0f,		0.0f),
		* 	vec4(0.0f,		0.0f,		scale.z,	0.0f),
		* 	vec4(0.0f,		0.0f,		0.0f,		1.0f)
		* );
		* ~~~~~~~~~~~~~~~~~~~~~~~~~~
		* @note This Matrix is a Transpose Matrix.
		*/
		mat4 scaling;
		/**
		* The Translation Matrix.
		* 
		* ~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
		* translate = mat4(
		* 	vec4(1.0f,			0.0f,			0.0f,			0.0f),
		* 	vec4(0.0f,			1.0f,			0.0f,			0.0f),
		* 	vec4(0.0f,			0.0f,			1.0f,			0.0f),
		* 	vec4(position.x, position.y,	position.z,	1.0f)
		* );
		* ~~~~~~~~~~~~~~~~~~~~~~~~~~
		*/
		mat4 translate;
		/**
		* The Identity Matrix. 
		* 
		* This Matrix describes the current transformational state of the transform. 
		* ~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
		* identity = translate * rotation_z * rotation_y * rotation_x * scaling;
		* ~~~~~~~~~~~~~~~~~~~~~~~~~~
		* @note This Matrix is a Transpose Matrix.
		*/
		mat4 identity;
		/**
		* Current redraw state of the transform. 
		* 
		* A dirty state means that the identity matrix has changed and vertices current state
		* will be sent to vertex buffer for redrawing. 
		* Determines if Update() method will have effect or not. 
		*/
		bool isDirty;
		/**
		* The Object that this Transform represents its Transformational State. 
		*/
		Object* Container;
};