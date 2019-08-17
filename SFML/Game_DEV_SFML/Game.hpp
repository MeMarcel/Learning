#include "SFML/Graphics.hpp"
#include "World.hpp"
#include "Player.hpp"
#include "StateStack.hpp"
#include "FontHolder.hpp"

class Game
{
public:
    Game();
    void run();
    void update(sf::Time deltaTime);
    void render();
    void input();
    void updateStatistics(sf::Time time);

private:
    sf::RenderWindow mWindow;
    Player mPlayer;
        sf::Font                mFont;
        FontHolder				mFonts;
		sf::Text				mStatisticsText;
		sf::Time				mStatisticsUpdateTime;
		std::size_t				mStatisticsNumFrames;
		StateStack				mStateStack;
		TextureHolder			mTextures;
		void					registerStates();
};
