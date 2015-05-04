#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SFML/Graphics.hpp>

class Object
{
private:
   static const float            mPI = 3.14159265359;

   b2Body*                       mBody;
   sf::RectangleShape            mShape;



public:
                                 Object(b2Body* body
                                       , sf::Vector2f size
                                       , sf::Vector2f pos
                                       , sf::Color color)
                                 : mBody(body)
                                 , mShape(size)
                                 {
                                    sf::FloatRect bounds = mShape.getLocalBounds();
                                    mShape.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
                                    mShape.setPosition(pos);

                                    mShape.setFillColor(color);
                                 }

   void                          update()
                                 {
                                    sf::Vector2f pos(mBody->GetPosition().x, mBody->GetPosition().y);
                                    mShape.setPosition(pos);

                                    mShape.setRotation((mPI / 180.f) * mBody->GetAngle());
                                 }

   // Getters
   const sf::RectangleShape&     getShape() { return mShape; }
};

#endif // OBJECT_HPP
