#include "widget.h"


namespace Core
{
	namespace UI
	{

		// Text
		Widget::Text::Text()
		{
			setCharacterSize(25);
			setOutlineColor(sf::Color::Black);
			setFillColor(sf::Color::White);
			
		}

		bool Widget::Rectangle::isRolledOn(const sf::RenderWindow& window) const
		{
			auto pos = sf::Mouse::getPosition(window);
			return getGlobalBounds().contains((float)pos.x, (float)pos.y);

		}

		bool Widget::Rectangle::isClicked(sf::Event ev, const sf::RenderWindow& window)
		{
			if (isRolledOn(window))
			{
				if (ev.type == sf::Event::MouseButtonPressed)
				{
					return ev.mouseButton.button == sf::Mouse::Left;
				}
			}
			return false;
		}
	}
}