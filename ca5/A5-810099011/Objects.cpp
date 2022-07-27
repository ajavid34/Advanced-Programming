#include "Objects.hpp"
using namespace std;
Thing::Thing(int x, int y, int sx, int sy, string addres) {
        point.x = x;
        point.y = y;
        size.x = sx;
        size.y = sy;
        img_file = addres;
    }
Thing::Thing(int x, int y, int sx, int sy) {
    point.x = x;
    point.y = y;
    size.x = sx;
    size.y = sy;
}
bool Thing::is_same_cor(Point p, Point psize, string status) {
    if (!status.compare("right")) {
        if ((p.x - (psize.x/2 - 7) < point.x + size.x / 2) && (p.x - (psize.x/2 - 7) > point.x - size.x / 2) &&
            (p.y - point.y < size.y) && (p.y - point.y > 0))
            return true;
        else if ((p.x + (psize.x / 6 - 7) < point.x + size.x / 2) && (p.x + (psize.x / 6 - 7) > point.x - size.x / 2) &&
            (p.y - point.y < size.y) && (p.y - point.y > 0))
            return true;
    }
    else if (!status.compare("left")) {
        if ((p.x - (psize.x / 6 - 7) < point.x + size.x / 2) && (p.x - (psize.x / 6 - 7) > point.x - size.x / 2) &&
            (p.y - point.y < size.y) && (p.y - point.y > 0))
            return true;
        else if ((p.x + (psize.x/2 - 7) < point.x + size.x / 2) && (p.x + (psize.x/2 - 7) > point.x - size.x / 2) &&
            (p.y - point.y < size.y) && (p.y - point.y > 0))
            return true;
    }
    return false;
}
Point Thing::get_cor() { return point; }
Point Thing::get_draw_pointtl() { return point - size; }
Point Thing::get_draw_pointbr() { return point + size; }
void Thing::change_time(double t) { time += t; }
void Thing::movehorizon(int dx) { point.x += dx; }
void Thing::update_change() { change_state = true; }
void Thing::calc_relativey(Point p) {
    int temp{ -HIGH_SCREEN_SIZE / 2 + p.y };
    if (p.y > HIGH_SCREEN_SIZE / 2 && relativey < temp)
        relativey = temp;
}
bool Enemy::is_same_cor(Point p, Point size) {
    if ((p.x < point.x + size.x / 2) && (p.x > point.x - size.x / 2) && (p.y < point.y + size.y) && (p.y > point.y))
        return true;
    if ((p.x < point.x + size.x / 2) && (p.x > point.x - size.x / 2) && (p.y + size.y < point.y + size.y) && (p.y + size.y > point.y))
        return true;
    return false;
}
bool Enemy::is_kill_player() { return change_state; }
bool Broken_Platform::is_broken() { return change_state; }
void Player::moveup(int dy) { point.y += dy; }
int Player::calc_score() {
    if (point.y > score + STARTING_Y)
        score = point.y - STARTING_Y;
    return score;
 }
