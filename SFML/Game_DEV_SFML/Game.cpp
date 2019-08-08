#include "Game.hpp"
//finished
Game::Game() : mWindow(sf::VideoMode(1024,720),"game")
 {

}

void Game::run()
{
    sf::Clock clock;
    sf::Time tick = sf::seconds(1.f / 60.f);

    sf::Time pastTime = sf::Time::Zero;

    while(this->mWindow.isOpen()){
        pastTime += clock.restart();
        while(pastTime > tick){
            input();
            update(tick.asSeconds());
            pastTime = pastTime - tick;
        }
        render();
    }
}

void Game::render(){
    this->mWindow.clear();
    this->mWindow.display();
}

void Game::update(float delta){

}

void Game::input(){

    sf::Event event;

    while(this->mWindow.pollEvent(event)){

        if(event.type == sf::Event::Closed)
            this->mWindow.close();
    }


}
