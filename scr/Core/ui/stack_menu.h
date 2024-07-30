#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "widget.h"

namespace Core {

	namespace UI {
		/**
		 * @brief Class for a stack menu
		 * A stack menu is a menu where its widgets appear in a vertical stack
		 */
		class stack_menu
		{
		private:

			std::vector<std::unique_ptr<Widget>> m_widgets;
			sf::RectangleShape m_background;

			sf::Vector2f m_basePosition;
			sf::Vector2f m_baseSize;

			Widget::Text m_titleText;

			void initWidget(Widget& widget);

		public:
			stack_menu(const sf::RenderWindow& window, float baseY, int width = 300);
			stack_menu(const sf::Vector2f& postion, int width);

			stack_menu(stack_menu&& other);
			stack_menu& operator=(stack_menu&& other);

			~stack_menu() = default;

			Widget* addWidget(std::unique_ptr<Widget> w);

			void setTitle(const std::string& title);

			void handleEvent(sf::Event e, const sf::RenderWindow& window);
			void render(sf::RenderTarget& renderer);
		};
	}
}


