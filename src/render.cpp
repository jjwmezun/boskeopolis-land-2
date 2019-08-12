#include "render.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprite_graphics.hpp"

namespace Render
{
	static constexpr int MAX_TEXTURES = 127;
	static constexpr int MAX_LOCAL_FILENAME_LENGTH = 255;

	static char texture_names_[ MAX_TEXTURES ][ MAX_LOCAL_FILENAME_LENGTH ];
	static SDL_Texture* textures_[ MAX_TEXTURES ];
	static Texture number_of_textures_ = 0;
	static SDL_Window* window_ = nullptr;
	static SDL_Renderer* renderer_ = nullptr;
	static SDL_Rect screen_ = { 0, 0, 400, 224 };
	static char* base_path_;
	static uint_fast16_t max_filename_length_ = 0;

	static Texture loadTexture( const char* filename );
	static bool initWindow();
	static bool initRenderer();
	static void initBasePath();
	static void clearTextures();

	void drawSprite( const SpriteGraphics& sprite )
	{
		drawTexture( sprite.texture, sprite.src, sprite.dest );
	};

	void drawTexture( Texture texture, const Rect& src, const Rect& dest )
	{
		SDL_RenderCopy( renderer_, textures_[ texture ], &src, &dest );
	};

	void colorScreen( const Color& color )
	{
		SDL_SetRenderDrawColor( renderer_, color.r, color.g, color.b, color.a );
		SDL_RenderFillRect( renderer_, &screen_ );
	};

	void clearScreen()
	{
		SDL_SetRenderDrawColor( renderer_, 0, 0, 0, 255 );
		SDL_RenderClear( renderer_ );
	};

	void present()
	{
		SDL_RenderPresent( renderer_ );
	};

	Texture getTexture( const char* filename )
	{
		// Check if texture is loaded already.
		for ( int i = 0; i < number_of_textures_; ++i )
		{
			if ( strcmp( texture_names_[ i ], filename ) == 0 )
			{
				return i;
			}
		}
		// If not, load it.
		return loadTexture( filename );
	}

	static Texture loadTexture( const char* filename )
	{
		char* full_filename = ( char* )( calloc( max_filename_length_, sizeof( char ) ) );
		strcat( full_filename, base_path_ );
		strcat( full_filename, filename );
		SDL_RWops* rwop = SDL_RWFromFile( full_filename, "rb" );
		free( full_filename ); // No longer needed. Make sure we free it ’fore any return statements.
		if ( rwop == nullptr )
		{
			SDL_Log( "SDL_RWFromFile failed: %s", SDL_GetError() );
			return -1;
		}
		SDL_Surface* surface = IMG_LoadPNG_RW( rwop );
		SDL_RWclose( rwop );
		if ( surface == nullptr )
		{
			SDL_Log( "SDL_Surface failed: %s", SDL_GetError() );
			return -1;
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer_, surface );
		SDL_FreeSurface( surface );
		if ( texture == nullptr )
		{
			SDL_Log( "SDL_CreateTextureFromSurface failed: %s", SDL_GetError() );
			return -1;
		}
		textures_[ number_of_textures_ ] = texture;
		strcpy( texture_names_[ number_of_textures_ ], filename ); // Keep track o’ the local filename so we can reference it later.
		Texture texture_id = number_of_textures_; // Remember this one's ID before we increase the #.
		++number_of_textures_;
		return texture_id;
	};

	bool init()
	{
		const bool status = initWindow() && initRenderer();
		initBasePath();
		return status;
	}

	void close()
	{
		clearTextures();
		SDL_DestroyRenderer( renderer_ );
		SDL_DestroyWindow( window_ );
		SDL_free( base_path_ );
	};

	static bool initWindow()
	{
		window_ = SDL_CreateWindow
		(
			"Boskeopolis Land II",
	    	0,
			0,
			400,
			224,
			SDL_WINDOW_RESIZABLE
		);
		if ( window_ == nullptr )
		{
	        SDL_Log( "Could not create window: %s\n", SDL_GetError() );
	        return false;
		}
		return true;
	}

	static bool initRenderer()
	{
		renderer_ = SDL_CreateRenderer( window_, -1, SDL_RENDERER_TARGETTEXTURE );
		if ( window_ == nullptr )
		{
	        SDL_Log( "Could not create renderer: %s\n", SDL_GetError() );
	        return false;
		}
		return true;
	}

	static void initBasePath()
	{
		base_path_ = SDL_GetBasePath();
		char* temp_base_path_ = base_path_;
		while ( *temp_base_path_ )
		{
			++max_filename_length_;
			++temp_base_path_;
		}
		max_filename_length_ += MAX_LOCAL_FILENAME_LENGTH;
	}

	static void clearTextures()
	{
		for ( int i = 0; i < number_of_textures_; ++i )
		{
			SDL_DestroyTexture( textures_[ i ] );
		}
	};
}
