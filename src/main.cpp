#include <cstdio>
#include "engine.hpp"
#include "game_state.hpp"
#include "input.hpp"
#include "render.hpp"

bool main_init();
void main_update();
void main_render();

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
	GameState::update();
	Input::update();
}

void main_render()
{
	Render::clearScreen();
	GameState::render();
	Render::present();
}
