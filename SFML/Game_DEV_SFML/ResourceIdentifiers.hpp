
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
        Eagle,
		Raptor,
		Avenger,
		Bullet,
		Missile,
		Desert,
		HealthRefill,
		MissileRefill,
		FireSpread,
		FireRate,
		TitleScreen,
		ButtonNormal,
		ButtonSelected,
		ButtonPressed
	};
}



typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;


typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif
