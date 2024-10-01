#include <math.h>
#include "Object.h"
#define BUFFER_NUM 10
#define BUFFER_ITEM_NUM 30

Object object_queue[BUFFER_NUM][BUFFER_ITEM_NUM];

ALLEGRO_SAMPLE *sample_coconut = NULL;
ALLEGRO_SAMPLE *sample_bomb = NULL;
ALLEGRO_SAMPLE *sample_banana = NULL;
ALLEGRO_SAMPLE *sample_star = NULL;

ALLEGRO_SAMPLE_INSTANCE *coconut_collide_sound;
ALLEGRO_SAMPLE_INSTANCE *bomb_collide_sound;
ALLEGRO_SAMPLE_INSTANCE *banana_collide_sound;
ALLEGRO_SAMPLE_INSTANCE *star_collide_sound;

ALLEGRO_BITMAP *coconut_img[2];//0:small, 1:big
ALLEGRO_BITMAP *bomb_img;
ALLEGRO_BITMAP *banana_img;
ALLEGRO_BITMAP *star_img;

//ALLEGRO_TIMER *list_loop_fps = NULL;

double loop_init_time = 0;
int loop_arrived_num = 0;
int loop_special_flag = 0;
int current_list_idx = 0;

void object_init(int window){

    // load effective sound
    sample_coconut = al_load_sample("./sound/coconut.wav");
    sample_bomb = al_load_sample("./sound/bomb.wav");
    sample_banana = al_load_sample("./sound/banana.wav");
    sample_star = al_load_sample("./sound/star.wav");
    if(!sample_star) printf("problem...");

    coconut_collide_sound = al_create_sample_instance(sample_coconut);
    bomb_collide_sound = al_create_sample_instance(sample_bomb);
    banana_collide_sound = al_create_sample_instance(sample_banana);
    star_collide_sound = al_create_sample_instance(sample_star);

    al_set_sample_instance_playmode(coconut_collide_sound, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(bomb_collide_sound, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(banana_collide_sound, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_playmode(star_collide_sound, ALLEGRO_PLAYMODE_ONCE);

    al_attach_sample_instance_to_mixer(coconut_collide_sound, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(bomb_collide_sound, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(banana_collide_sound, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(star_collide_sound, al_get_default_mixer());

    // load object images
    coconut_img[0] = al_load_bitmap("./image/coconut_1.png");
    coconut_img[1] = al_load_bitmap("./image/coconut_2.png");
    bomb_img = al_load_bitmap("./image/bomb.png");
    banana_img = al_load_bitmap("./image/banana.png");
    star_img = al_load_bitmap("./image/star.png");

    //list_loop_fps = al_create_timer(20.0/FPS); //??
    //al_register_event_source(event_queue, al_get_timer_event_source(list_loop_fps));
    object_start_loop(window);
    //al_start_timer(list_loop_fps);
}

void insert_banana(int j){
    int temp_i = rand()%BUFFER_NUM;
    object_queue[temp_i][j].name = BANANA;
    object_queue[temp_i][j].img = banana_img;
    object_queue[temp_i][j].speed = 2; //...??
    object_queue[temp_i][j].collide_sound = banana_collide_sound;

    object_queue[temp_i][j].width = al_get_bitmap_width(object_queue[temp_i][j].img);
    object_queue[temp_i][j].height = al_get_bitmap_height(object_queue[temp_i][j].img);
}

void object_start_loop(int window){
    loop_init_time = al_get_time();
    loop_arrived_num = 0;
    loop_special_flag = 0;

    int total[BUFFER_ITEM_NUM] = {0};
    int current = 0;
    for(int i=0; i<BUFFER_NUM; i++){
        for(int j=0; j<BUFFER_ITEM_NUM; j++){

            current = rand()%4;

            if(current == BOMB) current = rand()%2;

            if(current==COCONUT || current==BOMB){
                total[j]++;
                while(total[j] >= 4 && (current==COCONUT||current==BOMB))current = rand()%4;
                if(total[j] >= 4) total[j] = 0;
            }
            while(current == BANANA || (window==2 && current==BOMB)) current = rand()%4;


            switch(current){
            case COCONUT:
                object_queue[i][j].name = COCONUT;
                object_queue[i][j].img = coconut_img[rand()%2];
                object_queue[i][j].speed = 1;
                object_queue[i][j].collide_sound = coconut_collide_sound;
                break;
            case BOMB:
                object_queue[i][j].name = BOMB;
                object_queue[i][j].img = bomb_img;
                object_queue[i][j].speed = 2; //3...??
                object_queue[i][j].collide_sound = bomb_collide_sound;
                break;
            case STAR:
                object_queue[i][j].name = STAR;
                object_queue[i][j].img = star_img;
                object_queue[i][j].speed = 1;
                object_queue[i][j].collide_sound = star_collide_sound;
                break;
            default:
                printf("error occurred in function object_start_loop()");
            }
            object_queue[i][j].width = al_get_bitmap_width(object_queue[i][j].img);
            object_queue[i][j].height = al_get_bitmap_height(object_queue[i][j].img);
            object_queue[i][j].x = (window_width/BUFFER_NUM+1)* i;
            object_queue[i][j].y = 0;
            if(object_queue[i][j].name ==BOMB) object_queue[i][j].x -= 100;

            object_queue[i][j].pause_total_sec = rand()%300;//??
            object_queue[i][j].pause_curr_sec = 0;
            object_queue[i][j].pause_cd_state = 1;
            object_queue[i][j].state = STOP;

            if(j%4 == 0 && i == BUFFER_NUM-1) insert_banana(j);
        }
    }

}

void object_process(ALLEGRO_EVENT event, int window){
    if( event.type == ALLEGRO_EVENT_TIMER ){

        if(loop_arrived_num >= BUFFER_NUM && loop_special_flag){
            loop_special_flag = 0;

            if(current_list_idx < BUFFER_ITEM_NUM-1){
                loop_arrived_num = 0;
                current_list_idx++;
            }else
                object_start_loop(window);

        }//else if( event.timer.source == list_loop_fps ){
            if(loop_arrived_num >= BUFFER_NUM){
                if(current_list_idx < BUFFER_ITEM_NUM-1){
                    loop_arrived_num = 0;
                    current_list_idx++;
                }else
                    object_start_loop(window);
            }else loop_special_flag = 1;
        //}

        if( event.timer.source == fps ){
            for(int i=0; i<BUFFER_NUM; i++){
                if(object_queue[i][current_list_idx].pause_cd_state == 1){
                    if(object_queue[i][current_list_idx].pause_curr_sec == object_queue[i][current_list_idx].pause_total_sec){
                        object_queue[i][current_list_idx].state = MOVE;
                        object_queue[i][current_list_idx].pause_curr_sec = -1;
                        object_queue[i][current_list_idx].pause_cd_state = 0;
                    }else object_queue[i][current_list_idx].pause_curr_sec++;
                }
            }
        }
    }
}

void object_update(int window){
    for(int i=0; i<BUFFER_NUM; i++){

        if(object_queue[i][current_list_idx].state == MOVE){
            //check if obj collided with character
            if(object_queue[i][current_list_idx].x+object_queue[i][current_list_idx].width>chara.x
               && object_queue[i][current_list_idx].x<chara.x+chara.width
               && object_queue[i][current_list_idx].y+object_queue[i][current_list_idx].height>chara.y
               && object_queue[i][current_list_idx].y<chara.y+chara.height){
                    object_queue[i][current_list_idx].state = COLLIDE;

                    //test
                    //object_queue[i][current_list_idx].state = STOP;

                    switch(object_queue[i][current_list_idx].name){
                    case COCONUT:
                        if(object_queue[i][current_list_idx].img == coconut_img[0]) hp--;
                        else hp -= 2;
                        break;
                    case BOMB:
                        hp -= 4;
                        break;
                    case BANANA:
                        hp++;
                        break;
                    case STAR:
                        score += 5*(window-1);
                        if(score > highest_score) highest_score = score;
                        break;
                    default:
                        printf("error occurred in function object_update()");
                    }
                    if(hp <= 0){
                        //rest_init_time = al_get_time(); //....
                    }

                    loop_arrived_num++;
            }
            if(object_queue[i][current_list_idx].y+object_queue[i][current_list_idx].height >= floor_height){
                object_queue[i][current_list_idx].state = STOP;
                loop_arrived_num++;
            }else
                if(object_queue[i][current_list_idx].name == BOMB)
                    object_queue[i][current_list_idx].x += 3;
                object_queue[i][current_list_idx].y += 5*object_queue[i][current_list_idx].speed;
        }if(object_queue[i][current_list_idx].state == COLLIDE){

        }
    }
}

void object_draw(){
    if(hp <= 0){
        /*al_clear_to_color(al_map_rgb(100,100,100));
        al_draw_text(
            font,
            al_map_rgb(255, 255, 0),
            400, 400,
            ALLEGRO_ALIGN_CENTER,
            "READY!"
        );

        al_flip_display();
        al_rest(2.0);*/
    }
    for(int i=0; i<BUFFER_NUM; i++){
        if(object_queue[i][current_list_idx].state == MOVE){
            al_draw_bitmap(object_queue[i][current_list_idx].img, object_queue[i][current_list_idx].x, object_queue[i][current_list_idx].y, ALLEGRO_FLIP_HORIZONTAL);
        }
        if(object_queue[i][current_list_idx].state == COLLIDE){
            al_play_sample_instance(object_queue[i][current_list_idx].collide_sound);
            object_queue[i][current_list_idx].state = STOP;
        }
    }
}

void object_destroy(){
    al_destroy_bitmap(coconut_img[0]);
    al_destroy_bitmap(coconut_img[1]);
    al_destroy_bitmap(bomb_img);
    al_destroy_bitmap(banana_img);
    al_destroy_bitmap(star_img);

    /*al_destroy_sample_instance(sample_coconut);
    al_destroy_sample_instance(sample_bomb);
    al_destroy_sample_instance(sample_banana);
    al_destroy_sample_instance(sample_star);*/
    /*for(int i=0; i<BUFFER_NUM; i++)
        for(int j=0; j<BUFFER_ITEM_NUM; j++)
            al_destroy_sample_instance(object_queue[i][j].collide_sound);*/
}
