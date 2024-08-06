#pragma once

#include <ui/stack_menu.h>
#include <ui/widget.h>
#include <state/State_Base.h>

namespace space_invaders {

	class State_Highscores : public Core::State_Base {

		using Entry = std::pair<std::string, int>;

		struct EntryBox {
		public:
			EntryBox(int position, const std::string& name, int score);

			void draw(sf::RenderTarget& renderer);

		private:
			sf::RectangleShape m_background;
			Core::UI::Widget::Text m_nameText;
			Core::UI::Widget::Text m_scoreText;
		};

		enum class State { Submitting, Viewing };


	private:

		Core::UI::stack_menu m_submitScoreMenu;
		Core::UI::stack_menu m_highscoreMenu;
		Core::UI::stack_menu* m_pActiveMenu;

		std::vector<Entry> m_scores;
		std::vector<EntryBox> m_entryBoxes;

		State m_state;

		std::string m_submitString;
		int m_scoreToSubmit = 0;

		sf::RectangleShape m_banner;

		void initViewMenu();
		void initSubmitMenu();

		void switchToViewMenu();
		void createHighscoreView();
		void loadScores();
		void writeScores();
		void sortScores();
		void submitScore();


	public:
		State_Highscores(Core::Game& game, int score);
		State_Highscores(Core::Game& game);

		void handleEvent(sf::Event e) override;
		void handleInput() override {};
		void update(sf::Time deltaTime) override;
		void render(sf::RenderTarget& renderer) override;

		static int getHighestScore();


	};
}

