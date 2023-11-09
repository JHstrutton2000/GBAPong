#include <gb/gb.h>
#include <gb/drawing.h>

#include <stdio.h>
#include <stdlib.h>
#include <rand.h>

#include "sprites.c"

const INT16 width = 160; 
const INT16 height = 140;

const INT8 xoff = 10;
const INT8 yoff = 15;

INT16 Ballxpos = 88;
INT16 Ballypos = 78;

INT16 PrevBallx =0;
INT16 PrevBally =0;

INT8 Ballxvel = 0;
INT8 Ballyvel = 0;

INT16 PaddleAypos = 75;
INT8 PaddleAyvel = 0;

INT16 PaddleBypos = 75;
INT8 PaddleByvel = 0;

INT8 DistinceFromWall = 10;

BOOLEAN running = 0;

void updateSpritePositions(){
    move_sprite(_ball, Ballxpos, Ballypos);
    
    move_sprite(_paddleATop,    DistinceFromWall, PaddleAypos - 8);
    move_sprite(_paddleAMiddle, DistinceFromWall, PaddleAypos + 0);
    move_sprite(_paddleABottom, DistinceFromWall, PaddleAypos + 8);

    move_sprite(_paddleBTop,    width-DistinceFromWall, PaddleBypos - 8);
    move_sprite(_paddleBMiddle, width-DistinceFromWall, PaddleBypos + 0);
    move_sprite(_paddleBBottom, width-DistinceFromWall, PaddleBypos + 8);
}

void initSprites(){
    set_sprite_data(_ball, _ballTileCount, Ball);
    set_sprite_tile(_ball, _ballTileIndex);

    set_sprite_data(_paddleATop, _paddleTileCount, Paddle);
    set_sprite_tile(_paddleATop, _paddleTileIndex);

    set_sprite_data(_paddleAMiddle, _paddleTileCount, Paddle);
    set_sprite_tile(_paddleAMiddle, _paddleTileIndex);

    set_sprite_data(_paddleABottom, _paddleTileCount, Paddle);
    set_sprite_tile(_paddleABottom, _paddleTileIndex);

    set_sprite_data(_paddleBTop, _paddleTileCount, Paddle);
    set_sprite_tile(_paddleBTop, _paddleTileIndex);

    set_sprite_data(_paddleBMiddle, _paddleTileCount, Paddle);
    set_sprite_tile(_paddleBMiddle, _paddleTileIndex);

    set_sprite_data(_paddleBBottom, _paddleTileCount, Paddle);
    set_sprite_tile(_paddleBBottom, _paddleTileIndex);

    SHOW_SPRITES;
}

void score(){
    //Ballxvel = -Ballxvel;
    running = 0;

    srand((unsigned) (Ballxpos * Ballxvel + Ballypos * Ballxvel));

    // PrevBallx = Ballxpos * Ballxvel;
    // PrevBally = Ballypos * Ballxvel;

    Ballxvel = 0;
    Ballyvel = 0;


    Ballxpos = 88;
    Ballypos = 78;

    PaddleAypos = 75;
    PaddleAyvel = 0;

    PaddleBypos = 75;
    PaddleByvel = 0;
}

void AIMove(){
    PaddleBypos = Ballypos;

    PaddleByvel = ((Ballypos-8) - (PaddleBypos-12));
    if(PaddleByvel > 5)
        PaddleByvel = 5;
}

BOOLEAN UpPressed = 0;
BOOLEAN DownPressed = 0;

void PlayerMove(){
    if (joypad() & J_UP)
        UpPressed = 1;
    else
        UpPressed = 0;

    if (joypad() & J_DOWN) 
        DownPressed = 1;
    else
        DownPressed = 0;

    if(UpPressed)
        PaddleAyvel = -5;
    else if(DownPressed)
        PaddleAyvel = 5;
    else
        PaddleAyvel = 0;
}

// void clearBack(){
//     // Set up background display
//     set_bkg_data(0, 1, &color); // Load a color into the background palette

//     // Clear the screen
//     memset((UINT8*)0x9800, 0, 0x1800); // Clear the VRAM

//     gotoxy(10, height-10);

//     printf("Hello, Game Boy!");
// }

void main(){
    init();
    initSprites();
    rand(0x100);

    while(1){
        PlayerMove();
        // clearBack();
        if(running == 1){
            AIMove();

            if(Ballxpos > width || Ballxpos-8 < 0)
                score();
            if(Ballypos-8 > height || Ballypos-16 < 0)
                Ballyvel = -Ballyvel;

            if(Ballxvel > 0 && Ballxpos >= width-DistinceFromWall-4 && Ballypos-13 <= PaddleBypos && Ballypos-13 >= PaddleBypos-24){
                Ballxvel = -Ballxvel;
                Ballyvel += Ballypos - PaddleBypos;
            }
            else if(Ballxvel < 0 && Ballxpos-8 <= DistinceFromWall-4 && Ballypos-13 <= PaddleAypos && Ballypos-13 >= PaddleAypos-24){
                Ballxvel = -Ballxvel;
                Ballyvel += Ballypos - PaddleBypos;
            }

            if(Ballyvel == 0)
                Ballyvel++;

            if(Ballyvel > 5)
                Ballyvel = 5;
            else if(Ballyvel < -5)
                Ballyvel = -5;
                
            if(Ballxvel > 5)
                Ballxvel = 5;
            else if(Ballxvel < -5)
                Ballxvel = -5;

            if(PaddleAyvel > 0 && PaddleAypos > height)
                PaddleAypos = height;
            else if(PaddleAyvel < 0 && PaddleAypos-8 < yoff)
                PaddleAypos = yoff + 8;

            if( PaddleByvel > 0 && PaddleBypos > height)
                PaddleBypos = height;
            else if( PaddleByvel < 0 && PaddleBypos-8 < yoff)
                PaddleBypos = yoff + 8;
            // line(DistinceFromWall-4, PaddleAypos-24, width-DistinceFromWall-4, PaddleBypos-24);//top
            // line(DistinceFromWall-4, PaddleAypos,    width-DistinceFromWall-4, PaddleBypos);//bottom

            // circle(Ballxpos, Ballypos-13, 1, 1);

            // circle(Ballxpos-8, Ballypos-8 , 1, 1);//top left corner of ball
            // circle(Ballxpos-8, Ballypos-16, 1, 1);//bottom left corner of ball
            // circle(Ballxpos  , Ballypos-8 , 1, 1);//top right corner of ball
            // circle(Ballxpos  , Ballypos-16, 1, 1);//bottom right corner of ball

            Ballxpos += Ballxvel;
            Ballypos += Ballyvel;

            PaddleAypos += PaddleAyvel;
            PaddleBypos += PaddleByvel;
        }
        else if(PaddleAyvel != 0){
            running = 1;

            while(Ballxvel == 0){
                Ballxvel = rand() % 10 -5;
            }
            
            while(Ballyvel == 0){
                Ballyvel = rand() % 10 -5;
            }
        }

        updateSpritePositions();
        
        delay(20);
    }
}