#pragma once

#include <functional>

#include "widget.h"


namespace Core
{
	namespace UI
	{
		enum class ButtonSize
		{
			Small,
			Wide,
		};

		class Button : public Widget 
		{

		private:

			sf::Vector2f m_position;
			Rectangle m_button;
			Text m_text;
			std::function<void(void)> m_function = []() {};
			bool m_isDisabled = false;

			void updateText();

		public:

			Button(ButtonSize s = ButtonSize::Wide);

			void setFunction(std::function<void(void)> function);

			void setText(const std::string& text);

			void setTexture(const sf::Texture& texture);

			void handleEvent(sf::Event ev, const sf::RenderWindow& window) override;

			void render(sf::RenderTarget& renderer) override;

			void setPosition(const sf::Vector2f& pos) override;

			sf::Vector2f getSize() const override;

			void disable() override;
			void enable() override;
		};

		inline std::unique_ptr<Button> makeButton()
		{
			return std::make_unique<Button>();
		}
	}
}


