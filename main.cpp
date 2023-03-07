#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "GameMap.h"
#include "ImpTime.h"

BaseObject g_background;

bool Init()
{
    bool sc = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        return false;
    }
    //Set a hint with normal priority
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    //Create window
    g_window = SDL_CreateWindow("SONE", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(g_window == NULL) sc = false;
    else{
        //Create renderer for window
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL) sc = false;
        else{
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            //Declare SDL_Image
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags)) sc = false;
        }
    }
    return sc;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("img/bg2.png", g_screen);
    return ret;
}

void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen); g_screen = NULL;
    SDL_DestroyWindow(g_window); g_window = NULL;

    IMG_Quit();
    SDL_Quit();

}

int main(int argc, char* argv[])
{
    ImpTime fps_timer;
    if(!Init()) return -1;
    if(!LoadBackground()) return -1;

    GameMap game_map;
    game_map.LoadMap("soneMap/sonemap.txt");
    game_map.LoadTiles(g_screen);

    MainObject player;

    bool is_quit = false;
    while(!is_quit)
    {
        while(SDL_PollEvent(&g_event) != 0)
        {
            if(g_event.type == SDL_QUIT){
                is_quit = true;
            }
            player.HandleInputAction(g_event, g_screen);
        }
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);

        Map map_data = game_map.getMap();

        //player.HandleBullet(g_screen);
        player.SetMapXY(map_data.start_x, map_data.start_y);
        player.DoPlayer(map_data);
        //player.Show(g_screen);

        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        player.Show(g_screen);
        player.HandleBullet(g_screen);
        std::cout << player.get_bullet_list().size() << std::endl;
        SDL_RenderPresent(g_screen);

        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000 / FRAME_PER_SECOND;
        if(real_imp_time < time_one_frame){
            int delay_time = time_one_frame - real_imp_time;
            if(delay_time >= 0) SDL_Delay(delay_time);
        }
    }
    close();
    return 0;
}
