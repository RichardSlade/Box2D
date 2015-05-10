#include <iostream>

#include "World.hpp"

const static float32 TimeStep = 1.f / 60.f;
const static int32 VelocityIters = 6;
const static int32 PositionIters = 2;
const static unsigned int NumStaticBodies = 8;
const static float PlayerRadius = 2.f;

World::World(sf::RenderWindow& window)
: mWindow(window),
mPhysicsEngine(b2Vec2(0.f, 0.f)),
mPlayer(nullptr)
{
//   createStaticBodies();
   createPlayer();
}

void World::createStaticBodies()
{
      // Create ground
   sf::Vector2f pos(WorldX / 2.f, WorldY);

   generateBody(pos,
               sf::Vector2f(WorldX, WorldY / 16.f),
               b2BodyType::b2_staticBody);

   // Generate static bodies
   for(unsigned int i = 0; i < NumStaticBodies; i++)
   {
      pos = sf::Vector2f(randomClamped(0, WorldX), randomClamped(0, WorldY));

      if(i % 2 != 0)
      {
         sf::Vector2f size(WorldX / randomClamped(8, 32),
                           WorldY / randomClamped(8, 32));

         generateBody(pos,
                  size,
                  b2BodyType::b2_staticBody);
      }
      else
      {
         float size = WorldX / randomClamped(8, 32);

         generateBody(pos,
                  size,
                  b2BodyType::b2_staticBody);
      }
   }
}

void World::createPlayer()
{
   b2BodyType type = b2_dynamicBody;
   sf::Vector2f pos(WorldX / 2.f, WorldY / 2.f);

   b2BodyDef bodyDef;
   bodyDef.type = type;
   bodyDef.position.Set(pos.x, pos.y);

   b2Body* body = mPhysicsEngine.CreateBody(&bodyDef);

   b2CircleShape circle;
   circle.m_p.Set(0.f, 0.f);
   circle.m_radius = PlayerRadius;

   PhysicsBody::PhyBody phyBody = nullptr;

   b2FixtureDef fixtureDef;
   fixtureDef.shape = &circle;
   fixtureDef.density = 1.f;
   fixtureDef.friction = 0.3f;

   body->CreateFixture(&fixtureDef);

   mPlayer = Player::ptrPlayer(new Player(body,
                                          pos,
                                          PlayerRadius,
                                          sf::Color::Green));
}

void World::generateBody(sf::Vector2f pos,
                         sf::Vector2f size,
                         b2BodyType type = b2_staticBody)
{
   b2BodyDef bodyDef;
   bodyDef.type = type;
   bodyDef.position.Set(pos.x, pos.y);

   b2Body* body = mPhysicsEngine.CreateBody(&bodyDef);

   b2PolygonShape box;
   box.SetAsBox(size.x / 2.f, size.y / 2.f);

   PhysicsBody::PhyBody phyBody = nullptr;

   if(type == b2_staticBody)
   {
      body->CreateFixture(&box, 0.f);

      phyBody = PhysicsBody::PhyBody(new PhysicsBody(body,
                                                      pos,
                                                      size,
                                                      randomColour()));
   }
   else
   {
      b2FixtureDef fixtureDef;
      fixtureDef.shape = &box;
      fixtureDef.density = 1.f;
      fixtureDef.friction = 0.3f;

      body->CreateFixture(&fixtureDef);

      phyBody = PhysicsBody::PhyBody(new DynamicPhysicsBody(body,
                                                            pos,
                                                            size,
                                                            randomColour()));
   }

   if(phyBody)
      mPhysicsBodies.push_back(std::move(phyBody));
}

void World::generateBody(sf::Vector2f pos,
                      float radius,
                      b2BodyType type = b2_staticBody)
{
   b2BodyDef bodyDef;
   bodyDef.type = type;
   bodyDef.position.Set(pos.x, pos.y);

   b2Body* body = mPhysicsEngine.CreateBody(&bodyDef);

   b2CircleShape circle;
   circle.m_p.Set(0.f, 0.f);
   circle.m_radius = radius;

   PhysicsBody::PhyBody phyBody = nullptr;

   if(type == b2_staticBody)
   {
      body->CreateFixture(&circle, 0.f);

      phyBody = PhysicsBody::PhyBody(new PhysicsBody(body,
                                                      pos,
                                                      radius,
                                                      randomColour()));
   }
   else
   {
      b2FixtureDef fixtureDef;
      fixtureDef.shape = &circle;
      fixtureDef.density = 1.f;
      fixtureDef.friction = 0.3f;

      body->CreateFixture(&fixtureDef);

      phyBody = PhysicsBody::PhyBody(new DynamicPhysicsBody(body,
                                                            pos,
                                                            radius,
                                                            randomColour()));
   }

   if(phyBody)
      mPhysicsBodies.push_back(std::move(phyBody));
}

void World::handleRealTimeInput()
{
   sf::Vector2f vel;

   if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
   {
      vel.y = -10.f;
   }
   else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
   {
      vel.y = 10.f;
   }
   else vel.y = 0.f;

   if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
   {
      vel.x = -10.f;
   }
   else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
   {
      vel.x = 10.f;
   }
   else vel.x = 0.f;

   mPlayer->setVelocity(vel);
}

void World::updateWorld()
{
   for(std::list<PhysicsBody::PhyBody>::iterator it = mPhysicsBodies.begin();
       it != mPhysicsBodies.end();
       it++)
      (*it)->update();

   if(mPlayer)
      mPlayer->update();

   cleanUpPhysicsBodies();
}

void World::updatePhysics()
{
   mPhysicsEngine.Step(TimeStep, VelocityIters, PositionIters);
}

bool World::handleInput()
{
   sf::Event e;

   while(mWindow.pollEvent(e))
   {
      switch(e.type)
      {
         case sf::Event::KeyReleased:
         {
            if(e.key.code == sf::Keyboard::Escape)
               return false;

            break;
         }
         case sf::Event::Closed: return false;
         case sf::Event::MouseButtonReleased:
         {
            if(e.mouseButton.button == sf::Mouse::Left)
            {
               sf::Vector2f pos(pixelToMeter(sf::Mouse::getPosition(mWindow)));
               sf::Vector2f size(randomClamped(1, 3), randomClamped(1, 3));

               generateBody(pos,
                            size,
                            b2BodyType::b2_dynamicBody);
            }
            else if(e.mouseButton.button == sf::Mouse::Right)
            {
               sf::Vector2f pos(pixelToMeter(sf::Mouse::getPosition(mWindow)));
               float radius = randomClamped(1, 3);

               generateBody(pos,
                            radius,
                            b2BodyType::b2_dynamicBody);
            }

            break;
         }
         default: break;
      }
   }

   handleRealTimeInput();

   return true;
}

void World::render()
{
   for(std::list<PhysicsBody::PhyBody>::iterator it = mPhysicsBodies.begin();
       it != mPhysicsBodies.end();
       it++)
      mWindow.draw((*it)->getShape());

   if(mPlayer)
      mWindow.draw(mPlayer->getShape());
}


void World::cleanUpPhysicsBodies()
{
   auto wreckfieldBegin = std::remove_if(mPhysicsBodies.begin()
                                    , mPhysicsBodies.end()
                                    , std::mem_fn(&PhysicsBody::toDestroy));

   for(auto it = wreckfieldBegin; it != mPhysicsBodies.end(); it++)
      if((*it))
         mPhysicsEngine.DestroyBody((*it)->getBody());

   mPhysicsBodies.erase(wreckfieldBegin, mPhysicsBodies.end());
}
