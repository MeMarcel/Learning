#include "SceneNode.hpp"
#include <algorithm>

typedef std::unique_ptr<SceneNode> Ptr;
SceneNode::SceneNode()
{
    this->mParent = nullptr;
}

void SceneNode::attachChild(Ptr child)
{
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

Ptr SceneNode::detachChild(const SceneNode& node)
{
    auto found = std::find_if(mChildren.begin(),mChildren.end(), [&] (Ptr& p) -> bool {return p.get() == &node;});
    Ptr result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found);
    return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states )const{
    states.transform *= getTransform();
    drawCurrent(target,states);
    for(const Ptr& child : mChildren)
        child->draw(target,states);
}

void SceneNode::update(sf::Time delta){
    for(const Ptr& child: mChildren)
        child->update(delta);
}

    sf::Transform SceneNode::getWorldTransform() {
      sf::Transform resultTransform = sf::Transform::Identity;
        for(SceneNode *n  = this; n != nullptr; n = n->mParent )
            resultTransform = resultTransform * n->getTransform();
        return resultTransform;
    }
    sf::Vector2f SceneNode::getWorldPosition() {
        return getWorldTransform() * sf::Vector2f();
    }


