#include "lib/engine/engine.hpp"

int main() 
{
    std::cout << "Hello, Triforce!" << std::endl;
    Engine engine;

    bool isCreated = engine.create();
    if (!isCreated)
    {
        return -1;
    }

	engine.startGameLoop();
    engine.tearDown();
    return 0;
}