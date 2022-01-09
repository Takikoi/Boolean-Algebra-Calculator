#include "TruthTable.hpp"

void TruthTable::initStuff()
{
    pos = sf::Vector2f(50.f, 100.f);
    boolCellSize = sf::Vector2f(45.f, 45.f);

    if (!font.loadFromFile("../fonts/Comfortaa-Medium.ttf"))
        std::cout << "Failed to load font\n";

    // truthTBValue = new bool*[5];
    // for (short i = 0; i < 5; ++i)
    //     truthTBValue[i] = new bool[10];

    // for (short i = 0; i < 5; ++i)
    //     for (short j = 0; j < 10; ++j)
    //         truthTBValue[i][j] = 0;

    // checkInputSignal();
    // numCol = exp.size();
    // numRow = pow(numCol, 2.0);

    // truthTBText = new sf::Text*[5];
    // for (short i = 0; i < 5; ++i)
    //     truthTBText[i] = new sf::Text[10];
    

    boolCells = new BoolCell*[numCol];
    for (short i = 0; i < numCol; ++i)
        boolCells[i] = new BoolCell[numRow];

    for (short i = 0; i < numCol; ++i)
    {
        static float x(pos.x), y(pos.y);
        for (short j = 0; j < numRow; ++j)
        {
            if (truthTBValue[j][i])
            {
                boolCells[i][j] = BoolCell({x, y}, boolCellSize, font, "1");
                y += (boolCellSize.y + 5); // 5 is outline thickness of cell
            }
            else
            {
                boolCells[i][j] = BoolCell({x, y}, boolCellSize, font, "0");
                y += (boolCellSize.y + 5); // 5 is outline thickness of cell
            }
        }
        y = pos.y;
        x += (boolCellSize.x + 5);
    }
    

}

TruthTable::~TruthTable()
{
}

TruthTable::TruthTable()
{
    std::string str_ = "AB";
    bool** truthTBVal_;
    exp = str_;
    truthTBValue = truthTBVal_;
    numCol = str_.size();
    numRow = pow(numCol, 2.0);
    // initStuff();
}

TruthTable::TruthTable(const std::string& str_, bool** entry_)
{
    exp = str_;
    truthTBValue = entry_;

    numCol = exp.size();
    numRow = pow(2.0, numCol);

}

void TruthTable::generateTruthTB()
{

}

void TruthTable::render(sf::RenderTarget* target_)
{
    for (short i = 0; i < numCol; ++i)
        for (short j = 0; j < numRow; ++j)
            boolCells[i][j].render(target_);
}

void TruthTable::setExp(int a)
{
    // exp = exp_;
    numCol = a;
    numRow = pow(numCol, 2.0);
}
void TruthTable::setTBVal(bool** entry_)
{
    truthTBValue = entry_;
}