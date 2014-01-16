#include <renderable.h>
#include <graphics.h>

Renderable::Renderable()
  : pGraphicsData(0)
  , mTexture(0)
{}

float* Renderable::GetColor()
{
  return glm::value_ptr(mColor);
}

void Renderable::SetColor(float r, float g, float b, float a)
{
  mColor.r = r;
  mColor.b = b;
  mColor.g = g;
  mColor.a = a;
}

void Renderable::SetTexture(unsigned texture)
{
  mTexture = texture;
}