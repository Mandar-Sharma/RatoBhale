#include"menu.h"
#include<stdlib.h>
#include<iostream>
#include "SDL/SDL_image.h"
#include "SDL/SDL.h"
#include<string>
#include "SDL/SDL_ttf.h"
#include<math.h>
#include<SDL/SDL_mixer.h>
#include<time.h>
#include<stdio.h>
#include<sys/time.h>

struct timeval tv;


using namespace std;
//The attributes of the screen
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;


//The surfaces that will be used
SDL_Surface *bhale = NULL;
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *score=NULL;
SDL_Surface *thescore=NULL;
SDL_Surface *drop=NULL;
SDL_Surface *thedrop=NULL;
SDL_Surface *khukuri=NULL;
SDL_Surface *khukuri2=NULL;
SDL_Surface *timetext=NULL;
SDL_Surface *timesec=NULL;
SDL_Surface *timemin=NULL;
SDL_Surface *timehr=NULL;
SDL_Surface *gameover=NULL;
SDL_Rect clip[ 8 ];

//The font being used
TTF_Font *font = NULL;
//The color of the font
SDL_Color textColor = { 255, 255, 255 };

//The music that will be played
Mix_Music *music = NULL;

//The sound effects that will be used

Mix_Chunk *thokyo=NULL;
Mix_Chunk *kaa=NULL;

class startandendstuff
{
public:
    bool startstuff()
    {
            //Start SDL
        if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        {
            return 1;
        }
        //Initialize SDL_ttf
        if( TTF_Init() == -1 )
        {
            return false;
        }
        //Set up screen

        screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

        //Open the font
        font = TTF_OpenFont( "font.ttf", 40);

         //Initialize SDL_mixer
        if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
        {
            return false;
        }
        //If there was an error in setting up the screen
        if( screen == NULL )
        {
            return 1;
        }

        SDL_WM_SetCaption("The Rato Bhale Saga",NULL);


        //If everything initialized fine
        return true;
        }
        void endstuff()
    {
             //Free the surfaces
        SDL_FreeSurface( bhale );
        SDL_FreeSurface( background );
        SDL_FreeSurface(score);
        SDL_FreeSurface(thescore);
        SDL_FreeSurface(drop);
        SDL_FreeSurface(thedrop);
        SDL_FreeSurface(khukuri);
        SDL_FreeSurface(khukuri2);
        SDL_FreeSurface(timetext);
        SDL_FreeSurface(timesec);
        SDL_FreeSurface(timehr);
        SDL_FreeSurface(timemin);
        //Close the font that was used
        TTF_CloseFont( font );

        //Quit SDL_ttf
        TTF_Quit();
         //Free the sound effects
        Mix_FreeChunk( kaa );
        Mix_FreeChunk( thokyo );
        //Free the music
        Mix_FreeMusic( music );
         //Quit SDL_mixer
        Mix_CloseAudio();

    }
};
class image
{
public:
    SDL_Surface *load_image(std::string filename)
    {
        //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If nothing went wrong in loading the image
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );
        if( optimizedImage != NULL )
        {
            //Map the color key
           //Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xFF, 0xFF, 0xFF );

            //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
            //SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }
    }

    //Return the optimized image
    return optimizedImage;
    };

    void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination,SDL_Rect* clip = NULL )
    {
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;
    //Blit the surface
    SDL_BlitSurface( source, clip, destination, &offset );
    };
};

class collision
{
public:
    bool check(SDL_Rect A,SDL_Rect B)
    {
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;

    }
};


