#include "engine.hpp"
#include "input.hpp"
#include <SDL2/SDL.h>

namespace Engine
{
    static constexpr int MAX_KEY_CODES = 284;
    static Input::Type keycodes[ MAX_KEY_CODES ] { Input::Type::__NULL };
    static SDL_Event event_;

    void initKeycodes();

    bool init()
    {
        if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0 )
    	{
    		SDL_Log( "Unable to initialize SDL: %s\n", SDL_GetError() );
    		return false;
        }
        initKeycodes();
    	return true;
    }

    bool run()
    {
        while ( SDL_PollEvent( &event_ ) )
        {
            switch ( event_.type )
            {
                case ( SDL_QUIT ):
                {
                    return false;
                }
                break;

                case ( SDL_KEYDOWN ):
                {
    				if ( event_.key.keysym.scancode == SDL_SCANCODE_ESCAPE )
    				{
    					return false;
    				}
                    else
                    {
                        Input::setHeld( keycodes[ event_.key.keysym.scancode ] );
                    }
                }
                break;

                case ( SDL_KEYUP ):
                {
                    Input::setReleased( keycodes[ event_.key.keysym.scancode ] );
                }
                break;
            }
        }
        return true;
    }

    void close()
    {
        SDL_Quit();
    };

    int getTicks()
    {
    	return SDL_GetTicks();
    }

    void initKeycodes()
    {
        for ( int i = 0; i < MAX_KEY_CODES; ++i )
        {
            keycodes[ i ] = Input::Type::__NULL;
        }
    	keycodes[ SDL_SCANCODE_Z ] = Input::Type::CONFIRM;
    	keycodes[ SDL_SCANCODE_X ] = Input::Type::RUN;
    	keycodes[ SDL_SCANCODE_RIGHT ] = Input::Type::RIGHT;
        keycodes[ SDL_SCANCODE_LEFT ] = Input::Type::LEFT;
    }
}
