//
// Created by Lado on 11/6/20.
//

#ifndef LOTOS_VECTOR2D_H
#define LOTOS_VECTOR2D_H

#include <iostream>

class Vector2D {
public:
    float x, y;

    Vector2D();
    Vector2D(float x, float y);

    Vector2D& add(const Vector2D& vec);
    Vector2D& subtract(const Vector2D& vec);
    Vector2D& multiply(const Vector2D& vec);
    Vector2D& divide(const Vector2D& vec);

    friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

    Vector2D& operator+=(const Vector2D& vec);
    Vector2D& operator-=(const Vector2D& vec);
    Vector2D& operator*=(const Vector2D& vec);
    Vector2D& operator/=(const Vector2D& vec);

    Vector2D& operator*(const int& i);
    Vector2D& Zero();

    friend std::ostream& operator<<(std::ostream& ostream, const Vector2D& vec);
};

#endif //LOTOS_VECTOR2D_H
