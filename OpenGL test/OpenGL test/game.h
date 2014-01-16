#ifndef GAME_H
#define GAME_H

#include <global.h>

class Input;
class Graphics;
class Renderable;
class ObjectManager;
class Object;

class Game
{
public:
  Game();
  ~Game();
  void Initialize();
  void UserInput(float dt);
  void Update(float dt);
  void Draw();
  
  void DrawDebugCross();
  void DrawDots();
  Object* MakeObject(vec2 position, vec2 scale, float angle);
  inline float GetRandomFloat() {return (float)(rand()%10001)/10000.0f;}

  Input* pInput;
  Graphics* pGraphics;
  Renderable* pRenderable;
  ObjectManager* pObjectmanager;
  Object* pPlayer;
  ivec2 mWindowSize;
  std::vector<vec2> mDots;

private:
};

#endif