#include <graphics.h>
#include <camera.h>
#include <debug.h>
#include <stdio.h>
#include <stb_image.c>

Graphics::Graphics()
  : pCamera(NULL)
  , mBasicProgram(0)
  , mVertexShader(0)
  , mFragmentShader(0)
{}

Graphics::~Graphics()
{
  delete pCamera;
  glDeleteShader(mVertexShader);
  glDeleteShader(mFragmentShader);
  glDeleteProgram(mBasicProgram);
}

void Graphics::SetCamera(Camera* camera)
{
  pCamera = camera;
}

Camera* Graphics::GetCamera()
{
  return pCamera;
}

void Graphics::Initialize()
{
  MakeBox();
  LoadShaders();
  GetTexture("./image.png");
  GetTexture("./image2.png");
  GetTexture("./image3.png");
}

void Graphics::Update(float dt)
{
  pCamera->DebugInput(dt);
}

void Graphics::Render(std::vector<Object*>& obj)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glColor4f(1,1,1,1);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  const float* matrix = pCamera->GetProjectionMatrix();

  glUseProgram(mBasicProgram);
  int projection = glGetUniformLocation(mBasicProgram, "ProjectionMatrix");
  int transform = glGetUniformLocation(mBasicProgram, "TransformMatrix");
  int color = glGetUniformLocation(mBasicProgram, "Color");
  int texture = glGetUniformLocation(mBasicProgram, "Texture");

  glUniformMatrix4fv(projection,  1,  0,  matrix);
  glUniform1i(texture, 0);
  glActiveTexture(GL_TEXTURE0);

  for(size_t i = 0; i < obj.size(); ++i)
  {
    if(!(obj[i]->pRenderable))
      continue;

    if(obj[i]->pRenderable->mTexture == 0)
      continue;

    glBindTexture(GL_TEXTURE_2D, obj[i]->pRenderable->mTexture);

    const float* Color = obj[i]->pRenderable->GetColor();
    const float* TransformMatrix = obj[i]->mTransform.GetTransformMatrix();
    glUniform4fv(color, 1, Color);
    glUniformMatrix4fv(transform,  1,  0,  TransformMatrix);

    GraphicsData* pInst = obj[i]->pRenderable->pGraphicsData;
    glBindVertexArray(pInst->VertexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pInst->ArrayBufferID);
    //glTexCoordPointer(2, GL_FLOAT, sizeof(float) * 2, obj[i]->pRenderable->pGraphicsData->vertexbuffer.data() + sizeof(float) * 2);
    glDrawElements(GL_TRIANGLES, pInst->indices.size(), GL_UNSIGNED_INT, 0);
  }
  glUseProgram(0);
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

int Graphics::FindGraphicsDataIndex(const std::string& comp)
{
  if(mVertexTable.find(comp) != mVertexTable.end())
  {
    return mVertexTable[comp];
  }
  return -1;
}

int Graphics::AddGraphicsData(const std::string& name, GraphicsData* graphics)
{
  int index = FindGraphicsDataIndex(name);
  if(index == -1)
  {
    graphics->vertexbuffer.clear();
    float* fdata = new float[ graphics->vertices.size()*2 ];
    for(size_t i = 0; i < graphics->vertices.size(); ++i)
    {
      fdata[ i*2 ] = graphics->vertices[i].x;
      fdata[ i*2 + 1 ] = graphics->vertices[i].y;
      //printf("(%f,", fdata[i*2]);
      //printf(" %f)\n", fdata[i*2 + 1]);
    }

    for(size_t i = 0; i < graphics->vertices.size(); ++i)
    {

      graphics->vertexbuffer.push_back(graphics->vertices[i].x);
      graphics->vertexbuffer.push_back(graphics->vertices[i].y);
    }

    glGenVertexArrays(1, &graphics->VertexBufferID);
    glBindVertexArray(graphics->VertexBufferID);

    unsigned vbuffer;
    glGenBuffers(1, &vbuffer);
    glGenBuffers( 1, &graphics->ArrayBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, graphics->ArrayBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, graphics->indices.size() * sizeof( unsigned ), graphics->indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbuffer);

    Debug().CheckGLError();


    glBufferData(GL_ARRAY_BUFFER,
      sizeof(float) * graphics->vertices.size()*2, //number of verts in your array
      fdata, //actual array of verts
      GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const GLvoid*)(sizeof(float) * 2));

    Debug().CheckGLError();


    glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
    Debug().CheckGLError();

    mLoadedGraphics.push_back(graphics);
    index = mLoadedGraphics.size() - 1;
    mVertexTable[name] = index;
  }
  return index;
}

