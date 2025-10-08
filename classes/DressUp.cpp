#include "DressUp.h"
#include "../imgui/imgui.h"

//This is all really just to ensure when we press the button to open the game something is showing. Not attached to anything that exists here yet, and it barely works anyways
DressUp::DressUp()
{
    _gridCloth = new Grid(4, 4);
    _gridDoll = new Grid(1, 4);
}

DressUp::~DressUp()
{
    delete _gridCloth;
    delete _gridDoll; 
}

void DressUp::setUpBoard()
{
    setNumberOfPlayers(1);
    _gameOptions.rowX = 4;
    _gameOptions.rowY = 4;

    // Hard define the doll square placements
    // x = horizontal offset
    // y = vertical offset
    // 

    for (int y = 0; y < getDollGrid()->getHeight() ; y++) {
        for (int x = 0; x < getDollGrid()->getWidth(); x++) {
            //Grid::initializeSquaresWithOffset(x, y, squareSize, spriteName);
        }
    }
    
    // hard define the cloth square placements
    _gridDoll->initializeSquares(260, "clothing_square.png");
    _gridCloth->initializeSquares(260, "clothing_square.png");

    // Set the offset of each grid

    startGame();
}


Player* DressUp::checkForWinner(){return nullptr;}

bool DressUp::checkForDraw(){return false;}

std::string DressUp::initialStateString(){return "0000000000";}

std::string DressUp::stateString(){
    std::string s = "0000000000";
    return s;
}

void DressUp::setStateString(const std::string &s){}

bool DressUp::actionForEmptyHolder(BitHolder &holder)
{
    //Will need to adapt for replacing an item the doll already is wearing
    if (holder.bit()) {
        return false;
    }
    Bit *bit = PieceForPlayer(getCurrentPlayer()->playerNumber() == 0 ? HUMAN_PLAYER : AI_PLAYER);
    if (bit) {
        bit->setPosition(holder.getPosition());
        holder.setBit(bit);
        endTurn();
        return true;
    }   
    return false;
}





bool DressUp::canBitMoveFrom(Bit &bit, BitHolder &src)
{
    // you will eventually be able to move clothing pieces
    return false;
}

bool DressUp::canBitMoveFromTo(Bit &bit, BitHolder &src, BitHolder &dst) {return false;}

void DressUp::stopGame()
{
    //can use as our "clear all" button?
    _gridCloth->forEachSquare([](ChessSquare* square, int x, int y) {
        square->destroyBit();
    });
        //can use as our "clear all" button?
    _gridDoll->forEachSquare([](ChessSquare* square, int x, int y) {
        square->destroyBit();
    });
}

void DressUp::updateAI() 
{
    
}

// Implemented in DressUp.h
//  GameHasAI()
//  GetDollGrid()
//  GetClothGrid()


void DressUp::drawFrame()
{
	scanForMouse();

	_gridDoll = DressUp::getDollGrid();
    _gridCloth = getClothGrid();

    ImVec2 dollGridPosition = ImVec2(50, 50);
    ImGui::SetCursorPos(dollGridPosition);

    _gridDoll->forEachEnabledSquare([](ChessSquare* square, int x, int y){
        square->paintSprite();
    });

    ImVec2 clothGridPosition = ImVec2(500, 50);
    ImGui::SetCursorPos(clothGridPosition);

    _gridCloth->forEachEnabledSquare([](ChessSquare* square, int x, int y){
        square->paintSprite();
    });

}



//This will need to be modified to be whichever clothing piece the player selects?
Bit* DressUp::PieceForPlayer(const int playerNumber)
{
    // depending on playerNumber load the "x.png" or the "o.png" graphic
    Bit *bit = new Bit();
    // should possibly be cached from player class?
    bit->LoadTextureFromFile(playerNumber == AI_PLAYER ? "o.png" : "x.png");
    bit->setOwner(getPlayerAt(playerNumber == AI_PLAYER ? 1 : 0));
    return bit;
}

Player* DressUp::ownerAt(int index ) const
{
    //i dunno if this is even necessary. theres only 1 player
    auto square = _gridCloth->getSquare(index % 3, index / 3);
    if (!square || !square->bit()) {
        return nullptr;
    }
    return square->bit()->getOwner();
}