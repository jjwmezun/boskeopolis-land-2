#include "game_state.hpp"
#include "input.hpp"
#include "title_state.hpp"

namespace GameState
{
	Object current_state_;
	Object next_state_;

	void init()
	{
		current_state_ = TitleState::create();
	};

	void update( int ticks )
	{
		if ( next_state_.type != Type::__NULL )
		{
			current_state_ = next_state_;
			next_state_.type = Type::__NULL;
			Input::reset();
		}

		current_state_.update( ticks, current_state_.data );
	};

	void render()
	{
		current_state_.render( 0, current_state_.data );
	};

	void change( Object&& new_state )
	{
		next_state_ = new_state;
	};
}
