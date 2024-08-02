#pragma once

#include <SFML/Graphics.hpp>


#include "animation_renderer.h"
#include "entity/explosion.h"
#include "entity/player.h"
#include "entity/alien.h"
#include "entity/projectile.h"
#include "entity/shield.h"
#include "invader_manager.h"

namespace space_invaders
{
	class World
	{
	private:

        Animation_Renderer m_projectileRenderer;
        Invader_Manager m_invaders;
        Player m_player;
        Alien m_alien;


        std::vector<Projectile> m_projectiles;
        std::vector<Explosion> m_explosions;
        std::vector<Shield> m_shields;

        sf::RectangleShape m_explodeShape;
        sf::Clock m_invaderShotClock;
        sf::Clock m_playerShotClock;
        sf::Clock m_animTimer;

       
        sf::Sound m_playerShoot;

        Core::Random<> m_rng;

        bool m_isGameOver = false;

        void updateProjectiles(float dt, std::vector<sf::Vector2f>& collisionPoints);
        void playerProjectileInput();
        void enemyProjectileFire();
        CollisionResult getCollisionResult(float dtt);

	public:
        World();

        void input();
        int update(float dt);
        void draw(sf::RenderTarget& target);

        const Player& getPlayer() const;

        bool isGameOver() const;

        void setGameIsOver()
        {
            m_isGameOver = true;
        }

        
	};
}


