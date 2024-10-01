#ifndef HERO_H_INCLUDED
#define HERO_H_INCLUDED

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "./algif5/src/algif.h"
#include <vector>
#include "global.h"

enum class PenguinState{
    LEFT,
    RIGHT,
    STOP,
    WALK,
    SLIDE,
    HIT,
    DIE,
};

class Penguin{
public:
    Penguin() = default;

    int getX() {return this->x;}
    int getY() {return this->y;}
    int getHitboxX() {return this->hitbox_x;}
    int getHitboxY() {return this->hitbox_y;}

    void setMode(GameMode _mode){
        this->mode = _mode;
    }
    void setState(PenguinState _state){
        this->state = _state;
    }

    void Init();
    void Process(ALLEGRO_EVENT);
    void Update();
    void Draw();

private:
    GameMode mode = GameMode::NORMAL;

    int x, y;
    int hitbox_x, hitbox_y; // width, height of the image
    int counter;
    PenguinState sprite_dir; // Left, Right
    PenguinState state; // STOP, MOVE, SLIDE, HIT, DIE
    PenguinState prev_state;
    ALLEGRO_SAMPLE *sample = NULL;

    // walk content
    int walk_speed;
    int walk_pos; // image 01~04
    std::vector<ALLEGRO_BITMAP*> walkImg;
    ALLEGRO_SAMPLE_INSTANCE *walkSound;
    //std::map<PenguinState, int> walkImgCount;

    // slide content
    int slide_start;
    int slide_speed;
    ALLEGRO_BITMAP *slideImg;
    ALLEGRO_SAMPLE_INSTANCE *slideSound;

    // get hit content
    //int hit_pos;
    int hit_duration;
    int hit_duration_cd; //countdown
    ALLEGRO_BITMAP *hitImg;
    ALLEGRO_SAMPLE_INSTANCE *hitSound;

    // die content
    int die_duration;
    int die_duration_cd;
    ALGIF_ANIMATION *dieGif; //or image!!!
    ALLEGRO_SAMPLE_INSTANCE *dieSound;
};
#endif
