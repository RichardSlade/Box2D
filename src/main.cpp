#include <ctime>
#include <cstdlib>

#include "World.hpp"

int main()
{
   srand(time(NULL));

   sf::RenderWindow window(sf::VideoMode(ViewX, ViewY), "Box2D");
   World world(window);

   const sf::Time FPS = sf::seconds(1.f / 60.f);
   sf::Time countDown = FPS;
   sf::Clock clock;

   while(true)
   {
      // If user request to close window
      // function returns false
      if(!world.handleInput())
         break;

      countDown -= clock.restart();

      if(countDown < sf::Time::Zero)
      {
         countDown = FPS;
         world.updateWorld();
      }

      world.updatePhysics();

      window.clear(sf::Color(150, 150, 150));
      world.render();
      window.display();
   }

   window.close();

   return 0;
}

