#ifndef DEFINE_H_
#define DEFINE_H_ "DEFINE_H_"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#define BACK_GROUND_PATH "main pictures/background.png"
#define HIGH_SCREEN_SIZE 800
#define WIDTH_SCREEN_SIZE 640
#define LEFT_DOODLE_PATH "main pictures/left.png"
#define RIGHT_DOODLE_PATH "main pictures/right.png"
#define LEFT_DOODLE_JUMP_PATH "main pictures/left_jumping.png"
#define RIGHT_DOODLE_JUMP_PATH "main pictures/right_jumping.png"
#define WIDTH_DOODLE_SIZE 90
#define HIGH_DOODLE_SIZE 90
#define SPRING_PATH "main pictures/spring.png"
#define SPRING_UP_PATH "main pictures/springtoup.png"
#define SPRING_DOWN_PATH "main pictures/springdown.png"
#define SPRING_NAME "spring"
#define WIDTH_SPRING_SIZE 60
#define HIGH_SPRING_SIZE 31
#define FINISH_PATH "main pictures/finish.png"
#define ORDINARY_PLATFORM_PATH "main pictures/oplatform.png"
#define ORDINARY_PLATFORM_NAME "platform"
#define MOVING_PLATFORM_PATH "main pictures/mplatform.png"
#define MOVING_PLATFORM_NAME "mplatform"
#define BROKEN_PLATFORM_PATH "main pictures/broken.png"
#define BROKEN_PLATFORM_PATH1 "main pictures/broken1.png"
#define BROKEN_PLATFORM_PATH2 "main pictures/broken2.png"
#define BROKEN_PLATFORM_PATH3 "main pictures/broken3.png"
#define BROKEN_PLATFORM_NAME "bplatform"
#define WIDTH_PLATFORM_SIZE 85
#define HIGH_PLATFORM_SIZE 26 
#define ENEMY_PATH "main pictures/enemy.png"
#define ENEMY_NAME "enemy"
#define WIDTH_ENEMY_SIZE 120
#define HIGH_ENEMY_SIZE 80
#define STARTING_X WIDTH_SCREEN_SIZE/2
#define STARTING_Y HIGH_SCREEN_SIZE/2
#define STARTING_YVELOCITY 8
#define XVELOCITY 6
#define ACCELERATION -0.2
#define GAME_NAME "Doodle Jump"
#define MAP_NAME "map.txt"
#define MAX_FALL_SPEED -22
#define MAX_JUMP_SPEED 25
#define FONT "FreeSans.ttf"
#define TEXT_COLOR BLACK
#define RIGHT_KEY 'd'
#define LEFT_KEY 'a'
#define JUMP_PLATFORM 11
#define JUMP_SPRING 21
#define SCORE_FONT_SIZE 23
#define FINAL_TEXT_SIZE 40
#define JUMP_PLATFORM_SOUND_PATH "sounds/jump.wav"
#define BROKE_PLATFORM_SOUND_PATH "sounds/breaking-arcade.mp3"
#define SPRING_SOUND_PATH "sounds/springshoes.mp3"
#define MONSTER_SOUND_PATH "sounds/monster-crash.mp3"
#define END_FALL_SOUND_PATH "sounds/pada.mp3"
#define MOVING_PLATFORM_SPEED 5
#define DELAY 100/3
#endif