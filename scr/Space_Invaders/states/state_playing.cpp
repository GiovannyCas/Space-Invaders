#include "state_playing.h"

#include <Game.h>
#include <ui/button.h>
#include <resourse/resources_holder.h>

#include "../Space_Invaders/display_info.h"

namespace space_invaders 
{
    State_Playing::State_Playing(Core::Game& game)
        : Core::State_Base(game, "Playing the game")
        , m_gameOverMenu(game.getWindow(), Display::HEIGHT / 3)
        , m_scoreDisplay(Display::WIDTH / 8, "Score")
        , m_highestScoreDisplay(Display::WIDTH / 2, "HighScore")
    {

        auto mmButton = std::make_unique<Core::UI::Button>();
        mmButton->setText("Main Menu\n");
        mmButton->setFunction([&]() { m_pGame->popState(); });

        auto submitBtn = std::make_unique<Core::UI::Button>();
        submitBtn->setText("Submit Score");
     // To DO: HighScore Board 

        auto exitButton = std::make_unique<Core::UI::Button>();
        exitButton->setText("Exit game\n");
        exitButton->setFunction([&]() { m_pGame->exitGame(); });

        m_gameOverMenu.setTitle("GAME  OVER");
        m_gameOverMenu.addWidget(std::move(mmButton));
        m_gameOverMenu.addWidget(std::move(submitBtn));
        m_gameOverMenu.addWidget(std::move(exitButton));

    
    }

    void State_Playing::handleEvent(sf::Event e)
    {
        if (m_isGameover) {
            m_gameOverMenu.handleEvent(e, m_pGame->getWindow());
        }
    }

    void State_Playing::handleInput()
    {
        m_world.input();
    }

    void State_Playing::update(sf::Time deltaTime)
    {
        if (!m_isGameover) {
            m_score += m_world.update(deltaTime.asSeconds());
            m_scoreDisplay.update(m_score);

            if (m_score > m_highestScoreDisplay.getCurrentScoreDisplayed()) {
                m_highestScoreDisplay.update(m_score);
            }
        }

        m_isGameover = m_world.isGameOver();
    }

    void State_Playing::render(sf::RenderTarget& renderer)
    {
        m_world.draw(renderer);

        m_lifeDisplay.draw(renderer, m_world.getPlayer().getLives());
        m_scoreDisplay.draw(renderer);
        m_highestScoreDisplay.draw(renderer);

        if (m_isGameover) {
            m_gameOverMenu.render(renderer);
        }
    }

    ///////////////////////////////////////////////
    //     display member functions       ///
    State_Playing::Life_Display::Life_Display()
    {
        m_lifeStamp.setSize({ Player::WIDTH / 2, Player::WIDTH / 2 });
        m_lifeStamp.setTexture(&Core::Resource_Holder::get().textures.get("si/player"));
        m_lifeStamp.setTextureRect({ 0, 0, 11, 8 });
        m_label.setPosition(Display::WIDTH - (Player::WIDTH * 5), 10);
        m_label.setString("LIVES");
        m_label.setOutlineThickness(0);
    }

    void State_Playing::Life_Display::draw(sf::RenderTarget& window, int lives)
    {
        float xOrigin = m_label.getPosition().x + m_label.getGlobalBounds().width + 10;
        float yOrigin = m_label.getPosition().y + m_label.getGlobalBounds().height / 2;

        window.draw(m_label);
        for (int i = 0; i < lives; i++) {
            m_lifeStamp.setPosition(xOrigin + i * Player::WIDTH / 2 + i * 10, yOrigin);
            window.draw(m_lifeStamp);
        }
    }

    State_Playing::Score_Display::Score_Display(float x, const std::string& text)
        : m_text(text)
        , m_centerPosition(x)
    {
        updateDisplay();
        m_label.setOutlineThickness(0);
    }

    void State_Playing::Score_Display::update(int newScore)
    {
        m_currentScore = newScore;
        updateDisplay();
    }

    void State_Playing::Score_Display::draw(sf::RenderTarget& target)
    {
        target.draw(m_label);
    }

    int State_Playing::Score_Display::getCurrentScoreDisplayed() const
    {
        return m_currentScore;
    }

    void State_Playing::Score_Display::updateDisplay()
    {
        m_label.setString(m_text + "   " + std::to_string(m_currentScore));
        m_label.setPosition(m_centerPosition - m_label.getGlobalBounds().width / 2, 15);
    }

}
