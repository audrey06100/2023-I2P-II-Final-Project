#include "GameWindow.h"

//bool rest = true;

void
GameWindow::game_init(){

    icon = al_load_bitmap("./image/icon_penguinjump.png");
    al_set_display_icon(display, icon);
    al_reserve_samples(20); // voice mixer

    //load previous highest score
    FILE * fp = fopen("./txt/highest_score.txt", "r");
    fscanf(fp, "%d", &highest_score);
    previous_highest = highest_score;
    if(!fp) printf("failed to load file.\n");

}

void
GameWindow::show_err_msg(int msg){
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...\n");
    else
        fprintf(stderr, "unexpected msg: %d\n", msg);

    game_destroy();
    exit(9);
}

GameWindow::GameWindow(){
    if (!al_init())
        show_err_msg(-1);
    printf("Game Initializing...\n");
    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();

    fps = al_create_timer(1.0 / FPS);
    left_time_fps = al_create_timer(1.0);

    if(fps == NULL)
        show_err_msg(-1);

    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);

    al_set_window_position(display, 400, 0);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    al_register_event_source(event_queue, al_get_display_event_source( display ));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(fps));
    al_register_event_source(event_queue, al_get_timer_event_source(left_time_fps));

    game_init();
}

void
GameWindow::create_fallingitem(GameScene scene){
    loop_arrived_num = 0;
    loop_special_flag = 0;

    int total_debuff[item_num] = {0}; // debuff item in same row
    int current = 0;

    for(int i=0; i<row_num; i++){
        for(int j=0; j<item_num; j++){
            //printf("-----[%d, %d]-----\n", i, j);
            current = rand()%5; //snowball, seal, coin

            //if(current==SEAL) current = rand()%2;
            if(current==FISH || current==ICECUBE) current = rand()%5;
            if(current==FISH || current==ICECUBE) current = rand()%5;

            if(current==SNOWBALL || current==SEAL){
                total_debuff[j]++;
                while(total_debuff[j]>=4 && (current==SNOWBALL||current==SEAL)) current = rand()%3;
                if(total_debuff[j] >= 4) total_debuff[j] = 0;
            }
            while(scene==GameScene::LEVEL_1 && current==SEAL) current = rand()%3;

            switch(current){
            case SNOWBALL:
                fallingItemSet[i][j] = new SnowBall(i);
                break;
            case SEAL:
                fallingItemSet[i][j] = new Seal(i);
                break;
            case COIN:
                fallingItemSet[i][j] = new Coin(i);
                break;
            case FISH:
                fallingItemSet[i][j] = new Fish(i);
                break;
            case ICECUBE:
                fallingItemSet[i][j] = new IceCube(i);
                break;
            default:
                printf("error occurred in function create_fallingitem()\n");
            }

            /*if(i == row_num-1){
                int temp_i = 0;

                //insert fish
                if(j%4==0){
                    temp_i = rand()%3;
                    printf("tempi = %d\n", temp_i);
                    delete fallingItemSet[temp_i][j];
                    fallingItemSet[temp_i][j] = new Fish(i);
                }
                //insert ice cube
                if(j%3==0){
                    temp_i = rand()%7;
                    delete fallingItemSet[temp_i][j];
                    fallingItemSet[temp_i][j] = new IceCube(i);
                }
            }*/
        }
    }
}

void
GameWindow::process_fallingitem(ALLEGRO_EVENT event, GameScene scene){
    if( event.type == ALLEGRO_EVENT_TIMER ){

        if(loop_arrived_num >= row_num && loop_special_flag){
            loop_special_flag = 0;

            if(current_list_idx < item_num-1){
                loop_arrived_num = 0;
                current_list_idx++;
            }else{
                for(int i=0; i<row_num; i++)
                    for(int j=0; j<item_num; j++)
                        delete fallingItemSet[i][j];
                create_fallingitem(scene);
            }
        }
        if(loop_arrived_num >= row_num){
            if(current_list_idx < item_num-1){
                loop_arrived_num = 0;
                current_list_idx++;
            }else{
                for(int i=0; i<row_num; i++)
                    for(int j=0; j<item_num; j++)
                        delete fallingItemSet[i][j];
                create_fallingitem(scene);
            }
        }else loop_special_flag = 1;
    }
}

void
GameWindow::game_play(){
    int msg = 0;

    srand(time(NULL));

    game_begin();

    while ( msg != GAME_TERMINATE ) {
        msg = game_run();
        if ( msg == GAME_TERMINATE || judge_next_window == GameScene::QUIT){
            printf( "Quit Game\n" );
            msg = GAME_TERMINATE;
        }
    }

    show_err_msg(msg);
}

void
GameWindow::game_begin(){

    // set the volume of instance
    //al_set_sample_instance_gain(menuSound, 1);

    al_start_timer(fps);
    al_start_timer(left_time_fps);

    // initialize the menu before entering the loop
    menu = new Menu(GameScene::MENU);
}

int
GameWindow::game_run(){
    int error = 0;
    if( draw ){
        game_draw();
        draw = false;
    }
    if ( !al_is_event_queue_empty(event_queue) ) {
        error = process_event();
    }
    return error;
}

