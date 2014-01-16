#ifndef VERTEX_H
#define VERTEX_H

#include <global.h>

class VertexData
{
public:
  VertexData();
  std::vector<vec2>* GetVertices(void);
  void SetVertices(std::vector< vec2 > data);
  void MakeBox();

private:
  std::vector<vec2> mVertices;
};

#endif