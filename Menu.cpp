#include "Menu.h"

Menu::Menu(GameScene scene){
    this->scene = scene;

    if(scene == GameScene::MENU){
        button_anime_font_size = 0;
        button_anime_rest_cd = 0;
        small_font = al_load_ttf_font("./font/Powersmash.ttf",30,0);
        big_font = al_load_ttf_font("./font/Powersmash.ttf",50,0);


        menu_background = al_load_bitmap("./image/menu.png");
        button_img = al_load_bitmap("./image/5.png");

        // Load sound
        sample = al_load_sample("./sound/canon.wav");
        menuSound = al_create_sample_instance(sample);
        // Loop the song until the display closes
        al_set_sample_instance_playmode(menuSound, ALLEGRO_PLAYMODE_LOOP);
        al_restore_default_mixer(); //???
        al_attach_sample_instance_to_mixer(menuSound, al_get_default_mixer());

        if( mute ){
            al_play_sample_instance(menuSound);
            mute = false;
        }else{
            al_stop_sample_instance(menuSound);
            mute = true;
        }

        printf("menu initialized\n");
    }else if(scene == GameScene::ABOUT){
        small_font = al_load_ttf_font("./font/Powersmash.ttf",30,0);
        menu_background = al_load_bitmap("./image/menu.png");
        about_img = al_load_bitmap("./image/about.png");
    }
}

Menu::~Menu(){
    if(scene == GameScene::MENU){
        al_destroy_font(small_font);
        al_destroy_font(big_font);
        al_destroy_bitmap(menu_background);
        al_destroy_bitmap(button_img);
        al_destroy_sample_instance(menuSound);
        //printf("[Menu] has been destroyed\n");
    }else if(scene == GameScene::ABOUT){
        al_destroy_bitmap(about_img);
        printf("[About] has been destroyed\n");
    }
}
GameScene
Menu::Process(ALLEGRO_EVENT event){
    if(scene == GameScene::MENU){
        //process keyboard event
        if( event.type == ALLEGRO_EVENT_KEY_UP ){
            if( event.keyboard.keycode == ALLEGRO_KEY_ENTER ){
                return GameScene::START;
            }else if( event.keyboard.keycode == ALLEGRO_KEY_A ){
                return GameScene::ABOUT;
            }else if( event.keyboard.keycode == ALLEGRO_KEY_Q || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE ){
                //tmp_msg = GAME_TERMINATE;
                return GameScene::QUIT;
            }
        }

        //process mouse event


    }else if(scene == GameScene::ABOUT){
        //process keyboard event
        if( event.type == ALLEGRO_EVENT_KEY_UP ){
            if( event.keyboard.keycode == ALLEGRO_KEY_B ){
                return GameScene::MENU;
            }
        }

        //process mouse event
    }

    //mute menu sound
    if( event.type == ALLEGRO_EVENT_KEY_UP ){
        if(event.keyboard.keycode == ALLEGRO_KEY_M){
            if( mute ){
                al_play_sample_instance(menuSound);
                mute = false;
            }else{
                al_stop_sample_instance(menuSound);
                mute = true;
            }
        }
    }
    return GameScene::NONE;
}

void
Menu::Draw(){
    if(scene == GameScene::MENU){
        al_draw_bitmap(menu_background, -310, 0, 0);
        //al_draw_bitmap(menu_background, -400, 0, ALLEGRO_FLIP_HORIZONTAL);
        //al_draw_bitmap(button_img, window_width/2-125, 160, ALLEGRO_FLIP_HORIZONTAL);
        //al_draw_bitmap(button_img, window_width/2-125, 260, ALLEGRO_FLIP_HORIZONTAL);
        //al_draw_bitmap(button_img, window_width/2-125, 360, ALLEGRO_FLIP_HORIZONTAL);


        if(button_anime_font_size == 0){
            button_anime_rest_cd++;
        }
        if(button_anime_rest_cd >= 40){
            if(button_anime_font_size < 20){
                al_draw_text(al_load_ttf_font("./font/Powersmash.ttf",button_anime_font_size++,0), al_map_rgb(255,255,255), window_width/2-140, 140 , ALLEGRO_ALIGN_LEFT, "'A' : about");
                al_draw_text(al_load_ttf_font("./font/Powersmash.ttf",button_anime_font_size++,0), al_map_rgb(255,255,255), window_width/2-140, 200 , ALLEGRO_ALIGN_LEFT, "'Enter' : start");
                al_draw_text(al_load_ttf_font("./font/Powersmash.ttf",button_anime_font_size++,0), al_map_rgb(255,255,255), window_width/2-140, 260 , ALLEGRO_ALIGN_LEFT, "'Q' : quite");
            }else{
                al_draw_text(small_font, al_map_rgb(255,255,255), window_width/2-140, 140 , ALLEGRO_ALIGN_LEFT, "'A' : about");
                al_draw_text(small_font, al_map_rgb(255,255,255), window_width/2-140, 200 , ALLEGRO_ALIGN_LEFT, "'Enter' : start");
                al_draw_text(small_font, al_map_rgb(255,255,255), window_width/2-140, 260 , ALLEGRO_ALIGN_LEFT, "'Q' : quite");
            }
        }

    }else if(scene == GameScene::ABOUT){
        al_draw_bitmap(menu_background, -310, 0, 0);
        //al_draw_bitmap(white_back_img, 50, 100, 0);
        //al_draw_text(big_font, al_map_rgb(50, 50, 50), window_width/2, 120 , ALLEGRO_ALIGN_CENTRE, "about");
        al_draw_bitmap(about_img, 50, 100, 0);

        al_draw_text(small_font, al_map_rgb(0, 0, 0), window_width/2, 520 , ALLEGRO_ALIGN_CENTRE, "'B' : back");

    }
}
