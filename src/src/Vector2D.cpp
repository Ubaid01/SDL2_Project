#include "Vector2D.h"
#include <cmath> 

template<class T>
Vector2D<T>::Vector2D() : x(0), y(0) {}

template<class T>
Vector2D<T>::Vector2D(T x, T y) : x(x), y(y) {}

template<class T>
Vector2D<T> Vector2D<T>::operator+(const Vector2D& v) const { return Vector2D(x + v.x, y + v.y); }

template<class T>
Vector2D<T> Vector2D<T>::operator-(const Vector2D& v) const { return Vector2D(x - v.x, y - v.y); }

template<class T>
Vector2D<T> Vector2D<T>::operator*(T scalar) const { return Vector2D(x * scalar, y * scalar); }

template<class T>
Vector2D<T> Vector2D<T>::operator/(T scalar) const { return Vector2D(x / scalar, y / scalar); }

template<class T>
Vector2D<T>& Vector2D<T>::operator+=(const Vector2D& v)
{
    x += v.x;
    y += v.y;
    return *this;
}

template<class T>
Vector2D<T>& Vector2D<T>::operator-=(const Vector2D& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

template<class T>
Vector2D<T>& Vector2D<T>::operator*=(T scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

template<class T>
Vector2D<T>& Vector2D<T>::operator/=(T scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

template<class T>
T Vector2D<T>::magnitude() const { return std::sqrt(x * x + y * y); }

template<class T>
Vector2D<T> Vector2D<T>::normalized() const
{
    T mag = magnitude();
    if( mag == 0 )
		return Vector2D( 0, 0 ) ;
    return Vector2D(x / mag, y / mag);
}
