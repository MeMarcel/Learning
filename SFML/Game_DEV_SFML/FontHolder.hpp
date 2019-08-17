#ifndef FONTHOLDER_HPP
#define FONTHOLDER_HPP

#include "SFML/Graphics.hpp"
#include "ResourceHolder.hpp"

namespace Fonts{
	enum ID
	{
	    font1,
	};
}




typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif
