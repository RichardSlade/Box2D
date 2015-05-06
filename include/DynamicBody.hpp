#ifndef DYNAMICBODY_HPP
#define DYNAMICBODY_HPP

#include "Body.hpp"

class DynamicBody : public Body
{
public:
                        DynamicBody(b2Body* body
                                 , b2Vec2 size
                                 , b2Vec2 pos
                                 , sf::Color color)
                        : Body(body
                              , size
                              , pos
                              , color)
                        {};

   virtual              ~DynamicBody(){};

   virtual void         update()
                        {
                           b2Vec2 currentPos = mBody->GetPosition();

                           mShape.setPosition(metersToPixel(currentPos));
                           mShape.setRotation((180.f / mPI) * mBody->GetAngle());
                        }
};

#endif // DYNAMICBODY_HPP
