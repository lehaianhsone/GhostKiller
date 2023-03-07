#ifndef MAINOBJECT_H
#define MAINOBJECT_H

#include "CommonFunc.h"
#include "BaseObject.h"

#define PLAYER_SPEED 10
#define FRAME 50

class MainObject : public BaseObject
{
     public:
        MainObject();
        ~MainObject();

        enum WalkType{
            WALK_DOWN = 0,
            WALK_RIGHT = 1,
            WALK_UP = 2,
            WALK_LEFT = 3,
        };

        void Show(SDL_Renderer* des);
        void HandleInputAction(SDL_Event event, SDL_Renderer* screen);

        void DoPlayer(Map& map_data);
        void CheckToMap(Map& map_data);
        void SetMapXY(const int map_x, const int map_y)
        {this->map_x = map_x; this->map_y = map_y;}
        void CenterEntityOnMap(Map& map_data);

    private:
        float x_val;
        float y_val;

        float x_pos;
        float y_pos;

        Input input_type;
        int status;

        int map_x;
        int map_y;

};

#endif // MAINOBJECT_H

