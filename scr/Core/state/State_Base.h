#pragma once

#include <SFML/Graphics.hpp>

namespace Core {
    class Game;

    class State_Base
    {
    protected:
        Game* m_pGame;
        std::string m_name;


    public:
        State_Base(Game& game, const char* name);

        State_Base(Game& game, const char* name, unsigned int resizedWindowWidth, unsigned int resizedWindowHeight);

        virtual ~State_Base() = default;

        virtual void onOpen()
        {

        }

        virtual void handleEvent([[maybe_unused]] sf::Event e)
        {
        }
        virtual void handleInput()
        {
        }
        virtual void update([[maybe_unused]] sf::Time deltaTime)
        {
        }
        virtual void fixedUpdate([[maybe_unused]] sf::Time deltaTime)
        {
        }
        virtual void render(sf::RenderTarget& renderer) = 0;

        const std::string& getName()
        {
            return m_name;
        }

    };

}