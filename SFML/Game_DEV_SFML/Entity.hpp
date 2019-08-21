#include "SFML/Graphics.hpp"
#include "SceneNode.hpp"

class Entity : public SceneNode {
public:
    Entity(int hitpoints);
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
    void repair(int points);
    void damage(int points);
    void destroy();

    int getHitpoints() const;
    bool isDestroyed() const;
private:
    int mHitpoints;
protected:
    sf::Vector2f mVelocity;


};
