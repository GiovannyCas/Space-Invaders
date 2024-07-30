#include "State_Base.h"

#include "../Game.h"


namespace Core {
	State_Base::State_Base(Game& game, const char* name)
		: m_pGame(&game)
		, m_name(name)
	{
	}

	State_Base::State_Base(Game& game, const char* name, unsigned int resizedWindowWidth, unsigned int resizedWindowHeight)
		: m_pGame(&game)
		, m_name(name)
	{
		m_pGame->resizedWindow(resizedWindowWidth, resizedWindowHeight);
	}
}