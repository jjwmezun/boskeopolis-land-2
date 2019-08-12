#pragma once

#include "render.hpp"

struct SpriteGraphics
{
	Texture texture;
	Rect src;
	Rect dest;
};

SpriteGraphics createSpriteGraphics( const char* filename, int x, int y, int w, int h, int srcx, int srcy );
