#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"
#include "TextNode.hpp"


typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

class Aircraft : public Entity{
public:
    enum Type{
    Eagle,
    Raptor,
    Avenger,
    TypeCount
    };
public:
    explicit Aircraft(Type type, TextureHolder& textures, FontHolder& fonts);
    virtual void drawCurrent(sf::RenderTarget& target , sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time delta);
     virtual  unsigned int getCategory() const;
     void updateMovementPattern(sf::Time dt);
    float					getMaxSpeed() const;

private:
    Type myType;
    sf::Sprite mSprite;
    TextNode* mHealthDisplay;
    int mDirectionIndex = 0;
    float mDistanceToTravel = 0;
};
#endif
