#ifndef BULLETOBJECT_H
#define BULLETOBJECT_H

#include "CommonFunc.h"
#include "BaseObject.h"

#define FRAME 64

class BulletObject : public BaseObject
{
    public:
        BulletObject();
        ~BulletObject();

        enum BulletDirection
        {
            DIR_DOWN = 20,
            DIR_RIGHT = 21,
            DIR_UP = 22,
            DIR_LEFT = 23,
        };

        void set_x_val(const int& xVal) {x_val = xVal;}
        void set_y_val(const int& yVal) {y_val = yVal;}
        void set_pos(const int& xPos, const int& yPos) {x_pos = xPos; y_pos = yPos;}

        int get_x_val() const {return x_val;}
        int get_y_val() const {return y_val;}
        int get_x_pos() const {return x_pos;}
        int get_y_pos() const {return y_pos;}

        void set_is_move(const bool& isMove) {is_move_ = isMove;}
        bool get_is_move() const {return is_move_;}

        void set_bullet_dir(const unsigned int& bulletDir) {bullet_dir_ = bulletDir;}
        int get_bullet_dir() const {return bullet_dir_;}

        void HandleMove(const int& x_border, const int& y_border, Map& map_data);
        void Show(SDL_Renderer* des, int x, int y);
    private:
        int x_pos;
        int y_pos;
        int x_val;
        int y_val;
        bool is_move_;
        unsigned int bullet_dir_;
};

#endif // BULLETOBJECT_H
