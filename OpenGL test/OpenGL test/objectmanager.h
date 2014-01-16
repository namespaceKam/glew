#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <global.h>
class Object;

class ObjectManager
{
public:
  ObjectManager();
  void AddObject(Object* object);
  std::vector<Object*>& GetObjects();

private:
  std::vector<Object*> mObjects;
};

#endif