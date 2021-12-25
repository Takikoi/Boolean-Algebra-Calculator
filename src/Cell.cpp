#include "Cell.hpp"

void Cell::initVariables()
{
    rec.setSize(sf::Vector2f((float)WINDOW_WIDTH / NUM_CELLS, (float)WINDOW_WIDTH / NUM_CELLS));
    rec.setFillColor(sf::Color::Cyan);
}

void Cell::initTexture()
{
    if (!textureSheet.loadFromFile("../assets/Boolean Assets.png"))
        std::cout << "[ERROR] : Failed to load texture.";
}

void Cell::initSprites()
{
    sprites.setTexture(textureSheet);

    texRec.emplace("OR gate", sf::IntRect(0, 0, 64, 64));
    texRec.emplace("AND gate", sf::IntRect(CELL_SIZE, 0, 64, 64));
    texRec.emplace("NOT gate", sf::IntRect(CELL_SIZE*2, 0, 64, 64));
    texRec.emplace("Gate input junction", sf::IntRect(0, CELL_SIZE, 64, 64));
    texRec.emplace("Gate left input", sf::IntRect(CELL_SIZE, CELL_SIZE, 64, 64));
    texRec.emplace("Gate right input", sf::IntRect(CELL_SIZE*2, CELL_SIZE, 64, 64));
    texRec.emplace("Signal A", sf::IntRect(0, CELL_SIZE*2, 64, 64));
    texRec.emplace("Signal B", sf::IntRect(CELL_SIZE, CELL_SIZE*2, 64, 64));
    texRec.emplace("Signal C", sf::IntRect(CELL_SIZE*2, CELL_SIZE*2, 64, 64));
}

Cell::~Cell()
{
}

Cell::Cell() {}

Cell::Cell(const sf::Vector2f& pos_)
{
    initVariables();
    initTexture();
    initSprites();

    sprites.setPosition(pos_);
    rec.setPosition(pos_);
}


void Cell::update(const float& dtTime_, const sf::Vector2i& mousePos_, const std::string& type_)
{
    sprites.setTextureRect(texRec[type_]);
}

void Cell::render(sf::RenderTarget* target_)
{
    //target_->draw(rec);
    target_->draw(sprites);
}



void Cell::updateInput(const float& dtTime_, const sf::Vector2i& mousePos_)
{}

void Cell::setColor(const sf::Color& color_)
{
    rec.setFillColor(color_);
}

bool Cell::cursorDetected(const sf::Vector2i& mousePos_)
{
    if ((float)mousePos_.x > rec.getPosition().x && (float)mousePos_.x < (rec.getPosition().x + rec.getSize().x)
     && (float)mousePos_.y > rec.getPosition().y && (float)mousePos_.y < (rec.getPosition().y + rec.getSize().y))
    {
        return true;
    }
    else return false;
}