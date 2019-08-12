#pragma once

namespace Input
{
	enum class Type
	{
		CONFIRM,
		__NULL
	};

	bool isHeld( Type input );
	bool isPressed( Type input );
	void setHeld( Type input );
	void setReleased( Type input );
	void update();
	void reset();
}
