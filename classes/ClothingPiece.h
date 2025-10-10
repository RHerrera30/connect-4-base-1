// extends bit to create pieces of clothing that go in clothing grid and have a seperate sprite for the doll grid
#pragma once 
#include "Bit.h"
#include <string>

class ClothingPiece : public Bit
{
    public:
    ClothingPiece(const std::string& iconSprite, const std:: string& dollSprite); //sprite visual, sprite for icon, 
    ~ClothingPiece();

    const std::string& getIconSprite() const { return _iconSprite; }
    const std::string& getDollSprite() const { return _dollSprite; }

    void setIconSprite(const std::string& sprite) { _iconSprite = sprite; }
    void setDollSprite(const std::string& sprite) { _dollSprite = sprite; }


    private: 
    Sprite _sprite;
    std::string _iconSprite; //sprite for clothing grid
    std::string _dollSprite; //sprite for doll grid

};