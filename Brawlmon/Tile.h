#pragma once
#include "Actor.h"
class Tile :
    public Actor
{
public:
    Tile(std::string filename, float x, float y, int width, int height);
};