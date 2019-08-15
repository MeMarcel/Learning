#include "SFML/Graphics.hpp"
#include "SceneNode.hpp"

class Entity : public SceneNode {
public:
    void setVeloctiy(sf::Vector2f velocity);
    void setVeloctiy(float vx, float vy);
    sf::Vector2f getVelocity() const;
protected:
    sf::Vector2f mVelocity;

};
