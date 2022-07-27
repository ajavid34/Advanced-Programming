#ifndef OBJECTS_H
#define OBJECTS_H "OBJECTS_H"
#include "Defines.hpp"
#include "src/rsdl.hpp"
using namespace std;

class Thing {
public:
    Thing(int x, int y, int sx, int sy, string addres);
    Thing(int x, int y, int sx, int sy);
    Point get_cor();
    bool is_same_cor(Point p, Point psize, string status);
    Point get_draw_pointtl();
    Point get_draw_pointbr();
    bool is_on_screen();
    void objdraw(Point playercor, Window* window);
    void change_time(double t);
    void movehorizon(int dx);
    void update_change();
    void calc_relativey(Point p);
protected:
    Point point;
    Point size;
    string img_file{ "" };
    double time{ 0 };
    bool change_state{ false };
    int relativey{ 0 };
};

class Spring :public Thing {
public:
    Spring(int x, int y, int sx, int sy, string addres);
    void objdraw(Point playercor, Window* window);
    void animation();
private:
    int change_step{ 0 };
};
class Enemy :public Thing {
public:
    Enemy(int x, int y, int sx, int sy, string addres);
    bool is_kill_player();
    bool is_same_cor(Point p, Point size);
private:
};
class Ordinary_Platform :public Thing {
public:
    Ordinary_Platform(int x, int y, int sx, int sy, string addres);
private:

};
class Moving_Platform :public Thing {
public:
    Moving_Platform(int x, int y, int sx, int sy, string addres);
    void objdraw(Point playercor, Window* window);
private:
};
class Broken_Platform :public Thing {
public:
    Broken_Platform(int x, int y, int sx, int sy, string addres);
    bool is_broken();
    void objdraw(Point playercor, Window* window);
    void animation();
private:
    int broken_step{ 0 };
};
class Player :public Thing {
public:
    Player();
    Player(int x, int y, int sx, int sy);
    void move(string direction, int a = 0);
    void check_be_in_screen();
    void objdraw(Window* window);
    int jump_status{ 0 };
    void moveup(int dy);
    void movey();
    void movex(int dir);
    void hit(Thing& thing, string type, Window* window);
    int calc_score();
    void hunt_by_enemy(Enemy& enemy, Window* window);
    int go_where();
    void change_player_way(string state);
    void speed_limiter();
    void choice_pic();
private:
    string last_status{ "right" };
    double xvelocity{ 0 };
    double yvelocity{ STARTING_YVELOCITY };
    double acceleration{ ACCELERATION };
    int score{ 0 };
    int dy;
    bool go_left{ false };
    bool go_right{ false };
    string rimg_addres;
    string limg_addres;
};
#endif