#pragma once

#include "level_state_data.hpp"
#include "title_state_data.hpp"

namespace GameState
{
	enum class Type
	{
		__NULL,
		TITLE,
		LEVEL
	};

	union Data
	{
		TitleState::Data title;
		LevelState::Data level;
	};

	typedef void ( *Function )( int, Data& );

	struct Object
	{
		Type type = Type::__NULL;
		Function update;
		Function render;
		Function init;
		Data data;
	};

	void init();
	void update( int ticks );
	void render();
	void change( Object&& new_state );
}
