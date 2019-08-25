#include "SpriteNode.hpp"


    SpriteNode::SpriteNode(const sf::Texture& texture) : SceneNode(0) , mSprite(texture) {}
    SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rect) : SceneNode(0) , mSprite(texture,rect){}



 void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(this->mSprite,states);
}
