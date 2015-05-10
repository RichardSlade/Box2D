#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>

#include "DynamicPhysicsBody.hpp"

class Player : public DynamicPhysicsBody
{
public:
   typedef std::unique_ptr<Player> ptrPlayer;

private:
   sf::Vector2f      mVelocity;

public:
                     Player(b2Body* body,
                           sf::Vector2f pos,
                           float size,
                           sf::Color color)
                     : DynamicPhysicsBody(body,
                                          pos,
                                          size,
                                          color)
                     , mVelocity(sf::Vector2f())
                     {

                     }

   virtual           ~Player(){};

   virtual void      update()
                     {
//                        std::cout << "X: " << mVelocity.x << ", Y: " << mVelocity.y << std::endl;

                        mBody->SetLinearVelocity(b2Vec2(mVelocity.x, mVelocity.y));

                        DynamicPhysicsBody::update();
                     }

   // Setters
   void              setVelocity(sf::Vector2f vel) { mVelocity = vel; }
};

#endif // PLAYER_HPP
