#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <Box2D/Box2D.h>

static const std::vector<sf::Color> Colours = {sf::Color::Red,
                                               sf::Color::Magenta,
                                               sf::Color::Blue,
                                               sf::Color::Cyan,
                                               sf::Color::Yellow,
                                               sf::Color::White};

const float WorldX = 100;
const float WorldY = 75;

const float ViewX = 1200;
const float ViewY = 900;

const float mPI = 3.14159265359f;

const float Scale = ViewX / WorldX;
//const float ScaleX = ViewX / WorldX;
//const float ScaleY = ViewY / WorldY;

sf::Vector2f meterToPixel(float x, float y);
sf::Vector2f meterToPixel(sf::Vector2f meter);
float meterToPixel(float meter);

sf::Vector2f pixelToMeter(float x, float y);
sf::Vector2f pixelToMeter(sf::Vector2f meter);
sf::Vector2i pixelToMeter(sf::Vector2i meter);
float pixelToMeter(float meter);

sf::Color randomColour();
float randomClamped(unsigned int min, unsigned int max);

#endif // UTILITY_HPP
