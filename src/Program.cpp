#include "Program.hpp"


// ######################################################################## (Constructors & Init)

void Program::initVariables()
{
    vidmode = sf::VideoMode(1080, 720);
    dtTime = 0.f;
}
void Program::initStates()
{
    states.push(new ProgramState(window));
}

Program::~Program() {
    delete window;
    for (int i = 0; i < states.size(); ++i)
    {
        // delete allocated memory of each state pointer
        delete states.top();

        // empty out all state pointers from stack
        states.pop();
    }
    
}

Program::Program()
{
    // Init functions
    initVariables();
    initStates();

    // Create window
    window->create(vidmode, "Boolean Algebra Calculator 1.0", sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(60);
}

// ######################################################################## (Main Update & Render)

void Program::update()
{
    updateDtTime();
    pollEvent();

    if (!states.empty())
    {
        states.top()->update(dtTime);
    }
    
}

void Program::render()
{
    window->clear(sf::Color::Black);

    // Render Objects
    if (!states.empty())
    {
        states.top()->render(window);
    }
    

    window->display();
}

// ######################################################################## (Program functions)

const bool Program::running() const {
    return window->isOpen();
}

void Program::pollEvent()
{
    while (window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            window->close();
            break;
        
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape)
                window->close();
            break;
        }
    }
}

void Program::updateDtTime() 
{ 
    // get the time taken to complete 1 loop of update & render

    dtTime = dtClock.restart().asSeconds();
    system("cls");
    std::cout << "Delta Time: " << dtTime << std::endl;
    
}
