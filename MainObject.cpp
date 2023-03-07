#include "MainObject.h"

MainObject::MainObject()
{
    x_pos = y_pos = 0;
    x_val = y_val = 0;
    status = -1;
    input_type.left = input_type.right = 0;
    input_type.down = input_type.up = 0;
    map_x = map_y = 0;
}

void MainObject::Show(SDL_Renderer* des)
{
    if(status == WALK_LEFT){
        LoadImg("soneMap/sonePlayerL.png", des);
    }
    else if(status == WALK_RIGHT){
        LoadImg("soneMap/sonePlayerR.png", des);
    }
    else if(status == WALK_UP){
        LoadImg("soneMap/sonePlayerU.png", des);
    }
    else{
        LoadImg("soneMap/sonePlayerD.png", des);
    }

    rect_.x = x_pos - map_x;
    rect_.y = y_pos - map_y;

    SDL_Rect renderQuad = {rect_.x, rect_.y, FRAME, FRAME};

    SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
}

void MainObject::HandleInputAction(SDL_Event event, SDL_Renderer* screen)
{
    if(event.type == SDL_KEYDOWN){
        switch(event.key.keysym.sym){
        case SDLK_RIGHT:
            status = WALK_RIGHT;
            input_type.right = 1;
            input_type.left = 0;
            break;
        case SDLK_LEFT:
            status = WALK_LEFT;
            input_type.left = 1;
            input_type.right = 0;
            break;
        case SDLK_DOWN:
            status = WALK_DOWN;
            input_type.down = 1;
            input_type.up = 0;
            break;
        case SDLK_UP:
            status = WALK_UP;
            input_type.up = 1;
            input_type.down = 0;
            break;
        }
    }
    else if(event.type == SDL_KEYUP){
        switch(event.key.keysym.sym){
        case SDLK_RIGHT:
            input_type.right = 0;
            break;
        case SDLK_LEFT:
            input_type.left = 0;
            break;
        case SDLK_DOWN:
            input_type.down = 0;
            break;
        case SDLK_UP:
            input_type.up = 0;
            break;
        }
    }
}

void MainObject::DoPlayer(Map& map_data)
{
    x_val = 0;
    y_val = 0;

    if(input_type.left == 1){
        x_val -= PLAYER_SPEED;
    }
    if(input_type.right == 1){
        x_val += PLAYER_SPEED;
    }
    if(input_type.up == 1){
        y_val -= PLAYER_SPEED;
    }
    if(input_type.down == 1){
        y_val += PLAYER_SPEED;
    }

    //kiem tra va cham
    CheckToMap(map_data);
    CenterEntityOnMap(map_data);
}

void MainObject::CenterEntityOnMap(Map& map_data)
{
    map_data.start_x = x_pos - (SCREEN_WIDTH / 2);
    if(map_data.start_x < 0) map_data.start_x = 0;
    else if(map_data.start_x + SCREEN_WIDTH >= map_data.max_x)
        map_data.start_x = map_data.max_x - SCREEN_WIDTH;

    map_data.start_y = y_pos - (SCREEN_HEIGHT / 2);
    if(map_data.start_y < 0) map_data.start_y = 0;
    else if(map_data.start_y + SCREEN_HEIGHT >= map_data.max_y)
        map_data.start_y = map_data.max_y - SCREEN_HEIGHT;
}

void MainObject::CheckToMap(Map& map_data)
{
    /* (y1, x1) ******** (y2, x1)
        *                   *
        *                   *
       (y1, x2) ******** (y2, x2) */
    int x1 = 0, x2 = 0;
    int y1 = 0, y2 = 0;

    //check horizontal
    int height_min = FRAME < TILE_SIZE ? FRAME : TILE_SIZE;
    //o thu bao nhieu
    x1 = (x_pos + x_val) / TILE_SIZE;
    x2 = (x_pos + x_val + FRAME - 1) / TILE_SIZE;

    y1 = (y_pos) / TILE_SIZE;
    y2 = (y_pos + height_min - 1) / TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y){
        if(x_val > 0)   //main object dang di chuyen ve ben phai
        {
            if((map_data.tile[y1][x2] >= 2) || (map_data.tile[y2][x2] >= 2)){
                x_pos = x2 * TILE_SIZE - (FRAME + 1);
                x_val = 0;
            }
        }
        else if(x_val < 0)   //main object dang di chuyen ve ben phai
        {
            if((map_data.tile[y1][x1] >= 2) || (map_data.tile[y2][x1] >= 2)){
                x_pos = (x1 + 1) * TILE_SIZE;
                x_val = 0;
            }
        }
    }

    //check vertical
    int width_min = FRAME < TILE_SIZE ? FRAME : TILE_SIZE;
    x1 = (x_pos) / TILE_SIZE;
    x2 = (x_pos + width_min - 1) / TILE_SIZE;

    y1 = (y_pos + y_val) / TILE_SIZE;
    y2 = (y_pos + y_val + FRAME - 1) / TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y){
        if(y_val > 0)   //main object dang di chuyen ve xuong
        {
            if((map_data.tile[y2][x1] >= 2) || (map_data.tile[y2][x2] >= 2)){
                y_pos = y2 * TILE_SIZE - (FRAME + 1);
                y_val = 0;
            }
        }
        else if(y_val < 0)   //main object dang di chuyen ve ben phai
        {
            if((map_data.tile[y1][x1] >= 2) || (map_data.tile[y1][x2] >= 2)){
                y_pos = (y1 + 1) * TILE_SIZE;
                y_val = 0;
            }
        }
    }

    x_pos += x_val;
    y_pos += y_val;

    if(x_pos < 0) x_pos = 0;
    else if(x_pos + FRAME > map_data.max_x) x_pos = map_data.max_x - FRAME;
    if(y_pos < 0) y_pos = 0;
    else if(y_pos + FRAME > map_data.max_y) y_pos = map_data.max_y - FRAME;
}

MainObject::~MainObject()
{

}
