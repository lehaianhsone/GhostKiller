#ifndef THREATOBJECT_H
#define THREATOBJECT_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"

#define FRAME 64
#define TIME 1
class ThreatObject : public BaseObject
{
    public:
        ThreatObject();
        ~ThreatObject();

        enum GhostDirection
        {
            DIR_UP = 25,
            DIR_LEFT = 26,
            DIR_DOWN = 27,
            DIR_RIGHT = 28,
        };

        void set_x_val(const float& xVal) {x_val = xVal;}
        void set_y_val(const float& yVal) {y_val = yVal;}

        void set_x_pos(const float& xp) {x_pos = xp;}
        void set_y_pos(const float& yp) {y_pos = yp;}

        float get_x_pos() const {return x_pos;}
        float get_y_pos() const {return y_pos;}

        void SetMapXY(const int& mp_x, const int& mp_y)
        {map_x = mp_x; map_y = mp_y;}

        void Show(SDL_Renderer* des);
        bool is_alive() const {return isAlive;}
        void DoPlayer(Map& gMap, MainObject& p);
        void CheckToMap(Map& gMap);
        void CheckToBullet(MainObject& p);
    private:
        int map_x;
        int map_y;

        float x_val;
        float y_val;
        float x_pos;
        float y_pos;

        int unsigned ghost_dir;
        bool isAlive;
        bool isChange;

        int timeChangeDir;

        int mood_;
};

#endif // THREATOBJECT_H
