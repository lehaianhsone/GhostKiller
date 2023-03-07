#ifndef BULLETOBJECT_H
#define BULLETOBJECT_H

#include "CommonFunc.h"
#include "BaseObject.h"

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

        void set_x_val(const int& xVal) {x_val_ = xVal;}
        void set_y_val(const int& yVal) {y_val_ = yVal;}
        int get_x_val() const {return x_val_;}
        int get_y_val() const {return y_val_;}

        void set_is_move(const bool& isMove) {is_move_ = isMove;}
        bool get_is_move() const {return is_move_;}

        void set_bullet_dir(const unsigned int& bulletDir) {bullet_dir_ = bulletDir;}
        int get_bullet_dir() const {return bullet_dir_;}

        void HandleMove(const int& x_border, const int& y_border);
    private:
        int x_val_;
        int y_val_;
        bool is_move_;
        unsigned int bullet_dir_;
};

#endif // BULLETOBJECT_H
