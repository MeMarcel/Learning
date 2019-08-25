#include "Entity.hpp"
Entity::Entity(int hitpoints) : SceneNode(0),
 mHitpoints(hitpoints )
{
}
void Entity::setVelocity(sf::Vector2f velo)
{
    this->mVelocity = velo;
}

void Entity::setVelocity(float vx, float vy)
{
    this->mVelocity.x = vx;
    this->mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
    return mVelocity;
}

    void Entity::repair(int points){  mHitpoints += points;}
    void Entity::damage(int points){mHitpoints -= points;}
    void Entity::destroy(){mHitpoints = 0;}

    int Entity::getHitpoints() const {return this->mHitpoints;}
    bool Entity::isDestroyed() const { if(mHitpoints <= 0) return true;
    return false;}

void Entity::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	move(mVelocity * dt.asSeconds());
}
