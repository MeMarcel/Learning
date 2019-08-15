#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <vector>
#include <iostream>
#include <memory>
#include "SFML/Graphics.hpp"
class SceneNode : public sf::Transformable , public sf::Drawable, private sf::NonCopyable{
public:
    typedef std::unique_ptr<SceneNode> Ptr;
public:
    SceneNode();
    void attachChild(Ptr child);
        void attachChild(Ptr child,int i);

    Ptr detachChild(const SceneNode& node);
    virtual void update(sf::Time delta);
       std::vector<Ptr> mChildren;
private:
    int i = 0;
    SceneNode* mParent;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states )const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)const {  }

    virtual void updateCurrent(sf::Time delta){}
    sf::Transform getWorldTransform() ;
    sf::Vector2f getWorldPosition() ;
};
#endif
