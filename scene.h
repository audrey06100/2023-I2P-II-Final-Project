#include "global.h"
#include "monkey.h"
#include "Background.h"

extern int score;
extern int tmp_msg;
//extern int previous_window;
extern int left_time_cd;
extern ALLEGRO_SAMPLE_INSTANCE *sample_instance;
extern Background background[2];

void menu_init();
void menu_process(ALLEGRO_EVENT event);
void menu_draw();
void menu_destroy();

void game_scene_init(int window);
void game_process(ALLEGRO_EVENT event, int window);
void game_scene_draw();
void game_scene_destroy();

void about_scene_init();
void about_scene_process(ALLEGRO_EVENT event);
void about_scene_draw();
void about_scene_destroy();

void victory_scene_init();
void victory_scene_process(ALLEGRO_EVENT event);
void victory_scene_draw();
void victory_scene_destroy();

void defeat_scene_init();
void defeat_scene_process(ALLEGRO_EVENT event);
void defeat_scene_draw();
void defeat_scene_destroy();

void start_scene_init();
void start_scene_process(ALLEGRO_EVENT event);
void start_scene_draw();
void start_scene_destroy();
