#include "autumn.hpp"

namespace Autumn
{
	static constexpr double ACCY = 0.25 / 16.0;
	static constexpr double GRAVITY = 4.0 / 16.0;

	AutumnT create( int x, int y )
	{
		return
		{
			createSpriteGraphics( "autumn.png", x, y, 16, 25, 0, 0 ),
			( double )( y ),
			0.0,
			0.0
		};
	};

	void update( int ticks, AutumnT& autumn )
	{
		autumn.accy = ACCY * ticks;
		autumn.vy += autumn.accy;
		if ( autumn.vy > GRAVITY )
		{
			autumn.vy = GRAVITY;
		}
		autumn.y += autumn.vy * ticks;
		autumn.gfx.dest.y = ( int )( autumn.y );
	};
}
