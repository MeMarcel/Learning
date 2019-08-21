
#include "TextNode.hpp"
#include "ResourceIdentifiers.hpp"
#include "Utility.hpp"
TextNode::TextNode(FontHolder& font, const std::string& string) : SceneNode() , mText(){
    mText.setFont(font.get(Fonts::font1));
    setString(string);
}

 void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states)const {
    target.draw(mText,states);
 }


    void TextNode::setString(const std::string& string){
    mText.setString(string);
    centerOrigin(mText);

    }

