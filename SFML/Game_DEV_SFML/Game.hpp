#include "SFML/Graphics.hpp"

class Game
{
public:
    Game();
    void run();
    void update(float deltaTime);
    void render();
    void input();

private:
    sf::RenderWindow mWindow;
    sf::Sprite mPlayer;
};
