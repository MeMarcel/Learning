#include "Entity.hpp"
void Entity::setVeloctiy(sf::Vector2f velo)
{
    this->mVelocity = velo;
}

void Entity::setVeloctiy(float vx, float vy)
{
    this->mVelocity.x = vx;
    this->mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
    return mVelocity;
}
