#ifndef DATATABLE_HPP
#define DATATABLE_HPP
#include "SFML/Graphics.hpp"
#include "ResourceIdentifiers.hpp"
#include "Aircraft.hpp"
#include <vector>

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

std::vector<AircraftData> initializeAircraftData(){

	std::vector<AircraftData> data(Aircraft::TypeCount);

	data[Aircraft::Eagle].hitPoints = 100;
	data[Aircraft::Eagle].speed = 200.f;
	data[Aircraft::Eagle].fireInterval = sf::seconds(1);
	data[Aircraft::Eagle].texture = Textures::Eagle;

	data[Aircraft::Raptor].hitPoints = 20;
	data[Aircraft::Raptor].speed = -500.f;
	data[Aircraft::Raptor].texture = Textures::Raptor;
	data[Aircraft::Raptor].directions.push_back(Direction(-45.f,80.f));
	data[Aircraft::Raptor].directions.push_back(Direction(45.f , 160.f));
	data[Aircraft::Raptor].directions.push_back(Direction(-45.f, 80.f));
	data[Aircraft::Raptor].fireInterval = sf::Time::Zero;

	data[Aircraft::Avenger].hitPoints = 40;
	data[Aircraft::Avenger].speed = 50.f;
	data[Aircraft::Avenger].texture = Textures::Avenger;
	data[Aircraft::Avenger].directions.push_back(Direction(+50.f,  45.f));
	data[Aircraft::Avenger].directions.push_back(Direction(  45.f,  0.f));
	data[Aircraft::Avenger].directions.push_back(Direction(-45.f, 100.f));
	data[Aircraft::Avenger].directions.push_back(Direction(  50.f,  0.f));
	data[Aircraft::Avenger].directions.push_back(Direction(+50.f,  45.f));
	data[Aircraft::Avenger].fireInterval = sf::seconds(2);

return data;
}
#endif // DATATABLE_HPP
