#pragma once

#include "../Core/state/State_Base.h"

namespace space_invaders {


	class state_main_menu : public Core::State_Base 
	{
	private:
		
	public:
		state_main_menu(Core::Game& game);

		void handleEvent(sf::Event e) override;
		void handleInput() override {};
		void update(sf::Time deltaTime) override;
		void render(sf::RenderTarget& renderer) override;

	};
}
