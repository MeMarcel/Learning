#include "Game.hpp"
//finished
Game::Game() : mWindow(sf::VideoMode(1920,1080),"game") , world1(new World(mWindow))
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
            update(tick);
            pastTime = pastTime - tick;
        }
        render();
    }
}

void Game::render(){
    this->mWindow.clear();
    world1->draw();
    this->mWindow.display();
}

void Game::update(sf::Time delta){
world1->update(delta);
}

void Game::input(){

    sf::Event event;

    while(this->mWindow.pollEvent(event)){

        if(event.type == sf::Event::Closed)
            this->mWindow.close();
    }


}
