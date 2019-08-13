#include "Aircraft.hpp"

Textures::ID toTextureID(Aircraft::Type type)
{
    switch(type)
    {
    case Aircraft::Type::Eagle:
        return Textures::Eagle;
    case Aircraft::Type::Raptor:
        return Textures::Raptor;
    }
    assert(false);
}


Aircraft::Aircraft(Type type, const TextureHolder& textures) : myType(type), mSprite(textures.get(toTextureID(type))) {
mSprite.setOrigin(mSprite.getLocalBounds().width / 2.f ,mSprite.getLocalBounds().height / 2.f ); //set sprite orgini to center

}

 void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(this->mSprite);
}

 void Aircraft::updateCurrent(sf::Time delta){

 }
