#include "FallingItem.h"

//std::queue<FallingItem*> fallingItemSet[item_col_num];
FallingItem* fallingItemSet[row_num][item_num];
int loop_arrived_num = 0;
int loop_special_flag = 0;
int current_list_idx = 0;

FallingItem::FallingItem(int vector_idx){

    x = (window_width/row_num+1)* vector_idx;
    y = 0;

    pause_total_sec = rand()%300; //???
    pause_curr_sec = 0;
    pause_cd_state = 1;
    state = ItemState::STOP;
}

FallingItem::~FallingItem(){
    al_destroy_bitmap(itemImg);
    al_destroy_sample_instance(itemSound);
}

void
FallingItem::LoadImg(){
    char temp[50];
    ALLEGRO_BITMAP *img;
    if(!strcmp(class_name, "Coin") || !strcmp(class_name, "SnowBall")){
        int tmp_rand = rand()%2+1;
        sprintf(temp, "./image/%s_%d.png", class_name, tmp_rand);
        img = al_load_bitmap(temp);
        if(img)
            itemImg = img;
        else
            printf("[FallingItem] no %s image!!\n", class_name);
        this->hp *= tmp_rand;
        this->score *= tmp_rand;
    }else{
        sprintf(temp, "./image/%s.png", class_name);
        img = al_load_bitmap(temp);
        if(img)
            itemImg = img;
        else
            printf("[FallingItem] no %s image!!\n", class_name);
    }
    this->hitbox_x = al_get_bitmap_width(itemImg);
    this->hitbox_y = al_get_bitmap_height(itemImg);
}

void
FallingItem::LoadSound(){
    char temp[50];
    sprintf(temp, "./sound/%s.wav", class_name);
    ALLEGRO_SAMPLE *sample = al_load_sample(temp);
    if(sample)
        itemSound = al_create_sample_instance(sample);
    else
        printf("[FallingItem] no %s sound!!\n", class_name);
    al_reserve_samples(20);
    al_set_sample_instance_playmode(itemSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(itemSound, al_get_default_mixer());
}

void
FallingItem::Update(){
    if(state == ItemState::MOVE){
        if(y+hitbox_y >= floor_height){
            state = ItemState::STOP;
            loop_arrived_num++;
        }else{
            if(!strcmp(class_name, "Seal")) x += 3;
            y += speed;
        }
    }else if(state == ItemState::COLLIDE){
        loop_arrived_num++;
        state = ItemState::STOP;
    }
}

void
FallingItem::Process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){

            if(pause_cd_state == 1){
                if(pause_curr_sec == pause_total_sec){
                    state = ItemState::MOVE;
                    pause_curr_sec = -1;
                    pause_cd_state = 0;
                }else pause_curr_sec++;
            }
        }
    }
}

void
FallingItem::Draw(){
    if(state == ItemState::MOVE){
        al_draw_bitmap(itemImg, x, y, ALLEGRO_FLIP_HORIZONTAL); //0???
    }else if(state == ItemState::COLLIDE){
        al_play_sample_instance(itemSound);
        state = ItemState::STOP;
    }
}
