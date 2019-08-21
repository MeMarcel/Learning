
#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP

#include "SFML/Graphics.hpp"
#include "ResourceHolder.hpp"

namespace Fonts{
	enum ID
	{
	    font1,
	};
}

namespace Textures
{
	enum ID
	{
	    Avenger,
		Eagle,
		Raptor,
		Desert,
		TitleScreen,
		ButtonNormal,
		ButtonSelected,
		ButtonPressed,
	};
}



typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;


typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif
