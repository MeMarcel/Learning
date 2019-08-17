#include "Game.hpp"
#include <string>
#include <sstream>
#include "StateIdentifiers.hpp"
#include "State.hpp"
#include "GameState.hpp"
#include "TitleState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"

template <typename T>
std::string ToString(T val) {
  std::stringstream stream;
  stream << val;
  return stream.str();
}

Game::Game() : mWindow(sf::VideoMode(1024, 720), "test", sf::Style::Close)
, mTextures()
, mFonts()
, mPlayer()
, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
{

    mWindow.setKeyRepeatEnabled(false);
    mFonts.load(Fonts::font1,"Media/Sansation.ttf");
    mStatisticsText.setFont(mFonts.get(Fonts::font1));
    mTextures.load(Textures::TitleScreen, "Media/Textures/TitleScreen.png");

     registerStates();

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
    mStateStack.draw();
    mStatisticsText.setPosition(mWindow.getView().getCenter().x,0);
    this->mWindow.draw(mStatisticsText);
    this->mWindow.display();
}

void Game::update(sf::Time delta){

    mStateStack.update(delta);
     if(mStateStack.isEmpty())
        this->mWindow.close();
}

void Game::input(){

    sf::Event event;

    while(this->mWindow.pollEvent(event)){

            mStateStack.handleEvent(event);
        if(event.type == sf::Event::Closed)
            this->mWindow.close();
    }


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

void Game::registerStates(){

	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<PauseState>(States::Pause);
	mStateStack.pushState(States::Title);
}
