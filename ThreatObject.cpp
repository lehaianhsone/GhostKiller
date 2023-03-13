#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
    x_val = rand() % 20;
    y_val = rand() % 20;
    x_pos = 256;
    y_pos = 640;
    ghost_dir = rand() % 4 + 25;
    mood_= rand() % 2;
    isAlive = true;
    isChange = false;
    timeChangeDir = 0;
}

ThreatObject::~ThreatObject()
{
    //dtor
}

void ThreatObject::Show(SDL_Renderer* des)
{
    if(mood_ == 0) LoadImg("img/soneGhost1.png", des);
    else LoadImg("img/soneGhost2.png", des);
    rect_.x = x_pos - map_x;
    rect_.y = y_pos - map_y;

    SDL_Rect renderQuad = {rect_.x, rect_.y, FRAME, FRAME};

    SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
}

void ThreatObject::DoPlayer(Map& map_data, MainObject& p)
{
    if(ghost_dir == DIR_DOWN){
        x_val = 0;
        y_val = 15;
    }
    else if(ghost_dir == DIR_UP){
        x_val = 0;
        y_val = - 15;
    }
    else if(ghost_dir == DIR_RIGHT){
        x_val = 15;
        y_val = 0;
    }
    else if(ghost_dir == DIR_LEFT){
        x_val = - 15;
        y_val = 0;
    }
    CheckToMap(map_data);
    CheckToBullet(p);
    isChange = false;
}

void ThreatObject::CheckToMap(Map& map_data)
{
    if(timeChangeDir == TIME){
        timeChangeDir = 0;
        ghost_dir = rand() % 4 + 25;
    }
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
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];
            if((val1 >= 2 && val1 <= 16) || (val2 >= 2 && val2 <= 16)){
                if(!isChange){
                    isChange = true;
                    ghost_dir -= 2;
                }
            }
        }
        else if(x_val < 0)   //main object dang di chuyen ve ben phai
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];
            if((val1 >= 2 && val1 <= 16) || (val2 >= 2 && val2 <= 16)){
                if(!isChange){
                    isChange = true;
                    ghost_dir += 2;
                }
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
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];
            if((val1 >= 2 && val1 <= 16) || (val2 >= 2 && val2 <= 16)){
                if(!isChange){
                    isChange = true;
                    ghost_dir -= 2;
                }
            }
        }
        else if(y_val < 0)   //main object dang di chuyen ve ben phai
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];
            if((val1 >= 2 && val1 <= 16) || (val2 >= 2 && val2 <= 16)){
                if(!isChange){
                    isChange = true;
                    ghost_dir += 2;
                }
            }
        }
    }
    if(x_pos <= 0 || y_pos <= 0){
        ghost_dir += 2;
        isChange = true;
    }
    if(x_pos + FRAME > map_data.max_x || y_pos + FRAME > map_data.max_y){
        ghost_dir -= 2;
        isChange = true;
    }
    x_pos += x_val;
    y_pos += y_val;
    if(isChange) timeChangeDir++;
}

void ThreatObject::CheckToBullet(MainObject& p)
{
    std::vector<BulletObject*> bullet = p.get_bullet_list();
    SDL_Rect mainRect = rect_;
    SDL_Rect subRect = p.GetRect();
    if(checkCollision(mainRect, subRect)) p.set_is_alive(false);
    for(int i = 0; i < bullet.size(); i++){
        SDL_Rect tmpRect = bullet[i]->GetRect();
        if(checkCollision(mainRect, tmpRect)){
            isAlive = false;
            score += 10;
            std::cout << score << std::endl;
            bullet.erase(bullet.begin() + i);
            p.set_bullet_list(bullet);
        }
    }
}
