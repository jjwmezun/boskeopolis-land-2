#pragma once

#include "sprite_graphics.hpp"

struct AutumnT
{
	SpriteGraphics gfx;
	double y;
	double accy;
	double vy;
};

namespace Autumn
{
	AutumnT create( int x, int y );
	void update( AutumnT& autumn );
}