void
GameWindow::game_update(){
    //printf("update\n");

    if( judge_next_window != GameScene::NONE ){
        if( window == GameScene::MENU ){ //current window

            // initialize next scene
            if(judge_next_window == GameScene::ABOUT){
                delete menu;
                window = judge_next_window;
                menu = new Menu(window);
            }else if(judge_next_window == GameScene::START){
                delete menu;
                window = judge_next_window;
                game = new Game(window);
            }

        }else if( window == GameScene::ABOUT ){ //current window
            if(judge_next_window == GameScene::MENU){
                delete menu;
                window = judge_next_window;
                menu = new Menu(window);
            }
        }else if( window == GameScene::START ){ //current window
            if(judge_next_window == GameScene::LEVEL_1){
                delete game;
                window = judge_next_window;
                game = new Game(window);
                background = new Background(window);
                DC->get_Penguin().Init();
                create_fallingitem(window);
                printf("level 1 initialized\n");
            }
        }else if( window == GameScene::LEVEL_1 ){ //current window
            delete game;
            delete background;
            for(int i=0; i<row_num; i++){
                for(int j=0; j<item_num; j++){
                    delete fallingItemSet[i][j];
                }
            }
            if(judge_next_window == GameScene::MENU){ //Press Q/Escape
                window = judge_next_window;
                menu = new Menu(window);
            }else if(judge_next_window == GameScene::LEVEL_2){ //pass level 1
                window = judge_next_window;
                game = new Game(window);
                background = new Background(window);
                create_fallingitem(window);
                printf("level 2 initialized\n");

            }else if(judge_next_window == GameScene::WIN || judge_next_window == GameScene::LOSE){
                window = judge_next_window;
                game = new Game(window);
            }
        }else if( window == GameScene::LEVEL_2 ){ //current window
            delete game;
            delete background;
            for(int i=0; i<row_num; i++){
                for(int j=0; j<item_num; j++){
                    delete fallingItemSet[i][j];
                }
            }

            if(judge_next_window == GameScene::MENU){ //Press Q/Escape
                window = judge_next_window;
                menu = new Menu(window);
            }else if(judge_next_window == GameScene::WIN || judge_next_window == GameScene::LOSE){
                window = judge_next_window;
                game = new Game(window);
            }
        }else if( window == GameScene::WIN ){ //current window
            if(judge_next_window == GameScene::MENU){
                delete game;
                window = judge_next_window;
                menu = new Menu(window);
            }
        }else if( window == GameScene::LOSE ){ //current window
            delete game;

            if(judge_next_window == GameScene::MENU){
                window = judge_next_window;
                menu = new Menu(window);
            }else if(judge_next_window == GameScene::START){ //play again
                window = judge_next_window;
                game = new Game(window);
            }
        }

        judge_next_window = GameScene::NONE;
    }

    if( window == GameScene::LEVEL_1 || window == GameScene::LEVEL_2){
        background->Update();
        DC->get_Penguin().Update();
        for(int i=0; i<row_num; i++){
            game->Update(i);
            fallingItemSet[i][current_list_idx]->Update();
        }
    }
}

int
GameWindow::process_event(){
    //printf("process\n");
    GameScene tmp_next_window;

    // Request the event
    al_wait_for_event(event_queue, &event);

    // process the event of other component
    if( window == GameScene::MENU || window == GameScene::ABOUT ){
        tmp_next_window = menu->Process(event);

    }else if( window == GameScene::START || window == GameScene::WIN || window == GameScene::LOSE ){
        tmp_next_window = game->Process(event);

    }else if( window == GameScene::LEVEL_1 || window == GameScene::LEVEL_2){
        tmp_next_window = game->Process(event);
        DC->get_Penguin().Process(event);
        background->Process(event);
        if(rest_time_cd <= 0){
            process_fallingitem(event, window);
            for(int i=0; i<row_num; i++){
                fallingItemSet[i][current_list_idx]->Process(event);
            }
        }
    }
    if(tmp_next_window != GameScene::NONE){
        judge_next_window = tmp_next_window;
    }

    // Shutdown our program
    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        return GAME_TERMINATE;
    }else if(event.type == ALLEGRO_EVENT_TIMER){
        if(event.timer.source == fps)
            draw = true;
    }
    if(draw) game_update();
    return 0;
}

void
GameWindow::game_draw(){
    if( window == GameScene::MENU || window == GameScene::ABOUT){
        menu->Draw();
    }else if( window == GameScene::START || window == GameScene::WIN || window == GameScene::LOSE ){
        game->Draw();
    }else if( window == GameScene::LEVEL_1 || window == GameScene::LEVEL_2){
        background->Draw();
        DC->get_Penguin().Draw();
        game->Draw();
        for(int i=0; i<row_num; i++){
            fallingItemSet[i][current_list_idx]->Draw();
        }
    }
    al_flip_display();
}

void
GameWindow::game_destroy() {

    // Make sure you destroy all things
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    al_destroy_timer(fps);
    al_destroy_timer(left_time_fps);
    delete menu;
}
