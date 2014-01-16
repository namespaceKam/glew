#include <camera.h>
#include <Input.h>

Camera::Camera(Input& input) 
  : mInput(input) 
  , mWidth(800)
  , mHeight(600)
  , mPosX(0)
  , mPosY(0)
  , mScrollSpeed(100)
  , mZoom(0.5f)
{
  UpdateViewMatrix();
}

void Camera::Update(float dt)
{
}

void Camera::SetScrollSpeed(float speed)
{
  mScrollSpeed = speed;
}
void Camera::AdjustScrollSpeed(float adjust)
{
  mScrollSpeed += adjust;
}


void Camera::Resize(int x, int y)
{
  mWidth = x;
  mHeight = y;

  glutReshapeWindow(x, y);
  glViewport(0, 0, x, y);
  UpdateViewMatrix();
}

void Camera::Shift(float x, float y)
{
  mPosX += x;
  mPosY += y;
  UpdateViewMatrix();
}

void Camera::SetPosition(float x, float y)
{
  mPosX = x;
  mPosY = y;
  UpdateViewMatrix();
}

vec2 Camera::GetPosition(void)
{
  vec2 pos(mPosX, mPosY);
  return pos;
}

void Camera::UpdateViewMatrix()
{
  float lower_x = mPosX - mWidth * mZoom;
  float lower_y = mPosY - mHeight * mZoom;
  float upper_x = mPosX + mWidth * mZoom;
  float upper_y = mPosY + mHeight * mZoom;
  /*glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(lower_x, upper_x, lower_y, upper_y);*/

  mProjectionMatrix[0][0] = 2.0f / (upper_x - lower_x);
  mProjectionMatrix[0][1] = 0;
  mProjectionMatrix[0][2] = 0;
  mProjectionMatrix[0][3] = 0;

  mProjectionMatrix[1][0] = 0;
  mProjectionMatrix[1][1] = 2.0f / (upper_x - lower_x);
  mProjectionMatrix[1][2] = 0;
  mProjectionMatrix[1][3] = 0;

  mProjectionMatrix[2][0] = 0;
  mProjectionMatrix[2][1] = 0;
  mProjectionMatrix[2][2] = -1.0f;
  mProjectionMatrix[2][3] = 0;

  mProjectionMatrix[3][0] = -(upper_x + lower_x) / (upper_x - lower_x);
  mProjectionMatrix[3][1] = -(upper_y + lower_y) / (upper_y - lower_y);
  mProjectionMatrix[3][2] = 0;
  mProjectionMatrix[3][3] = 1;
}

void Camera::DebugInput(float dt)
{
  float dx = mScrollSpeed * dt;
  float dy = mScrollSpeed * dt;

  if(mInput.IsKeyDown('w'))
    Shift(0, dx);
  if(mInput.IsKeyDown('a'))
    Shift(-dx, 0);
  if(mInput.IsKeyDown('s'))
    Shift(0, -dy);
  if(mInput.IsKeyDown('d'))
    Shift(dy, 0);

  if(mInput.IsKeyDown('q'))
    AdjustScrollSpeed(1.0f);
  if(mInput.IsKeyDown('e'))
    AdjustScrollSpeed(-1.0f);

  if(mInput.IsKeyDown('z'))
    AdjustZoom(0.01f);
  if(mInput.IsKeyDown('x'))
    AdjustZoom(-0.01f);

}

void Camera::AdjustZoom(float offset)
{
  mZoom += offset;
  UpdateViewMatrix();
}

void Camera::SetZoom(float zoom)
{
  mZoom = zoom;
  UpdateViewMatrix();
}

const float* Camera::GetProjectionMatrix(void)
{
  return glm::value_ptr(mProjectionMatrix);
}