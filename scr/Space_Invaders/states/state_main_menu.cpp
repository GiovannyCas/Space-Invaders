#include "state_main_menu.h"

#include "../Core/Game.h"

#include "../Core/ui/button.h"
#include "state_highscores.h"
#include "state_playing.h"
#include "../display_info.h"

namespace space_invaders {

	state_main_menu::state_main_menu(Core::Game& game)
		: Core::State_Base(game, "Main Menu", Display::WIDTH, Display::HEIGHT)
		, m_mainMenu(game.getWindow(), Display::HEIGHT / 2 - 100)
    {
        m_banner.setSize({ (float)Display::WIDTH, 200 });
        m_banner.setTexture(&Core::Resource_Holder::get().textures.get("si/logo"));

        auto playBtn = Core::UI::makeButton();
        playBtn->setText("Play game");
        playBtn->setFunction([&]() { m_pGame->pushState<State_Playing>(*m_pGame); });

        auto highscoresBtn = Core::UI::makeButton();
        highscoresBtn->setText("Highscores");
        highscoresBtn->setFunction(
            [&]() { m_pGame->pushState<State_Highscores>(*m_pGame); });

        auto exitBtn = Core::UI::makeButton();
        exitBtn->setText("Exit game");
        exitBtn->setFunction([&]() { m_pGame->popState(); });

        m_mainMenu.addWidget(std::move(playBtn));
        m_mainMenu.addWidget(std::move(highscoresBtn));
        m_mainMenu.addWidget(std::move(exitBtn));
        m_mainMenu.setTitle("Choose Action");
    }

    void state_main_menu::handleEvent(sf::Event ev)
    {
        m_mainMenu.handleEvent(ev, m_pGame->getWindow());
    }

    void state_main_menu::update(sf::Time deltaTime)
    {
       

    }

    void state_main_menu::render(sf::RenderTarget& renderer)
    {
       
        m_mainMenu.render(renderer);
        renderer.draw(m_banner);
    }


}
