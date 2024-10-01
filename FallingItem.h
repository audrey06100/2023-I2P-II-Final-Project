#ifndef FALLINGITEM_H_INCLUDED
#define FALLINGITEM_H_INCLUDED
#include <queue>
#include "Object.h"
#include "global.h"
//#include "Game.h"

enum class ItemState{
    STOP,
    MOVE,
    COLLIDE,
};

class FallingItem: public Object{
public:
    FallingItem(int vector_idx);
    virtual ~FallingItem();

    void Draw();
    void Process(ALLEGRO_EVENT);
    void Update();

    // Load bitmaps of image
    void LoadImg();
    // Load sound
    void LoadSound();

    int getX() {return this->x;}
    int getY() {return this->y;}
    int getHitboxX() {return this->hitbox_x;}
    int getHitboxY() {return this->hitbox_y;}
    int getHp() {return this->hp;}
    int getScore() {return this->score;}
    ItemState getState() {return this->state;}
    void getName(char *temp){
        strcpy(temp, class_name);
        return;
    }

    void setState(ItemState _state){
        this->state = _state;
    }

protected:
    char class_name[20];
    int x, y;
    int hitbox_x, hitbox_y; // width, height of the image
    int hp; //扣分是負的!!
    int score;
    int speed;
    int pause_total_sec; //total rest seconds
    int pause_curr_sec;
    int pause_cd_state; //0:沒在數了(obj已經出來)
    ItemState state = ItemState::STOP;

private:

    ALLEGRO_BITMAP *itemImg;
    ALLEGRO_SAMPLE_INSTANCE *itemSound;

};

//extern std::queue<FallingItem*> fallingItemSet[item_col_num];
extern FallingItem* fallingItemSet[row_num][item_num];
extern int loop_arrived_num; //跑最後一條了
extern int loop_special_flag; //全部跑完，要重新生items
extern int current_list_idx;

#endif
