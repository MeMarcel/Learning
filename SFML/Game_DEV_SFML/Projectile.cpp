#include "Projectile.hpp"
#include "SFML/Graphics.hpp"
#include "Utility.hpp"
#include "ResourceIdentifiers.hpp"
#include "DataTables.hpp"

#include <cmath>
#include <cassert>


namespace P
{
	const std::vector<ProjectileData> Table = initializeProjectileData();
}

Projectile::Projectile(Type type, const TextureHolder& textures)
: Entity(1)
, mType(type)
, mSprite(textures.get(P::Table[type].texture))
, mTargetDirection()
{
	centerOrigin(mSprite);

}

void Projectile::guideTowards(sf::Vector2f position)
{


	assert(isGuided());
	mTargetDirection = unitVector(position - getTransform() * sf::Vector2f());
	//std::cout << "vectorDir:" << mTargetDirection.x << mTargetDirection.y << "postion:" << position.x << "y: "<< position.y << "actual postion:" << getWorldPosition().x << "y: " << getWorldPosition().y << std::endl;
}

bool Projectile::isGuided() const
{
	return mType == Missile;
}

void Projectile::updateCurrent(sf::Time dt, CommandQueue& commands)
{

if (isGuided())
	{
		const float approachRate = 700.f;

		sf::Vector2f newVelocity = unitVector(approachRate * dt.asSeconds() * mTargetDirection + getVelocity());
		newVelocity *= getMaxSpeed();
		float angle = std::atan2(newVelocity.y, newVelocity.x);

		setRotation(toDegree(angle) + 90.f);
		setVelocity(newVelocity);
	}

	Entity::updateCurrent(dt, commands);
	}



void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform = getTransform();
	target.draw(mSprite, states);
}

unsigned int Projectile::getCategory() const
{
	if (mType == EnemyBullet)
		return Category::EnemyProjectile;
	else
		return Category::AlliedProjectile;
}

sf::FloatRect Projectile::getBoundingRect ()
{
	return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

float Projectile::getMaxSpeed() const
{
	return P::Table[mType].speed;
}

int Projectile::getDamage() const
{
	return P::Table[mType].damage;
}
