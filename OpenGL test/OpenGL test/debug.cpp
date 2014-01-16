#include <debug.h>
#include <global.h>

DebugLogger::DebugLogger()
{
  log.open("log.txt",std::ios::in);
}

void DebugLogger::Print(const std::string& text)
{
  std::cerr<<text;
  log << text;
  log.flush();
}
void DebugLogger::CheckGLError()
{
  Print("checking for errors...");
  GLenum errCode;
  const GLubyte *errString;

  if ((errCode = glGetError()) != GL_NO_ERROR) {
    errString = gluErrorString(errCode);
    fprintf (stderr, "OpenGL Error: %s\n", errString);
    log << "OpenGL Error: " << log << "\n";
  }
  else
    Print(" ...no errors found\n");    
}

