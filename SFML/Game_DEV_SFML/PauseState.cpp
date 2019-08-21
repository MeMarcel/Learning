
#include "PauseState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include "Button.hpp"
#include "Label.hpp"

PauseState::PauseState(StateStack& stack, Context context)
: State(stack, context)
, mBackgroundSprite()

, mContainer()
{
    	sf::Vector2f windowSize(context.window->getSize());
    auto playButton = std::make_shared<GUI::Button>(*context.fonts,*context.textures);
   	playButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 125);
	playButton->setText("Play");
	playButton->setCallback([this] ()
	{
		requestStackPop();

	});

	auto backToMenuButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	backToMenuButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 75);
	backToMenuButton->setText("Back to menu");
	backToMenuButton->setCallback([this] ()
	{
		requestStateClear();
		requestStackPush(States::Menu);
	});

	mContainer.pack(playButton);
	mContainer.pack(backToMenuButton);

}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mContainer);

}

bool PauseState::update(sf::Time)
{

	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
    mContainer.handleEvent(event);
	return false;
}
