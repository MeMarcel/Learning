#include "Aircraft.hpp"
#include <assert.h>
#include "DataTables.hpp"
#include <string>
#include "Utility.hpp"


namespace
{
	const std::vector<AircraftData> Table = initializeAircraftData();
}
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


Aircraft::Aircraft(Type type, TextureHolder& textures,FontHolder& mFonts) : Entity(Table[type].hitPoints) , myType(type), mSprite(textures.get(Table[type].texture)) {
mSprite.setOrigin(mSprite.getLocalBounds().width / 2.f ,mSprite.getLocalBounds().height / 2.f ); //set sprite orgini to center
    if(myType == Eagle) setRotation(90);
    std::unique_ptr<TextNode> temp(new TextNode(mFonts,""));
    mHealthDisplay = temp.get();
    attachChild(std::move(temp));
    mDistanceToTravel = 0;
}

 void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(this->mSprite,states);
}

 void Aircraft::updateCurrent(sf::Time delta){

    updateMovementPattern(delta);
    move(delta.asSeconds() * mVelocity);
    //setRotation(getRotation() +200 * delta.asSeconds());
    if(myType==Eagle){
    mHealthDisplay->setPosition(0,50);
    mHealthDisplay->setString(toString(getHitpoints() ) + "HP");
    mHealthDisplay->setRotation( -getRotation());}

 }
   unsigned int Aircraft::getCategory() const{

        switch(myType){
    case Eagle:

        return Category::PlayerAircraft;
    default:
        return Category::EnemyAircraft;
        }
    }

void Aircraft::updateMovementPattern(sf::Time dt){

const std::vector<Direction>& directions = Table[myType].directions;
    if(!directions.empty()){
        float distanceToTravel = directions[mDirectionIndex].distance;
        if (mDistanceToTravel > distanceToTravel){
            mDirectionIndex = (mDirectionIndex + 1) % directions.size();
        mDistanceToTravel = 0.f;
        }
        float radians = toRadian(directions[mDirectionIndex].angle);
        std::cout << "angle:" << directions[mDirectionIndex].angle << std::endl;
        float vx = getMaxSpeed() * std::cos(radians);
        float vy = getMaxSpeed() * std::sin(radians);
        setVelocity(vx,vy);
        mDistanceToTravel += getMaxSpeed() * dt.asSeconds();
    }
}
float Aircraft::getMaxSpeed() const
{
	return Table[myType].speed;
}
