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
		data.level.autumn_gfx = createSpriteGraphics( "autumn.png", 32, 32, 16, 25, 0, 0 );
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
		const auto& level = data.level;
		if ( Input::isHeld( Input::Type::CONFIRM ) )
		{
			GameState::change( TitleState::create() );
		}
	};

	void render( int, GameState::Data& data )
	{
		const auto& level = data.level;
		Render::colorScreen( level.color );
		Render::drawSprite( level.autumn_gfx );
	};

	void init( int, GameState::Data& data )
	{
	};
}
