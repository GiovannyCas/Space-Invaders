#include "state_highscores.h"

#include "../display_info.h"
#include <Game.h>
#include <ui/button.h>
#include <ui/textbox.h>

#include <fstream>
#include <iostream>
#include <sstream>

namespace space_invaders {
    namespace {
        const auto scoresPath = "res/SpaceInvaders/scores.txt";
    }

    State_Highscores::State_Highscores(Core::Game& game, int score)
        : State_Highscores(game)
    {
        initSubmitMenu();
        m_scoreToSubmit = score;
        m_pActiveMenu = &m_submitScoreMenu;
        m_state = State::Submitting;
    }

    State_Highscores::State_Highscores(Core::Game& game)
        : Core::State_Base(game, "Highscores")
        , m_submitScoreMenu(game.getWindow(), 100.0f)
        , m_highscoreMenu(game.getWindow(), Display::HEIGHT - 100.0f)
        , m_state(State::Viewing)
    {
        initViewMenu();
        m_pActiveMenu = &m_highscoreMenu;
        m_banner.setSize({ (float)Display::WIDTH, 200 });
        m_banner.setTexture(&Core::Resource_Holder::get().textures.get("si/highscores"));
        createHighscoreView();
    }

    void State_Highscores::handleEvent(sf::Event e)
    {
        m_pActiveMenu->handleEvent(e, m_pGame->getWindow());
    }

    void State_Highscores::update(sf::Time deltaTime)
    {
       
    }

    void State_Highscores::render(sf::RenderTarget& renderer)
    {
     
        m_pActiveMenu->render(renderer);
        if (m_state == State::Viewing) {
            for (auto& entry : m_entryBoxes) {
                entry.draw(renderer);
            }
            renderer.draw(m_banner);
        }
    }

    int State_Highscores::getHighestScore()
    {
        std::ifstream inFile(scoresPath);
        std::string buffer;

        std::getline(inFile, buffer, ',');
        std::getline(inFile, buffer, ',');
        if (buffer.empty())
            return 0;
        else
            return std::stoi(buffer);
    }

    void State_Highscores::initViewMenu()
    {
        loadScores();

        auto backBtn = Core::UI::makeButton();
        backBtn->setText("Main Menu");
        backBtn->setFunction([&]() { m_pGame->popState(); });
        m_highscoreMenu.addWidget(std::move(backBtn));
    }

    void State_Highscores::initSubmitMenu()
    {
        auto nameTextBox = Core::UI::makeTextBox(m_submitString);
        nameTextBox->setLabel("Click text box to enter name");

        auto submitBtn = Core::UI::makeButton();
        submitBtn->setText("Submit Score");
        submitBtn->setFunction([&]() {
            if (!m_submitString.empty()) {
                submitScore();
                switchToViewMenu();
            }
            });

        auto backBtn = Core::UI::makeButton();
        backBtn->setText("View HighScores");
        backBtn->setFunction([&]() {
            loadScores();
            switchToViewMenu();
            });

        m_submitScoreMenu.addWidget(std::move(nameTextBox));
        m_submitScoreMenu.addWidget(std::move(submitBtn));
        m_submitScoreMenu.addWidget(std::move(backBtn));
    }

    void State_Highscores::switchToViewMenu()
    {
        m_state = State::Viewing;
        m_pActiveMenu = &m_highscoreMenu;
        createHighscoreView();
    }

    void State_Highscores::createHighscoreView()
    {
        loadScores();
        sortScores();
        m_entryBoxes.clear();
        for (unsigned i = 0; i < m_scores.size(); i++) {
            auto& name = m_scores[i].first;
            auto score = m_scores[i].second;

            m_entryBoxes.emplace_back(i + 1, name, score);
            if (i >= 9)
                return; // Only show top 10 scores
        }
    }

    void State_Highscores::loadScores()
    {
        m_scores.clear();
        std::ifstream inFile(scoresPath);
        std::string line;
        int switcher = 0;
        std::string name;
        int score;
        while (std::getline(inFile, line, ',')) {
            if (switcher++ % 2 == 0) {
                name = line;
            }
            else {
                score = std::stoi(line);
                m_scores.emplace_back(std::make_pair(name, score));
            }
        }
        sortScores();
    }

    void State_Highscores::writeScores()
    {
        sortScores();
        std::ofstream outFile(scoresPath);
        for (auto& entry : m_scores) {
            outFile << entry.first << "," << entry.second << ",";
        }
    }

    void State_Highscores::sortScores()
    {
        std::sort(m_scores.begin(), m_scores.end(),
            [](Entry& a, Entry& b) { return a.second > b.second; });
    }

    void State_Highscores::submitScore()
    {
        loadScores();
        m_scores.emplace_back(std::make_pair(m_submitString, m_scoreToSubmit));
        writeScores();
    }

    State_Highscores::EntryBox::EntryBox(int position, const std::string& name, int score)
    {
        float size = 35;
        float y = 200 + position * (size - 2);
        m_background.setSize({ Display::WIDTH / 1.5f, size });
        m_background.setPosition(
            { Display::WIDTH / 2 - m_background.getGlobalBounds().width / 2, y });

        m_nameText.setCharacterSize((unsigned)size - 5);
        m_scoreText.setCharacterSize((unsigned)size - 5);

        m_nameText.setString(std::to_string(position) + "     " + name);
        m_scoreText.setString(std::to_string(score));

        m_nameText.setPosition(m_background.getPosition());
        m_scoreText.setPosition(m_background.getPosition().x +
            m_background.getGlobalBounds().width -
            m_scoreText.getGlobalBounds().width - 10,
            y);

        m_background.setOutlineThickness(2);
        m_background.setOutlineColor(sf::Color::Green);
        m_background.setFillColor(position % 2 == 0 ? sf::Color::Black
            : sf::Color{ 50, 40, 50 });
    }

    void State_Highscores::EntryBox::draw(sf::RenderTarget& renderer)
    {
        renderer.draw(m_background);
        renderer.draw(m_nameText);
        renderer.draw(m_scoreText);
    }
}