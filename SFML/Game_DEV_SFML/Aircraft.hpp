#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include "Entity.hpp"
#include "RessourceTexture.hpp"

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

class Aircraft : public Entity{
public:
    enum Type{
    Eagle,
    Raptor,
    };
public:
    explicit Aircraft(Type type, TextureHolder& textures);
    virtual void drawCurrent(sf::RenderTarget& target , sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time delta);
     virtual  unsigned int getCategory() const;

private:
    Type myType;
    sf::Sprite mSprite;
};
#endif
