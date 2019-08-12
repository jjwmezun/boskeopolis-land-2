#include "sprite_graphics.hpp"

SpriteGraphics createSpriteGraphics( const char* filename, int x, int y, int w, int h, int srcx, int srcy )
{
	return
	{
		Render::getTexture( filename ),
		{ srcx, srcy, w, h },
		{ x, y, w, h }
	};
};
