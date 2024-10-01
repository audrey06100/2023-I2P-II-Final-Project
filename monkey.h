#ifndef MONKEY_H
#define MONKEY_H
#include "global.h"

// the state of character
enum {STOP = 0, MOVE, COLLIDE};
typedef struct character{
    int x, y; // the position of image
    int width, height; // the width and height of image
    bool dir; // left: false, right: true
    int state; // the state of character
    ALLEGRO_BITMAP *img_move[2];
    ALLEGRO_BITMAP *img_atk[2];
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation //draw frequency
}Character;

void character_init();
void charater_process(ALLEGRO_EVENT event);
void charater_update();
void character_draw();
void character_destory();
#endif
