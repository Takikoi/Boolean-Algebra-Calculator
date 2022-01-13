#include "OutputState.hpp"

void OutputState::initUI()
{
    if (!backGroundTexture.loadFromFile("../assets/OutputBG.png"))
        std::cout << "Failed to load texture\n";
    backGround.setTexture(backGroundTexture);

    if (!font.loadFromFile("../fonts/Comfortaa-Medium.ttf"))
        std::cout << "Failed to load font\n";
}

void OutputState::initBoolResult()
{
    // Change the max character per line according to how many inputs
    if (rawExp.getInp().size() >= 5)
        expTxt_maxperline = 30;
    else 
        expTxt_maxperline = 45;


//=== Input Expression
    rawExpTxt.setFont(font);
    rawExpTxt.setCharacterSize(26);
    rawExpTxt.setColor(sf::Color(78, 78, 78));
    if (rawExp.getInp().size() >= 5)
        rawExpTxt.setPosition({WINDOW_WIDTH/2 + 50, 50});
    else 
        rawExpTxt.setPosition({330, 50});
    rawExpTxt.setStyle(sf::Text::Bold);

    std::string str_rawExp = "";
    str_rawExp.append("Input: ");
    str_rawExp.append(rawExp.getExp());

    // End line whenever the text reaches maxperline
    if ((float)str_rawExp.size() / expTxt_maxperline > 1)
        for (short j = expTxt_maxperline; j < str_rawExp.size(); j += expTxt_maxperline)
            str_rawExp.insert(j, "\n"); 

    rawExpTxt.setString(str_rawExp);


//=== SOP expression
    sopTxt.setFont(font);
    sopTxt.setCharacterSize(26);
    sopTxt.setColor(sf::Color(78, 78, 78));
    if (rawExp.getInp().size() >= 5)
        sopTxt.setPosition({WINDOW_WIDTH/2 + 50, 150});
    else 
        sopTxt.setPosition({330, 150});
    sopTxt.setStyle(sf::Text::Bold);

    std::string str_sop = "";
    str_sop.append("SOP: ");
    str_sop.append(rawExp.getSOP());

    // End line whenever the text reaches maxperline
    if ((float)str_sop.size() / expTxt_maxperline > 1)
        for (short i = expTxt_maxperline; i < str_sop.size(); i += expTxt_maxperline)
            str_sop.insert(i, "\n");
    
    sopTxt.setString(str_sop);



//=== Simplified Expression
    std::string str_simplifiedExp = "Simplified: ";
    if (rawExp.getInp().size() <= 4) // only process 4 input
    {
        simplifiedExp.initialise(rawExp.getOutput(), pow(2.0, rawExp.getInp().size()), rawExp.getInp());
        simplifiedExp.setPrimeImp();
        simplifiedExp.minimise();
        str_simplifiedExp.append(simplifiedExp.getFunctions());
    }
    else str_simplifiedExp.append(" This program now can only simplify expressions with MAXIMUM 4 inputs");
    
    simplifiedExpTxt.setFont(font);
    simplifiedExpTxt.setCharacterSize(26);
    simplifiedExpTxt.setColor(sf::Color(78, 78, 78));
    simplifiedExpTxt.setStyle(sf::Text::Bold);
    if (rawExp.getInp().size() >= 5)
        simplifiedExpTxt.setPosition({WINDOW_WIDTH/2 + 50, WINDOW_HEIGHT/2});
    else 
        simplifiedExpTxt.setPosition({330, WINDOW_HEIGHT/2});
    
    // End line whenever the text reaches maxperline
    if ((float)str_simplifiedExp.size() / expTxt_maxperline > 1)
        for (short j = expTxt_maxperline; j < str_simplifiedExp.size(); j += expTxt_maxperline)
            str_simplifiedExp.insert(j, "\n"); 

    simplifiedExpTxt.setString(str_simplifiedExp);
}

void OutputState::initButtons()
{
    reStartButton = Button("Restart", {200, 100}, 24, sf::Color::Black, sf::Color::White);
    reStartButton.setFont(font);
    reStartButton.setPosition({WINDOW_WIDTH - 200 - 100, WINDOW_HEIGHT - 100 - 100});
}


OutputState::~OutputState()
{
}

OutputState::OutputState(sf::RenderWindow* window_, const std::string& exp_)
    : State(window_), rawExp(exp_), truthTB(rawExp.getInp(), rawExp.getTB().getBool(), rawExp.getOutput())
{
    initUI();
    initButtons();
    if (rawExp.getInp().size() <= 5)
        initBoolResult();
}

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
            // When left click is released
            lock_click_left1 = false;
            exitFlag = GO_TO_MENU;
            exit = true;
        }
    }
}

void OutputState::render(sf::RenderTarget* target_)
{
    window->draw(backGround);
    if (rawExp.getInp().size() <= 5) // only render max 5 input
        truthTB.render(window);
    target_->draw(sopTxt);
    target_->draw(rawExpTxt);
    target_->draw(simplifiedExpTxt);
    reStartButton.render(window);
}