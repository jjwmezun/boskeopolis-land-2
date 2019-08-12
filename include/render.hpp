#pragma once

#include <SDL2/SDL.h>

typedef SDL_Color Color;
typedef int_fast8_t Texture;
typedef SDL_Rect Rect;

class SpriteGraphics;

namespace Render
{
	void drawSprite( const SpriteGraphics& sprite );
	void drawTexture( Texture texture, const Rect& src, const Rect& dest );
	void colorScreen( const Color& color );
	void clearScreen();
	void present();
	Texture getTexture( const char* filename );
	bool init();
	void close();
}
