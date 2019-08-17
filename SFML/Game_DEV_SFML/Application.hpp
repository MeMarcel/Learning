
class Application{
public:
                            Application();
    void                    registerStates();

private:
    StateStack              mStateStack;
    void                    processInput();
    void                    update(sf::Time dt);
    void                    draw();

};
