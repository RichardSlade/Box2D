#include <cstdlib>

#include "Utility.hpp"

sf::Vector2f meterToPixel(float x, float y)
{
   return sf::Vector2f(x * Scale
                     , y * Scale);
}

sf::Vector2f meterToPixel(sf::Vector2f meter)
{
   return sf::Vector2f(meter.x * Scale
                     , meter.y * Scale);
}

float meterToPixel(float meter)
{
   return meter * Scale;
}

sf::Vector2f pixelToMeter(float x, float y)
{
   return sf::Vector2f(x / Scale
                     , y / Scale);
}

sf::Vector2f pixelToMeter(sf::Vector2f pixel)
{
   return sf::Vector2f(pixel.x / Scale
                     , pixel.y / Scale);
}

sf::Vector2i pixelToMeter(sf::Vector2i pixel)
{
   return sf::Vector2i(pixel.x / Scale
                     , pixel.y / Scale);
}

float pixelToMeter(float pixel)
{
   return pixel / Scale;
}

sf::Color randomColour()
{
   return Colours.at(rand() % (Colours.size() - 1));
}

float randomClamped(unsigned int min, unsigned int max)
{
   return std::rand() % max + min;
}
