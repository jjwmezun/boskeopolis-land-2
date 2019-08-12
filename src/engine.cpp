#include "engine.hpp"
#include "input.hpp"
#include <SDL2/SDL.h>

Input::Type keycodes[ 284 ] { Input::Type::__NULL };

namespace Engine
{
    static SDL_Event event_;

    bool init()
    {
        if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0 )
    	{
    		SDL_Log( "Unable to initialize SDL: %s\n", SDL_GetError() );
    		return false;
        }
    	keycodes[ SDL_SCANCODE_Z ] = Input::Type::CONFIRM;
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
}
