#ifndef PICKUP_HPP
#define PICKUP_HPP
#include "Entity.hpp"
#include "Aircraft.hpp"
#include "DataTables.hpp"

class Pickup : public Entity
{
    public:
    enum Type
        {
            HealthRefill,
            MissileRefill,
            FireSpread,
            FireRate,
            TypeCount

        };
    public:
                                Pickup(Type type,
                                        const TextureHolder& textures);
    virtual  unsigned int   getCategory();
    virtual                     sf::FloatRect getBoundingRect() ;

    void                        apply(Aircraft& player) const;

    protected:
        virtual void             drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        Type                      mType;
        sf::Sprite                mSprite;

};


#endif // PICKUP_HPP
