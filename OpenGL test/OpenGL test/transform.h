#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <global.h>

class Transform
{
public:
  Transform();
  void SetRotation(float radians);
  void AddRotation(float radians);
  mat2 GetRotation();
  const float* GetTransformMatrix();
  float GetAngle();
  void SetPosition(float x, float y);
  void SetScale(float x, float y);
  const vec2& GetPosition(void);
  const vec2& GetScale(void);
  void IncrementPosition(float x, float y);
  void IncrementScale(float x, float y);

private:
  bool mNeedsUpdate;
  void UpdateScaleMatrix();
  void UpdateRotationMatrix();
  void UpdateTranslationMatrix();
  mat2 mRotation;
  float mAngle;
  vec2 mPosition;
  vec2 mScale;

  mat4 matScale;
  mat4 matRotate;
  mat4 matTranslate;

  mat4 mTransformationMatrix;
};

#endif