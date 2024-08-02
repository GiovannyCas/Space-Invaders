#pragma once

#include "../world.h"
#include <ui/stack_menu.h>
#include <state/State_Base.h>

namespace space_invaders
{

	class State_Playing : public Core::State_Base
	{
		/*
		
			 The main state; where all the gameplay happens
		
		*/

	private:
		World m_world;

		int m_score = 0;
		bool m_isGameover;
		sf::Clock m_gameOverClock;

		Core::UI::stack_menu m_gameOverMenu;

		// Displays how many lives the player has left
		class Life_Display {
		public:
			Life_Display();

			void draw(sf::RenderTarget& window, int lives);

		private:
			Core::UI::Widget::Text m_label;
			sf::RectangleShape m_lifeStamp;
		} m_lifeDisplay;

		// Displays the Player's current score
		class Score_Display {
		public:
			Score_Display(float centreX, const std::string& text);

			void update(int newScore);

			void draw(sf::RenderTarget& target);

			int getCurrentScoreDisplayed() const;

		private:
			void updateDisplay();

			Core::UI::Widget::Text m_label;
			std::string m_text;
			int m_currentScore;
			float m_centerPosition;
		} m_scoreDisplay, m_highestScoreDisplay;


	public:
		State_Playing(Core::Game& game);

		void handleEvent(sf::Event e) override;
		void handleInput() override;
		void update(sf::Time deltaTime) override;
		void render(sf::RenderTarget& renderer) override;
	};

}

