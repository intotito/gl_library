#include <VertexArray.hpp>

VertexArray::VertexArray(): m_ID(0)
{
	glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray()
{
	Unbind();
	glDeleteVertexArrays(1, &m_ID); 
}

void VertexArray::Bind() {
	glBindVertexArray(m_ID);
}
void VertexArray::Unbind() {
	glBindVertexArray(0);
}

/*void VertexArray::LinkAttribute(VertexArrayAttribute* vaa, VertexBuffer* vb)
{
	{

		//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, 0);
		//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(3 * sizeof(GLfloat)));
		
		vb->Bind();
		glEnableVertexAttribArray(vaa->index);
		glVertexAttribPointer(vaa->index, vaa->count, vaa->type, vaa->normalized,
			//			vaa->GetSize() * width * vaa->count, (void*)stride);
			vaa->GetSize() * width * vaa->count, (void*)stride);
		stride += (vaa->count * vaa->GetSize());
	}
}
*/
void VertexArray::AddLayout(VertexBufferLayout* vbl, VertexBuffer* vb) {
	vb->Bind();
	const auto& elements = vbl->GetAttributes();
	int pointer = 0;
	for (int i = 0; i < elements.size(); i++) {
		VertexArrayAttribute* element = elements[i];
		glEnableVertexAttribArray(element->index);
		glVertexAttribPointer(element->index, element->count, element->type, element->normalized, vbl->GetStride(), (void*)pointer);
		pointer += (element->count * element->GetSize());
	}
	delete vbl;
}
