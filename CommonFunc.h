#pragma once

#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//Screen
const int FRAME_PER_SECOND = 20;    //fps
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 255;
const int COLOR_KEY_G = 255;
const int COLOR_KEY_B = 255;

const int RENDER_DRAW_COLOR = 255;

#define TILE_SIZE 64
#define MAX_MAP_X 20
#define MAX_MAP_Y 20
#define BUFF_BULLET 17

struct Map
{
    //toa do
    int start_x;
    int start_y;
    //gia tri toi da cua ban do
    int max_x;
    int max_y;
    //tile[i][j]: dang map ma o (i, j) se hien thi
    int tile[MAX_MAP_Y][MAX_MAP_X];
    //file chua ban raw map (00 01 ...)
    char* file_name;
};

struct Input{
    int down;
    int right;
    int up;
    int left;
    //int shoot;
};
#endif // COMONFUNC_H
