#include "Button.hpp"

Button::~Button()
{
}

Button::Button()
{
}

Button::Button(std::string btnText, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color textColor) 
{
    button.setSize(buttonSize);
    button.setFillColor(bgColor);

    // Get these for later use:
    buttonWidth = buttonSize.x;
    buttonHeight = buttonSize.y;

    text.setString(btnText);
    text.setCharacterSize(charSize);
    text.setColor(textColor);
}

// Pass font by reference:
void Button::setFont(sf::Font &fonts) {
    text.setFont(fonts);
}

void Button::setBackColor(sf::Color color = sf::Color::Black) {
    button.setFillColor(color);
}

void Button::setTextColor(sf::Color color = sf::Color::White) {
    text.setColor(color);
}

void Button::setPosition(sf::Vector2f point) 
{
    button.setPosition(point);
    sprites.setPosition(point);

    // Center text on button:
    float xPos = (point.x + buttonWidth / 2) - (text.getLocalBounds().width / 2);
    float yPos = (point.y + buttonHeight / 2.2) - (text.getLocalBounds().height / 2);
    text.setPosition(xPos, yPos);
}

void Button::render(sf::RenderTarget* target_) 
{
    target_->draw(button);
    target_->draw(sprites);
    target_->draw(text);
}

// Check if the mouse is within the bounds of the button:
bool Button::cursorDetected(const sf::Vector2i& mousePos_) 
{
    int mouseX = mousePos_.x;
    int mouseY = mousePos_.y;

    int btnPosX = button.getPosition().x;
    int btnPosY = button.getPosition().y;

    int btnxPosWidth = button.getPosition().x + buttonWidth;
    int btnyPosHeight = button.getPosition().y + buttonHeight;

    if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY)
        return true;
    
    return false;
}

void Button::loadTextureFromFile(const std::string& filename_, const sf::IntRect& textureRec_) {
    texture.loadFromFile(filename_, textureRec_);
    sprites.setTexture(texture);
}

void Button::loadTextureFromFile(const std::string& filename_) {
    texture.loadFromFile(filename_);
    sprites.setTexture(texture);
}

sf::Sprite& Button::getSprite() {
    return sprites;
}
