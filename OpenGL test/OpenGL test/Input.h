#ifndef INPUT_H
#define INPUT_H
#include <global.h>

class Input
{
  static const unsigned char num_keys = static_cast<unsigned char>(-1);
  bool* mKeyCurrent;
  bool* mKeyPrevious;
  bool mMouseClicked;
  bool mMouseClickedPrevious;
  ivec2 mMousePos;
  float dt;

public:
  void InitInput(void);
  void KeyboardDown(unsigned char key, int x, int y);
  void KeyboardUp(unsigned char key, int x, int y);
  void Mouse(int button, int state, int x, int y);
  void MouseMove(int x, int y);
  void UpdateInput(void);
  ~Input();

  bool IsKeyDown(unsigned char key);
  bool IsKeyClicked(unsigned char key);
  bool IsMouseDown(void);
  bool IsMouseClicked(void);
  ivec2 GetMousePos(void);
};
#endif