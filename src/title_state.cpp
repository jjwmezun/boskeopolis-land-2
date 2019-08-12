#include "input.hpp"
#include "level_state.hpp"
#include "render.hpp"
#include "title_state.hpp"

namespace TitleState
{
	void update( int, GameState::Data& data );
	void render( int, GameState::Data& data );
	void init( int, GameState::Data& data );

	GameState::Object create()
	{
		GameState::Data data;
		data.title = { 255, 0, 0, 255 };
		return
		{
			GameState::Type::TITLE,
			&update,
			&render,
			&init,
			data
		};
	};

	void update( int, GameState::Data& data )
	{
		if ( Input::isHeld( Input::Type::CONFIRM ) )
		{
			GameState::change( LevelState::create() );
		}
	};

	void render( int, GameState::Data& data )
	{
		Render::colorScreen( data.title.color );
	};

	void init( int, GameState::Data& data )
	{
	};
}
