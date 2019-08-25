#include "Pickup.hpp"
#include "DataTables.hpp"

namespace
{
	const std::vector<PickupData> Table = initializePickupData();
}

Pickup::Pickup(Type type, const TextureHolder& textures) : Entity(1) , mType(type) , mSprite(textures.get(Table[mType].texture)) {


}
unsigned int   Pickup::getCategory(){
return Category::Pickup;
}

void Pickup::apply(Aircraft& player) const{
    Table[mType].action(player);
}

sf::FloatRect Pickup::getBoundingRect() {
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}


void Pickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(mSprite,states);
}


