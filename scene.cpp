#include "scene.h"

ALLEGRO_FONT *small_font = NULL;
ALLEGRO_FONT *big_font = NULL;

ALLEGRO_BITMAP *menu_background = NULL;
ALLEGRO_BITMAP *previous_background = NULL;
ALLEGRO_BITMAP *button_img = NULL;
ALLEGRO_BITMAP *white_back_img = NULL;
ALLEGRO_BITMAP *about_img = NULL;

int start_time_cd = 3;

int button_anime_font_size = 0;
int button_anime_rest_cd = 0;

// function of menu
void menu_init(){
    button_anime_font_size = 0;
    button_anime_rest_cd = 0;

    small_font = al_load_ttf_font("./font/pirulen.ttf",14,0);
    big_font = al_load_ttf_font("./font/pirulen.ttf",30,0);

    menu_background = al_load_bitmap("./image/mountain.png");
    white_back_img = al_load_bitmap("./image/white.png");
    button_img = al_load_bitmap("./image/5.png");

    al_play_sample_instance(sample_instance);

    printf("menu initialized\n");
}
void menu_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_KEY_UP ){
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER ){
            //al_stop_sample_instance(sample_instance);
            judge_next_window = START;
        }else if( event.keyboard.keycode == ALLEGRO_KEY_2 ){
            //al_stop_sample_instance(sample_instance);
            judge_next_window = LEVEL_2;
        }else if( event.keyboard.keycode == ALLEGRO_KEY_A ){
            judge_next_window = ABOUT;
        }else if( event.keyboard.keycode == ALLEGRO_KEY_Q || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE ){
            tmp_msg = GAME_TERMINATE;
        }else if( event.keyboard.keycode == ALLEGRO_KEY_M ){
            if( sound ){
                al_stop_sample_instance(sample_instance);
                sound = false;
            }else{
                al_play_sample_instance(sample_instance);
                sound = true;
            }
        }
    }
}
void menu_draw(){
    al_draw_bitmap(menu_background, -400, 0, ALLEGRO_FLIP_HORIZONTAL);

    al_draw_bitmap(button_img, window_width/2-125, 160, ALLEGRO_FLIP_HORIZONTAL);
    al_draw_bitmap(button_img, window_width/2-125, 260, ALLEGRO_FLIP_HORIZONTAL);
    al_draw_bitmap(button_img, window_width/2-125, 360, ALLEGRO_FLIP_HORIZONTAL);

    if(button_anime_font_size == 0){
        button_anime_rest_cd++;
    }
    if(button_anime_rest_cd >= 40){
        if(button_anime_font_size < 14){
            al_draw_text(al_load_ttf_font("./font/pirulen.ttf",button_anime_font_size++,0), al_map_rgb(255,255,255), window_width/2, 230 , ALLEGRO_ALIGN_CENTRE, "'A' : about");
            al_draw_text(al_load_ttf_font("./font/pirulen.ttf",button_anime_font_size++,0), al_map_rgb(255,255,255), window_width/2, 330 , ALLEGRO_ALIGN_CENTRE, "'Enter' : start");
            al_draw_text(al_load_ttf_font("./font/pirulen.ttf",button_anime_font_size++,0), al_map_rgb(255,255,255), window_width/2, 430 , ALLEGRO_ALIGN_CENTRE, "'Q' : quite");
        }else{
            al_draw_text(small_font, al_map_rgb(255,255,255), window_width/2, 230 , ALLEGRO_ALIGN_CENTRE, "'A' : about");
            al_draw_text(small_font, al_map_rgb(255,255,255), window_width/2, 330 , ALLEGRO_ALIGN_CENTRE, "'Enter' : start");
            al_draw_text(small_font, al_map_rgb(255,255,255), window_width/2, 430 , ALLEGRO_ALIGN_CENTRE, "'Q' : quite");
        }
    }
}
void menu_destroy(){
    al_destroy_font(small_font);
    al_destroy_font(big_font);
    al_destroy_bitmap(menu_background);
    al_destroy_bitmap(white_back_img);
    al_destroy_bitmap(button_img);
}

