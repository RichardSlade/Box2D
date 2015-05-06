#ifndef BODY_HPP
#define BODY_HPP

#include <iostream>
#include <stdexcept>
#include <iostream>

#include "Utility.hpp"

class Body
{
protected:
   b2Body*                       mBody;
   sf::RectangleShape            mShape;

public:
                                 Body(b2Body* body
                                       , b2Vec2 size
                                       , b2Vec2 pos
                                       , sf::Color color)
                                 : mBody(body)
                                 , mShape(metersToPixel(size))
                                 {
                                    sf::FloatRect bounds = mShape.getLocalBounds();
                                    mShape.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

                                    mShape.setPosition(metersToPixel(pos));
                                    mShape.setFillColor(color);
                                 }

   virtual                       ~Body(){}

   virtual void                  update(){};

   // Getters
   const sf::RectangleShape&     getShape() { return mShape; }
};

#endif // BODY_HPP
