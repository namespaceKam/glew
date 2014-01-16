#include <Input.h>

void Input::InitInput(void)
{
  mKeyCurrent = new bool[num_keys];
  mKeyPrevious = new bool[num_keys];
  mMouseClicked = false;
  mMouseClickedPrevious = false;
  for(unsigned char i = 0; i < num_keys; ++i)
  {
    mKeyCurrent[i] = 0;
    mKeyPrevious[i] = 0;
  }
  mMousePos.x = 0;  mMousePos.y = 0;
}

void Input::KeyboardDown(unsigned char key, int x, int y)
{
  mKeyCurrent[key] = true;
}

void Input::KeyboardUp(unsigned char key, int x, int y)
{
  mKeyCurrent[key] = false;
}

void Input::Mouse(int button, int state, int x, int y)
{
  if(button == GLUT_LEFT_BUTTON)
  {
    if(state == GLUT_DOWN)
      mMouseClicked = true;
    else
      mMouseClicked = false;
  }
}

void Input::MouseMove(int x, int y)
{
  mMousePos.x = x;
  mMousePos.y = y;
}

void Input::UpdateInput(void)
{
  for(unsigned char i = 0; i < num_keys; ++i)
  {
    mKeyPrevious[i] = mKeyCurrent[i];
  }
  mMouseClickedPrevious = mMouseClicked;
}

Input::~Input()
{
  delete[] mKeyCurrent;
  delete[] mKeyPrevious;
}

bool Input::IsKeyDown(unsigned char key)
{
  return mKeyCurrent[key];
}

bool Input::IsKeyClicked(unsigned char key)
{
  return mKeyCurrent[key] && !mKeyPrevious[key];
}

bool Input::IsMouseDown(void)
{
  return mMouseClicked;
}
bool Input::IsMouseClicked(void)
{ 
  return mMouseClicked && !mMouseClickedPrevious;
}

ivec2 Input::GetMousePos(void)
{
  return mMousePos;
}