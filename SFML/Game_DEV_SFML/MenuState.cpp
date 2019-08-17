#include "MenuState.hpp"
#include "StateIdentifiers.hpp"
#include "FontHolder.hpp"


MenuState::MenuState(StateStack& stack, Context context) : State(stack,context) {
moptionIndex = 0;
sf::Text playOption, exitOption;
playOption.setFont(context.fonts->get(Fonts::font1));
exitOption.setFont(context.fonts->get(Fonts::font1));
exitOption.setString("Exit");
playOption.setString("Play");
playOption.setColor(sf::Color::Red);
playOption.setPosition(context.window->getView().getSize()/2.f);
exitOption.setPosition(context.window->getView().getSize().x/2.f , context.window->getView().getSize().y/2.f + 100);
mOptions.push_back(playOption);
mOptions.push_back(exitOption);
}



void MenuState::draw(){
     sf::RenderWindow& window = *getContext().window;
     for(sf::Text t : mOptions) {

        window.draw(t);
     }
}

bool MenuState::update(sf::Time dt){return true;}

bool MenuState::handleEvent(const sf::Event& e){

if(e.key.code == sf::Keyboard::Up){
         if(0 < moptionIndex){
    moptionIndex -=1;
   updateMenu();}
}
if(e.key.code == sf::Keyboard::Down){
    if(mOptions.size() - 1 > moptionIndex){
    moptionIndex +=1;
   updateMenu();}
}
if(e.key.code == sf::Keyboard::Return){
    if(moptionIndex == Play){
        requestStackPop();
        requestStackPush(States::Game);
    }
        if(moptionIndex == Exit){
        requestStackPop();

    }
}
return true;
}
    void MenuState::updateMenu(){

     for(sf::Text& t : this->mOptions) {

        t.setColor(sf::Color::White);
     }

     mOptions[moptionIndex].setColor(sf::Color::Red);

    }
