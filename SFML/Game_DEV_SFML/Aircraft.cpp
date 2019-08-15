#include "Aircraft.hpp"
#include <assert.h>
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


Aircraft::Aircraft(Type type, TextureHolder& textures) : myType(type), mSprite(textures.get(toTextureID(type))) {
mSprite.setOrigin(mSprite.getLocalBounds().width / 2.f ,mSprite.getLocalBounds().height / 2.f ); //set sprite orgini to center
    if(myType == Eagle) setRotation(90);
}

 void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(this->mSprite,states);
}

 void Aircraft::updateCurrent(sf::Time delta){

    move(delta.asSeconds() * mVelocity);
    //setRotation(getRotation() +200 * delta.asSeconds());

 }
   unsigned int Aircraft::getCategory() const{

        switch(myType){
    case Eagle:

        return Category::PlayerAircraft;
    default:
        return Category::EnemyAircraft;
        }
    }
