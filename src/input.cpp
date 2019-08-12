#include "input.hpp"

namespace Input
{
	static constexpr int MAX_INPUT_TYPES = ( int )( Type::__NULL );

	static bool held_[ MAX_INPUT_TYPES ] = { false };
	static bool pressed_[ MAX_INPUT_TYPES ] = { false };
	static bool released_since_reset_[ MAX_INPUT_TYPES ] = { true };

	bool isHeld( Type input )
	{
		return held_[ ( int )( input ) ];
	};

	bool isPressed( Type input )
	{
		return pressed_[ ( int )( input ) ];
	};

	void setHeld( Type input )
	{
		if ( input != Type::__NULL )
		{
			if ( !held_[ ( int )( input ) ] )
			{
				pressed_[ ( int )( input ) ] = true;
			}
			held_[ ( int )( input ) ] = released_since_reset_[ ( int )( input ) ];
		}
	};

	void setReleased( Type input )
	{
		if ( input != Type::__NULL )
		{
			held_[ ( int )( input ) ] = false;
			pressed_[ ( int )( input ) ] = false;
			released_since_reset_[ ( int )( input ) ] = true;
		}
	};

	void update()
	{
		for ( int i = 0; i < MAX_INPUT_TYPES; ++i )
		{
			pressed_[ i ] = false;
		}
	}

	void reset()
	{
		for ( int i = 0; i < MAX_INPUT_TYPES; ++i )
		{
			held_[ i ] = pressed_[ i ] = released_since_reset_[ i ] = false;
		}
	};
}
