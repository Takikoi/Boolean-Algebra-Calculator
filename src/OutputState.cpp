#include "OutputState.hpp"

void OutputState::initStuff()
{
    if (!backGroundTexture.loadFromFile("../assets/OutputBG.png"))
        std::cout << "Failed to load texture\n";
    backGround.setTexture(backGroundTexture);

    if (!font.loadFromFile("../fonts/Comfortaa-Medium.ttf"))
        std::cout << "Failed to load font\n";

    if (rawExp.getInp().size() >= 5)
        sopTxt_maxperline = 35;
    else 
        sopTxt_maxperline = 50;
    


    simplifiedExp.initialise(rawExp.getOutput(), pow(2.0, rawExp.getInp().size()), "");
    simplifiedExp.setPrimeImp();
	simplifiedExp.minimise();
    simplifiedExp.displayFunctions();
    // std::cout << "Simplified exp: " << simplifiedExp.getFunctions() << " \n";

    sopTxt.setFont(font);
    sopTxt.setCharacterSize(26);
    sopTxt.setColor(sf::Color(78, 78, 78));
    if (rawExp.getInp().size() >= 5)
        sopTxt.setPosition({WINDOW_WIDTH/2 + 50, 50});
    else 
        sopTxt.setPosition({330, 50});

    sopTxt.setStyle(sf::Text::Bold);

    std::string str_sop = "";
    str_sop.append("SOP: ");
    str_sop.append(rawExp.getSOP());

    if (str_sop.size() / sopTxt_maxperline > 1)
        for (short i = sopTxt_maxperline; i < str_sop.size(); i += sopTxt_maxperline)
            str_sop.insert(i, "\n");
    
    sopTxt.setString(str_sop);

    simplifiedExpTxt.setFont(font);
    simplifiedExpTxt.setCharacterSize(64);
    simplifiedExpTxt.setColor(sf::Color(78, 78, 78));
    simplifiedExpTxt.setPosition({100, 100});

    reStartButton = Button("Restart", {200, 100}, 24, sf::Color::Black, sf::Color::White);
    reStartButton.setFont(font);
    reStartButton.setPosition({900, 600});
    
}

OutputState::~OutputState()
{
}

OutputState::OutputState()
{
}

OutputState::OutputState(sf::RenderWindow* window_, const std::string& exp_)
    : State(), window(window_), sopStr(exp_), rawExp(exp_), truthTB(rawExp.getInp(), rawExp.getTB().getBool(), rawExp.getOutput())
{
    initStuff();
}

void OutputState::updateInput(const float& dtTime_, const sf::Vector2i& mousePos_)
{
}

void OutputState::updateMousePos(const sf::Vector2i& mousePos_)
{}

void OutputState::update(const float& dtTime_, const sf::Vector2i& mousePos_)
{
    static bool lock_click_left1 = false;
    if (reStartButton.cursorDetected(mousePos_))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_click_left1 == false)
        {
            lock_click_left1 = true;
        }
        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && lock_click_left1 == true)
        {
            lock_click_left1 = false;
            exitFlag = GO_TO_MENU;
            quit = true;
        }
    }
}

void OutputState::render(sf::RenderTarget* target_)
{
    window->draw(backGround);
    truthTB.render(window);
    target_->draw(sopTxt);
    reStartButton.render(window);
}

void OutputState::handleEvent(sf::Event& ev_)
{}

void OutputState::setExp(const std::string& exp_) {
    sopStr = exp_;
}