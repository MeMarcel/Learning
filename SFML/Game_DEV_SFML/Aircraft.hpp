#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"
#include "TextNode.hpp"
#include "CommandQueue.hpp"
#include "Projectile.hpp"

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

class Aircraft : public Entity{
public:
    enum Type{
    Eagle,
    Raptor,
    Avenger,
    TypeCount
    };
public:
    explicit Aircraft(Type type, TextureHolder& textures, FontHolder& fonts);
    virtual void drawCurrent(sf::RenderTarget& target , sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time delta, CommandQueue& command);
     virtual  unsigned int getCategory() const;
     virtual sf::FloatRect getBoundingRect();
     void updateMovementPattern(sf::Time dt);
    float					getMaxSpeed() const;
    void fire();
    void launchMissile();
    void checkProjectileLaunch(sf::Time dt, CommandQueue& commands);
    void createBullets(SceneNode& node, const TextureHolder& textures) ;
    void createProjectile(SceneNode& node, Projectile::Type, float xOffset, float yOffset, const TextureHolder& textures) ;
    bool isAllied () const;
    void collectMissiles(int missileCount);
    void increaseFireSpread(int inc);
    void increaseFireRate(int inc);


private:
    TextNode* mMissileDisplay;
    int missileCount;
    Type myType;
    sf::Sprite mSprite;
    TextNode* mHealthDisplay;
    int mDirectionIndex = 0;
    float mDistanceToTravel = 0;
    bool mIsFire = false;
    bool mIsLaunchMissile = false;
    sf::Time mFireCountdown = sf::Time::Zero;
    Command mFireCommand;
    Command mMissileCommand;
    int mFireRateLevel = 3;
    int mSpreadLevel = 1;

};
#endif
