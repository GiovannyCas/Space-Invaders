#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "state/State_Base.h"


namespace Core {
	class Game
	{
		/*

			Main controlling class of the game.
			Handles state switches and the main loop, as well
			as counting the FPS
			*/

		struct Action {
			enum class Type {
				None,
				Push,
				Change,
				Pop,
				Quit,
			};
			Type type = Type::None;
			std::unique_ptr<State_Base> state;
		};

	private:

		sf::RenderWindow m_window;
		std::vector<std::unique_ptr<State_Base>> m_states;

		Action m_action;

		State_Base& getCurrentState();


		void handleEvent();
		void updateStates();


	public:

		Game();

		void Run();

		template<typename T>
		void initGame();

		void pushState(std::unique_ptr<State_Base> state);
		void popState();
		void exitGame();

		template <typename T, typename... Args>
		void pushState(Args&&... args);

		template <typename T, typename... Args>
		void changeState(Args&&... args);

		const sf::RenderWindow& getWindow() const;

		void resizedWindow(unsigned int width, unsigned int height);
	};


	template <typename T>
	inline void Game::initGame()
	{
		m_states.push_back(std::make_unique<T>(*this));
	}

	template <typename T, typename... Args>
	inline void Game::pushState(Args&&... args)
	{
		m_action.type = Action::Type::Push;
		m_action.state = std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T, typename... Args>
	inline void Game::changeState(Args&&... args)
	{
		m_action.type = Action::Type::Change;
		m_action.state = std::make_unique<T>(std::forward<Args>(args)...);
	}
}
