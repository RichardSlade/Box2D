#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <Box2D/Box2D.h>

const float WorldX = 100;
const float WorldY = 75;

const float ViewX = 640;
const float ViewY = 480;

const float mPI = 3.14159265359;

const float ScaleX = ViewX / WorldX;
const float ScaleY = ViewY / WorldY;

sf::Vector2f metersToPixel(b2Vec2 meters)
{
   return sf::Vector2f(meters.x * ScaleX
                     , meters.y * ScaleY);
}

#endif // UTILITY_HPP
