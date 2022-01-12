#include "Cell.hpp"

void Cell::initVariables()
{
    rec.setSize(sf::Vector2f((float)CELL_SIZE, (float)CELL_SIZE));
    rec.setFillColor(sf::Color::Cyan);
}

void Cell::initTexture()
{
    if (!textureSheet.loadFromFile("../assets/Boolean Assets ver2.png"))
        std::cout << "[ERROR] : Failed to load texture.";
}

void Cell::initSprites()
{
    sprites.setTexture(textureSheet);

    texRec.emplace(EMPTY_CELL, sf::IntRect(CELL_SIZE*6, 0, 64, 64));

    texRec.emplace(OR_GATE,  sf::IntRect(CELL_SIZE*0, 0, 64, 64));
    texRec.emplace(AND_GATE, sf::IntRect(CELL_SIZE*1, 0, 64, 64));
    texRec.emplace(NOT_GATE, sf::IntRect(CELL_SIZE*2, 0, 64, 64));

    texRec.emplace(GATE_INPUT,        sf::IntRect(CELL_SIZE*0, CELL_SIZE, 64, 64));
    texRec.emplace(WIRE_CORNER_LEFT,  sf::IntRect(CELL_SIZE*1, CELL_SIZE, 64, 64));
    texRec.emplace(WIRE_CORNER_RIGHT, sf::IntRect(CELL_SIZE*2, CELL_SIZE, 64, 64));
    texRec.emplace(WIRE_HORIZONTAL,   sf::IntRect(CELL_SIZE*3, CELL_SIZE, 64, 64));
    texRec.emplace(WIRE_VERTICAL,     sf::IntRect(CELL_SIZE*4, CELL_SIZE, 64, 64));

    texRec.emplace(SIGNAL_IN_A, sf::IntRect(CELL_SIZE*0, CELL_SIZE*2, 64, 64));
    texRec.emplace(SIGNAL_IN_B, sf::IntRect(CELL_SIZE*1, CELL_SIZE*2, 64, 64));
    texRec.emplace(SIGNAL_IN_C, sf::IntRect(CELL_SIZE*2, CELL_SIZE*2, 64, 64));
    texRec.emplace(SIGNAL_IN_D, sf::IntRect(CELL_SIZE*3, CELL_SIZE*2, 64, 64));
    texRec.emplace(SIGNAL_IN_E, sf::IntRect(CELL_SIZE*4, CELL_SIZE*2, 64, 64));
    texRec.emplace(SIGNAL_IN_F, sf::IntRect(CELL_SIZE*5, CELL_SIZE*2, 64, 64));
    texRec.emplace(SIGNAL_IN_G, sf::IntRect(CELL_SIZE*6, CELL_SIZE*2, 64, 64));

    texRec.emplace(SIGNAL_OUT, sf::IntRect(CELL_SIZE*3, 0, 64, 64));

    // Set initial type is EMPTY_CELL
    sprites.setTextureRect(texRec[EMPTY_CELL]);
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

// ######################################################################## (Main Update & Render)

void Cell::update(const float& dtTime_, const sf::Vector2i& mousePos_, const CellType& type_)
{
    sprites.setTextureRect(texRec[type_]);
}

void Cell::render(sf::RenderTarget* target_)
{
    //target_->draw(rec);
    target_->draw(sprites);
}

// ######################################################################## (Program functions)

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

void Cell::changeToNextType()
{
    if (currentType == SIGNAL_OUT)
        currentType = EMPTY_CELL;
    else 
        currentType++;
    sprites.setTextureRect(texRec[currentType]);
    std::cout << currentType << std::endl;
}

void Cell::changeToPreviousType()
{
    if (currentType == EMPTY_CELL)
        currentType = SIGNAL_OUT;
    else 
        currentType--;
    sprites.setTextureRect(texRec[currentType]);
    std::cout << currentType << std::endl;
}

const unsigned char& Cell::getCurrentType() const {
    return currentType;
}