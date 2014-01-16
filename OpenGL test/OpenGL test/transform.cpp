#include <transform.h>

Transform::Transform()
  : mAngle(0)
  , mNeedsUpdate(true)
{
  mRotation[0][0] = 1;   mRotation[0][1] = 0;
  mRotation[1][0] = 0;   mRotation[1][1] = 1;

  matScale = mat4(1.0f);
  matRotate = mat4(1.0f);
  matTranslate = mat4(1.0f);
}

void Transform::SetRotation(float radians)
{
  mAngle = radians;
  UpdateRotationMatrix();
}

void Transform::AddRotation(float radians)
{
  mAngle += radians;
  UpdateRotationMatrix();
}

void Transform::UpdateScaleMatrix()
{
  mNeedsUpdate = true;
  matScale[0][0] = mScale.x;   matScale[1][1] = mScale.y;  matScale[2][2] = 1;
}

void Transform::UpdateRotationMatrix()
{
  mNeedsUpdate = true;
  float c = std::cos(mAngle);
  float s = std::sin(mAngle);
  mRotation[0][0] = c;   mRotation[0][1] = -s;
  mRotation[1][0] = s;   mRotation[1][1] = c;

  matRotate[0][0] = c;   matRotate[0][1] = -s;
  matRotate[1][0] = s;   matRotate[1][1] = c;
}

void Transform::UpdateTranslationMatrix()
{
  mNeedsUpdate = true;
  matTranslate[3][0] = mPosition.x; matTranslate[3][1] = mPosition.y;  matTranslate[3][2] = 0;
}

mat2 Transform::GetRotation()
{
  return mRotation;
}
 
float Transform::GetAngle()
{
  return mAngle;
}

const float* Transform::GetTransformMatrix()
{
  if(mNeedsUpdate)
  {
    mTransformationMatrix = matTranslate * matRotate * matScale;
    mNeedsUpdate = false;
  }
  return glm::value_ptr(mTransformationMatrix);
}

void Transform::SetPosition(float x, float y)
{
  mPosition.x = x;
  mPosition.y = y;
  UpdateTranslationMatrix();
}

void Transform::SetScale(float x, float y)
{
  mScale.x = x;
  mScale.y = y;
  UpdateScaleMatrix();
}

const vec2& Transform::GetPosition(void)
{
  return mPosition;
}

const vec2& Transform::GetScale(void)
{
  return mScale;
}

void Transform::IncrementPosition(float x, float y)
{
  mPosition.x += x;
  mPosition.y += y;
  UpdateTranslationMatrix();
}

void Transform::IncrementScale(float x, float y)
{
  mScale.x += x;
  mScale.y += y;
  UpdateScaleMatrix();
}