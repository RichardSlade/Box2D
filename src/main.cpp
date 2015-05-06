#include <iostream>

#include "Body.hpp"

sf::RenderWindow window(sf::VideoMode(ViewX, ViewY), "Box2D");
bool closeWindow = false;

void handleInput();

int main()
{
   // Setup Box2D with gravity
   b2Vec2 gravity(0.f, 20.f);
   b2World world(gravity);

   // Container for Bodies
   std::vector<Body> bodies;


   // Define ground body
   b2BodyDef groundBodyDef;
   b2Vec2 pos(WorldX / 4.f, WorldY);
   groundBodyDef.position.Set(pos.x, pos.y);

   b2Body* groundBody = world.CreateBody(&groundBodyDef);

   b2PolygonShape groundBox;
   b2Vec2 size(WorldX / 8.f, WorldY / 16.f);
   groundBox.SetAsBox(size.x, size.y);

   groundBody->CreateFixture(&groundBox, 0.f);

   size *= 2.f;

   Body ground(groundBody
               , size
               , pos
               , sf::Color::Green);


   // Define Dynamic body
   b2BodyDef bodyDef;
   bodyDef.type = b2_dynamicBody;
   pos = b2Vec2(WorldX / 2.f, WorldY / 4.f);
   bodyDef.position.Set(pos.x, pos.y);

   b2Body* body = world.CreateBody(&bodyDef);

   b2PolygonShape dynamicBox;
   size = b2Vec2(15.f, 15.f);
   dynamicBox.SetAsBox(size.x, size.y);

   b2FixtureDef fixtureDef;
   fixtureDef.shape = &dynamicBox;
   fixtureDef.density = 1.f;
   fixtureDef.friction = 0.3f;

   body->CreateFixture(&fixtureDef);

   size *= 2.f;

   Body dynamic(body
                  , size
                  , pos
                  , sf::Color::Red);

   const float32 timeStep = 1.f / 60.f;
   const int32 velocityIters = 6;
   const int32 positionIters = 2;

   const sf::Time FPS = sf::seconds(1.f / 60.f);
   sf::Time countDown = FPS;
   sf::Clock clock;

   while(!closeWindow)
   {
      handleInput();

      countDown -= clock.restart();

      if(countDown < sf::Time::Zero)
      {
         countDown = FPS;
         dynamic.update();
      }

      world.Step(timeStep, velocityIters, positionIters);

      window.clear();

      window.draw(ground.getShape());
      window.draw(dynamic.getShape());

      window.display();
   }

   window.close();

   return 0;
}

void handleInput()
{
   sf::Event e;

   while(window.pollEvent(e))
   {
      switch(e.type)
      {
         case sf::Event::KeyReleased:
         {
            if(e.key.code == sf::Keyboard::Escape)
               closeWindow = true;

            break;
         }
         case sf::Event::Closed:
         {
            closeWindow = true;
            break;
         }
         default: break;
      }
   }
}
