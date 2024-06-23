#pragma once

#ifndef __VECTOR2D_H
#define __VECTOR2D_H

template<class T>
class Vector2D
{
public:
    Vector2D();
    Vector2D(T x, T y);

    T getX() const { return x; }
    T getY() const { return y; }
    T setX(T x) { this->x = x; }
    void setY(T y) { this->y = y; }

    Vector2D operator+(const Vector2D& v) const;
    Vector2D operator-(const Vector2D& v) const;
    Vector2D operator*(T scalar) const;
    Vector2D operator/(T scalar) const;
    Vector2D& operator+=(const Vector2D& v);
    Vector2D& operator-=(const Vector2D& v);
    Vector2D& operator*=(T scalar);
    Vector2D& operator/=(T scalar);

    // Magnitude and normalization
    T magnitude() const;
    Vector2D normalized() const;

private:
    T x;
    T y;
};

#endif // __VECTOR2D_H
