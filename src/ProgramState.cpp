#include "ProgramState.hpp"

ProgramState::~ProgramState()
{
    delete window;
}

ProgramState::ProgramState(sf::RenderWindow* window_) 
    : State(window_)
{
}

// ######################################################################## (Main Update & Render)

void ProgramState::update(const float& dtTime_)
{
    updateInput(dtTime_);
    logicGate.update(dtTime_);
}

void ProgramState::render(sf::RenderTarget* target_)
{
    if (!target_)
        target_ = window;
    logicGate.render(target_);
}

// ######################################################################## (Program functions)

void ProgramState::updateInput(const float& dtTime_)
{
    checkForQuit();
    updateMousePos();
    using namespace std;
    //cout << "pos: " << mousePos.x << ", " << mousePos.y << endl;
    sf::Vector2i winpos = window->getPosition();
    //cout << "pos: " << winpos.x << ", " << winpos.y << endl;
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    //     logicGate.move(dtTime_, sf::Vector2f(-1.f, 0.f));
    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    //     logicGate.move(dtTime_, sf::Vector2f(1.f, 0.f));

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    //     logicGate.move(dtTime_, sf::Vector2f(0.f, -1.f));
    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    //     logicGate.move(dtTime_, sf::Vector2f(0.f, 1.f));


}

void ProgramState::endState()
{
    std::cout << "end program state.";
}