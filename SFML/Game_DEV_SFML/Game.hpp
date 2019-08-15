#include "SFML/Graphics.hpp"
#include "World.hpp"

class Game
{
public:
    Game();
    void run();
    void update(sf::Time deltaTime);
    void render();
    void input();

private:
    sf::RenderWindow mWindow;
    sf::Sprite mPlayer;
    std::unique_ptr<World> world1;
};
