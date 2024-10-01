#include "Penguin.h"
#include "DataCenter.h"
#include "Game.h"

const int draw_frequency = 8;

void
Penguin::Init(){
    char temp[50];
    ALLEGRO_BITMAP *img = NULL;

    // load character images & sound
    //walk
    for(int i=0; i<4; i++){
        sprintf(temp, "./image/penguin/penguin_walk%02d.png", i+1);
        img = al_load_bitmap(temp);
        if(img)
            walkImg.push_back(img);
        else
            printf("[Penguin] no walk image!!\n");
    }
    sample = al_load_sample("./sound/Walk.wav");
    walkSound  = al_create_sample_instance(sample);
    //slide
    sprintf(temp, "./image/penguin/penguin_slide02.png");
    img = al_load_bitmap(temp);
    if(img)
        slideImg = img;
    else
        printf("[Penguin] no slide image!!\n");
    sample = al_load_sample("./sound/Walk.wav");
    slideSound  = al_create_sample_instance(sample);
    //hit
    sprintf(temp, "./image/penguin/penguin_hurt.png");
    img = al_load_bitmap(temp);
    if(img)
        hitImg = img;
    else
        printf("[Penguin] no hit image!!\n");
    sample = al_load_sample("./sound/atk_sound.wav");
    hitSound  = al_create_sample_instance(sample);
    //die
    sprintf(temp, "./image/penguin/penguin_die.gif");
    /*ALGIF_ANIMATION* gif = algif_load_animation(temp);
    gif->loop = 1;
    if(gif)
        dieGif = gif, printf("[gif] done.\n");
    else
        printf("[Penguin] no gif!!\n");*/
    sample = al_load_sample("./sound/atk_sound.wav");
    dieSound  = al_create_sample_instance(sample);


    // initial the information of character
    x = window_width-120;//120
    y = window_height-150;//120
    hitbox_x = al_get_bitmap_width(walkImg[0]);
    hitbox_y = al_get_bitmap_height(walkImg[0]);
    counter = 0;
    sprite_dir = PenguinState::RIGHT;
    state = PenguinState::STOP;
    //prev_state = STOP;

    walk_speed = 2;
    slide_speed = 6;
    walk_pos = 0;
    //slide_pos = 0;
    //hit_pos = 0;
    //slide_start = 0;
    hit_duration = 5; //???
    die_duration = 7; //???
}
/*
Penguin::~Penguin(){
    //destroy images
    for(int i=0; i<4; i++){
        al_destroy_bitmap(walkImg[i]);
    }
    for(int i=0; i<2; i++){
        al_destroy_bitmap(slideImg[i]);
    }
    al_destroy_bitmap(hitImg);
    al_destroy_bitmap(dieGif);

    //destroy sound
    //al_destroy_sample_instance();
}
*/
void
Penguin::Process(ALLEGRO_EVENT event){
    //process the animation
    if(event.type == ALLEGRO_EVENT_TIMER){
        if(event.timer.source == fps){
            if(state != PenguinState::DIE){
                counter = (counter+1) % draw_frequency; // 0~10
                //dieGif->start_time = 0;
                if(counter == 0){ //change image
                    if(state == PenguinState::WALK){
                        walk_pos = (walk_pos+1) % 4;
                    }else if(state == PenguinState::HIT){
                        hit_duration_cd--;
                        if(hit_duration_cd == 0){
                            state = PenguinState::STOP;
                            hit_duration_cd = hit_duration;
                        }
                    }
                }
            }else{
                /*die_duration_cd--;
                if(die_duration_cd == 0){
                    if(dieGif->done){
                        dieGif->done = false;
                    }
                }*/
            }
        }
    }
    // process the keyboard event
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
        key_state[event.keyboard.keycode] = true;
        counter = 0;
        hit_duration_cd = hit_duration;
    }else if(event.type == ALLEGRO_EVENT_KEY_UP){
        key_state[event.keyboard.keycode] = false;
        if(state == PenguinState::WALK){
            al_stop_sample_instance(walkSound);
        }else if(state == PenguinState::SLIDE){
            al_stop_sample_instance(slideSound);
        }
        state = PenguinState::STOP;
    }
}

