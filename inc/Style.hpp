#pragma once
#include <SFML/Graphics.hpp>

class Style
{
    public:

     Style(sf::Color _fillColor, sf::Color _outlineColor, float _outlineThickness);
     
     sf::Color fillColor;
	 sf::Color outlineColor;
	 float outlineThickness;
    
};