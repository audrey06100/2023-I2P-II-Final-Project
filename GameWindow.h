#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <queue>
#include "DataCenter.h"
#include "global.h"
#include "Menu.h"
#include "Shop.h"
#include "Game.h"
#include "Penguin.h"
#include "Background.h"
#include "FallingItem.h"
#include "Coin.h"
#include "SnowBall.h"
#include "Fish.h"
#include "IceCube.h"
#include "Seal.h"

class GameWindow{
public:
    //constructor
    GameWindow();

    //each process of scene
    void game_init();
    void game_play();
    //void game_reset();
    void game_begin();

    void create_fallingitem(GameScene);
    void process_fallingitem(ALLEGRO_EVENT, GameScene);

    int process_event();
    void game_update();
    void game_draw();
    int game_run();

    void show_err_msg(int msg);
    void game_destroy();

private:
    ALLEGRO_BITMAP *icon;

    ALLEGRO_DISPLAY* display = NULL;

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;

    //ALLEGRO_SAMPLE *sample = NULL;
    //ALLEGRO_SAMPLE_INSTANCE *menuSound = NULL;

    Menu *menu = NULL;
    Game *game = NULL;

    Background *background = NULL;
    Penguin& penguin = DC->get_Penguin();
    //std::vector<std::queue<FallingItem*>>& fallingItemSet = DC->get_FallingItem();
    //std::queue<FallingItem*> fallingItemSet[item_col_num];// = DC->get_FallingItem();

    bool draw = false;
    bool mute = false;

    GameScene window = GameScene::MENU;
    GameScene judge_next_window = GameScene::NONE;
};
#endif
