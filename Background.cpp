#include "Background.h"

Background::Background(GameScene scene){
    this->scene = scene;

    char temp[50];

    // load background image
    sprintf(temp, "./image/background_%d.png", (int)scene);
    ALLEGRO_BITMAP *img = al_load_bitmap(temp);
    if(img)
        backgroundImg = img;
    else
        printf("[Background] no level %d image!!\n", (int)scene);

    // load game sound
    sprintf(temp, "./sound/background_%d.wav", (int)scene);
    sample = al_load_sample(temp);

    // load game sound
    al_reserve_samples(20);
    backgroundSound = al_create_sample_instance(sample);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());

    al_set_sample_instance_gain(backgroundSound, 1) ;
    al_play_sample_instance(backgroundSound);

    // initial the geometric information of background
    x = 0;
    y = 0;
    width = al_get_bitmap_width(backgroundImg);
    height = al_get_bitmap_height(backgroundImg);
}

Background::~Background(){
    al_destroy_sample_instance(backgroundSound);
    al_destroy_bitmap(backgroundImg);
}

void
Background::Update(){
    Penguin &penguin = DC->get_Penguin();
    if( key_state[ALLEGRO_KEY_A] || key_state[ALLEGRO_KEY_LEFT] ){
        if(penguin.getX() > -penguin.getHitboxX()/2) x += 0.5;
    }else if( key_state[ALLEGRO_KEY_D] || key_state[ALLEGRO_KEY_RIGHT] ){
        if(penguin.getX() < window_width-penguin.getHitboxX()/2) x -= 0.5;
    }
}

void
Background::Process(ALLEGRO_EVENT event){
    if(event.type == ALLEGRO_EVENT_KEY_UP){
        if(event.keyboard.keycode == ALLEGRO_KEY_M){
            if( mute ){
                al_play_sample_instance(backgroundSound);
                mute = false;
            }else{
                al_stop_sample_instance(backgroundSound);
                mute = true;
            }
        }
    }
}

void
Background::Draw(){
    al_draw_bitmap(backgroundImg, -310, 0, 0);
}
