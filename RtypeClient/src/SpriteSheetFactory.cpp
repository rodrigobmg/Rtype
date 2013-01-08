#include "SpriteSheetFactory.h"

SpriteSheetFactory::SpriteSheetFactory()
{
  // FIXME: all these spriteSheets are leaked. OK, it doesn't matter as it's a singleton, but if we want to free some resource at runtime, make sure to fix this.
 
  // SHIPS spritesheet
   spriteSheets[0] = new SpriteSheet();
  spriteSheets[0]->setFilename("sprites/r-typesheet42.gif");

  std::map<int, std::list<Rectangle<int> > > animList;
  std::list<Rectangle<int> > singleAnim;
  singleAnim.push_back(Rectangle<int>(33, 17));
  singleAnim.push_back(Rectangle<int>(33, 17, Vector2<int>(132, 0)));
  animList[0] = singleAnim;

  singleAnim.clear();
  singleAnim.push_back(Rectangle<int>(33, 17, Vector2<int>(0, 17)));
  singleAnim.push_back(Rectangle<int>(33, 17, Vector2<int>(132, 17)));
  animList[1] = singleAnim;
  spriteSheets[0]->setAnimations(animList);
  spriteSheets[0]->setInterpolation(3);
  spriteSheets[0]->setTimeBetweenAnimationFrame(250);
  spriteSheets[0]->setSmoothLoop(true);
  //

  // Background fixed image
  animList.clear();
  singleAnim.clear();

  spriteSheets[1] = new SpriteSheet();
  spriteSheets[1]->setFilename("sprites/farback.gif");
  singleAnim.push_back(Rectangle<int>(1599, 599));
  animList[0] = singleAnim;
  spriteSheets[1]->setAnimations(animList);
  spriteSheets[1]->setInterpolation(0);
  spriteSheets[1]->setTimeBetweenAnimationFrame(250);
  spriteSheets[1]->setSmoothLoop(false);
  //

  // Background scrolling image
  animList.clear();
  singleAnim.clear();

  spriteSheets[2] = new SpriteSheet();
  spriteSheets[2]->setFilename("sprites/starfield.png");
  singleAnim.push_back(Rectangle<int>(799, 599, Vector2<int>(-799, 0)));
  singleAnim.push_back(Rectangle<int>(799, 599, Vector2<int>(0, 0)));
  singleAnim.push_back(Rectangle<int>(799, 599, Vector2<int>(799, 0)));
  animList[0] = singleAnim;
  spriteSheets[2]->setAnimations(animList);
  spriteSheets[2]->setInterpolation(0);
  spriteSheets[2]->setTimeBetweenAnimationFrame(8000);
  spriteSheets[2]->setSmoothLoop(false);
  spriteSheets[2]->setSmoothFrames(true);
  //


  // [------- UI -------]

  // UI buttons
  animList.clear();
  singleAnim.clear();

  spriteSheets[3] = new SpriteSheet();
  spriteSheets[3]->setFilename("sprites/button_default.png");
  singleAnim.push_back(Rectangle<int>(141, 27, Vector2<int>(0, 0)));
  animList[0] = singleAnim;
  singleAnim.clear();
  // TODO: add [selected] "animation" (proper to default) (it's just an image, but c'm'on, better than nothing)
  singleAnim.push_back(Rectangle<int>(141, 29, Vector2<int>(0, 55)));
  animList[1] = singleAnim;

  spriteSheets[3]->setAnimations(animList);
  spriteSheets[3]->setInterpolation(0);
  spriteSheets[3]->setTimeBetweenAnimationFrame(250);
  spriteSheets[3]->setSmoothLoop(false);
  //
  
  //UI arrows
  animList.clear();
  singleAnim.clear();

  spriteSheets[4] = new SpriteSheet();
  spriteSheets[4]->setFilename("sprites/arrows.png");
  singleAnim.push_back(Rectangle<int>(23, 26, Vector2<int>(0, -1)));
  singleAnim.push_back(Rectangle<int>(23, 26, Vector2<int>(0, 47)));
  animList[0] = singleAnim;
  
  spriteSheets[4]->setAnimations(animList);
  spriteSheets[4]->setInterpolation(0);
  spriteSheets[4]->setTimeBetweenAnimationFrame(800);
  spriteSheets[4]->setSmoothLoop(false);


}

SpriteSheetFactory* SpriteSheetFactory::instance = nullptr;

SpriteSheetFactory* SpriteSheetFactory::getInstance()
{
  if (instance == nullptr)
    instance = new SpriteSheetFactory();
  return instance;
}

SpriteSheet* SpriteSheetFactory::getSpriteSheet(int id)
{
  return spriteSheets[id];
}