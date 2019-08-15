#include "SFML/Graphics.hpp"
#include "SceneNode.hpp"

class Entity : public SceneNode {
public:
    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float vx, float vy);
    sf::Vector2f getVelocity() const;
        void accelerate(sf::Vector2f speed){
        this->mVelocity += speed;
    }
        void accelerate(float vx, float vy){
        this->mVelocity.x += vx;
        this->mVelocity.y += vy;
    }
protected:
    sf::Vector2f mVelocity;


};
