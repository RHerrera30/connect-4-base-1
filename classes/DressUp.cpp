#include "DressUp.h"
#include "../imgui/imgui.h"
#include <map>

std::map<int, std::string> clothes; // key: clothing_id, value: clothing_name

//This is all really just to ensure when we press the button to open the game something is showing. Not attached to anything that exists here yet, and it barely works anyways
DressUp::DressUp()
{
    _gridCloth = new Grid(3, 4);
    _gridDoll = new Grid(1, 4);

    clothes.insert({1, "head_clean"}); // that's what im looking for 
    clothes.insert({2, "head_yes"});
    clothes.insert({3, "head_no_complaints"});
    
    clothes.insert({4, "shirt_reg"});
    clothes.insert({5, "shirt_ugly"});
    clothes.insert({6, "shirt_cool"});
    
    clothes.insert({7, "pants_stained"});
    clothes.insert({8, "pants_bell_bottom"});
    clothes.insert({9, "pants_well_fitted"});

    clothes.insert({10, "shoes_yucky"});
    clothes.insert({11, "shoes_wretched"});
    clothes.insert({12, "shoes_sexy"});
    
}

DressUp::~DressUp()
{
    delete _gridCloth;
    delete _gridDoll; 
}

enum ClothingType {
    HAT,
    SHIRT,
    PANTS,
    SHOES
};

void DressUp::setUpBoard()
{
    setNumberOfPlayers(1);
    // _gameOptions.rowX = 4;
    // _gameOptions.rowY = 4;

    // Set the offset of each grid
    int offsetX = 0;
    int offsetY = 0;
    int spriteSize = 100;
    const char * spriteName = "square.png";
    _gridDoll->initializeSquaresWithOffset(offsetX, offsetY, spriteSize, spriteName);
    offsetX = (spriteSize * _gridDoll->getWidth()) + spriteSize; // offsets by the width of the doll board, plus one sprite width
    offsetY = 0; // we don't need to shift vertically here
    _gridCloth->initializeSquaresWithOffset(offsetX, offsetY, spriteSize, spriteName);


    //test adding bits to the clothing grid 
    for (int y = 0; y < _gridCloth->getHeight(); ++y) {
        for (int x = 0; x < _gridCloth->getWidth(); ++x) {
        // Example: create a Bit or ClothingPiece for each square
        Bit* bit = new Bit();
        
        // Optionally, set a unique texture for each bit for testing
        std::string folder = "dressup\\";
        std::string textureName = clothes.at(2);
        const char * texturePath = folder.append(textureName).append(".png").c_str();
        //const char * textureName = clothes.at((y * 3) + x).append("png").c_str();
        bit->LoadTextureFromFile(texturePath);
        ///TODO: set texture based on clothing type and some kind of index 

        bit->setPosition(_gridCloth->getSquare(x,y)->getPosition()); // <-- Sync positions
        _gridCloth->getSquare(x, y)->setBit(bit);
        }
    }


    startGame();
}


Player* DressUp::checkForWinner(){return nullptr;}

bool DressUp::checkForDraw(){return false;}

std::string DressUp::initialStateString(){return "0000 0000 0000 0000 0000";}

std::string DressUp::stateString(){
    std::string s = "0000 0000 0000 0000 0000";
    return s;
}

void DressUp::setStateString(const std::string &s){
    // first 4 bits will be the doll
    
    // other 16 bits will be the clothing spaces
}



bool DressUp::actionForEmptyHolder(BitHolder &holder)
{
    ImVec2 holderPosition = holder.getPosition();
    //printf("Clicked holder at position: (%f, %f)\n", holderPosition.x, holderPosition.y);
    //printf("Holder pointer: %p, Bit pointer: %p\n", &holder, holder.bit());
    
    std::cout << "Pos: " << "Clicked holder at position:" << holderPosition.x << holderPosition.y << std::endl;
    //Will need to adapt for replacing an item the doll already is wearing

    // based on the bit that is is the current/clicked holder we will then ask the 
    //bit what kind of clothing piece it is, and then load in the doll grid 
    //the apprpricate piece in the approrpiate position/slot 
    int x = static_cast<int>(holder.getPosition().x);
    int y = static_cast<int>(holder.getPosition().y);

    ChessSquare* square = _gridCloth->getSquare(x, y);
    Bit* clothingPiece = holder.bit();

    if (square) {
        clothingPiece = square->bit();
    }


    if (clothingPiece){
        std::cout << "Selected clothing piece:" << clothingPiece << std::endl;
        // set this clothing piece on the doll grid
        setOnDollGrid(clothingPiece);
        return true; 
    }

    std::cout << "No selected clothing piece:" << std::endl;
    return false;



}

bool DressUp::setOnDollGrid(Bit* clothingPiece)
{
    
    // find the correct column / index on the doll grid to place the selected clothing item on
    

    // if the doll grid already has an item there, redefine its contents. 
    // else, set a new bit and add it there
    _gridDoll->getSquare(0, 1)->setBit(clothingPiece);
    return true;
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
    ImGui::Dummy(ImVec2(260, 260));

    _gridDoll->forEachEnabledSquare([](ChessSquare* square, int x, int y){
        square->paintSprite();
    });

    _gridDoll->forEachEnabledSquare([](ChessSquare* square, int x, int y){
        if(square->bit()){
            square->bit()->paintSprite();
        }
    });

    ImVec2 clothGridPosition = ImVec2(500, 50);
    ImGui::SetCursorPos(clothGridPosition);
    ImGui::Dummy(ImVec2(260, 260));


    _gridCloth->forEachEnabledSquare([](ChessSquare* square, int x, int y){
        if(square->bit()){
            square->bit()->paintSprite();
        }
    });

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