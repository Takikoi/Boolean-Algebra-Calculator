// Made by Ben Bollinger

#pragma once

#include <iostream>
#include "SFML_modules.hpp"
#include "SYSTEM_modules.hpp"

class Button 
{
private:
	sf::RectangleShape button;
	sf::Text text;
	sf::Texture texture;
	sf::Sprite sprites;

	int buttonWidth;
	int buttonHeight;
	
public:
	Button();
	Button(std::string buttonText, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color textColor);
	~Button();
	
	void setFont(sf::Font &fonts);
	void setBackColor(sf::Color color);
	void setTextColor(sf::Color color);
	void setPosition(sf::Vector2f point);
	void render(sf::RenderTarget* window);

	// Check if the mouse is within the bounds of the button:
	bool cursorDetected(const sf::Vector2i& mousePos_);

	void loadTextureFromFile(const std::string& filename_, const sf::IntRect& textureRec_);
	void loadTextureFromFile(const std::string& filename_);
	sf::Sprite& getSprite();
};