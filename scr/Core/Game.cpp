#include "Game.h"


namespace Core {

	Game::Game() : m_window({ 1,1 }, "Arcade")
	{
		m_window.setPosition({ m_window.getPosition().x, 0 });
		m_window.setFramerateLimit(60);

	}

	void Game::Run()
	{
		constexpr unsigned TPS = 30;
		const sf::Time timePerUpdate = sf::seconds(1.0f / float(TPS));
		unsigned tick = 0;

		sf::Clock timer;
		auto lastTime = sf::Time::Zero;
		auto lag = sf::Time::Zero;

		// Main Loop of the Game 
		while (m_window.isOpen())
		{
			auto& state = getCurrentState();


			// Get times 
			auto time = timer.getElapsedTime();
			auto elapsed = time - lastTime;
			lastTime = time;
			lag += elapsed;

			// Update
			state.handleInput();
			state.update(elapsed);



			// Render
			m_window.clear();
			state.render(m_window);
			
			m_window.display();


			// Handle window events
			handleEvent();
			updateStates();
		}
	}

	void Game::handleEvent()
	{
		sf::Event ev;

		while (m_window.pollEvent(ev))
		{
			getCurrentState().handleEvent(ev);
			switch (ev.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;


			default:
				break;
			}
		}


	}

	void Game::updateStates()
	{

		switch (m_action.type) {
		case Action::Type::Push:
			m_states.push_back(std::move(m_action.state));
			m_action.type = Action::Type::None;
			break;

		case Action::Type::Pop:
			m_states.pop_back();
			if (!m_states.empty()) {
				getCurrentState().onOpen();
			}
			m_action.type = Action::Type::None;
			break;

		case Action::Type::Change:
			m_states.pop_back();
			m_states.push_back(std::move(m_action.state));
			m_action.type = Action::Type::None;
			break;

		case Action::Type::Quit:
			m_states.clear();
			break;

		default:
			break;
		}
	}

	void Game::pushState(std::unique_ptr<State_Base> state)
	{
		m_states.push_back(std::move(state));
		getCurrentState().onOpen();
	}

	void Game::popState()
	{
		// Flags a boolean for the game to pop state
		m_action.type = Action::Type::Pop;
	}

	void Game::exitGame()
	{
		m_action.type = Action::Type::Quit;
	}

	const sf::RenderWindow& Game::getWindow() const
	{
		return m_window;
	}

	void Game::resizedWindow(unsigned int width, unsigned int height)
	{
		m_window.close();
		m_window.create({ width, height }, "Arcade");
		m_window.setFramerateLimit(60);

	}


	State_Base& Game::getCurrentState()
	{
		// Returns a reference to the current game state
		return *m_states.back();
	}

}