// function of game scene
void game_scene_init(int window){
    background_init(window);
    character_init();
    object_init(window);

    left_time_cd = 59;
    previous_window = 0;

    printf("level %d initialized\n", window-1);
}
void game_process(ALLEGRO_EVENT event, int window){
    if( event.type == ALLEGRO_EVENT_KEY_UP ){
        if( event.keyboard.keycode == ALLEGRO_KEY_Q || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE ){
            //al_stop_sample_instance(background[window-2].game_sound);
            judge_next_window = MENU;
        }else if( event.keyboard.keycode == ALLEGRO_KEY_2 ){
            judge_next_window = LEVEL_2;
        }else if( event.keyboard.keycode == ALLEGRO_KEY_W ){
            judge_next_window = WIN;
        }else if( event.keyboard.keycode == ALLEGRO_KEY_L ){
            judge_next_window = LOSE;
        }else if( event.keyboard.keycode == ALLEGRO_KEY_S ){
            left_time_cd = 10;
        }
    }else if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == left_time_fps){
            left_time_cd--;
            if(left_time_cd == 0){
                al_draw_bitmap(menu_background, -400, 0, ALLEGRO_FLIP_HORIZONTAL);
                al_rest(0.5);
                judge_next_window = LEVEL_2;
            }
        }
    }
}
void game_scene_draw(int window){
    background_draw();
    character_draw();
    object_draw();

    if( left_time_cd >57 ){
        char temp[20];
        sprintf( temp, "Level %d", window-1 );
        al_draw_text(big_font, al_map_rgb(255, 255, 255), window_width/2, window_height/2-50 , ALLEGRO_ALIGN_CENTRE, temp);
    }
}
void game_scene_destroy(int window){
    background_destroy(window);
    character_destory();
    object_destroy();
}

// function of about scene
void about_scene_init(){
    //white_back_img = al_load_bitmap("./image/white.png");
    about_img = al_load_bitmap("./image/about.png");
}
void about_scene_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_KEY_UP ){
        if( event.keyboard.keycode == ALLEGRO_KEY_B ){
            judge_next_window = MENU;
        }
    }
}
void about_scene_draw(){
    al_draw_bitmap(menu_background, -400, 0, ALLEGRO_FLIP_HORIZONTAL);
    //al_draw_bitmap(white_back_img, 50, 100, 0);
    //al_draw_text(big_font, al_map_rgb(50, 50, 50), WIDTH/2, 120 , ALLEGRO_ALIGN_CENTRE, "about");
    al_draw_bitmap(about_img, 50, 100, 0);

    al_draw_text(small_font, al_map_rgb(255, 255, 255), window_width/2, 520 , ALLEGRO_ALIGN_CENTRE, "'B' : back");
}
void about_scene_destroy(){
    al_destroy_bitmap(about_img);
}

// function of win scene
void victory_scene_init(int window){
    char temp[50];
    sprintf(temp, "./image/forest_%d.png", window-1);
    previous_background = al_load_bitmap(temp);
}
void victory_scene_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_KEY_UP ){
        if( event.keyboard.keycode == ALLEGRO_KEY_Q || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE ){
            al_stop_sample_instance(background[1].game_sound);
            judge_next_window = MENU;
        }
    }
}
void victory_scene_draw(){

    al_draw_bitmap(previous_background, -100, 0, 0);
    al_draw_bitmap(white_back_img, 50, 100, 0);

    al_draw_text(big_font, al_map_rgb(255, 255, 255), window_width/2, window_height/2-20 , ALLEGRO_ALIGN_CENTRE, "victory");
    al_draw_text(small_font, al_map_rgb(0, 0, 0), window_width/2, window_height/2+120 , ALLEGRO_ALIGN_CENTRE, "'Q' : quit");
}
void victory_scene_destroy(){
    al_destroy_bitmap(previous_background);
}

// function of lose scene
void defeat_scene_init(int window){
    char temp[50];
    sprintf(temp, "./image/forest_%d.png", window-1);
    previous_background = al_load_bitmap(temp);
}
void defeat_scene_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_KEY_UP ){
        if( event.keyboard.keycode == ALLEGRO_KEY_R ){
            judge_next_window = 2;
        }else if( event.keyboard.keycode == ALLEGRO_KEY_Q || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE ){
            judge_next_window = MENU;
        }
    }
}
void defeat_scene_draw(){
    al_draw_bitmap(previous_background, -100, 0, 0);
    al_draw_bitmap(white_back_img, 50, 100, 0);

    al_draw_text(big_font, al_map_rgb(255, 0, 0), window_width/2, window_height/2-20 , ALLEGRO_ALIGN_CENTRE, "defeat");
    al_draw_text(small_font, al_map_rgb(0, 0, 0), window_width/2, window_height/2+100 , ALLEGRO_ALIGN_CENTRE, "'R' : restart");
    al_draw_text(small_font, al_map_rgb(0, 0, 0), window_width/2, window_height/2+120 , ALLEGRO_ALIGN_CENTRE, "'Q' : quit");
}
void defeat_scene_destroy(){
    al_destroy_bitmap(previous_background);
}

// function of start scene
void start_scene_init(int window){
    start_time_cd = 3;
}
void start_scene_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == left_time_fps && start_time_cd ){
            start_time_cd--;
            if(start_time_cd == 0){
                judge_next_window = 2;
            }
        }
    }
}
void start_scene_draw(){
    al_clear_to_color(al_map_rgb(0, 0, 0));

    char temp[20];
    sprintf( temp, "%d", start_time_cd );
    al_draw_text(big_font, al_map_rgb(255, 255, 255), window_width/2, window_height/2-50 , ALLEGRO_ALIGN_CENTRE, temp);
}
void start_scene_destroy(){

}
