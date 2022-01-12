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

    states.emplace(MENU_STATE, new MenuState(window));
    states.emplace(TYPEIN_STATE, new TypeinInputState(window));
    states.emplace(GRAPHIC_STATE, new GraphicInputState(window));
    states.emplace(OUTPUT_STATE, new OutputState(window, ""));

    // key = OUTPUT_STATE;
}

Program::~Program() 
{
    // Only for C++17 & above
    for (auto const& [key, value] : states)
        delete value;
    
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

    // Update window position
    updateWindowPos();

    // Update cursor position
    updateMousePos();

    if (!states[key]->exitState())
    {
        states[key]->update(dtTime, mousePos);
    }
    else
    {
        static float delay(0.f);
        delay += dtTime;
        if (delay >= 0.07f) // Ping : 70ms
        {
            std::string exp = "";
            delay = 0.f;
            switch (states[key]->getExitFlag())
            {
            case GO_TO_TYPEIN:
            key = TYPEIN_STATE;
                delete states[key];
                states[key] = new TypeinInputState(window);
                break;
            
            case GO_TO_GRAPHIC:
                key = GRAPHIC_STATE;
                delete states[key];
                states[key] = new GraphicInputState(window);
                break;

            case GO_TO_OUTPUT:
                exp = states[key]->getExp();
                key = OUTPUT_STATE;
                delete states[key];
                states[key] = new OutputState(window, exp);
                break;

            case GO_TO_MENU:
                key = MENU_STATE;
                delete states[key];
                states[key] = new MenuState(window);
                break;
            }
        }
    }
    
}

void Program::render()
{
    window->clear(sf::Color(236, 234, 234));

    // Render Objects
    states[key]->render(window);

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

        case sf::Event::TextEntered:
            states[key]->handleEvent(ev);
        }
    }

}

void Program::updateDtTime() 
{ 
    dtTime = dtClock.restart().asSeconds();
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
