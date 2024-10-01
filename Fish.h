#ifndef FISH_H_INCLUDED
#define FISH_H_INCLUDED
#include "FallingItem.h"

class Fish : public FallingItem{
public:
    Fish(int vector_idx) : FallingItem(vector_idx){

        strncpy(class_name, "Fish", 20);
        hp = 1;
        score = 0;
        speed = 7;

        LoadImg();
        LoadSound();
    }
};
#endif
