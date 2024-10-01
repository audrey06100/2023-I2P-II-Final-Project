#ifndef DATACENTER_H_INCLUDED
#define DATACENTER_H_INCLUDED
#include <vector>
#include <queue>
#include "Penguin.h"
#include "FallingItem.h"

class DataCenter{
public:
    /*std::vector<std::queue<FallingItem*>>& get_FallingItem(){
        return fallingItemSet;
    }*/
    /*std::queue<FallingItem*>* get_FallingItem(){
        return fallingItemSet;
    }*/

    Penguin& get_Penguin() {return penguin;}

private:
    //std::vector<std::queue<FallingItem*>> fallingItemSet;
    //std::queue<FallingItem*> fallingItemSet[item_col_num];
    Penguin penguin;

};

extern DataCenter* const DC;

#endif
