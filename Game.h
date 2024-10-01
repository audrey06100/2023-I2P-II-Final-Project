#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <vector>
#include "global.h"
#include "DataCenter.h"
//#include "Object.h"

class Game : public Object{
public:
    Game(GameScene, GameMode=GameMode::NORMAL);
    virtual ~Game();

    void Draw();
    void Update(int);
    GameScene Process(ALLEGRO_EVENT);

private:
    GameScene scene = GameScene::LEVEL_1;
    GameMode mode = GameMode::NORMAL;

    ALLEGRO_FONT *small_font = NULL;
    ALLEGRO_FONT *big_font = NULL;

    ALLEGRO_BITMAP *previous_background = NULL;
    ALLEGRO_BITMAP *white_back_img = NULL;

    Penguin& penguin = DC->get_Penguin();

    int hp = 5;
    int score = 0;

    int start_time_cd = 3;
    int left_time_cd = 60;

};

extern int rest_time_cd;

#endif