void
Penguin::Update(){
    if(key_state[ALLEGRO_KEY_A] || key_state[ALLEGRO_KEY_LEFT]){
        sprite_dir = PenguinState::LEFT;
        if(x + hitbox_x/2 < 0){
            //stop sound
            if(state == PenguinState::WALK){
                al_stop_sample_instance(walkSound);
            }else if(state == PenguinState::SLIDE){
                al_stop_sample_instance(slideSound);
            }
            state = PenguinState::STOP;
        }else{
            if(mode == GameMode::NORMAL){
                x -= walk_speed;
                state = PenguinState::WALK;
                al_set_sample_instance_playmode(walkSound, ALLEGRO_PLAYMODE_LOOP);
                al_attach_sample_instance_to_mixer(walkSound, al_get_default_mixer());
            }else if(mode == GameMode::ICE){
                x -= slide_speed;
                state = PenguinState::SLIDE;
                al_set_sample_instance_playmode(slideSound, ALLEGRO_PLAYMODE_LOOP);
                al_attach_sample_instance_to_mixer(slideSound, al_get_default_mixer());
            }
        }
    }else if(key_state[ALLEGRO_KEY_D] || key_state[ALLEGRO_KEY_RIGHT]){
        sprite_dir = PenguinState::RIGHT;
        if(x + hitbox_x/2 > window_width){
            //stop sound
            if(state == PenguinState::WALK){
                al_stop_sample_instance(walkSound);
            }else if(state == PenguinState::SLIDE){
                al_stop_sample_instance(slideSound);
            }
            state = PenguinState::STOP;
        }else{
            if(mode == GameMode::NORMAL){
                x += walk_speed;
                state = PenguinState::WALK;
                al_set_sample_instance_playmode(walkSound, ALLEGRO_PLAYMODE_LOOP);
                al_attach_sample_instance_to_mixer(walkSound, al_get_default_mixer());
            }else if(mode == GameMode::ICE){
                x += slide_speed;
                state = PenguinState::SLIDE;
                al_set_sample_instance_playmode(slideSound, ALLEGRO_PLAYMODE_LOOP);
                al_attach_sample_instance_to_mixer(slideSound, al_get_default_mixer());
            }
        }
    }//else if(counter == 0 || counter == draw_frequency-1){
        //state = PenguinState::STOP;
    //}

}

void
Penguin::Draw(){
    if(state == PenguinState::STOP){
        if(sprite_dir == PenguinState::LEFT){
            al_draw_bitmap(walkImg[0], x, y, ALLEGRO_FLIP_HORIZONTAL);
        }else{
            al_draw_bitmap(walkImg[0], x, y, 0);
        }
    }else if(state == PenguinState::WALK){
        if(sprite_dir == PenguinState::LEFT){
            al_draw_bitmap(walkImg[walk_pos], x, y, ALLEGRO_FLIP_HORIZONTAL);
        }else{
            al_draw_bitmap(walkImg[walk_pos], x, y, 0);
        }
    }else if(state == PenguinState::SLIDE){
        if(sprite_dir == PenguinState::LEFT){
            al_draw_bitmap(slideImg, x, y, ALLEGRO_FLIP_HORIZONTAL);
        }else{
            al_draw_bitmap(slideImg, x, y, 0);
        }
    }else if(state == PenguinState::HIT || state == PenguinState::DIE){
        if(sprite_dir == PenguinState::LEFT){
            //if(counter < hit_duration) al_draw_bitmap(hitImg, x, y, ALLEGRO_FLIP_HORIZONTAL);
            al_draw_bitmap(hitImg, x, y, ALLEGRO_FLIP_HORIZONTAL);
        }else{
            al_draw_bitmap(hitImg, x, y, 0);
        }
    }/*else if(state == PenguinState::DIE){
        ALLEGRO_BITMAP *frame = algif_get_bitmap(dieGif, al_get_time());
        if(frame){
            if(sprite_dir == PenguinState::LEFT){
                al_draw_bitmap(frame, x, y, ALLEGRO_FLIP_HORIZONTAL);
            }else{
                al_draw_bitmap(frame, x, y, 0);
            }
        }
    }*/
}
