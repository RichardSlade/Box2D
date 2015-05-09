#ifndef DYNAMICPHYSICSBODY_HPP
#define DYNAMICPHYSICSBODY_HPP

#include <iostream>

#include "PhysicsBody.hpp"

class DynamicPhysicsBody : public PhysicsBody
{
public:
                        DynamicPhysicsBody(b2Body* body
                                          , sf::Vector2f pos
                                          , sf::Vector2f size
                                          , sf::Color color)
                        : PhysicsBody(body
                                    , pos
                                    , size
                                    , color
                                    , b2BodyType::b2_dynamicBody)
                        {};

                        DynamicPhysicsBody(b2Body* body
                                          , sf::Vector2f pos
                                          , float radius
                                          , sf::Color color)
                        : PhysicsBody(body
                                    , pos
                                    , radius
                                    , color
                                    , b2BodyType::b2_dynamicBody)
                        {};

   virtual              ~DynamicPhysicsBody(){};

   virtual void         update()
                        {
                           b2Vec2 currentPos = mBody->GetPosition();

                           mShape->setPosition(meterToPixel(currentPos.x, currentPos.y));
                           mShape->setRotation((180.f / mPI) * mBody->GetAngle());

                           PhysicsBody::update();
                        }
};

#endif // DYNAMICPHYSICSBODY_HPP
