#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#define GAME_TERMINATE -1
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define window_width 400
#define window_height 600
#define floor_height 500 //=window_height
#define row_num 10
#define item_num 30

enum class GameScene{
    START,
    LEVEL_1,
    LEVEL_2,
    BONUS,
    WIN,
    LOSE,
    MENU,
    ABOUT,
    //SHOP,
    NONE,
    QUIT,
};

enum class GameMode{
    NORMAL,
    BONUS,
    ICE,
    //PROTECTED,
};

enum {SNOWBALL = 0, SEAL, COIN, FISH, ICECUBE};

// note that you can't assign initial value here!
extern const float FPS;

extern ALLEGRO_TIMER *fps;
extern ALLEGRO_TIMER *left_time_fps;
extern bool key_state[ALLEGRO_KEY_MAX];

extern bool mute;
extern int highest_score;
extern int previous_highest;

extern int previous_hp;
extern int previous_score;
extern int previous_time;
extern GameScene previous_scene;

#endif
