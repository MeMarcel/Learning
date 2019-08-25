#include "Aircraft.hpp"
#include <assert.h>
#include "DataTables.hpp"
#include <string>
#include "Utility.hpp"
#include "Category.hpp"


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
    centerOrigin(mSprite);
    mFireRateLevel = 10;
    missileCount = 100;

    mFireCommand.category = Category::SceneAirLayer;
	mFireCommand.action   = [this, &textures] (SceneNode& node, sf::Time)
	{
	   // std::cout << (myType == Aircraft::Raptor);
		createBullets(node, textures);
		            //std::cout << "test";

	};

	mMissileCommand.category = Category::SceneAirLayer;
	mMissileCommand.action   = [this, &textures] (SceneNode& node, sf::Time)
	{
                createProjectile(node, Projectile::Missile, 0.f, 0.5f, textures);
            //createProjectile(node, Projectile::Missile, 0.f, 0.25f, textures);
        		//createProjectile(node, Projectile::Missile, 0.f, 0.f, textures);

	};

	if (getCategory() == Category::PlayerAircraft)
	{
		std::unique_ptr<TextNode> missileDisplay(new TextNode(mFonts, ""));
		missileDisplay->setPosition(0, 70);
		mMissileDisplay = missileDisplay.get();
		attachChild(std::move(missileDisplay));
	}

mFireCountdown = sf::Time::Zero;
}

 void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(this->mSprite,states);
}
    void Aircraft::collectMissiles(int missileCount){
        missileCount += missileCount;
    }



 void Aircraft::updateCurrent(sf::Time delta,CommandQueue& commands){

    checkProjectileLaunch(delta, commands);
    updateMovementPattern(delta);
    move(delta.asSeconds() * mVelocity);
    //setRotation(getRotation() +200 * delta.asSeconds());
    if(myType==Eagle){
    mHealthDisplay->setPosition(0,50);
    mHealthDisplay->setString(toString(getHitpoints() ) + "HP");
    mHealthDisplay->setRotation( -getRotation());
    mMissileDisplay->setString(toString(missileCount ) + "Rockets");
        mMissileDisplay->setRotation( -getRotation());
        mMissileDisplay->setPosition(-50,-50);

    }

    else {

       // std::cout << isAllied() << getCategory();
    }

 }

 void Aircraft::increaseFireSpread(int inc){
    this->mSpreadLevel += inc;
 }

  void Aircraft::increaseFireRate(int inc){
    this->mFireRateLevel += inc;
 }

unsigned int Aircraft::getCategory() const
{

    if(isAllied())
		return Category::PlayerAircraft;

	else{
        		return Category::EnemyAircraft;
        		std::cout << "EnemyAircraft";

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
        float vx = getMaxSpeed() * std::cos(radians);
        float vy = getMaxSpeed() * std::sin(radians);
        setVelocity(vx,vy);
        mDistanceToTravel += std::abs(getMaxSpeed() * dt.asSeconds());
    }
}
float Aircraft::getMaxSpeed() const
{
	return Table[myType].speed;
}
    void Aircraft::fire(){

        this->mIsFire = 1;}
    void Aircraft::launchMissile(){
        this->mIsLaunchMissile = 1;}

void Aircraft::checkProjectileLaunch(sf::Time dt, CommandQueue& commands){
    if(!isAllied()) mIsFire = 1;
    if( mIsFire  && mFireCountdown <= sf::Time::Zero ){
    //std::cout << mFireCommand.category << std::endl;
        commands.push(mFireCommand);
    mFireCountdown += sf::seconds(1.f / (mFireRateLevel + 1));
    mIsFire = false;
    }
    else if (mFireCountdown > sf::Time::Zero) {mFireCountdown -= dt;}

    if(mIsLaunchMissile && missileCount > 0){
        missileCount--;
        commands.push(mMissileCommand);
       // std::cout << "mIsLaunchMissile";

mIsLaunchMissile = false;
    }
}
bool Aircraft::isAllied () const{
    if(myType == Eagle) return true;
    return false;
}
void Aircraft::createBullets(SceneNode& node, const TextureHolder& textures)
{

	Projectile::Type type = isAllied() ? Projectile::AlliedBullet : Projectile::EnemyBullet;

	switch (mSpreadLevel)
	{
		case 1:
			createProjectile(node, type, 0.5, 0, textures);
			break;

		case 2:
			createProjectile(node, type, -0.33f, 0.33f, textures);
			createProjectile(node, type, +0.33f, 0.33f, textures);
			break;

		case 3:
			createProjectile(node, type, -0.5f, -0.33f, textures);
			createProjectile(node, type,  0.5f, 0.0f, textures);
			createProjectile(node, type, +0.5f, 0.33f, textures);
			break;
	}
}
void Aircraft::createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures)
{

    std::unique_ptr<Projectile> projectile(new Projectile(type, textures));

	sf::Vector2f offset(xOffset * mSprite.getGlobalBounds().width, yOffset * mSprite.getGlobalBounds().height);
	sf::Vector2f velocity( projectile->getMaxSpeed(),0);

	float sign = isAllied() ? 1.f : -1.f;
	projectile->setPosition(getWorldPosition() + offset * sign);
	projectile->setVelocity(velocity * sign);
	projectile->setRotation(90);
	node.attachChild(std::move(projectile));

}



sf::FloatRect Aircraft::getBoundingRect()
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}
