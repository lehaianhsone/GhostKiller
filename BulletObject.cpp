#include "BulletObject.h"

BulletObject::BulletObject()
{
    x_val = y_val = 0;
    x_pos = y_pos = 0;
    is_move_ = false;

}

void BulletObject::HandleMove(const int& x_border, const int& y_border, Map& map_data)
{
    /* (y1, x1) ******** (y2, x1)
        *                   *
        *                   *
       (y1, x2) ******** (y2, x2) */
    int x1 = 0, x2 = 0;
    int y1 = 0, y2 = 0;

    if(bullet_dir_ == DIR_RIGHT)
    {
        x1 = (x_pos) / TILE_SIZE;
        x2 = (x_pos + x_val) / TILE_SIZE;

        y1 = (y_pos) / TILE_SIZE;
        y2 = (y_pos + FRAME) / TILE_SIZE;

        if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y){
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];
            if(val1 >= BUFF_BULLET || val2 >= BUFF_BULLET)
            {
                map_data.tile[y1][x2] = 1;
                map_data.tile[y2][x2] = 1;
                is_move_ = false;
            }
            else{
                if((val1 >= 2) || (val2 >= 2)){
                    x_val = 0;
                    is_move_ = false;
                }
            }
        }
        rect_.x += x_val;
        x_pos += x_val;
        if(rect_.x >= x_border) is_move_ = false;
    }
    else if(bullet_dir_ == DIR_LEFT)
    {
        x1 = (x_pos + x_val) / TILE_SIZE;
        x2 = (x_pos) / TILE_SIZE;

        y1 = (y_pos) / TILE_SIZE;
        y2 = (y_pos + FRAME) / TILE_SIZE;
        if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y){
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];
            if(val1 >= BUFF_BULLET || val2 >= BUFF_BULLET)
            {
                map_data.tile[y1][x1] = 1;
                map_data.tile[y2][x1] = 1;
                is_move_ = false;
            }
            else{
                if((val1 >= 2) || (val2 >= 2)){
                    x_val = 0;
                    is_move_ = false;
                }
            }
        }
        rect_.x -= x_val;
        x_pos -= x_val;
        if(rect_.x <= 0) is_move_ = false;
    }
    else if(bullet_dir_ == DIR_UP)
    {
        x1 = (x_pos) / TILE_SIZE;
        x2 = (x_pos + FRAME) / TILE_SIZE;

        y1 = (y_pos + y_val) / TILE_SIZE;
        y2 = (y_pos) / TILE_SIZE;
        if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y){
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];
            if(val1 >= BUFF_BULLET || val2 >= BUFF_BULLET)
            {
                map_data.tile[y1][x1] = 1;
                map_data.tile[y1][x2] = 1;
                is_move_ = false;
            }
            else{
                if((val1 >= 2) || (val2 >= 2)){
                    y_val = 0;
                    is_move_ = false;
                }
            }
        }
        rect_.y -= y_val;
        y_pos -= y_val;
        if(rect_.y <= 0) is_move_ = false;
    }
    else{
        x1 = (x_pos) / TILE_SIZE;
        x2 = (x_pos + FRAME) / TILE_SIZE;

        y1 = (y_pos) / TILE_SIZE;
        y2 = (y_pos + y_val) / TILE_SIZE;
        if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y){
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];
            if(val1 >= BUFF_BULLET || val2 >= BUFF_BULLET)
            {
                map_data.tile[y2][x1] = 1;
                map_data.tile[y2][x2] = 1;
                is_move_ = false;
            }
            else{
                if((val1 >= 2) || (val2 >= 2)){
                    y_val = 0;
                    is_move_ = false;
                }
            }
        }
        rect_.y += y_val;
        y_pos += y_val;
        if(rect_.y >= y_border) is_move_ = false;
    }
}

void BulletObject::Show(SDL_Renderer* des, int x, int y)
{
    rect_.x = x_pos - x;
    rect_.y = y_pos - y;

    SDL_Rect renderQuad = {rect_.x, rect_.y, FRAME, FRAME};

    SDL_RenderCopy(des, p_object_, NULL, &renderQuad);

}

BulletObject::~BulletObject()
{

}
