#include <cstdio>
#include "engine.hpp"
#include "game_state.hpp"
#include "input.hpp"
#include "render.hpp"

static constexpr int MILLISECONDS_PER_SECOND = 1000;
static constexpr int FRAMERATE = 30;

static int ticks_;

bool main_init();
void main_update();
void main_render();
int startTicks();
void endTicks();

int main( int argc, char** argv )
{
	if ( !main_init() )
	{
		return -1;
	}
	while ( Engine::run() )
	{
		main_update();
		main_render();
	}
	Render::close();
	Engine::close();
	return 0;
}

bool main_init()
{
	if ( !Engine::init() )
	{
		printf( "¡Engine failed to initialize!\n" );
		return false;
	}

	if ( !Render::init() )
	{
		printf( "¡Renderer failed to initialize!\n" );
		return false;
	}
	GameState::init();
	return true;
}

void main_update()
{
	const int current_ticks = startTicks();
	GameState::update( current_ticks );
	Input::update();
	endTicks();
}

void main_render()
{
	Render::clearScreen();
	GameState::render();
	Render::present();
}

int startTicks()
{
	int current_ticks = Engine::getTicks() - ticks_;
	// Maintain 60 FPS
	/*while ( current_ticks < ( int )( MILLISECONDS_PER_SECOND / FRAMERATE ) )
	{
		current_ticks = Engine::getTicks() - ticks_;
	};*/
	return current_ticks;
}

void endTicks()
{
	ticks_ = Engine::getTicks();
}
