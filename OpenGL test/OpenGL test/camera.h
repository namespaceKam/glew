#ifndef CAMERA_H
#define CAMERA_H

#include <global.h>

class Input;

class Camera
{
public:
  Camera(Input& input);
  void Update(float dt);
  void Resize(int x, int y);
  void Shift(float x, float y);
  void SetPosition(float x, float y);
  void DebugInput(float dt);
  void SetScrollSpeed(float speed);
  void AdjustScrollSpeed(float adjust);
  vec2 GetPosition(void);
  const float* GetProjectionMatrix(void);
  void AdjustZoom(float offset);
  void SetZoom(float zoom);

private:
  void UpdateViewMatrix();

  Input& mInput;

  mat4 mProjectionMatrix;

  float mPosX;
  float mPosY;
  unsigned mWidth;
  unsigned mHeight;
  float mScrollSpeed;
  float mZoom;
};

#endif