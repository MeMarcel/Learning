#include "World.hpp"
#include "RessourceTexture.hpp"
#include "ResourceHolder.hpp"

World::World(sf::RenderWindow& window) : mWindow(window)
                                        , mWorldView(window.getDefaultView())

, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, mScrollSpeed(-500.f)
                                        , mPlayerAircraft(nullptr)
                                        {
                                            loadTextures();
                                            buildScene();

                                            mWorldView.setCenter(mSpawnPosition);
                                        }

void World::loadTextures(){

    mTextures.load(Textures::Eagle, "Media/Textures/Eagle.png");
    mTextures.load(Textures::Raptor, "Media/Textures/Raptor.png");
    mTextures.load(Textures::Desert, "Media/Textures/Desert.png");
}

void World::buildScene(){
    for(int i=0; i < LayerCount; ++i)
    {
        SceneNode::Ptr Layer(new SceneNode());
        mSceneLayers[i] = Layer.get();

        mSceneGraph.attachChild(std::move(Layer));
    }

    sf::Texture& texture = mTextures.get(Textures::Desert);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture,textureRect));
    backgroundSprite->setPosition(mWorldBounds.left,mWorldBounds.top);
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite),1);

    std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
        mPlayerAircraft = leader.get();
        mPlayerAircraft->setPosition(mSpawnPosition);
        mPlayerAircraft->setVeloctiy(0.f, mScrollSpeed);
        mSceneLayers[Air]->attachChild(std::move(leader));

    std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, mTextures));
        leftEscort->setPosition(-80.f,50.f);
        mPlayerAircraft->attachChild(std::move(leftEscort));

        std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, mTextures));
        rightEscort->setPosition(80.f,50.f);
        mPlayerAircraft->attachChild(std::move(rightEscort));
}
void World::draw(){

    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);



}
void World::update(sf::Time dt){
    mWorldView.move(0.f, mScrollSpeed *  dt.asSeconds());
    sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	// If player touches borders, flip its X velocity
	if (position.y <= 0
	 || position.y >=  mWorldBounds.height - 150.f)
	{
		velocity.y = -velocity.y;
		mPlayerAircraft->setVeloctiy(velocity);
		mScrollSpeed = -mScrollSpeed;
	}
    mSceneGraph.update(dt);

}