int main( int argc, char* args[] )
{
    //homescreen makemenu;
    //makemenu.homepage();

    startandendstuff in;
    in.startstuff();

    collision co;
    Uint8 *keys=NULL;
    SDL_Event event;


    int flow=1;
    int scorecount=0;
    int dropcount=0;
    char showscore[10000];
    char showdrop [10000];
    char secc[10000];
    char minc[10000];
    char hrc[10000];
    //Load the music
    music = Mix_LoadMUS( "bhaletheme.wav" );
     //Load the sound effects
    kaa = Mix_LoadWAV( "Kaa.wav" );
    thokyo=Mix_LoadWAV("thokyo.wav");


    clip[ 0 ].x = 0;
    clip[ 0 ].y = 0;
    clip[ 0 ].w = 100;
    clip[ 0 ].h = 100;

    //Clip range for the top right
    clip[ 1 ].x = 100;
    clip[ 1 ].y = 0;
    clip[ 1 ].w = 100;
    clip[ 1 ].h = 100;

    //Clip range for the bottom left
    clip[ 2 ].x = 200;
    clip[ 2 ].y = 0;
    clip[ 2 ].w = 100;
    clip[ 2 ].h = 100;

    //Clip range for the bottom right
    clip[ 3 ].x = 300;
    clip[ 3 ].y = 0;
    clip[ 3 ].w = 100;
    clip[ 3 ].h = 100;

    clip[ 4 ].x = 0;
    clip[ 4 ].y = 100;
    clip[ 4 ].w = 100;
    clip[ 4 ].h = 100;

    clip[ 5 ].x = 100;
    clip[ 5 ].y = 100;
    clip[ 5 ].w = 100;
    clip[ 5 ].h = 100;

    clip[ 6 ].x = 200;
    clip[ 6 ].y = 100;
    clip[ 6 ].w = 100;
    clip[ 6 ].h = 100;

    clip[ 7 ].x = 300;
    clip[ 7 ].y = 100;
    clip[ 7 ].w = 100;
    clip[ 7 ].h = 100;

    //Render the text
    score = TTF_RenderText_Solid( font, "Score", textColor );
    //thescore = TTF_RenderText_Solid( font, showscore, textColor );

    drop = TTF_RenderText_Solid( font, "Drop", textColor );
    timetext=TTF_RenderText_Solid(font,"Time : ",textColor);
    image fb;

    //Load the images
    background = fb.load_image( "backg.jpg" );
    gameover=fb.load_image("gameover.png");
    bhale=IMG_Load("bhales.png");
    khukuri=IMG_Load("khukuri.png");
    khukuri2=IMG_Load("khukuri.png");
    //Apply the background to the screen
/**<  */

    SDL_Flip(screen);
    int a=0;
    int b=0;
    int c=1;
    int t=0;
    int d=0;
    int e=0;
    int f=5;
    int g=835;
    int h=95;
    int u=600;

    int run=1;
         //Play the music
        if( Mix_PlayMusic( music, -1 ) == -1 )
        {
            return 1;
        }


    while(flow)

    {
        gettimeofday(&tv, NULL);
        int timer=tv.tv_sec+20700;
        int sec=timer%60;
        int hr=(timer/3600)%12;
		int min=(timer%3600)/60;
        int temp=h;
        fb.apply_surface( 0, 0, background, screen );
        fb.apply_surface(40,b,bhale,screen,&clip[a]);


        fb.apply_surface(g,h,khukuri,screen);
        fb.apply_surface(g,u,khukuri2,screen);
        itoa(scorecount,showscore,10);
        itoa(dropcount,showdrop,10);
        itoa(sec,secc,10);
        itoa(min,minc,10);
        itoa(hr,hrc,10);
        fb.apply_surface( 800, 20, score, screen );
        fb.apply_surface( 800, 60, drop, screen );
        fb.apply_surface(650,550,timetext,screen);
        thedrop = TTF_RenderText_Solid( font, showdrop, textColor );
        thescore = TTF_RenderText_Solid( font, showscore, textColor );
        timesec = TTF_RenderText_Solid( font, secc, textColor );
        timemin = TTF_RenderText_Solid( font, minc, textColor );
        timehr = TTF_RenderText_Solid( font, hrc, textColor );
        fb.apply_surface( 925, 20, thescore, screen );
        fb.apply_surface( 950, 60, thedrop, screen );
        fb.apply_surface(750,550,timehr,screen);
        fb.apply_surface(850,550,timemin,screen);
        fb.apply_surface(950,550,timesec,screen);
        SDL_Delay( 40 );
        SDL_Flip( screen );
        SDL_Rect bhaleplace;

            bhaleplace.x=40;
            bhaleplace.y=b;
            bhaleplace.h=80;
            bhaleplace.w=80;

        SDL_Rect khukurikata;

            khukurikata.x=g;
            khukurikata.y=h;
            khukurikata.h=27;
            khukurikata.w=150;

        SDL_Rect khukurikata2;

            khukurikata2.x=g;
            khukurikata2.y=u;
            khukurikata2.h=27;
            khukurikata2.w=150;

        SDL_Rect edge;

            edge.x=1;
            edge.y=1;
            edge.h=1000;
            edge.w=5;

         if((co.check(edge,khukurikata))==1)
         {

            h=rand()%570+60;
             g=835;

         }
         if((co.check(edge,khukurikata2))==1)
         {

            u=(rand()%570+60)-50;
             g=((rand()%675)+845);

         }

         if(((co.check(bhaleplace,khukurikata))==1)||(co.check(bhaleplace,khukurikata2))==1)
         {

            Mix_PlayChannel( -1, thokyo, 0 ) == 1;
            SDL_Delay(1100);
            in.endstuff();
            in.startstuff();
            gameover=IMG_Load("gameover.png");
            fb.apply_surface(0,0,gameover,screen);
            SDL_Delay(3000);
         }

        a=a+1;
        b=b+(c*t);
        d=d+1;
        g=g-15;

        if(d=25)
        {
            t=t+1;
            d=0;
        }
        if(a>=7)
           {
             a=0;
           }

            if(b>570)
        {
            dropcount=dropcount+1;
            b=0;
            t=0;
            d=0;

        }

        if(SDL_PollEvent(&event))
        {
            //If a key was pressed
            if(event.type==SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                case SDLK_SPACE:
                    {


                        scorecount=scorecount+1;
                        //Play kaa scratch effect
                        if( Mix_PlayChannel( -1, kaa, 0 ) == -1 )
                        {
                            return 1;
                        }
                        b=b-45;
                        for(e=0;e<5;e++)
                           {
                             b=b-(f*e);
                            }
                            if(b<=0)
                            {
                                b=0;
                            }
                    }

                d=0;
                e=0;
                t=0;
               }
            }
            if(event.type==SDL_QUIT || event.key.keysym.sym==SDLK_ESCAPE)
                {flow=0;}
        }

    }

    in.endstuff();
    //Quit SDL
    SDL_Quit();
    return 0;
}

