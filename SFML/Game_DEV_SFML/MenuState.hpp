#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP
#include <vector>
#include "SFML/Graphics.hpp"
#include "State.hpp"
#include "StateStack.hpp"
#include "Container.hpp"
#include <TGUI/TGUI.hpp>


class MenuState : public State{

public:
                                MenuState(StateStack& stack, Context context);
    virtual void                draw();
    virtual bool                update(sf::Time dt);
    virtual bool                handleEvent(const sf::Event& event);
    void                         updateMenu();

private:
		GUI::Container			mGUIContainer;
				sf::Sprite				mBackgroundSprite;
        tgui::Gui mGui;

};

#endif // MENUSTATE_HPP
