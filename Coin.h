#ifndef COIN_H_INCLUDED
#define COIN_H_INCLUDED
#include "FallingItem.h"

class Coin : public FallingItem{
public:
    Coin(int vector_idx) : FallingItem(vector_idx){

        strncpy(class_name, "Coin", 20);
        hp = 0;
        score = 5;
        speed = 5;

        LoadImg();
        LoadSound();
    }
};
#endif
