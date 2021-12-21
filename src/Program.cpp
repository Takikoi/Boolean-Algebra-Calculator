#include "Program.hpp"


// ######################################################################## (Constructors & Init)

void Program::initWindow()
{
    title = "Boolean Algebra Calculator 1.0";
    windowBounds = sf::VideoMode(1800, 900);
    window = new sf::RenderWindow(windowBounds, title, sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(FPS);
    screenBounds = sf::VideoMode::getDesktopMode();
}

void Program::initStates()
{
    states.push(new ProgramState(window));
}

void Program::initKeys()
{
    supportedKeys.emplace("A", sf::Keyboard::A);
    supportedKeys.emplace("D", sf::Keyboard::D);
    supportedKeys.emplace("W", sf::Keyboard::W);
    supportedKeys.emplace("S", sf::Keyboard::S);
}

Program::~Program() 
{
    // No need to call window->close(), bc it's already out of the isOpen() loop
    delete window;
    while (!states.empty())
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
    initWindow();
    initKeys();
    initStates();

    info();
}

// ######################################################################## (Main Update & Render)

void Program::update()
{
    // Get loop elapsed time
    updateDtTime();
    // Get input from user
    pollProgramEvent();
    updateWindowPos();
    updateMousePos();

    if (!states.empty())
    {
        states.top()->update(dtTime);

        if (states.top()->getQuit())
        {
            states.top()->endState();
            delete states.top();
            states.pop();
        }
        
    }
    else 
    {
        window->close();
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

void Program::info() const {
    using namespace std;
    cout << "========== " << title << " ==========" << endl;
    cout << "[Screen Resolution] : " << screenBounds.width << " x " << screenBounds.height << endl;
    cout << "[Window Dimensions] : " << windowBounds.width << " x " << windowBounds.height << endl;
    cout << "[Program FPS]       : " << FPS << endl;
    cout << "[VSYNC enabled]     : false " << endl;
}

const bool Program::running() const {
    return window->isOpen();
}

void Program::pollProgramEvent()
{
    while (window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            window->close();
            break;
        }
    }
}

void Program::updateDtTime() 
{ 
    // get the time taken to complete 1 loop of update & render
    dtTime = dtClock.restart().asSeconds();
    //system("cls");
    //std::cout << "Delta Time: " << dtTime << std::endl;
    
}

void Program::updateWindowPos() {
    windowPos = window->getPosition();
}

void Program::updateMousePos() {
    // Set the cursor origin to the position of the window relative to the screen
    mousePos = sf::Mouse::getPosition();
    mousePos -= windowPos;

    if (mousePos.x < 0)
        mousePos.x = 0;

    if (mousePos.y < 0)
        mousePos.y = 0;

    using namespace std;
    // cout << "Mouse pos: " << setw(4) << left << mousePos.x << ", " << setw(4) << left <<  mousePos.y << "____ " 
    //      << "Win pos: " << setw(4) << left << windowPos.x << ", " << setw(4) << left <<  windowPos.y << "____ " 
    //      << "Screen size: " << setw(4) << left << screenBounds.width << ", " << setw(4) << left <<  screenBounds.height << endl;
}

const sf::Vector2i& Program::getWindowPos() const {
    return windowPos;
}

const sf::Vector2i& Program::getMousePos() const {
    return mousePos;
}