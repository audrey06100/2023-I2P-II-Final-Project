#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Object.h"
#include "global.h"

class Menu : public Object{
public:
    Menu(GameScene);
    virtual ~Menu();

    GameScene Process(ALLEGRO_EVENT);
    void Draw();

private:
    GameScene scene = GameScene::MENU;

    ALLEGRO_FONT *small_font = NULL;
    ALLEGRO_FONT *big_font = NULL;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *menuSound = NULL;

    ALLEGRO_BITMAP *menu_background = NULL;
    ALLEGRO_BITMAP *button_img = NULL;
    ALLEGRO_BITMAP *about_img = NULL;

    int button_anime_font_size = 0;
    int button_anime_rest_cd = 0;
};
#endif
