#include <objectmanager.h>

ObjectManager::ObjectManager()
{}

void ObjectManager::AddObject(Object* object)
{
  mObjects.push_back(object);
}

std::vector<Object*>& ObjectManager::GetObjects()
{
  return mObjects;
}