int Player::go_where() {
    if (go_left)
        return -1;
    else if (go_right)
        return 1;
    else
        return 0;
}
void Player::change_player_way(string state) {
    if (!state.compare("right"))
        go_right = true;
    else if (!state.compare("left"))
        go_left = true;
    else {
        go_left = false;
        go_right = false;
    }
}    
Ordinary_Platform::Ordinary_Platform(int x, int y, int sx, int sy, string addres) :Thing(x, y, sx, sy, addres) {}
Enemy::Enemy(int x, int y, int sx, int sy, string addres) : Thing(x, y, sx, sy, addres) {}
Moving_Platform::Moving_Platform(int x, int y, int sx, int sy, string addres) : Thing(x, y, sx, sy, addres) {}
Broken_Platform::Broken_Platform(int x, int y, int sx, int sy, string addres) : Thing(x, y, sx, sy, addres) {}
Spring::Spring(int x, int y, int sx, int sy, string addres) : Thing(x, y, sx, sy, addres) {}
Player::Player(int x = STARTING_X, int y = STARTING_Y, int sx = WIDTH_DOODLE_SIZE, int sy = HIGH_DOODLE_SIZE) : Thing(x, y, sx, sy) {}
Player::Player(): Thing(STARTING_X, STARTING_Y, WIDTH_DOODLE_SIZE, HIGH_DOODLE_SIZE) {} 
void Thing::objdraw(Point p, Window* win) {
    calc_relativey(p);
    Point top_left((point.x - size.x / 2), ((HIGH_SCREEN_SIZE - point.y) - size.y + relativey));
    if (is_on_screen()) {
        win->draw_img(img_file, Rectangle(top_left, size.x, size.y));
    }
}
void Broken_Platform::objdraw(Point p, Window* win) {
    animation();
    calc_relativey(p);
    Point top_left((point.x - size.x / 2), ((HIGH_SCREEN_SIZE - point.y) - size.y + relativey));
    if (is_on_screen()) {
        win->draw_img(img_file, Rectangle(top_left, size.x, size.y));
    }
}
void Broken_Platform::animation() {
    if (broken_step > 1 && broken_step <= 4) {
        img_file = BROKEN_PLATFORM_PATH1;
        point.y -= 4;
    }
    else if (broken_step > 4 && broken_step <= 7) {
        img_file = BROKEN_PLATFORM_PATH2;
        point.y -= 4;
    }
    else if (broken_step > 7) {
        img_file = BROKEN_PLATFORM_PATH3;
        point.y -= 8;
    }
    if (is_broken() && broken_step < 10)
        broken_step++;
}
void Spring::objdraw(Point p, Window* win) {
    animation();
    calc_relativey(p);
    Point top_left((point.x - size.x / 2), ((HIGH_SCREEN_SIZE - point.y) - size.y + relativey));
    if (is_on_screen()) {
        win->draw_img(img_file, Rectangle(top_left, size.x, size.y));
    }
}
void Spring::animation() {
    if (change_state && change_step > 14) {
        change_state = false;
        change_state = 0;
    }
    if (change_step > 0 && change_step <= 6)
        img_file = SPRING_DOWN_PATH;
    else if (change_step > 6 && change_step <= 12)
        img_file = SPRING_UP_PATH;
    else if (change_step > 12)
        img_file = SPRING_PATH;
    if (change_state && change_step < 13)
        change_step++;
}
void Moving_Platform::objdraw(Point p, Window* win) {
    if (!change_state) {
        point.x += MOVING_PLATFORM_SPEED;
        if (point.x + size.x / 2 >= WIDTH_SCREEN_SIZE)
            change_state = true;
    }
    else if (change_state) {
        point.x -= MOVING_PLATFORM_SPEED;
        if (point.x - size.x / 2 <= 0)
            change_state = false;
    }
    calc_relativey(p);
    Point top_left((point.x - size.x / 2), ((HIGH_SCREEN_SIZE - point.y) - size.y + relativey));
    if (is_on_screen()) {
        win->draw_img(img_file, Rectangle(top_left, size.x, size.y));
    }
}
bool Thing::is_on_screen() {
    if (point.y - relativey < -size.y)
        return false;
    else
        return true;
}
void Player::move(string dir, int a) {
    if (!dir.compare("right")) {
        movex(1);
        last_status = "right";
    }
    else if (!dir.compare("left")) {
        movex(-1);
        last_status = "left";
    }
}
void Player::movex(int dir) {
    if (dir > 0)
        xvelocity = XVELOCITY;
    else
        xvelocity = -XVELOCITY;
    int dx = time * xvelocity;
    movehorizon(dx);
}
void Player::speed_limiter() {
    if (time > 3.5) {
        change_time(-0.5);
    }
    if (dy > MAX_JUMP_SPEED)
        dy = MAX_JUMP_SPEED;
    else if (dy < MAX_FALL_SPEED)
        dy = MAX_FALL_SPEED;
}
void Player::movey() {
    change_time(0.1);
    dy = acceleration * time * time + time * yvelocity;
    if (abs(yvelocity) == 0)
        time = 0;
    yvelocity += acceleration * time;
    speed_limiter();
    moveup(dy);
}
void Player::choice_pic() {
    rimg_addres = RIGHT_DOODLE_PATH;
    limg_addres = LEFT_DOODLE_PATH;
    if (jump_status) {
        rimg_addres = RIGHT_DOODLE_JUMP_PATH;
        limg_addres = LEFT_DOODLE_JUMP_PATH;
        jump_status -= 1;
    }
}
void Player::objdraw(Window* win) {
    calc_relativey(point);
    Point top_left((point.x - size.x / 2), ((HIGH_SCREEN_SIZE - point.y) - size.y + relativey));
    choice_pic();
    if (!last_status.compare("right")) {
        win->draw_img(rimg_addres, Rectangle(top_left, size.x, size.y));
    }
    else if (!last_status.compare("left")) {
        win->draw_img(limg_addres, Rectangle(top_left, size.x, size.y));
    }
}
void Player::hit(Thing& ting, string type, Window* win) {
    if (ting.is_same_cor(point, size, last_status) && dy < 0 && ting.is_on_screen()) {
        if (!type.compare(ORDINARY_PLATFORM_NAME) || !type.compare(MOVING_PLATFORM_NAME)) {
            yvelocity = JUMP_PLATFORM;
            jump_status = 8;
            win->play_sound_effect(JUMP_PLATFORM_SOUND_PATH);
        }
        else if (!type.compare(BROKEN_PLATFORM_NAME)) {
            ting.update_change();
            yvelocity += (yvelocity > 0) ? -0.3 : 0.3;
            win->play_sound_effect(BROKE_PLATFORM_SOUND_PATH);
        }
        else if (!type.compare(SPRING_NAME)) {
            ting.update_change();
            yvelocity = JUMP_SPRING;
            jump_status = 8;
            win->play_sound_effect(SPRING_SOUND_PATH);
        }
    }
}
void Player::hunt_by_enemy(Enemy& enemy, Window* win) {
    if (enemy.is_same_cor(point, size)) {
        enemy.update_change();
        yvelocity += (yvelocity > 0) ? -0.1 : 0.1;
        win->play_sound_effect(MONSTER_SOUND_PATH);
    }
}
void Player::check_be_in_screen() {
    if (point.x > WIDTH_SCREEN_SIZE)
        point.x = 0;
    else if (point.x < 0)
        point.x = WIDTH_SCREEN_SIZE;
}