#include <Transform.hpp>
#include <Object.hpp>
Transform::Transform(): scale(vec3(1.0f, 1.0f, 1.0f)), rotation(vec3(0.0f, 0.0f, 0.0f)), 
	position(vec3(0.0f, 0.0f, 0.0f)), isDirty(false), Container(nullptr)
{
	rotation_x = mat4(
		vec4(1.0f,	0.0f,				0.0f,				0.0f),
		vec4(0.0f,	cos(rotation.x),	sin(rotation.x),	0.0f),
		vec4(0.0f,	-sin(rotation.x),	cos(rotation.x),	0.0f),
		vec4(0.0f,	0.0f,				0.0f,				1.0f)
	);
	rotation_y = mat4(
		vec4(cos(rotation.y),	0.0f,	-sin(rotation.y),	0.0f),
		vec4(0.0f,				1.0f,	0.0f,				0.0f),
		vec4(sin(rotation.y),	0.0f,	cos(rotation.y),	0.0f),
		vec4(0.0f,				0.0f,	0.0f,				1.0f)
	);

	rotation_z = mat4(
		vec4(cos(rotation.z),	sin(rotation.z),	0.0f,	0.0f),
		vec4(-sin(rotation.z),	cos(rotation.z),	0.0f,	0.0f),
		vec4(0.0f,				0.0f,				1.0f,	0.0f),
		vec4(0.0f,				0.0f,				0.0f,	1.0f)
	);

	scaling = mat4(
		vec4(scale.x,	0.0f,		0.0f,		0.0f),
		vec4(0.0f,		scale.y,	0.0f,		0.0f),
		vec4(0.0f,		0.0f,		scale.z,	0.0f),
		vec4(0.0f,		0.0f,		0.0f,		1.0f)
	);

	translate = mat4(
		vec4(1.0f,			0.0f,			0.0f,			0.0f),
		vec4(0.0f,			1.0f,			0.0f,			0.0f), 
		vec4(0.0f,			0.0f,			1.0f,			0.0f), 
		vec4(position.x, position.y,	position.z,	1.0f)
	);

	identity = translate * rotation_z * rotation_y * rotation_x * scaling;

//	identity = rotation_z * rotation_y * rotation_x * scaling;
}

Transform::~Transform()
{

}

void Transform::SetContainer(Object* object) {
	Container = object;
}

vec3 const& Transform::GetPosition() const
{
	return position;
}

vec3 const& Transform::GetScale() const
{
	return scale;
}

vec3 const& Transform::GetRotation() const
{
	return rotation;
}

void Transform::Update()
{
	if (isDirty && Container)
	{
		std::cout << "Is Dirty ------------------------------ " << std::endl;
		identity = translate * rotation_z * rotation_y * rotation_x * scaling;
		Container->TransformObject(identity);
		unsigned int vBuffer = Container->GetBuffer();
		if (vBuffer) {
			glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
			glBufferSubData(GL_ARRAY_BUFFER, Container->GetSceneAddress(), Container->GetByteSize(), Container->GetData());
		}
		isDirty = false;
	}
}

void Transform::Translate(vec3 translation)
{
	Transform::position += translation;
	translate[3] = vec4(Transform::position, 1.0f);
	isDirty = true;
}

void Transform::TranslateX(float dx)
{
	position.x += dx;
	translate[3] = vec4(Transform::position, 1.0f);
	isDirty = true;
}

void Transform::TranslateY(float dy)
{
	position.y += dy;
	translate[3] = vec4(Transform::position, 1.0f);
	isDirty = true;
}

void Transform::TranslateZ(float dz)
{
	position.z += dz;
	translate[3] = vec4(Transform::position, 1.0f);
	isDirty = true;
}

void Transform::SetPosition(vec3 position)
{
	
	Transform::position = position;
	translate[3] = vec4(Transform::position, 1.0f);
	isDirty = true;
}

void Transform::RotateX(float angle)
{
	rotation.x += angle;
	rotation_x[1] = vec4(0.0f, cos(rotation.x), sin(rotation.x), 0.0f);
	rotation_x[2] = vec4(0.0f, -sin(rotation.x), cos(rotation.x), 0.0f);
	isDirty = true;
}

void Transform::RotateY(float angle)
{
	rotation.y += angle;
	rotation_y[0] = vec4(cos(rotation.y), 0.0f, -sin(rotation.y), 0.0f);
	rotation_y[2] = vec4(sin(rotation.y), 0.0f, cos(rotation.y), 0.0f);
	isDirty = true;
}


void Transform::RotateZ(float angle)
{
	rotation.z += angle;
	rotation_z[0] = vec4(cos(rotation.z), sin(rotation.z), 0.0f, 0.0f);
	rotation_z[1] = vec4(-sin(rotation.z), cos(rotation.z), 0.0f, 0.0f);
	isDirty = true;
}

void Transform::SetRotation(vec3 rotation)
{
	SetRotationX(rotation.x);
	SetRotationY(rotation.y);
	SetRotationZ(rotation.z);
	std::cout << "Rotation y: " << rotation.y << std::endl;
	PrintMatrix(rotation_x);
	PrintMatrix(rotation_y);
	PrintMatrix(rotation_z);
	isDirty = true;

}

void Transform::SetRotationX(float rotationX)
{
	rotation.x = rotationX;
	rotation_x[1] = vec4(0.0f, cos(rotation.x), sin(rotation.x), 0.0f);
	rotation_x[2] = vec4(0.0f, -sin(rotation.x), cos(rotation.x), 0.0f);
	isDirty = true;
}

void Transform::SetRotationY(float rotationY)
{
	rotation.y = rotationY;
	rotation_y[0] = vec4(cos(rotation.y), 0.0f, -sin(rotation.y), 0.0f);
	rotation_y[2] = vec4(sin(rotation.y), 0.0f, cos(rotation.y), 0.0f);
	isDirty = true;
}

void Transform::SetRotationZ(float rotationZ)
{
	rotation.z = rotationZ;
	rotation_z[0] = vec4(cos(rotation.z), sin(rotation.z), 0.0f, 0.0f);
	rotation_z[1] = vec4(-sin(rotation.z), cos(rotation.z), 0.0f, 0.0f);
	isDirty = true;
}

void Transform::SetScale(vec3 scale)
{
	Transform::scale = scale;
	scaling[0].x = Transform::scale.x;
	scaling[1].y = Transform::scale.y;
	scaling[2].z = Transform::scale.z;
	isDirty = true;
}

void Transform::SetScale(float scale)
{
	Transform::scale = vec3(scale, scale, scale);
	scaling[0].x = Transform::scale.x;
	scaling[1].y = Transform::scale.y;
	scaling[2].z = Transform::scale.z;
	isDirty = true;
}

void Transform::SetScaleX(float scaleX)
{
	scale.x = scaleX;
	scaling[0].x = Transform::scale.x;
	isDirty = true;
}

void Transform::SetScaleY(float scaleY)
{
	scale.y = scaleY;
	scaling[1].y = Transform::scale.y;
	isDirty = true;
}

void Transform::SetScaleZ(float scaleZ)
{
	scale.z = scaleZ;
	scaling[2].z = Transform::scale.z;
	isDirty = true;
}

void Transform::PrintMatrix(mat4 matrix) {
	for (int i = 0; i < 4; i++) {
		std::cout << "|";
		for (int j = 0; j < 4; j++) {
			std::cout.precision(2);
			std::cout << matrix[i][j] << ((j < 3) ? "\t" : "");
		}
		std::cout << "|" << std::endl;
	}
	std::cout << std::endl;
}