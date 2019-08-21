#ifndef WORLD_HPP
#define WORLD_HPP

#include "Aircraft.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "Aircraft.hpp"
#include "CommandQueue.hpp"
#include <array>


class World : private sf::NonCopyable
{
public:
    explicit World(sf::RenderWindow& window);
    void update(sf::Time dt);
    void draw();
    CommandQueue& getCommandQueue();
    sf::View getView(){return mWorldView;}
    sf::FloatRect						getViewBounds() const;
private:
    void loadTextures();
    void buildScene();
    void                                spawnEnemies();
    void                                addEnemies();
    void                                addEnemy(Aircraft::Type type, float x, float y);

private:
    enum Layer
    {
        Background,
        Air,
        LayerCount
    };

		struct SpawnPoint
		{
			SpawnPoint(Aircraft::Type type, float x, float y)
			: type(type)
			, x(x)
			, y(y)
			{
			}

			Aircraft::Type type;
			float x;
			float y;
		};

private:

    std::vector<SpawnPoint>                      mSpawnPoints;
    CommandQueue                                mCommandQueue;
    sf::RenderWindow&                           mWindow;
    sf::View                                    mWorldView;
    TextureHolder                               mTextures;
    FontHolder                                  mFonts;

    SceneNode                                   mSceneGraph;
    std::array<SceneNode*, LayerCount>          mSceneLayers;

    sf::FloatRect                               mWorldBounds;
    sf::Vector2f                                mSpawnPosition;
    float                                       mScrollSpeed;
    Aircraft*                                   mPlayerAircraft;
};
#endif // WORLD_HPP
