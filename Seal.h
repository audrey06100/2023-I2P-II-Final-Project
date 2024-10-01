#ifndef SEAL_H_INCLUDED
#define SEAL_H_INCLUDED
#include "FallingItem.h"

class Seal : public FallingItem{
public:
    Seal(int vector_idx) : FallingItem(vector_idx){

        strncpy(class_name, "Seal", 20);
        hp = -10;
        score = 0;
        speed = 10;
        x -= 100;

        LoadImg();
        LoadSound();
    }
};
#endif
