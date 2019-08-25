#include "World.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"
#include <cmath>
#include <limits>
#include "Pickup.hpp"

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
	mTextures.load(Textures::Avenger, "Media/Textures/Avenger.png");
	mTextures.load(Textures::Desert, "Media/Textures/Desert.png");

	mTextures.load(Textures::Bullet, "Media/Textures/Bullet.png");
	mTextures.load(Textures::Missile, "Media/Textures/Missile.png");

	mTextures.load(Textures::HealthRefill, "Media/Textures/HealthRefill.png");
	mTextures.load(Textures::MissileRefill, "Media/Textures/MissileRefill.png");
	mTextures.load(Textures::FireSpread, "Media/Textures/FireSpread.png");
	mTextures.load(Textures::FireRate, "Media/Textures/FireRate.png");
    mFonts.load(Fonts::font1,"Media/Sansation.ttf");
}

void World::buildScene(){
    for( unsigned int i=0; i < LayerCount; ++i)
    {
        unsigned int c = Category::None;
        if(i == Air) c = Category::SceneAirLayer;

        SceneNode::Ptr Layer(new SceneNode(c));
        mSceneLayers[i] = Layer.get();

        mSceneGraph.attachChild(std::move(Layer));
    }

    sf::Texture& texture = mTextures.get(Textures::Desert);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture,textureRect));
    backgroundSprite->setPosition(mWorldBounds.left,mWorldBounds.top);
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

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
        //std::cout << getViewBounds().left << std::endl;

        SpawnPoint spawn = mSpawnPoints.back();
        std::unique_ptr<Aircraft> eSpawn( new Aircraft(spawn.type,mTextures,mFonts));
        eSpawn->setPosition(spawn.x,spawn.y);
        eSpawn->setRotation(-90.f);
        mSceneLayers[Air]->attachChild(std::move(eSpawn));
        mSpawnPoints.pop_back();
    }
}
void World::destroyEntitiesOutsideView()
{
	Command command;
	command.category = Category::Projectile | Category::EnemyAircraft;
	command.action = derivedAction<Entity>([this] (Entity& e, sf::Time)
	{
		if (!getBattlefieldBounds().intersects(e.getBoundingRect()))
			e.destroy();
	});

	mCommandQueue.push(command);
}
sf::FloatRect World::getBattlefieldBounds() const
{
	// Return view bounds + some area at top, where enemies spawn
	sf::FloatRect bounds = getViewBounds();
	bounds.top -= 100.f;
	bounds.height += 100.f;

	return bounds;
}

sf::FloatRect World::getViewBounds() const
{
	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}

void World::addEnemies(){
    for (int i = 0; i < 1000; i++)
    addEnemy(Aircraft::Raptor, i*1000 , 200);

    std::sort(mSpawnPoints.begin(),mSpawnPoints.end(), [] (SpawnPoint lhs, SpawnPoint rhs) {return lhs.x > rhs.x;});
}

void World::addEnemy(Aircraft::Type type, float x, float y){
    SpawnPoint p(type,x,y);
    mSpawnPoints.push_back(p);
}
void World::update(sf::Time dt){


	mPlayerAircraft->setVelocity(0.f, 0.f);
	destroyEntitiesOutsideView();
 guideMissiles();
                    int i = 0;

	// Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
	while (!mCommandQueue.isEmpty()){
            		mSceneGraph.onCommand(mCommandQueue.pop(), dt);

	}

		sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));

    mPlayerAircraft->accelerate(mScrollSpeed,0);
    mWorldView.move(mScrollSpeed *dt.asSeconds(),0);
    handleCollisions();

    mSceneGraph.removeWrecks();
     spawnEnemies();
	// Regular update step, adapt position (correct if outside view)
	mSceneGraph.update(dt,mCommandQueue);
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


void World::guideMissiles(){
Command enemyCollector;
enemyCollector.category = Category::EnemyAircraft;
enemyCollector.action = derivedAction<Aircraft>([this] (Aircraft& enemy, sf::Time) {
    if(!enemy.isDestroyed()){
}
    this->mActiveEnemies.push_back(&enemy);
});

Command missileGuider;
    missileGuider.category = Category::AlliedProjectile;
    missileGuider.action = derivedAction<Projectile>([this] (Projectile& miss, sf::Time){
        if(!miss.isGuided()) return;
        float minDistance = std::numeric_limits<float>::max();
        Aircraft* closestEnemy = nullptr;
        for(Aircraft* enemy : mActiveEnemies){

        float dis = miss.distance(*enemy,miss);

            if( dis < minDistance){
                closestEnemy = enemy;
                minDistance = dis;

                }
        }
                if(closestEnemy){

            miss.guideTowards(closestEnemy->getWorldPosition());
        }


    });
    mCommandQueue.push(enemyCollector);
    mCommandQueue.push(missileGuider);

    mActiveEnemies.clear();

}

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
	unsigned int category1 = colliders.first->getCategory();
	unsigned int category2 = colliders.second->getCategory();

	// Make sure first pair entry has category type1 and second has type2
	if (type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
}


void World::handleCollisions()
{
	std::set<SceneNode::Pair> collisionPairs;
	mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

	for(SceneNode::Pair pair : collisionPairs)
	{
		if (matchesCategories(pair, Category::PlayerAircraft, Category::EnemyAircraft))
		{
			auto& player = static_cast<Aircraft&>(*pair.first);
			auto& enemy = static_cast<Aircraft&>(*pair.second);

			// Collision: Player damage = enemy's remaining HP
			player.damage(enemy.getHitpoints());
			enemy.destroy();
		}

		else if (matchesCategories(pair, Category::PlayerAircraft, Category::Pickup))
		{
			auto& player = static_cast<Aircraft&>(*pair.first);
			auto& pickup = static_cast<Pickup&>(*pair.second);

			// Apply pickup effect to player, destroy projectile
			pickup.apply(player);
			pickup.destroy();
		}

		else if (matchesCategories(pair, Category::EnemyAircraft, Category::AlliedProjectile)
			  || matchesCategories(pair, Category::PlayerAircraft, Category::EnemyProjectile))
		{
			auto& aircraft = static_cast<Aircraft&>(*pair.first);
			auto& projectile = static_cast<Projectile&>(*pair.second);

			// Apply projectile damage to aircraft, destroy projectile
			aircraft.damage(projectile.getDamage());
			projectile.destroy();
		}
	}
}

