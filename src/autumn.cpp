#include "autumn.hpp"

#include <cstdio>

namespace Autumn
{
	static constexpr double ACCY = 0.25;
	static constexpr double GRAVITY = 4.0;

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

	void update( AutumnT& autumn )
	{
		printf( "%f\n", autumn.y );
		autumn.accy = ACCY;
		autumn.vy += autumn.accy;
		if ( autumn.vy > GRAVITY )
		{
			autumn.vy = GRAVITY;
		}
		autumn.y += autumn.vy;
		autumn.gfx.dest.y = ( int )( autumn.y );
	};
}
