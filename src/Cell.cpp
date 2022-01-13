#include "Cell.hpp"

void Cell::initBounds()
{
    boundingBox.setSize(sf::Vector2f((float)CELL_SIZE, (float)CELL_SIZE));
    boundingBox.setFillColor(sf::Color::Cyan);
}

void Cell::initTexture()
{
    if (!textureSheet.loadFromFile("../assets/Boolean Assets ver2.png"))
        std::cout << "[ERROR] : Failed to load texture.";

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
    initBounds();
    initTexture();

    sprites.setPosition(pos_);
    boundingBox.setPosition(pos_);
}

// ######################################################################## (Main Update & Render)

void Cell::update(const float& dtTime_, const sf::Vector2i& mousePos_, const CellType& type_)
{
    sprites.setTextureRect(texRec[type_]);
}

void Cell::render(sf::RenderTarget* target_)
{
    //target_->draw(boundingBox);
    target_->draw(sprites);
}

// ######################################################################## (Program functions)


bool Cell::cursorDetected(const sf::Vector2i& mousePos_)
{
    // when ti cursor is in the bounding box region
    if ((float)mousePos_.x > boundingBox.getPosition().x && (float)mousePos_.x < (boundingBox.getPosition().x + boundingBox.getSize().x)
     && (float)mousePos_.y > boundingBox.getPosition().y && (float)mousePos_.y < (boundingBox.getPosition().y + boundingBox.getSize().y))
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
    // std::cout << currentType << std::endl;
}

void Cell::changeToPreviousType()
{
    if (currentType == EMPTY_CELL)
        currentType = SIGNAL_OUT;
    else 
        currentType--;
    sprites.setTextureRect(texRec[currentType]);
    // std::cout << currentType << std::endl;
}

const unsigned char& Cell::getCurrentType() const {
    return currentType;
}