#ifndef OBJECT_H
#define OBJECT_H

#include <global.h>
#include <transform.h>
#include <vertex.h>

class Renderable;

class Object
{
public:
  Object();
  Transform mTransform;
  Renderable* pRenderable;

private:
};

#endif