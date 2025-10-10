#include "ClothingPiece.h"

ClothingPiece::ClothingPiece(const std::string& iconSprite, const std::string& dollSprite)
    : _iconSprite(iconSprite), _dollSprite(dollSprite)
    {
        _sprite.LoadTextureFromFile(_iconSprite.c_str());
    };