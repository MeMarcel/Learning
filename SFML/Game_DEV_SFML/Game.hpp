#include "SFML/Graphics.hpp"
#include "World.hpp"
#include "Player.hpp"

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
    std::unique_ptr<World> mWorld;
        sf::Font				mFont;
		sf::Text				mStatisticsText;
		sf::Time				mStatisticsUpdateTime;
		std::size_t				mStatisticsNumFrames;
};
