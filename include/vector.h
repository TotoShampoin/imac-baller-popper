#ifndef __VECTOR_H__
#define __VECTOR_H__

/**
 * Classe de vecteur à 2 dimensions.
 */
struct Vec2 {
    float x = 0, y = 0;

    Vec2 operator-();
    Vec2 operator+(Vec2&);
    Vec2 operator-(Vec2&);
    Vec2 operator*(float);
    Vec2 operator/(float);
    
    Vec2& operator+=(Vec2&);
    Vec2& operator-=(Vec2&);
    Vec2& operator*=(float);
    Vec2& operator/=(float);
    
    bool operator==(Vec2&);

    // Effectue un produit scalaire avec un autre vecteur.
    float dotProd(Vec2&);

    // La magnitude au carré
    float magnitude2();
    // La magnitude
    float magnitude();
    // L'argument
    float angle();
    // Le vecteur normal
    Vec2 norm();
};

#endif
