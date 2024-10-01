#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "DataCenter.h"
#include "Object.h"
#include "global.h"

class Background: public Object{
public:
    Background(GameScene);
    virtual ~Background();

    void Draw();
    void Update();
    void Process(ALLEGRO_EVENT);

    int getWidth() {return width;}
    int getHeight() {return height;}

private:
    GameScene scene = GameScene::LEVEL_1;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *backgroundSound;
    //ALLEGRO_FONT *background_font = NULL;

    double x = 0;
    double y = 0;
    int width;
    int height;
    ALLEGRO_BITMAP *backgroundImg; //normal, bonus
};
#endif
