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
    Ptr detachChild(const SceneNode& node);
private:
    std::vector<Ptr> mChildren;
    SceneNode* mParent;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states )const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)const{}
    virtual void update(sf::Time delta);
    virtual void updateCurrent(sf::Time delta){}
    sf::Transform getWorldTransform() ;
    sf::Vector2f getWorldPosition() ;
};
