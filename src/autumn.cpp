#include "autumn.hpp"

namespace Autumn
{
	static constexpr double ACCY = 0.25 / 16.0;
	static constexpr double GRAVITY = 4.0 / 16.0;

	static double height( const AutumnT& autumn );
	static double bottom( const AutumnT& autumn );

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

		if ( bottom( autumn ) > 224.0 )
		{
			autumn.y = 224.0 - height( autumn );
		}
	};

	static double height( const AutumnT& autumn )
	{
		return ( double )( autumn.gfx.dest.h );
	};

	static double bottom( const AutumnT& autumn )
	{
		return height( autumn ) + autumn.y;
	};
}
