#ifndef TEXTNODE_HPP
#define TEXTNODE_HPP
#include "SceneNode.hpp"
#include "SFML/Graphics.hpp"
#include "ResourceIdentifiers.hpp"
#include <String>

class TextNode : public SceneNode{
public:
    TextNode(FontHolder& font, const std::string& string);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)const;
    void setString( const std::string& string);

    private:
        sf::Text        mText;



};

#endif // TEXTNODE_HPP
