#include "Entity.hpp"
#include "RessourceTexture.hpp"

class Aircraft : public Entity{
public:
    enum Type{
    Eagle,
    Raptor,
    };
public:
    explicit Aircraft(Type type, const TextureHolder& textures);
    virtual void drawCurrent(sf::RenderTarget& target , sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time delta);
private:
    Type myType;
    sf::Sprite mSprite;
};
