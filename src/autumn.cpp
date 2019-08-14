#include "autumn.hpp"
#include "input.hpp"

namespace Autumn
{
	static constexpr double WALK_SPEED = 0.25 / 16.0;
	static constexpr double WALK_TOP_SPEED = 2.0 / 16.0;
	static constexpr double RUNNING_SPEED = WALK_SPEED * 2.0;
	static constexpr double RUNNING_TOP_SPEED = WALK_TOP_SPEED * 2.0;
	static constexpr double FALL_ACC = 0.25 / 16.0;
	static constexpr double GRAVITY = 4.0 / 16.0;
	static constexpr double TRACTION = 1.0087733838994224; // 16√1.15 so that it’s 1.15 when 16 ticks ( 60FPS )
	static constexpr double JUMP_ACC = 1.0 / 16.0;
	static constexpr double JUMP_TOP_SPEED = 6.0 / 16.0;
	static constexpr int JUMP_LIMIT = 16 * 6;

	static double height( const AutumnT& autumn );
	static double bottom( const AutumnT& autumn );
	static bool onGround( const AutumnT& autumn );
	static void handleWalking( int ticks, AutumnT& autumn );
	static void handleFalling( int ticks, AutumnT& autumn );

	AutumnT create( int x, int y )
	{
		return
		{
			createSpriteGraphics( "autumn.png", x, y, 16, 25, 0, 0 ),
			( double )( x ),
			0.0,
			0.0,
			( double )( y ),
			0.0,
			0.0,
			JumpState::NOT_JUMPING,
			0
		};
	};

	void update( int ticks, AutumnT& autumn )
	{
		handleWalking( ticks, autumn );

		switch ( autumn.jump_state )
		{
			case ( JumpState::NOT_JUMPING ):
			{
				if ( Input::isPressed( Input::Type::CONFIRM ) && onGround( autumn ) )
				{
					autumn.jump_state = JumpState::IS_JUMPING;
					autumn.jump_timer = 0;
				}
				else
				{
					autumn.accy = FALL_ACC * ( double )( ticks );
				}
			}
			break;

			case ( JumpState::IS_JUMPING ):
			{
				if ( autumn.jump_timer >= JUMP_LIMIT || !Input::isHeld( Input::Type::CONFIRM ) )
				{
					autumn.jump_state = JumpState::NOT_JUMPING;
				}
				else
				{
					autumn.accy = -JUMP_ACC * ( double )( ticks );
					autumn.jump_timer += ticks;
				}
			}
			break;
		}

		handleFalling( ticks, autumn );
	};

	static void handleWalking( int ticks, AutumnT& autumn )
	{
		const bool is_running = Input::isHeld( Input::Type::RUN );
		const double acceleration = ( is_running ) ? RUNNING_SPEED : WALK_SPEED;
		const double top_speed = ( is_running ) ? RUNNING_TOP_SPEED : WALK_TOP_SPEED;
		if ( Input::isHeld( Input::Type::LEFT ) )
		{
			autumn.accx = -acceleration * ( double )( ticks );
		}
		else if ( Input::isHeld( Input::Type::RIGHT ) )
		{
			autumn.accx = acceleration * ( double )( ticks );
		}
		else
		{
			autumn.accx = 0.0;
		}
		autumn.vx += autumn.accx;
		if ( autumn.vx > top_speed )
		{
			autumn.vx = top_speed;
		}
		else if ( autumn.vx < -top_speed )
		{
			autumn.vx = -top_speed;
		}
		if ( autumn.accx == 0.0 && ticks > 0 )
		{
			autumn.vx /= pow( TRACTION, ticks );
		}
		autumn.x += autumn.vx * ( double )( ticks );
		autumn.gfx.dest.x = ( int )( autumn.x );
	}

	static void handleFalling( int ticks, AutumnT& autumn )
	{
		autumn.vy += autumn.accy;
		if ( autumn.vy > GRAVITY )
		{
			autumn.vy = GRAVITY;
		}
		else if ( autumn.vy < -JUMP_TOP_SPEED )
		{
			autumn.vy = -JUMP_TOP_SPEED;
		}
		autumn.y += autumn.vy * ( double )( ticks );
		if ( bottom( autumn ) > 224.0 )
		{
			autumn.y = 224.0 - height( autumn );
		}
		autumn.gfx.dest.y = ( int )( autumn.y );
	};

	static double height( const AutumnT& autumn )
	{
		return ( double )( autumn.gfx.dest.h );
	};

	static double bottom( const AutumnT& autumn )
	{
		return height( autumn ) + autumn.y;
	};

	static bool onGround( const AutumnT& autumn )
	{
		return bottom( autumn ) == 224.0;
	};
}
