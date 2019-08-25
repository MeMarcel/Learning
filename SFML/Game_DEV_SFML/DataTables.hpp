#ifndef DATATABLE_HPP
#define DATATABLE_HPP
#include "SFML/Graphics.hpp"
#include "ResourceIdentifiers.hpp"
#include "Aircraft.hpp"
#include <vector>
#include "Projectile.hpp"
#include "Pickup.hpp"

struct Direction
{
	Direction(float angle, float distance)
	: angle(angle)
	, distance(distance)
	{
	}

	float angle;
	float distance;
};
struct AircraftData {
    int hitPoints;
    float speed;
    Textures::ID                    texture;
    sf::Time						fireInterval;
    //sf::IntRect						textureRect;
    //sf::Time						shieldInterval;
	std::vector<Direction>			directions;
    bool							hasRollAnimation;
};

struct ProjectileData {
    int damage;
    float speed;
    Textures::ID                    texture;

};

struct PickupData{
    std::function<void(Aircraft&)>	action;
    Textures::ID                    texture;
};

std::vector<ProjectileData> initializeProjectileData();
std::vector<AircraftData> initializeAircraftData();
std::vector<PickupData> initializePickupData();



#endif // DATATABLE_HPP
