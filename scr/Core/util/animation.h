#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace Core {
	class Animation {

	public:
		struct Frame {
			Frame(const sf::IntRect& bnds, sf::Time dly)
				: bounds(bnds)
				, delay(dly)
			{
			}

			sf::IntRect bounds; // The area in a texture of the frame
			sf::Time delay;     // Time delay to next frame
		};


	private:
		sf::Clock m_timer; // Timer for progressing the animation

		std::vector<Frame> m_frames; // List of animation frames

		unsigned m_framePointer = 0; // The index of the current active frame
		const unsigned FRAME_WIDTH;
		const unsigned FRAME_HEIGHT;


	public:
		
		Animation(unsigned frameWidth, unsigned frameHeight);

		void addFrame(unsigned index, sf::Time delay);

		const sf::IntRect& getFrame();


	};
}

