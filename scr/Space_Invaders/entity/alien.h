#pragma once

#include <util/animation.h>
#include <util/random.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../collidable.h"

namespace space_invaders {
	class Alien : public Collidable {
	public:
		enum class State { Waiting, Flying, Destroyed };

	private:
		Core::Random<>& m_rng;

		sf::RectangleShape m_sprite;
		float m_vx;
		State m_state;
		Core::Animation m_animation;

	

	public:


		Alien(Core::Random<>& rand);

		State getState() const;

		void update(float dt);

		void draw(sf::RenderTarget& window);

		const sf::Vector2f& getPosition() const;
		void onCollide(Collidable& other);
	sf::Sound m_flyingSound;

	};
}
