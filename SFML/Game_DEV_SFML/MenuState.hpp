#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP
#include <vector>
#include "SFML/Graphics.hpp"
#include "State.hpp"
#include "StateStack.hpp"


class MenuState : public State{
public:
    enum OptionNames{
    Play,
    Exit,
    };
public:
                                MenuState(StateStack& stack, Context context);
    virtual void                draw();
    virtual bool                update(sf::Time dt);
    virtual bool                handleEvent(const sf::Event& event);
    void                         updateMenu();

private:
    std::vector<sf::Text> mOptions;
    std::size_t           moptionIndex;

};

#endif // MENUSTATE_HPP
