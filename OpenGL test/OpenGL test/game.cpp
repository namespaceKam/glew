#include <game.h>
#include <Input.h>
#include <graphics.h>
#include <renderable.h>
#include <objectmanager.h>
#include <camera.h>
#include <object.h>

Game::Game()
  : pInput(NULL)
  , pGraphics(NULL)
  , pRenderable(NULL)
  , pObjectmanager(NULL)
  , pPlayer(NULL)
  , mWindowSize(800, 600)
{}

Game::~Game()
{
  delete pInput;
  delete pGraphics;
  delete pObjectmanager;
}

void Game::Initialize()
{
  pInput = new Input();
  pInput->InitInput();
  pGraphics = new Graphics();
  pGraphics->Initialize();
  pGraphics->SetCamera(new Camera(*pInput ));
  pObjectmanager = new ObjectManager();
}

void Game::UserInput(float dt)
{
  pInput->UpdateInput();

}

void Game::Update(float dt)
{
  if(pInput->IsKeyDown('p'))
  {
    printf("object count: %d\n", pObjectmanager->GetObjects().size());

    if( !pPlayer )
    pPlayer = MakeObject( vec2( -400 + rand()%800, -400 + rand()%800 ),
      vec2(1 + GetRandomFloat() * 50, 1 + GetRandomFloat() * 50),
      GetRandomFloat() * 3.141592f);
    else
    MakeObject( vec2( -400 + rand()%800, -400 + rand()%800 ),
      vec2(1 + GetRandomFloat() * 50, 1 + GetRandomFloat() * 50),
      GetRandomFloat() * 3.141592f);
  }

  if(pInput->IsKeyDown('o'))
  {
    if(pPlayer)
    {
      pPlayer->pRenderable->SetTexture(pGraphics->GetTexture("./image.png"));
    }
  }

  if(pPlayer)
  {
    if( pInput->IsKeyDown('t') )
      pPlayer->mTransform.IncrementPosition(0, 1);
    if( pInput->IsKeyDown('g') )
      pPlayer->mTransform.IncrementPosition(0, -1);
    if( pInput->IsKeyDown('f') )
      pPlayer->mTransform.IncrementPosition(-1, 0);
    if( pInput->IsKeyDown('h') )
      pPlayer->mTransform.IncrementPosition(1, 0);
    if( pInput->IsKeyDown('r') )
      pPlayer->mTransform.AddRotation(-0.05f);
    if( pInput->IsKeyDown('y') )
      pPlayer->mTransform.AddRotation(0.05f);
    if( pInput->IsKeyDown('v') )
      pPlayer->mTransform.IncrementScale(0.5f, 0.5f);
    if( pInput->IsKeyDown('b') )
      pPlayer->mTransform.IncrementScale(-0.5f, -0.5f);
  }

  pGraphics->Update(dt);
}

void Game::Draw()
{
  pGraphics->Render(pObjectmanager->GetObjects());
}

void Game::DrawDebugCross()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0.5, 0.5, 0.5);
  glBegin(GL_LINES);
  glVertex2f(-100, 0);
  glVertex2f(100, 0);

  glVertex2f(0, -100);
  glVertex2f(0, 100);
  glEnd();
}

void Game::DrawDots()
{
  glPointSize(5.0f);
  glColor3f(1, 1, 1);
  glBegin(GL_POINTS);
  for(unsigned i = 0; i < mDots.size(); ++i)
    glVertex2f( mDots[i].x, mDots[i].y );
  glEnd();
}

Object* Game::MakeObject(vec2 position, vec2 scale, float angle)
{
  Object* object = new Object();
  object->mTransform.SetPosition(position.x, position.y);
  object->mTransform.SetScale(scale.x, scale.y);
  object->mTransform.SetRotation(angle);

  Renderable* renderable = new Renderable();

  renderable->pGraphicsData = pGraphics->GetSavedGraphicsData("box");

  renderable->SetColor(GetRandomFloat(), GetRandomFloat(), GetRandomFloat(), GetRandomFloat());

  object->pRenderable = renderable;

  int roll = rand() % 3;
  std::string file;
  switch(roll)
  {
  case 0:
    file = "./image.png";
    break;
  case 1:
    file = "./image2.png";
    break;
  default:
    file = "./image3.png";
    break;
  }

  object->pRenderable->SetTexture(pGraphics->GetTexture(file));

  pObjectmanager->AddObject(object);
  return object;
}

//1) use graphics to make or find vertex
//2) assign that vertex to renderable
//3) assign that renderable to object