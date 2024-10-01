#include "Game.h"

int rest_time_cd = 3;

Game::Game(GameScene scene, GameMode mode){
    this->scene = scene;
    this->mode = mode;
    penguin.setMode(mode);

    small_font = al_load_ttf_font("./font/Powersmash.ttf",20,0);
    big_font = al_load_ttf_font("./font/Powersmash.ttf",50,0);

    if(scene == GameScene::START){
        start_time_cd = 3;
        hp = 5;
        score = 0;
        previous_score = 0;
    }else if(scene == GameScene::LEVEL_1){
        left_time_cd = 60;
        rest_time_cd = 3;
        hp = 5;
        score = 0;
    }else if(scene == GameScene::LEVEL_2){
        left_time_cd = 60;
        rest_time_cd = 3;
        hp = 5;
        score = previous_score;
    }else if(scene == GameScene::WIN || scene == GameScene::LOSE){
        char temp[50];
        sprintf(temp, "./image/background_%d.png", previous_scene);
        previous_background = al_load_bitmap(temp);
        white_back_img = al_load_bitmap("./image/white.png");
    }
}

Game::~Game(){
    //previous_hp = hp;
    previous_score = score;
    previous_scene = scene;
    if(highest_score > previous_highest){
        FILE *fp = fopen("./txt/highest_score.txt", "w");
        fprintf(fp, "%d", highest_score);
    }

    al_destroy_font(small_font);
    al_destroy_font(big_font);

    if(scene == GameScene::WIN || scene == GameScene::LOSE){
        al_destroy_bitmap(previous_background);
        al_destroy_bitmap(white_back_img);
    }

    //printf("[Game] has been destroyed\n");
}

void
Game::Update(int row){
    FallingItem* item = fallingItemSet[row][current_list_idx];
    if(item->getState() == ItemState::MOVE){
        //check if item collided with penguin
        if(item->getX()+item->getHitboxX()>penguin.getX()
           && item->getX()<penguin.getX()+penguin.getHitboxX()
           && item->getY()+item->getHitboxY()>penguin.getY()
           && item->getY()<penguin.getY()+penguin.getHitboxY()
           && item->getState() != ItemState::COLLIDE){
            item->setState(ItemState::COLLIDE);
            //printf("state = %d\n", (int)item->getState());

            hp += item->getHp();
            score += item->getScore();
            if(score > highest_score) highest_score = score;

            char temp[50];
            item->getName(temp);
            if(!strcmp(temp, "SnowBall")){
                penguin.setState(PenguinState::HIT);
            }else if(!strcmp(temp, "IceCube")){
                penguin.setMode(GameMode::ICE);
                penguin.setState(PenguinState::SLIDE);
            }else if(!strcmp(temp, "Seal")){
                hp = 0;
                penguin.setState(PenguinState::DIE);
            }
        }
    }
}

GameScene
Game::Process(ALLEGRO_EVENT event){

    if( event.type == ALLEGRO_EVENT_KEY_UP ){
        if( event.keyboard.keycode == ALLEGRO_KEY_Q || event.keyboard.keycode == ALLEGRO_KEY_ESCAPE ){
            return GameScene::MENU;
        }
    }
    if(scene == GameScene::START){
        if( event.type == ALLEGRO_EVENT_TIMER ){
            if( event.timer.source == left_time_fps && start_time_cd ){
                start_time_cd--;
                if(start_time_cd == 0){
                    return GameScene::LEVEL_1;
                }
            }
        }
    }else if(scene == GameScene::LEVEL_1 || scene == GameScene::LEVEL_2){
        if( event.type == ALLEGRO_EVENT_KEY_UP){
            if( event.keyboard.keycode == ALLEGRO_KEY_2 && scene == GameScene::LEVEL_1){
                return GameScene::LEVEL_2;
            }else if( event.keyboard.keycode == ALLEGRO_KEY_W ){
                return GameScene::WIN;
            }else if( event.keyboard.keycode == ALLEGRO_KEY_L ){
                return GameScene::LOSE;
            }else if( event.keyboard.keycode == ALLEGRO_KEY_S ){
                left_time_cd = 10;
            }
        }else if( event.type == ALLEGRO_EVENT_TIMER ){
            if( event.timer.source == left_time_fps){
                left_time_cd--;
                if(rest_time_cd > 0){
                    rest_time_cd--;
                }
            }
        }
        if( hp <= 0 ){
            printf("game over...\n");
            al_rest(0.5);
            return GameScene::LOSE;

        }else if( left_time_cd <= 0 ){
            if( scene == GameScene::LEVEL_1 ){
                return GameScene::LEVEL_2;
            }else if( scene == GameScene::LEVEL_2 ){
                return GameScene::WIN;
            }
        }
    }else if(scene == GameScene::LOSE){
        if( event.type == ALLEGRO_EVENT_KEY_UP ){
            if( event.keyboard.keycode == ALLEGRO_KEY_R ){
                return GameScene::START;
            }
        }
    }
    return GameScene::NONE;
}

