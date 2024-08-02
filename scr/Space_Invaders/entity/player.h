#pragma once

#include <SFML/Graphics.hpp>

#include <SFML/Audio.hpp>

#include "../collidable.h"

#include <util/animation.h>

namespace space_invaders
{
	class Player :public Collidable
	{
	private:

		sf::RectangleShape m_sprite;
		Core::Animation m_deathAnimation;
		sf::Vector2f m_velocity;
		sf::Clock m_deathTimer;

		bool m_isAlive = true;
		int m_livesLeft = 3;

		sf::Sound m_deathSound;

		void restart();

	public:

		constexpr static int WIDTH = 44;
		constexpr static int HEIGHT = 32;

		Player();

		void input();
		void update(float dt);
		void draw(sf::RenderTarget& target);

		// Gets the coordinates of the gun
		sf::Vector2f getGunPosition() const;

		const sf::Vector2f& getPosition() const;
		void onCollide(Collidable& other) override;

		int getLives() const;
		bool isAlive() const;

		void tryRevive();
	};
}


