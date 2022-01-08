#include "Program.hpp"


// ######################################################################## (Constructors & Init)

void Program::initWindow()
{
    title = "Boolean Algebra Calculator 1.0";
    windowBounds = sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
    window = new sf::RenderWindow(windowBounds, title, sf::Style::Close | sf::Style::Titlebar);
    window->setPosition(sf::Vector2i(0, 0));
    window->setFramerateLimit(FPS);
    screenBounds = sf::VideoMode::getDesktopMode();
}

void Program::initStates()
{
    // states.push_back(new MenuState(window));
    states.push_back(new TypeinInputState(window));
    // states.push_back(new GraphicInputState(window));
    // states.push_back(new OutputState(window));
}

Program::~Program() 
{
    for (State* iter : states)
        delete iter;
    
    delete window;
}

Program::Program()
{
    // Init functions
    initWindow();
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

    
    if (!states[iter]->getQuit())
    {
        states[iter]->update(dtTime, mousePos);
    }
    else
    {
        if (states[iter]->getExitFlag() == GO_TO_GRAPHIC)
            iter++;
    }
    
}

void Program::render()
{
    window->clear(sf::Color(236, 234, 234));

    // Render Objects
    states[iter]->render(window);

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
    static bool lock_click;
    while (window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            window->close();
            break;

        case sf::Event::TextEntered:
            states[iter]->handleEvent(ev);
        }
        //graphicInputState->handleEvent(ev);
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
    mousePos.x -= windowPos.x;
    mousePos.y -= (windowPos.y + 34.f);

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