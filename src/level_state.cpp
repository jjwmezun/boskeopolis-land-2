#include "input.hpp"
#include "level_state.hpp"
#include "title_state.hpp"

namespace LevelState
{
	void update( int, GameState::Data& data );
	void render( int, GameState::Data& data );
	void init( int, GameState::Data& data );

	GameState::Object create()
	{
		GameState::Data data;
		data.level.color = { 0, 0, 255, 255 };
		data.level.autumn = Autumn::create( 32, 32 );
		return
		{
			GameState::Type::LEVEL,
			&update,
			&render,
			&init,
			data
		};
	};

	void update( int, GameState::Data& data )
	{
		auto& level = data.level;
		if ( Input::isHeld( Input::Type::CONFIRM ) )
		{
			GameState::change( TitleState::create() );
		}
		Autumn::update( level.autumn );
	};

	void render( int, GameState::Data& data )
	{
		const auto& level = data.level;
		Render::colorScreen( level.color );
		Render::drawSprite( level.autumn.gfx );
	};

	void init( int, GameState::Data& data )
	{
	};
}