GraphicsData* Graphics::GetSavedGraphicsData(const std::string& name)
{
  int index = FindGraphicsDataIndex(name);
  if(index == -1)
    return NULL;

  return mLoadedGraphics[index];
}

void Graphics::MakeBox()
{
  GraphicsData* graphicsdata = new GraphicsData();

  vec2 box[8] =
  { vec2(-0.5f, -0.5f), vec2(0, 1)
  , vec2(-0.5f, 0.5f), vec2(0, 0)
  , vec2( 0.5f, 0.5f), vec2(1, 0)
  , vec2( 0.5f, -0.5f), vec2(1, 1)
  };

  unsigned indices[6] =
  {
    3,1,0,
    3,2,1
  };

  for(unsigned i = 0; i < 8; ++i)
    graphicsdata->vertices.push_back(box[i]);

  for(unsigned i = 0; i < 6; ++i)
    graphicsdata->indices.push_back(indices[i]);

  AddGraphicsData("box", graphicsdata);
}

char* Graphics::LoadShaderFile(const std::string& filename)
{
  FILE* fp = fopen(filename.c_str(), "rc");

  if(!fp)
    return NULL;

  std::string buffer;
  while(!feof(fp))
  {
    buffer.push_back(fgetc(fp));
  }
  fclose(fp);

  unsigned size = buffer.size();
  char* file = new char[size + 1];
  file[size] = '\0';
  memcpy(file, buffer.data(), size * sizeof(char));
  std::cout<<'\n'<<file<<'\n';
  return file;
}

void Graphics::LoadShaders()
{
  mVertexShader = glCreateShader(GL_VERTEX_SHADER);
  mFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  mBasicProgram = glCreateProgram();

  //TODO: add delete commands in case these fail

  if( !CompileShader("vertexshader.vert", GL_VERTEX_SHADER, mVertexShader, mBasicProgram) )
    return; //crash inc

  if( !CompileShader("fragmentshader.frag", GL_FRAGMENT_SHADER, mFragmentShader, mBasicProgram) )
    return; //crash inc

  if( !LinkShaders( mBasicProgram ) )
    return; //crash inc



  //mFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  
  //const char* `VertexShader = CompileShader("vertexshader.vert", mVertexShader);
  //const char* FragmentShader = CompileShader("fragmentshader.frag", mFragmentShader);
  
}

bool Graphics::CompileShader(const char* filename, GLenum type, unsigned& shader, unsigned program)
{
  int why = -1;
  char log[1024];

  const char* buffer = LoadShaderFile(filename);
  
  shader = glCreateShader(type);
  glShaderSource(shader, 1, &buffer, &why);
  glCompileShader(shader);
  
  int size = 0;
  glGetShaderInfoLog(shader, 1024, 0, log);
  
  //if(size >= 1)
  //{
   std::cout<<log;
 //  return false;
  //}

  //glAttachShader(program, shader);

  return true;
}


bool Graphics::LinkShaders(unsigned program)
{
  char log[1024];
  glAttachShader(mBasicProgram, mVertexShader);
  glAttachShader(mBasicProgram, mFragmentShader);

  glBindAttribLocation(mBasicProgram, 0, "vertex");
  glBindAttribLocation(mBasicProgram, 1, "texture_coordinate");
  glLinkProgram(program);
  
  int size = 0;
  glGetProgramInfoLog(program, 1024, &size, log);
  
  if(size >= 1)
  {
   std::cout<<log;
   return false;
  }

  return true;
}

unsigned Graphics::GetTexture(const std::string& filename)
{
  if(mLoadedTextures.find(filename) != mLoadedTextures.end())
    return mLoadedTextures[filename];

  std::fstream file;
  file.open(filename, std::ios::in);
  if(file.is_open())
    std::cout<<"success";
  else
    return 0;
  file.close();

  glEnable(GL_TEXTURE_2D);

  int width, height, bytes;
  unsigned textureID;
  unsigned char* data = stbi_load(filename.c_str(), &width, &height, &bytes, 0);
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, bytes, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glBindTexture(GL_TEXTURE_2D, 0);
  mLoadedTextures[filename] = textureID;

  stbi_image_free(data);
  return textureID;
}