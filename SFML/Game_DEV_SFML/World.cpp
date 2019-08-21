#include "World.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"

World::World(sf::RenderWindow& window) : mWindow(window)
                                        , mWorldView(window.getDefaultView())

, mWorldBounds(0.f, 0.f, 60000.f, 600)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, mScrollSpeed(250.f)
                                        , mPlayerAircraft(nullptr)
                                        {
                                            loadTextures();
                                            buildScene();


                                        }

void World::loadTextures(){

    mTextures.load(Textures::Eagle, "Media/Textures/Eagle.png");
    mTextures.load(Textures::Raptor, "Media/Textures/Raptor.png");
    mTextures.load(Textures::Desert, "Media/Textures/Desert.png");
    mFonts.load(Fonts::font1,"Media/Sansation.ttf");
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

    std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures,mFonts));
        mPlayerAircraft = leader.get();
        mPlayerAircraft->setPosition(mSpawnPosition);
        mPlayerAircraft->setVelocity(0.f, mScrollSpeed);
        mSceneLayers[Air]->attachChild(std::move(leader));

   /* std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, mTextures,mFonts));
        leftEscort->setPosition(-80.f,50.f);
        mPlayerAircraft->attachChild(std::move(leftEscort));

        std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, mTextures,mFonts));
        rightEscort->setPosition(80.f,50.f);
        mPlayerAircraft->attachChild(std::move(rightEscort));*/

        addEnemies();
}
void World::draw(){

    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}
void World::spawnEnemies(){

    while(!mSpawnPoints.empty() && mSpawnPoints.back().x < getViewBounds().left + getViewBounds().width){
        std::cout << getViewBounds().left << std::endl;

        SpawnPoint spawn = mSpawnPoints.back();
        std::unique_ptr<Aircraft> eSpawn( new Aircraft(spawn.type,mTextures,mFonts));
        eSpawn->setPosition(spawn.x,spawn.y);
        eSpawn->setRotation(-90.f);
        mSceneLayers[Air]->attachChild(std::move(eSpawn));
        mSpawnPoints.pop_back();
    }
}


sf::FloatRect World::getViewBounds() const
{
	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}

void World::addEnemies(){
    for (int i = 0; i < 100; i++)
    addEnemy(Aircraft::Raptor, i*1000 , 200);

    std::sort(mSpawnPoints.begin(),mSpawnPoints.end(), [] (SpawnPoint lhs, SpawnPoint rhs) {return lhs.x > rhs.x;});
}

void World::addEnemy(Aircraft::Type type, float x, float y){
    SpawnPoint p(type,x,y);
    mSpawnPoints.push_back(p);
}
void World::update(sf::Time dt){

    spawnEnemies();

	mPlayerAircraft->setVelocity(0.f, 0.f);

	// Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);

		sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));

    mPlayerAircraft->accelerate(mScrollSpeed,0);
    mWorldView.move(mScrollSpeed *dt.asSeconds(),0);


	// Regular update step, adapt position (correct if outside view)
	mSceneGraph.update(dt);
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());

	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerAircraft->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayerAircraft->setPosition(position);
    if(position.y < 0 || position.y > mWorldBounds.height) mScrollSpeed = -mScrollSpeed;

}

CommandQueue& World::getCommandQueue(){
    return mCommandQueue;
}
