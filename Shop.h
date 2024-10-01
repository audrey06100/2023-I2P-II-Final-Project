#ifndef SHOP_H_INCLUDED
#define SHOP_H_INCLUDED
#include "global.h"

class Shop : public Object{
public:
    Shop();
    virtual ~Shop();

    void Reset();
    void Draw();

    GameScene Process(ALLEGRO_EVENT);

private:

};
#endif
