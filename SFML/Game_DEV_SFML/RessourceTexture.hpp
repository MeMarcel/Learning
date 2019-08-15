
#ifndef  RESSOURCETEXTURE_HPP
#define RESSOURCETEXTURE_HPP
#include "ResourceHolder.hpp"
#include <SFML/Graphics.hpp>

namespace Textures
{
	enum ID
	{
		Eagle,
		Raptor,
		Desert
	};
}



typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif
