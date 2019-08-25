#ifndef COMMANDQUEUE
#define COMMANDQUEUE
#include "Command.hpp"
#include <queue>

class CommandQueue{
public:
    void        push(const Command& command);
    Command     pop();
    bool        isEmpty() const;
        std::queue<Command> mQueue;

private:

};


#endif // COMMANDQUEUE_HPP
