#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

#include "Object.hpp"

sf::Vector2f metersToPixel(b2Vec2 meters)
{

}

int main()
{
   sf::RenderWindow window(sf::VideoMode(800, 600), "Box2D");

   b2Vec2 gravity(0.f, -10.f);
   b2World world(gravity);

   b2BodyDef groundBodyDef;
   sf::Vector2f pos(0.f, 10.f);
   groundBodyDef.position.Set(pos.x, pos.y);

   b2Body* groundBody = world.CreateBody(&groundBodyDef);

   b2PolygonShape groundBox;
   sf::Vector2f size(50.f, 10.f);
   groundBox.SetAsBox(size.x, size.y);

   groundBody->CreateFixture(&groundBox, 0.f);

   Object ground(groundBody
               , size
               , pos
               , sf::Color::Green);

   b2BodyDef bodyDef;
   bodyDef.type = b2_dynamicBody;
   pos = sf::Vector2f(0.f, 4.f);
   bodyDef.position.Set(pos.x, pos.y);

   b2Body* body = world.CreateBody(&bodyDef);

   b2PolygonShape dynamicBox;
   size = sf::Vector2f(1.f, 1.f);
   dynamicBox.SetAsBox(size.x, size.y);

   b2FixtureDef fixtureDef;
   fixtureDef.shape = &dynamicBox;
   fixtureDef.density = 1.f;
   fixtureDef.friction = 0.3f;

   body->CreateFixture(&fixtureDef);

   Object dynamic(body
                  , size
                  , pos
                  , sf::Color::Red);

   const float32 timeStep = 1.f / 60.f;
   const int32 velocityIters = 6;
   const int32 positionIters = 2;

   const sf::Time FPS = sf::seconds(1.f / 60.f);
   sf::Time countDown = FPS;
   sf::Clock clock;

   bool closeWindow = false;

   int count = 100;

   while(!closeWindow)
//   while(--count > 0)
   {
      sf::Event e;

      while(window.pollEvent(e))
      {
         if(e.key.code == sf::Keyboard::Escape)
            closeWindow = true;
      }

      countDown -= clock.restart();

      if(countDown < sf::Time::Zero)
      {
         countDown = FPS;

         ground.update();
         dynamic.update();
      }

      world.Step(timeStep, velocityIters, positionIters);

      std::cout << "Ground Pos: " << groundBody->GetPosition().x <<  groundBody->GetPosition().y << "\tAngle: " << groundBody->GetAngle() << std::endl;
//      std::cout << "Body Pos: " << body->GetPosition().x <<  body->GetPosition().y << "\tAngle: " << body->GetAngle() << std::endl;

      window.clear();

      window.draw(ground.getShape());
      window.draw(dynamic.getShape());

      window.display();
   }

   window.close();

   return 0;
}
