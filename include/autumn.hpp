#pragma once

#include "sprite_graphics.hpp"

struct AutumnT
{
	SpriteGraphics gfx;
	double x;
	double accx;
	double vx;
	double y;
	double accy;
	double vy;
};

namespace Autumn
{
	AutumnT create( int x, int y );
	void update( int ticks, AutumnT& autumn );
}
