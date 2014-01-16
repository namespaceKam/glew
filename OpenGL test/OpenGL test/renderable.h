#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <global.h>

struct GraphicsData;


class Renderable
{
  friend class Graphics;
public:
  Renderable();
  float* GetColor();
  void SetColor(float r, float g, float b, float a);
  GraphicsData* pGraphicsData;
  void SetTexture(unsigned texture);

private:
  vec4 mColor;
  unsigned mTexture;  //point to a texture
};

#endif