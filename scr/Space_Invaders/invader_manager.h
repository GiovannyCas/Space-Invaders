#pragma once

#include "animation_renderer.h"
#include "display_info.h"
#include "entity/invader.h"
#include "entity/projectile.h"

#include <SFML/Audio.hpp>
#include <vector>

#include <util/random.h>


namespace space_invaders
{
	class World;
	using CollisionResult = std::pair<int, std::vector<sf::Vector2f>>;

	class Invader_Manager
	{

	private:

		std::vector<Invader> m_invaders;
		sf::Clock m_stepTimer;
		sf::Time m_stepGap;

		World& m_world;

		Animation_Renderer m_invaderRenderer;
		unsigned m_aliveInvaders = 0;

		bool m_hasAllInvadersBeenAdded = false;

		bool m_isMovingLeft = false;
		bool m_moveDown = false;

		int m_initX = 0;
		int m_initY = 4;
		int m_ticks = 0;

		sf::Sound m_stepSounds[4];
		sf::Sound m_invaderKilledSound;

		// Changes time between the alien's steps based on number alive
		void updateStepDelay();

		// Checks the invaders position to see if all the aliens should move
		// down Or if the game is over
		bool testInvaderPosition(const Invader& invader) const;


	public:

		Invader_Manager(World& world);

		// Moves all of the invaders to the left or right, if the clock has
		// reached a certain time
		void tryStepInvaders();

		// Draws all of the alive invaders
		void drawInvaders(sf::RenderTarget& target);

		// Tries to collide the invaders with the projectiles
		// Returns the points of collision
		CollisionResult tryCollideWithProjectiles(std::vector<Projectile>& projectiles);

		// This is for firing projectiles from the enemy
		sf::Vector2f getRandomLowestInvaderPoint(Core::Random<>& random);

		int getAliveInvadersCount() const;

		/*
			These two functions are for the initilization of the invaders.
			It will add one invader at a time unil all have been added.
		*/
		void initAddInvader();
		bool areInvadersAlive() const;



	};
}
