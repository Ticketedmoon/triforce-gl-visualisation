#include "lib/engine/engine.hpp"

int main() 
{
    std::cout << "Hello, Triforce!" << std::endl;

    Engine engine;
    engine.startGameLoop();
    engine.tearDown();
    return 0;
}
