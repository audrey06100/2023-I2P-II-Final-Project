#ifndef BONUSLETTERS_H_INCLUDED
#define BONUSLETTERS_H_INCLUDED
#include "FallingItem.h"

class BonusLetters : public FallingItem{
public:
    BonusLetters(int vector_idx, char letter) : FallingItem(vector_idx, letter){

        strncpy(class_name, "BonusLetters", 20);
        hp = 0;
        score = 0;
        speed = 5;

        LoadImg();
        LoadSound();
    }
};
#endif
