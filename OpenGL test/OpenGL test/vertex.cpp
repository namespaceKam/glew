#include <vertex.h>

VertexData::VertexData()
{}

std::vector<vec2>* VertexData::GetVertices(void)
{
  return &mVertices;
}

void VertexData::SetVertices(std::vector< vec2 > data)
{
  mVertices = data;
}