void
Game::Draw(){
    char temp[50];

    if(scene == GameScene::START){
        al_clear_to_color(al_map_rgb(0, 0, 0));

        sprintf( temp, "%d", start_time_cd );
        al_draw_text(big_font, al_map_rgb(255, 255, 255), window_width/2, window_height/2-50 , ALLEGRO_ALIGN_CENTRE, temp);

    }else if(scene == GameScene::LEVEL_1 || scene == GameScene::LEVEL_2){
        if( left_time_cd > 57 ){
            sprintf(temp, "Level %d", (int)scene);
        }
        al_draw_text(big_font, al_map_rgb(255, 255, 255), window_width/2, window_height/2-50 , ALLEGRO_ALIGN_CENTRE, temp);

        sprintf( temp, "HP : %d", hp );
        al_draw_text(small_font, al_map_rgb(255,255,255), 270, 10 , ALLEGRO_ALIGN_LEFT, temp);
        sprintf( temp, "SCORE : %d", score );
        al_draw_text(small_font, al_map_rgb(255,255,255), 270, 30 , ALLEGRO_ALIGN_LEFT, temp);
        sprintf( temp, "HIGHEST : %d", highest_score );
        al_draw_text(small_font, al_map_rgb(255,255,255), 270, 50 , ALLEGRO_ALIGN_LEFT, temp);
        al_draw_rectangle(260, 0, window_width, 80, al_map_rgb(255, 255, 255), 3);

        sprintf( temp, "0 : %d", left_time_cd );
        al_draw_text(big_font, al_map_rgb(255, 255, 255), 20, 10 , ALLEGRO_ALIGN_LEFT, temp);

    }else if(scene == GameScene::WIN){
        al_draw_bitmap(previous_background, -310, 0, 0);
        al_draw_bitmap(white_back_img, 50, 100, 0);

        al_draw_text(big_font, al_map_rgb(255, 255, 255), window_width/2, window_height/2-20 , ALLEGRO_ALIGN_CENTRE, "victory");
        al_draw_text(small_font, al_map_rgb(0, 0, 0), window_width/2, window_height/2+120 , ALLEGRO_ALIGN_CENTRE, "'Q' : quit");
    }else if(scene == GameScene::LOSE){
        al_draw_bitmap(previous_background, -310, 0, 0);
        al_draw_bitmap(white_back_img, 50, 100, 0);

        al_draw_text(big_font, al_map_rgb(255, 0, 0), window_width/2, window_height/2-20 , ALLEGRO_ALIGN_CENTRE, "defeat");
        al_draw_text(small_font, al_map_rgb(0, 0, 0), window_width/2, window_height/2+100 , ALLEGRO_ALIGN_CENTRE, "'R' : restart");
        al_draw_text(small_font, al_map_rgb(0, 0, 0), window_width/2, window_height/2+120 , ALLEGRO_ALIGN_CENTRE, "'Q' : quit");
    }
}
