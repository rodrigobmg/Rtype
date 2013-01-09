#include "DrawableRemote.h"

DrawableRemote::DrawableRemote() :
  Drawable(*SpriteSheetFactory::getInstance()->getSpriteSheet(0)),
  updater(nullptr)
{
  this->animate(1);

}

void DrawableRemote::update(float elapsedTime)
{
  if (updater != nullptr)
    {
      this->setPosition(updater->xPosition, updater->yPosition);
      // TODO: animate depending on the updater.
      delete updater;
      updater = nullptr;
    }
  Drawable::update(elapsedTime);
}

void DrawableRemote::setUpdate(const Protocol::drawable& d)
{
  updater = new Protocol::drawable(d);
}
