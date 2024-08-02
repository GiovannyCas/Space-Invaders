#pragma once



#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "resource_manager.h"

namespace Core
{
	class Resource_Holder
	{

	private:
		Resource_Holder();

	public:
		
		Resource_Manager<sf::Font> fonts;
		Resource_Manager<sf::Texture> textures;
		Resource_Manager<sf::SoundBuffer> soundBuffers;


		static Resource_Holder& get();

		
	};
}

