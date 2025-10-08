#include "DressUp.h"
//This is all really just to ensure when we press the button to open the game something is showing. Not attached to anything that exists here yet, and it barely works anyways
DressUp::DressUp()
{
    _grid = new Grid(2, 4);
}

DressUp::~DressUp()
{
    delete _grid;
}

void DressUp::setUpBoard()
{
    setNumberOfPlayers(2);
    _gameOptions.rowX = 2;
    _gameOptions.rowY = 4;
    _grid->initializeSquares(260, "square.png");

    // if (gameHasAI()) {
    //     setAIPlayer(AI_PLAYER);
    // }

    startGame();
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

bool DressUp::canBitMoveFromTo(Bit &bit, BitHolder &src, BitHolder &dst)
{
    // you will eventually be able to move clothing pieces
    return false;
}

void DressUp::stopGame()
{
    //can use as our "clear all" button?
    _grid->forEachSquare([](ChessSquare* square, int x, int y) {
        square->destroyBit();
    });
}

Player* DressUp::ownerAt(int index ) const
{
    //i dunno if this is even necessary. theres only 1 player
    auto square = _grid->getSquare(index % 3, index / 3);
    if (!square || !square->bit()) {
        return nullptr;
    }
    return square->bit()->getOwner();
}

Player* DressUp::checkForWinner()
{
    //also probably not needed. there's no win state
    static const int kWinningTriples[8][3] =  { {0,1,2}, {3,4,5}, {6,7,8},  // rows
                                                {0,3,6}, {1,4,7}, {2,5,8},  // cols
                                                {0,4,8}, {2,4,6} };         // diagonals
    for( int i=0; i<8; i++ ) {
        const int *triple = kWinningTriples[i];
        Player *player = ownerAt(triple[0]);
        if( player && player == ownerAt(triple[1]) && player == ownerAt(triple[2]) )
            return player;
    }
    return nullptr;
}

bool DressUp::checkForDraw()
{
    //don't need this either i think
    bool isDraw = true;
    // check to see if the board is full
    _grid->forEachSquare([&isDraw](ChessSquare* square, int x, int y) {
        if (!square->bit()) {
            isDraw = false;
        }
    });
    return isDraw;
}

std::string DressUp::initialStateString()
{
    //state string could be useful for that "randomize" idea?
    //I extended state string by one so that it doesn't go out of bounds trying to update
    return "0000000000";
}

std::string DressUp::stateString()
{
    std::string s = "0000000000";
    _grid->forEachSquare([&](ChessSquare* square, int x, int y) {
        Bit *bit = square->bit();
        if (bit) {
            s[y * 3 + x] = std::to_string(bit->getOwner()->playerNumber()+1)[0];
        }
    });
    return s;
}

void DressUp::setStateString(const std::string &s)
{
    _grid->forEachSquare([&](ChessSquare* square, int x, int y) {
        int index = y*3 + x;
        int playerNumber = s[index] - '0';
        if (playerNumber) {
            square->setBit( PieceForPlayer(playerNumber-1) );
        } else {
            square->setBit( nullptr );
        }
    });
}

void DressUp::updateAI() 
{
    //don't need ai
}



