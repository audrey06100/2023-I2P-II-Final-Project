#ifndef SNOWBALL_H_INCLUDED
#define SNOWBALL_H_INCLUDED
#include "FallingItem.h"

class SnowBall : public FallingItem{
public:
    SnowBall(int vector_idx) : FallingItem(vector_idx){

        strncpy(class_name, "SnowBall", 20);
        hp = -1;
        score = 0;
        speed = 5;

        LoadImg();
        LoadSound();
    }

};
#endif
