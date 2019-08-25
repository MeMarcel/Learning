#include "SceneNode.hpp"
#include <algorithm>
#include <cmath>
#include "Utility.hpp"





typedef std::unique_ptr<SceneNode> Ptr;
SceneNode::SceneNode(unsigned int  c) : mCategory(c)
{
    this->mParent = nullptr;
}

bool collision( SceneNode& lhs,  SceneNode& rhs){
    return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}

void SceneNode::checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs){
    if(this != &node && collision(*this,node) && !node.isDestroyed())
        collisionPairs.insert(std::minmax(this,&node));
    for(Ptr& child : mChildren)
        child->checkNodeCollision(node,collisionPairs);

}
sf::FloatRect	SceneNode::getBoundingRect(){
    sf::FloatRect a;
return a;
}
void SceneNode::checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs){
checkNodeCollision(sceneGraph, collisionPairs);

	for(Ptr& child : sceneGraph.mChildren)
		checkSceneCollision(*child, collisionPairs);

}


void SceneNode::removeWrecks()
{
	// Remove all children which request so
	auto wreckfieldBegin = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
	mChildren.erase(wreckfieldBegin, mChildren.end());

	// Call function recursively for all remaining children
	std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::removeWrecks));
}



bool SceneNode::isMarkedForRemoval() const
{
	// By default, remove node if entity is destroyed
	return isDestroyed();
}

bool SceneNode::isDestroyed() const
{
	// By default, scene node needn't be removed
	return false;
}


void SceneNode::attachChild(Ptr child)
{

    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::SceneNode(){
    this->mParent = nullptr;
mCategory = 0;
}
Ptr SceneNode::detachChild(const SceneNode& node)
{
    auto found = std::find_if(mChildren.begin(),mChildren.end(), [&] (Ptr& p) -> bool {return p.get() == &node;});
    Ptr result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found);
    return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states )const
{

    states.transform *= getTransform();
    drawCurrent(target,states);
    for(const Ptr& child : mChildren)
        child->draw(target,states);
}

void SceneNode::update(sf::Time delta, CommandQueue& commands)
{
    updateCurrent(delta,commands);
    for(const Ptr& child: mChildren)
        child->update(delta,commands);
}

sf::Transform SceneNode::getWorldTransform()
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
		transform = node->getTransform() * transform;
    return transform;
}
sf::Vector2f SceneNode::getWorldPosition()
{
    return getWorldTransform() * sf::Vector2f();
}

unsigned int SceneNode::getCategory() const
{
    return mCategory;
}
float SceneNode::distance( SceneNode& lhs,  SceneNode& rhs){
return length(lhs.getWorldPosition() - rhs.getWorldPosition());
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
    if(command.category & getCategory()){
           //std::cout << (command.category == Category::PlayerAircraft) <<  getCategory() << std::endl;
            command.action(*this,dt);
               // std::cout << command.category << ":" << getCategory() << std::endl;
    }

    for(Ptr& child : mChildren)
        child->onCommand(command,dt);
}


