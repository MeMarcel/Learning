#include "MenuState.hpp"
#include "Button.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


template <typename width, typename heigh>
    struct Size{
        width x;
        heigh y;

    };
MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, mGui(*context.window)
{
    auto theme = tgui::Theme::create("Black.txt");
    auto windowWidth = tgui::bindWidth(mGui);
    auto windowHeight = tgui::bindHeight(mGui);
    tgui::Button::Ptr playButton = theme->load("Button");
    Size<tgui::Layout,tgui::Layout> size;
    size.x = windowWidth;
    size.y = windowHeight / 8;

    playButton->setSize(windowWidth / 6, windowHeight / 8);
    playButton->setPosition(windowWidth / 2 - windowWidth / 12, windowHeight /2 - 2* (size.y + 30));
    playButton->setText("New Game");
    mGui.add(playButton);
    playButton->connect("pressed", [this] ()
	{

		requestStackPop();
        requestStackPush(States::Game);

	});

	    tgui::Button::Ptr loadButton = theme->load("Button");
    loadButton->setSize(windowWidth / 6, windowHeight / 8);
    loadButton->setPosition(windowWidth / 2 +  - windowWidth / 12, windowHeight /2 - (size.y + 30) );
    loadButton->setText("Load Game");
    mGui.add(loadButton);
    loadButton->connect("pressed", [this] ()
	{

		requestStackPop();
        requestStackPush(States::Game);

	});

		    tgui::Button::Ptr multiplayerButton = theme->load("Button");
    multiplayerButton->setSize(windowWidth / 6, windowHeight / 8);
    multiplayerButton->setPosition(windowWidth / 2 +  - windowWidth / 12, windowHeight /2  );
    multiplayerButton->setText("Multiplayer");
    mGui.add(multiplayerButton);
    multiplayerButton->connect("pressed", [this] ()
	{

		requestStackPop();
        requestStackPush(States::Game);

	});

			    tgui::Button::Ptr settingsButton = theme->load("Button");
    settingsButton->setSize(windowWidth / 6, windowHeight / 8);
    settingsButton->setPosition(windowWidth / 2 +  - windowWidth / 12, windowHeight /2  + (size.y + 30)  );
    settingsButton->setText("Settings");
    mGui.add(settingsButton);
    settingsButton->connect("pressed", [this] ()
	{

		requestStackPop();
        requestStackPush(States::Game);

	});

				    tgui::Button::Ptr exitButton = theme->load("Button");
    exitButton->setSize(windowWidth / 6, windowHeight / 8);
    exitButton->setPosition(windowWidth / 2 +  - windowWidth / 12, windowHeight /2 + 2*(size.y + 30)  );
    exitButton->setText("Exit");
    mGui.add(exitButton);
    exitButton->connect("pressed", [this] ()
	{

		requestStackPop();


	});


	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	mBackgroundSprite.setTexture(texture);





}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	        mGui.draw();
}

bool MenuState::update(sf::Time)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    mGui.handleEvent(event);
	return false;
}
