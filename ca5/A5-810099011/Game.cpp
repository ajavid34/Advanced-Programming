#include "Game.hpp"
using namespace std;
Game::Game() {
    draw_back_ground();
    read_map();
}
void Game::read_map() {
    int number_of_entities;
    int x, y;
    string type;
    ifstream file(MAP_NAME);
    file >> number_of_entities;
    for (int i = 0; i < number_of_entities; i++) {
        file >> x >> y >> type;
        if (!type.compare(ORDINARY_PLATFORM_NAME)) {
            platform.push_back(Ordinary_Platform(x, y, WIDTH_PLATFORM_SIZE, HIGH_PLATFORM_SIZE, ORDINARY_PLATFORM_PATH));
        }
        else if (!type.compare(MOVING_PLATFORM_NAME)) {
            mplatform.push_back(Moving_Platform(x, y, WIDTH_PLATFORM_SIZE, HIGH_PLATFORM_SIZE, MOVING_PLATFORM_PATH));
        }
        else if (!type.compare(ENEMY_NAME)) {
            enemy.push_back(Enemy(x, y, HIGH_ENEMY_SIZE, WIDTH_ENEMY_SIZE, ENEMY_PATH));
        }
        else if (!type.compare(BROKEN_PLATFORM_NAME)) {
            bplatform.push_back(Broken_Platform(x, y, WIDTH_PLATFORM_SIZE, HIGH_PLATFORM_SIZE, BROKEN_PLATFORM_PATH));
        }
        else if (!type.compare(SPRING_NAME)) {
            springs.push_back(Spring(x, y, WIDTH_SPRING_SIZE, HIGH_SPRING_SIZE, SPRING_PATH));
        }
    }
    file.close();
}
void Game::update() {
    if (is_over()) {
        if (play_fall_sound == 1)
            window->play_sound_effect(END_FALL_SOUND_PATH);
        final_screen();
        ending_event();
        return;
    }
    draw_back_ground();
    show_score();
    player.objdraw(window);
    player.check_be_in_screen();
    player.movey();
    for (int i = 0; i < enemy.size(); i++) {
        enemy[i].objdraw(player.get_cor(), window);
        player.hunt_by_enemy(enemy[i], window);
    }
    for (int i = 0; i < mplatform.size(); i++) {
        mplatform[i].objdraw(player.get_cor(), window);
        player.hit(mplatform[i], MOVING_PLATFORM_NAME, window);
    }
    for (int i = 0; i < platform.size(); i++) {
        platform[i].objdraw(player.get_cor(), window);
        player.hit(platform[i], ORDINARY_PLATFORM_NAME, window);
    }
    for (int i = 0; i < bplatform.size(); i++) {
        bplatform[i].objdraw(player.get_cor(), window);
        player.hit(bplatform[i], BROKEN_PLATFORM_NAME, window);
    }
    for (int i = 0; i < springs.size(); i++) {
        springs[i].objdraw(player.get_cor(), window);
        player.hit(springs[i], SPRING_NAME, window);
    }
    window->update_screen();
}
void Game::get_event() {
    if (player.go_where() == 1)
        player.move("right");
    if (player.go_where() == -1)
        player.move("left");
    while (window->has_pending_event()) {
        Event e = window->poll_for_event();
        switch (e.get_type()) {
        case Event::EventType::QUIT: {
            exit(0);
            break;
        }
        case Event::EventType::KEY_PRESS: {
            char pressed_char = e.get_pressed_key();
            if (pressed_char == RIGHT_KEY) {
                player.move("right");
                player.change_player_way("right");
            }
            else if (pressed_char == LEFT_KEY) {
                player.move("left");
                player.change_player_way("left");
            }
            break;
        }
        case Event::EventType::KEY_RELEASE: {
            player.change_player_way("stop");
            break;
        }
        }
    }
}
void Game::draw_back_ground() {
    window->clear();
    window->draw_img(BACK_GROUND_PATH);
}

void Game::show_score() {
    string score = to_string(player.calc_score());
    Point src(10, 10);
    window->show_text(score, src, TEXT_COLOR, FONT, SCORE_FONT_SIZE);
}
bool Game::is_over() {
    if (!player.is_on_screen()) {
        play_fall_sound++;
        return true;
    }
    for (int i = 0; i < enemy.size(); i++) 
        if (enemy[i].is_kill_player()) 
            return true;
    return false;
}
void Game::final_screen() {
    string score = "Your Final Score is :" + to_string(player.calc_score());
    Point src(50, 50);
    window->clear();
    window->draw_img(FINISH_PATH);
    window->show_text(score, src, TEXT_COLOR, FONT, FINAL_TEXT_SIZE);
    window->show_text("Prees Any Key and Leave!", Point(50, 150), TEXT_COLOR, FONT, FINAL_TEXT_SIZE);
    window->update_screen();
}
void Game::ending_event() {
    while (window->has_pending_event()) {
        Event e = window->poll_for_event();
        switch (e.get_type()) {
        case Event::EventType::QUIT: {
            exit(0);
            break;
        }
        case Event::EventType::KEY_PRESS: {
            ending_state = true;
        }
        }
    }
}
bool Game::is_end() { return ending_state; }