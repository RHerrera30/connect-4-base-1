#pragma once
#include "Game.h"


class DressUp : public Game
{
    public:
    DressUp();
    ~DressUp();

    // set up the board
    void    setUpBoard() override;

    Player*     checkForWinner() override;
    bool        checkForDraw() override;
    std::string initialStateString() override;
    std::string stateString() override;
    void        setStateString(const std::string &s) override;
    bool        actionForEmptyHolder(BitHolder &holder) override;
    bool        canBitMoveFrom(Bit &bit, BitHolder &src) override;
    bool        canBitMoveFromTo(Bit &bit, BitHolder &src, BitHolder &dst) override;
    void        stopGame() override;

	void        updateAI() override;
    bool        gameHasAI() override { return true; }
    Grid*       getDollGrid() { return _gridDoll; }
    Grid*       getClothGrid() { return _gridCloth; }
    Grid*       getGrid() override { return _gridCloth;} // including to satisfy virtual override
    void        drawFrame() override; // we need to make our own custom version of draw frame to draw all the grids
private:
    Bit *       PieceForPlayer(const int playerNumber);
    Player*     ownerAt(int index ) const;
    // int         negamax(std::string& state, int depth, int playerColor)
    
    Grid*       _gridDoll;
    Grid*       _gridCloth;

    
};