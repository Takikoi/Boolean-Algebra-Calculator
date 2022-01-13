#include "TruthTable.hpp"

void TruthTable::initBoolCell()
{
    float x_tmp(posTBOrigin.x);
    for (char& chr : exp)
    {
        std::string str(1, chr);
        inputSignalText.push_back(BoolCell({x_tmp, posTBOrigin.y}, boolCellSize, font, str));
        x_tmp += (boolCellSize.x + 5);
    } inputSignalText.push_back(BoolCell({x_tmp, posTBOrigin.y}, boolCellSize, font, "x"));

    boolValCells = new BoolCell*[numCol];
    for (short i = 0; i < numCol; ++i)
        boolValCells[i] = new BoolCell[numRow];

    float x(posTBVal.x), y(posTBVal.y);
    for (short i = 0; i < numCol; ++i)
    {
        for (short j = 0; j < numRow; ++j)
        {
            if (truthTBValue[j][i])
                boolValCells[i][j] = BoolCell({x, y}, boolCellSize, font, "1");
            else
                boolValCells[i][j] = BoolCell({x, y}, boolCellSize, font, "0");

            if (numCol >= 5 && j == 15) {
                y = posTBVal.y;
                x += (boolCellSize.x + 5) * 6 + gap;
            }
            else
                y += (boolCellSize.y + 5); // 5 is outline thickness of cell
        }
        y = posTBVal.y;
        if (numCol >= 5)
            x -= ((boolCellSize.x + 5) * 5 + gap);
        else 
            x += (boolCellSize.x + 5);
    }


    boolOutputCells = new BoolCell[numRow];
    float x_tmp1(posTBVal.x + numCol*(boolCellSize.x + 5)), y_tmp1(posTBVal.y);
    for (short j = 0; j < numRow; ++j)
    {
        if (truthTBOuput[j])
            boolOutputCells[j] = BoolCell({x_tmp1, y_tmp1}, boolCellSize, font, "1");
        else
            boolOutputCells[j] = BoolCell({x_tmp1, y_tmp1}, boolCellSize, font, "0");

        if (j == 15) {
            y_tmp1 = posTBVal.y;
            x_tmp1 += ((boolCellSize.x + 5) * (numCol + 1) + gap);
        }
        else y_tmp1 += (boolCellSize.y + 5); 
    }
}

void TruthTable::initVariables()
{
    posTBVal = sf::Vector2f(50.f, 100.f);
    posTBOrigin = sf::Vector2f(50.f, 50.f);
    boolCellSize = sf::Vector2f(45.f, 45.f);

    if (!font.loadFromFile("../fonts/Comfortaa-Medium.ttf"))
        std::cout << "Failed to load font\n";
}

TruthTable::~TruthTable()
{
}

TruthTable::TruthTable(const std::string& str_, bool** entry_, bool* output_)
    : exp(str_), truthTBValue(entry_), numCol(str_.size()), numRow(pow(2.0, numCol)), truthTBOuput(output_)
{
    initVariables();
    if (numCol <= 5)
        initBoolCell();
}

void TruthTable::render(sf::RenderTarget* target_)
{
    for (BoolCell& inpTxt : inputSignalText)
        inpTxt.render(target_);

    for (short i = 0; i < numCol; ++i)
        for (short j = 0; j < numRow; ++j)
            boolValCells[i][j].render(target_);

    for (short j = 0; j < numRow; ++j)
        boolOutputCells[j].render(target_);
}
