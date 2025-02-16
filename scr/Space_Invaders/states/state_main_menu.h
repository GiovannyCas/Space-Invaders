#pragma once


#include "../Core/ui/stack_menu.h"
#include "../Core/state/State_Base.h"


namespace space_invaders {


	class state_main_menu : public Core::State_Base 
	{
	private:
		Core::UI::stack_menu m_mainMenu;
		sf::RectangleShape m_banner;



	public:
		state_main_menu(Core::Game& game);

		void handleEvent(sf::Event ev) override;
		void handleInput() override {};
		void update(sf::Time deltaTime) override;
		void render(sf::RenderTarget& renderer) override;

	};
}
