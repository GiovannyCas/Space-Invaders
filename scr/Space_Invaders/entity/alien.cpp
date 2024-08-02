#include "alien.h"

#include "../display_info.h"
#include <resourse/resources_holder.h>


namespace space_invaders {
    namespace {
        constexpr float WIDTH = 72;
        constexpr float HEIGHT = 36;
        constexpr float Y_POS = 45;
    } 

    Alien::Alien(Core::Random<>& rand)
        : Collidable(WIDTH, HEIGHT)
        , m_rng(rand)
        , m_animation(16, 8)
    {
        m_sprite.setSize({ WIDTH, HEIGHT });
        m_sprite.setPosition((float)Display::WIDTH, Y_POS);
        m_sprite.setTexture(&Core::Resource_Holder::get().textures.get("si/ufo"));

        for (int i = 0; i < 3; i++) {
            m_animation.addFrame(i, sf::seconds(0.2f));
        }
        m_flyingSound.setBuffer(
            Core::Resource_Holder::get().soundBuffers.get("si/ufo_lowpitch"));
        m_flyingSound.setVolume(15);
    }

    Alien::State Alien::getState() const
    {
        return m_state;
    }

    void Alien::update(float dt)
    {
        switch (m_state) 
        {
        case State::Destroyed:
            m_state = State::Waiting;
            break;

        case State::Flying:
            m_sprite.move(m_vx * dt, 0);
            if (getPosition().x <= -WIDTH ||getPosition().x >= Display::WIDTH + WIDTH)
            {
                m_state = State::Waiting;
            }
            if ((int)m_flyingSound.getStatus() != (int)sf::Sound::Status::Playing ||
                m_flyingSound.getPlayingOffset() >= sf::seconds(1.5))
            {
               // m_flyingSound.setPlayingOffset(sf::seconds(0.2f));
                m_flyingSound.play();
            }
            break;

        case State::Waiting:
            if (m_rng.getIntInRange(1, 250) == 100) {
                m_state = State::Flying;
                m_vx = (float)m_rng.getIntInRange(-1, 1) * 200.0f;
                float xPos;
                if (m_vx >= 0) {
                    xPos = -WIDTH;
                }
                else {
                    xPos = Display::WIDTH;
                }
                m_sprite.setPosition(xPos, Y_POS);
            }
            break;
        }
    }

    void Alien::draw(sf::RenderTarget& window)
    {
        if (m_state == State::Flying) {
            m_sprite.setTextureRect(m_animation.getFrame());
            window.draw(m_sprite);
        }
    }

    const sf::Vector2f& Alien::getPosition() const
    {
        return m_sprite.getPosition();
    }

    void Alien::onCollide([[maybe_unused]] Collidable& other)
    {
        m_state = State::Destroyed;
        m_sprite.setPosition(
            -1000,
            0); // Move offscreen so it cannot be collided with projectiles
    }
}