#include "autumn.hpp"

namespace Autumn
{
	AutumnT create( int x, int y )
	{
		return
		{
			createSpriteGraphics( "autumn.png", x, y, 16, 25, 0, 0 )
		};
	};
}
