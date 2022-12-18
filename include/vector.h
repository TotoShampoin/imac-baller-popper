#ifndef __VECTOR_H__
#define __VECTOR_H__

struct Vec2 {
    float x = 0, y = 0;

    Vec2 operator-();
    Vec2 operator+(Vec2&);
    Vec2 operator-(Vec2&);
    Vec2 operator*(float);
    
    Vec2& operator+=(Vec2&);
    Vec2& operator-=(Vec2&);
    Vec2& operator*=(float);
    
    bool operator==(Vec2&);

    float magnitude2();
};

#endif
