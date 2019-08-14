#pragma once

#include "sprite_graphics.hpp"

namespace Autumn
{
	enum class JumpState
	{
		NOT_JUMPING,
		IS_JUMPING
	};
}

struct AutumnT
{
	SpriteGraphics gfx;
	double x;
	double accx;
	double vx;
	double y;
	double accy;
	double vy;
	Autumn::JumpState jump_state;
	int jump_timer;
};

namespace Autumn
{
	AutumnT create( int x, int y );
	void update( int ticks, AutumnT& autumn );
}
