#ifndef ICECUBE_H_INCLUDED
#define ICECUBE_H_INCLUDED
#include "FallingItem.h"

class IceCube : public FallingItem{
public:
    IceCube(int vector_idx) : FallingItem(vector_idx){

        strncpy(class_name, "IceCube", 20);
        hp = 0;
        score = 0;
        speed = 7;

        LoadImg();
        LoadSound();
    }
};
#endif
