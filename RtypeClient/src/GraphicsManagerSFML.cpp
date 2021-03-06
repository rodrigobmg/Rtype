#include "GraphicsManagerSFML.h"

GraphicsManagerSFML::GraphicsManagerSFML(void) : window(sf::VideoMode(800, 600, 32), "what ?")
{
  reset();
  font = nullptr;
}


GraphicsManagerSFML::~GraphicsManagerSFML(void)
{
}

void GraphicsManagerSFML::reset()
{
  // Initialize the view to a rectangle located at (100, 100) and with a size of 400x200
  view.reset(sf::FloatRect(0, 0, 800, 600));
  // Rotate it by 45 degrees
  // view.rotate(45);
  // Apply it
  window.setView(view);
  // TODO: the view has to follow the game
  // BONUS: we could play with the view (shake) if we take dmg :D
}

void GraphicsManagerSFML::clear()
{
  window.clear(sf::Color());
}

void GraphicsManagerSFML::draw(const Drawable* drawable, const ValueDrawer& v_drawer)
{
  // std::cout << "getting spritesheet..." << std::endl;

  const std::string& ss = drawable->getSpriteSheetFilename();

  // std::cout << "creating sprite..." << std::endl;
  const ValueDrawable& v_drawable(drawable->getModifiedValue());
  sf::Sprite s(*getTextureFromFilename(ss),
	       GraphicsManagerSFML::rectangleToSFMLRect(Rectangle<int>(v_drawable.dimension.x,
								       v_drawable.dimension.y,
								       Vector2<int>(v_drawable.position.x, v_drawable.position.y))));
  s.setPosition(v_drawer.position.x, v_drawer.position.y);
  s.setScale(v_drawer.scale.x + 1, v_drawer.scale.y + 1);
  s.rotate(v_drawer.rotation);
  window.draw(s);
}

void GraphicsManagerSFML::write(const std::string& text, const ValueDrawer& drawer)
{
  // Create a text
   sf::Text t;
   sf::Font f;
   f.loadFromFile("sprites/Xephyr Shadow Italic.ttf");
   // NOTE: that font is ugly, but the default font is not supported by 
   t.setString(std::string(text));
   t.setFont(f);
   t.setStyle(sf::Text::Bold);
  t.setCharacterSize(20);
  t.setPosition(drawer.position.x, drawer.position.y);
  t.setScale(drawer.scale.x + 1, drawer.scale.y + 1);
  t.setRotation(drawer.rotation);
  window.draw(t);
}

sf::Font& GraphicsManagerSFML::getFont()
{
	if (font == nullptr)
    {
		font = new sf::Font();
		font->loadFromFile("sprites/Xephyr Shadow Italic.ttf");
	}
	return *font;
}

void GraphicsManagerSFML::display()
{
  window.display();
}

template<typename T>
const sf::Rect<T> GraphicsManagerSFML::rectangleToSFMLRect(const Rectangle<T>& r)
{
  sf::Rect<T> r_sfml;
  r_sfml.height = r.height;
  r_sfml.width = r.width;
  r_sfml.left = r.position.x;
  r_sfml.top = r.position.y;
  return r_sfml;
}

const sf::Window& GraphicsManagerSFML::getWindow() const
{
  return window;
}

const sf::Texture* GraphicsManagerSFML::getTextureFromFilename(const std::string& filename)
{
	//std::cout << "getting texture: " << filename << std::endl;
  if (textures[filename] == nullptr)
    {
	  //std::cout << "It doesn't exist..." << std::endl;
      textures[filename] = new sf::Texture();
      // FIXME: use some log like feature.
      //std::cout << "Tying to open: " << filename << std::endl;
      try {
	//std::cout << "Trying..." << std::endl;
	std::cout << textures[filename]->loadFromFile(filename) << std::endl;
	//std::cout << "done..." << std::endl;
      }
      catch(std::exception e)
	{
	  std::cout << "holy shit couldn't open: " << filename << std::endl;
	}
    }
  //else
	  //std::cout << "It exists already !" << std::endl;
  return textures[filename];
}
