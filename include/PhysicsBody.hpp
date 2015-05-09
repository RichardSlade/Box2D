#ifndef PHYSICSBODY_HPP
#define PHYSICSBODY_HPP

#include <iostream>
#include <stdexcept>
#include <iostream>
#include <memory>

#include "Utility.hpp"

class PhysicsBody
{
public:
   typedef std::unique_ptr<PhysicsBody> PhyBody;

protected:
   b2Body*                       mBody;
   sf::Shape*                    mShape;

   b2BodyType                    mType;
   bool                          mDestroy;

public:
                                 PhysicsBody(b2Body* body,
                                             sf::Vector2f pos,
                                             sf::Vector2f size,
                                             sf::Color color,
                                             b2BodyType type = b2BodyType::b2_staticBody)
                                 : mBody(body)
                                 , mShape(new sf::RectangleShape(meterToPixel(size)))
                                 , mType(type)
                                 , mDestroy(false)
                                 {
                                    sf::FloatRect bounds = mShape->getLocalBounds();
                                    mShape->setOrigin(bounds.width / 2.f, bounds.height / 2.f);

                                    mShape->setPosition(meterToPixel(pos));
                                    mShape->setFillColor(color);
                                 }

                                 PhysicsBody(b2Body* body,
                                             sf::Vector2f pos,
                                             float32 radius,
                                             sf::Color color,
                                             b2BodyType type = b2BodyType::b2_staticBody)
                                 : mBody(body)
                                 , mShape(new sf::CircleShape(meterToPixel(radius)))
                                 , mType(type)
                                 {
                                    sf::FloatRect bounds = mShape->getLocalBounds();
                                    mShape->setOrigin(bounds.width / 2.f, bounds.height / 2.f);

                                    mShape->setPosition(meterToPixel(pos));
                                    mShape->setFillColor(color);
                                 }

   virtual                       ~PhysicsBody(){ delete mShape; }

   virtual void                  update()
                                 {
                                    b2Vec2 pos = mBody->GetPosition();

                                    if(pos.y > WorldY
                                       || pos.x > WorldX
                                       || pos.x < 0.f)
                                       mDestroy = true;
                                 };

   // Getters
   const sf::Shape&              getShape() { return *mShape; }

   b2Body*                       getBody() { return mBody; }

   bool                          toDestroy() {return mDestroy; }
};

#endif // PHYSICSBODY_HPP
