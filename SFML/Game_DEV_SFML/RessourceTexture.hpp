#include <SFML/Graphics.hpp>
#include "ResourceHolder.hpp"
namespace Textures{
    enum ID{
        Eagle,
        Raptor,
    };
}

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
