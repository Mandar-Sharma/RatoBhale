#ifndef _menu.h
#define _menu.h
#include<iostream>
#include<fstream>
#include "SDL/SDL.h"
#include<SDL/SDL_image.h>
#include<string>
#include "SDL/SDL_ttf.h"
using namespace std;
class homescreen
{

  private:

    int flag1=0;
    int flag2=0;
    int flag3=0;
  public:

void homepage()
{


    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    TTF_Font*font=TTF_OpenFont("finalold.ttf",40);
    SDL_Surface*screen,*text1,*text2,*text3=NULL;
    screen=SDL_SetVideoMode(1000,600,32,SDL_SWSURFACE);

    bool running=true;
    const int FPS=30;
    Uint32 start;
    //SDL_Rect rect;
    SDL_Rect pos[2];
    pos[0].x=screen->clip_rect.w/2-30;
    pos[0].y=screen->clip_rect.h/2;
    pos[1].x=screen->clip_rect.w/2;
    pos[1].y=screen->clip_rect.h/2+30;
    pos[2].x=screen->clip_rect.w/2-10;
    pos[2].y=screen->clip_rect.h/2+60;
    //SDL_Rect rect1;
    //rect1.x=100;
    //rect1.y=200;
    //rect1.w=200;
    //rect1.h=200;

    //unsigned int color1=SDL_MapRGB(screen->format,0,0,0);
    //unsigned  int color=SDL_MapRGB(screen->format,0xff,0xff,0xff);
    SDL_Color  textcolor[3]= {{255,0,255},{0,0,255},{0,255,0}};

    text1=TTF_RenderText_Solid(font,"NEW GAME",textcolor[0]);
    text2=TTF_RenderText_Solid(font,"EXIT",textcolor[0]);
    text3=TTF_RenderText_Solid(font,"SCORE",textcolor[0]);
   // int text[3]={text1,text2,text3};
    int x;
    int y;
    while(running)
    {
        start=SDL_GetTicks();
        SDL_Event event;
        if(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                running=false;
                break;
            case SDL_MOUSEMOTION:
                x=event.motion.x;
                y=event.motion.y;
               if(x>=pos[0].x&&x<=pos[0].x+pos[0].w&&y>=pos[0].y&&y<=pos[0].y+pos[0].h)
                {
                    text1=TTF_RenderText_Solid(font,"NEW GAME",textcolor[1]);
                    //text1=TTF_RenderText_Solid(font,"EXIT",textcolor[1]);
                    //color=SDL_MapRGB(screen->format,0x00,0xff,0xff);

                }
                else if(x>=pos[1].x&&x<=pos[1].x+pos[1].w&&y>=pos[1].y&&y<=pos[1].y+pos[1].h)
                {
                    text2=TTF_RenderText_Solid(font,"EXIT",textcolor[1]);

                }
                else if((x>=pos[2].x&&x<=pos[2].x+pos[2].w&&y>=pos[2].y&&y<=pos[2].y+pos[2].h))
                {
                    text3=TTF_RenderText_Solid(font,"SCORE",textcolor[1]);
                }
                else if(!(x>=pos[1].x&&x<=pos[1].x+pos[1].w&&y>=pos[1].y&&y<=pos[1].y+pos[1].h))
               {

                    text2=TTF_RenderText_Solid(font,"EXIT",textcolor[0]);

                }

                //color=SDL_MapRGB(screen->format,0xff,0xff,0xff);
                else if(!x>=pos[0].x&&x<=pos[0].x+pos[0].w&&y>=pos[0].y&&y<=pos[0].y+pos[0].h)
                {
                    text1=TTF_RenderText_Solid(font,"NEW GAME",textcolor[0]);
                }
                 else if(!(x>=pos[2].x&&x<=pos[2].x+pos[2].w&&y>=pos[2].y&&y<=pos[2].y+pos[2].h))
                 {
                     text3=TTF_RenderText_Solid(font,"SCORE",textcolor[0]);
                 }

                break;
            case SDL_MOUSEBUTTONDOWN:

                if(x>=pos[0].x&&x<=pos[0].x+pos[0].w&&y>=pos[0].y&&y<=pos[0].y+pos[0].h)
                {
                    //color=SDL_MapRGB(screen->format,0xff,0x00,0xff);
                    text1=TTF_RenderText_Solid(font,"NEW GAME",textcolor[2]);
                    flag1=1;

                }
                else if(x>=pos[1].x&&x<=pos[1].x+pos[1].w&&y>=pos[1].y&&y<=pos[1].y+pos[1].h)
                {
                    text2=TTF_RenderText_Solid(font,"EXIT",textcolor[2]);
                    SDL_Quit();
                    //flag2=1;
                }
                else if(x>=pos[2].x&&x<=pos[2].x+pos[2].w&&y>=pos[2].y&&y<=pos[2].y+pos[2].h)
                {

                    text3=TTF_RenderText_Solid(font,"SCORE",textcolor[2]);
                    flag3=1;
                }
                break;

            }
        }

        // SDL_FillRect(screen,&pos[0],color);

        SDL_BlitSurface(text1,NULL,screen,&pos[0]);
        SDL_BlitSurface(text2,NULL,screen,&pos[1]);
        SDL_BlitSurface(text3,NULL,screen,&pos[2]);

        SDL_Flip(screen);

        if(flag1==1)
        {
            SDL_FreeSurface(text1);
        }

        if(1000/FPS>SDL_GetTicks()-start)//how many seconds it goes througt the frame
        {
            SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
        }
    }

    TTF_CloseFont(font);
    SDL_Quit();


}
int r_flag1()
{
    return(flag1);
}
int r_flag3()
{
    return(flag3);
}
};
#endif
