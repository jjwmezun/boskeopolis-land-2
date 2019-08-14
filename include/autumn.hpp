#pragma once

#include "sprite_graphics.hpp"

struct AutumnT
{
	SpriteGraphics gfx;
};

namespace Autumn
{
	AutumnT create( int x, int y );
}
