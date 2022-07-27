#ifndef GAME_H
#define GAME_H "GAME_H"
#include "Defines.hpp"
#include "src/rsdl.hpp"
#include "Objects.hpp"
using namespace std;

class Game {
public:
    Game();
    void read_map();
    bool is_over();
    void update();
    void get_event();
    void draw_back_ground();
    void show_score();
    void final_screen();
    void ending_event();
    bool is_end();
private:
    vector<Enemy> enemy;
    vector<Moving_Platform> mplatform;
    vector<Ordinary_Platform> platform;
    vector<Broken_Platform> bplatform;
    vector<Spring> springs;
    Player player;
    Window* window = new Window(WIDTH_SCREEN_SIZE, HIGH_SCREEN_SIZE, GAME_NAME);
    bool ending_state{ false };
    int play_fall_sound{ 0 };
};
#endif