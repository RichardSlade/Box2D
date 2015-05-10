#ifndef WORLD_HPP
#define WORLD_HPP

#include <list>

//#include "DynamicPhysicsBody.hpp"
#include "Player.hpp"

class World
{
private:
   sf::RenderWindow&                   mWindow;
   b2World                             mPhysicsEngine;

//   sf::Vector2i                        mOldMousePos;

   Player::ptrPlayer                   mPlayer;
   std::list<PhysicsBody::PhyBody>     mPhysicsBodies;

   void                                createStaticBodies();
   void                                createPlayer();

   void                                generateBody(sf::Vector2f pos,
                                                    sf::Vector2f size,
                                                    b2BodyType type);

   void                                generateBody(sf::Vector2f pos,
                                                    float radius,
                                                    b2BodyType type);

   void                                handleRealTimeInput();

public:
                                       World(sf::RenderWindow& window);

   void                                updateWorld();
   void                                updatePhysics();
   bool                                handleInput();
   void                                render();

   void                                cleanUpPhysicsBodies();

};

#endif // WORLD_HPP
