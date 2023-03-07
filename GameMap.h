#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "CommonFunc.h"
#include "BaseObject.h"

#define MAX_TILE 13

class TileMap : public BaseObject
{
public:
    TileMap(){;}
    ~TileMap(){;}
};

class GameMap
{
public:
    GameMap(){;}
    ~GameMap(){;}

    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    Map getMap() {return game_map;}
    void SetMap(Map& map_data) {game_map = map_data;}

private:
    Map game_map;
    //so luong hinh anh phai dung den (dat, nuoc,...)
    TileMap tile_map[MAX_TILE];
};

#endif // GAMEMAP_H
