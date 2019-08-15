#include "Game.hpp"
#include <string>
#include <sstream>

template <typename T>
std::string ToString(T val) {
  std::stringstream stream;
  stream << val;
  return stream.str();
}

Game::Game() : mWindow(sf::VideoMode(1024,720),"game") , mWorld(new World(mWindow))
 {
    	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setFont(mFont);
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
         updateStatistics(pastTime);
        render();
    }
}

void Game::render(){
    this->mWindow.clear();
    mWorld->draw();
    mStatisticsText.setPosition(mWorld->getView().getCenter().x,0);
    this->mWindow.draw(mStatisticsText);
    this->mWindow.display();
}

void Game::update(sf::Time delta){
    mWorld->update(delta);
}

void Game::input(){

    CommandQueue& commands = mWorld->getCommandQueue();
    sf::Event event;

    while(this->mWindow.pollEvent(event)){

            mPlayer.handleEvent(event, commands);
        if(event.type == sf::Event::Closed)
            this->mWindow.close();
    }

    mPlayer.handleRealtimeInput(commands);
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + ToString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + ToString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}
