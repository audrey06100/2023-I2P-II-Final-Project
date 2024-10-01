#include "global.h"

// variables for global usage
const float FPS = 60.0;

ALLEGRO_TIMER *fps = NULL;
ALLEGRO_TIMER *left_time_fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};

bool mute = true;
int highest_score;
int previous_highest;

int previous_hp;
int previous_score;
//int previous_time;
GameScene previous_scene;
