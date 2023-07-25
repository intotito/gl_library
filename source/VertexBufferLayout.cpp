#include <VertexBufferLayout.hpp>

VertexBufferLayout::VertexBufferLayout(): stride(0)
{
}

VertexBufferLayout::~VertexBufferLayout()
{
}

void VertexBufferLayout::Add(VertexArrayAttribute vaa)
{
	attributes.push_back(vaa);
	stride += vaa.count * vaa.GetSize();
}

const std::vector<VertexArrayAttribute> VertexBufferLayout::GetAttributes() const
{
	return attributes;
}
