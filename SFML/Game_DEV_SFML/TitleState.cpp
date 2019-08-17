#include "TitleState.hpp"
#include "StateIdentifiers.hpp"
#include "FontHolder.hpp"
TitleState::TitleState(StateStack& stack,Context c) : State(stack,c)

,mText()
,mShowText(1)
,mTextEffectTime(sf::Time::Zero)
{
    mBackgroundSprite.setTexture(c.textures->get(Textures::TitleScreen));
    mText.setFont(c.fonts->get(Fonts::font1));

    mText.setString("Press any key to start");
    mText.setColor(sf::Color::Red);
	mText.setPosition(c.window->getView().getSize() / 2.f);
}
void TitleState::draw(){
   sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);

	if (mShowText)
		window.draw(mText);
}
bool TitleState::update(sf::Time dt){
    mTextEffectTime +=dt;
    if(mTextEffectTime.asSeconds() > 0.25){
            mShowText = !mShowText;
        mTextEffectTime = sf::Time::Zero;
    }


    return true;}

bool TitleState::handleEvent(const sf::Event& event){
    if(sf::Event::KeyPressed == event.type){
        requestStackPop();
        requestStackPush(States::Menu);
    }
    return true;

}

