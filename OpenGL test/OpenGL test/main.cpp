#pragma warning(disable: 4996)  //fopen_s

#include <global.h>
#include <Input.h>
#include <camera.h>
#include <graphics.h>
#include <renderable.h>
#include <objectmanager.h>
#include <object.h>
#include <game.h>
#include <debug.h>

void KeyDown(unsigned char key, int x, int y); 
void KeyUp(unsigned char key, int x, int y);
void MouseClick(int button, int state, int x, int y);
void MouseMoved(int x, int y);
void ResizeWindow(int x, int y);
void MainUpdate(void);
void MainDraw(void);
void Exit(void);
void ShowFPS();
float CalculateFPS();

Game* pGame;
float GameFPS;
std::string sGameFPS;
int main(int argc, char **argv)
{
  // Setup windwing
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(800, 600);
  pGame = new Game();
  pGame->mWindowSize.x = 800; pGame->mWindowSize.y = 600;
  glutCreateWindow("OK");
  Debug().Print("test");

  glewInit();

  pGame->Initialize();

  // Define GLUT callbacks
  glutIdleFunc(MainUpdate);
  glutDisplayFunc(MainDraw);
  glutKeyboardFunc(KeyDown);
  glutKeyboardUpFunc(KeyUp);
  glutMouseFunc(MouseClick);
  glutMotionFunc(MouseMoved);
  glutPassiveMotionFunc(MouseMoved);
  glutReshapeFunc(ResizeWindow);
  // Enter renderable loop
  glutMainLoop();
  delete pGame;
  return 0;
}

void KeyDown(unsigned char key, int x, int y)
{
  //printf("key down: %d\n", key);
  pGame->pInput->KeyboardDown(key, x, y);
}
void KeyUp(unsigned char key, int x, int y)
{
  pGame->pInput->KeyboardUp(key, x, y);
}

void MouseClick(int button, int state, int x, int y)
{
  if((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
  {
    ivec2 pos = pGame->pInput->GetMousePos();
    pGame->mDots.push_back(vec2(pos.x, pos.y));
    printf("mouse clicked at (%d, %d)\n", pos.x, pos.y);
  }
}

void MouseMoved(int x, int y)
{
  //printf("mouse moved (%d, %d)\n", x, y);
  pGame->pInput->MouseMove(x, y);
}

void ResizeWindow(int x, int y)
{
  pGame->mWindowSize.x = x;
  pGame->mWindowSize.y = y;
  pGame->pGraphics->GetCamera()->Resize(x, y);
  //printf("new window dimensions (%d, %d)\n", x, y);
}

void ShowFPS()
{
  //calculate and show fps
  std::stringstream toStr;
  std::string title = "glew sniffing";
  toStr << CalculateFPS();
  sGameFPS = toStr.str();
  glutSetWindowTitle( (title + " - " + sGameFPS).c_str() );
}


float CalculateFPS()
{
  static int frameCount = 0;
  static int currentTime = 0;
  static int previousTime = 0;
  static float fps = 0;

  //  Increase frame count
  frameCount++;

  //  Get the number of milliseconds since last time calculation
  currentTime = glutGet(GLUT_ELAPSED_TIME);

  //  Calculate time passed
  int timeInterval = currentTime - previousTime;

  if(timeInterval > 1000)
  {
    //  calculate the number of frames per second
    fps = frameCount / (timeInterval / 1000.0f);

    GameFPS = (timeInterval / 1000.0f) / frameCount;

    //  Set time
    previousTime = currentTime;

    //  Reset frame count
    frameCount = 0;
  }

  return fps;
}

void MainUpdate(void)
{
  CalculateFPS();
  ShowFPS();

  pGame->UserInput(GameFPS);
  pGame->Update(GameFPS);

  if(pGame->pInput->IsKeyDown(27))
    Exit();
}

void MainDraw(void)
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  pGame->Draw();

  glutSwapBuffers();
  glutPostRedisplay();
}

void Exit()
{
  glutLeaveMainLoop();
}