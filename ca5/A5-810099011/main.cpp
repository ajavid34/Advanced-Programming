#include "Defines.hpp"
#include "src/rsdl.hpp"
#include "Game.hpp"
using namespace std;

int main() {
    Game game;
    while (!game.is_end()) {
        game.update();
        game.get_event();
        delay(DELAY);
    }
}