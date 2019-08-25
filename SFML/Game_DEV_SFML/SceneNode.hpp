#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include "Category.hpp"

#include <vector>
#include <iostream>
#include <memory>
#include "SFML/Graphics.hpp"
#include "Command.hpp"
#include "CommandQueue.hpp"
#include <set>
#include <algorithm>
class CommandQueue;

struct Command;
class SceneNode : public sf::Transformable , public sf::Drawable, private sf::NonCopyable{
public:
    typedef std::unique_ptr<SceneNode> Ptr;
    typedef std::pair<SceneNode*, SceneNode*> Pair;
public:
    SceneNode();
    SceneNode(unsigned int c);
    void attachChild(Ptr child);

    Ptr detachChild(const SceneNode& node);
    virtual void update(sf::Time delta,CommandQueue& commands);
       std::vector<Ptr> mChildren;
    virtual unsigned int getCategory() const;
    void onCommand(const Command& command, sf::Time dt);
       sf::Transform getWorldTransform() ;
    sf::Vector2f getWorldPosition()  ;
        virtual sf::FloatRect	getBoundingRect();
        float distance( SceneNode& lhs,  SceneNode& rhs);
        void checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPair);
        void checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);

        		void					removeWrecks();
		virtual bool			isMarkedForRemoval() const;
		virtual bool			isDestroyed() const;


private:
    SceneNode* mParent;
    unsigned int  mCategory;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states )const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)const {  }

    virtual void updateCurrent(sf::Time delta,CommandQueue& commands){}


};
#endif
