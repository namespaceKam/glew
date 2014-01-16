#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <global.h>
#include <object.h>
#include <renderable.h>
#include <map>

class Camera;

struct GraphicsData
{
  std::vector<vec2> vertices;
  std::vector<float> vertexbuffer;
  std::vector<unsigned> indices;  
  unsigned VertexBufferID;
  unsigned ArrayBufferID;
};

class Graphics
{
public:
  Graphics();
  ~Graphics();
  void SetCamera(Camera* camera);
  Camera* GetCamera();
  void Initialize();
  void Update(float dt);
  void Render(std::vector<Object*>& objects);
  int FindGraphicsDataIndex(const std::string& comp);
  int AddGraphicsData(const std::string& name, GraphicsData* graphics);
  GraphicsData* GetSavedGraphicsData(const std::string& name);
  char* LoadShaderFile(const std::string& filename);
  unsigned GetTexture(const std::string& filename);

private:
  Camera* pCamera;
  void MakeBox();
  void LoadShaders();
  bool LinkShaders(unsigned program);
  bool CompileShader(const char* filename, GLenum type, unsigned& shader, unsigned program);
  std::vector<GraphicsData*> mLoadedGraphics;
  std::map<std::string, int> mVertexTable;
  std::map<std::string, unsigned> mLoadedTextures;

  unsigned mBasicProgram;
  unsigned mVertexShader;
  unsigned mFragmentShader;
};

#endif