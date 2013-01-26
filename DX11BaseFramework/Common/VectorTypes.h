#pragma once

#include <windows.h>
#include <cmath>

class Vector3
{
private:
	float x, y, z;
public:
	Vector3();
	Vector3(float xVal, float yVal, float zVal); //ctor
	Vector3 Perp();
	Vector3& operator=(const Vector3 &rhs);
	bool operator ==(const Vector3 &rhs) const;
	Vector3 operator-= (const Vector3 &rhs);
	Vector3 operator+= (const Vector3 &rhs);
	Vector3 operator- (const Vector3 &rhs);
	Vector3 operator+ (const Vector3 &rhs);
	float operator* (const Vector3 &rhs); //dot product
	Vector3 operator* (const float &rhs); //scalar product
	Vector3 operator*= (const float &rhs);
	bool operator<(const Vector3& other) const;
	Vector3 operator%(const Vector3 &vector)const; //cross product
	Vector3 vectorProduct(const Vector3 &vector)const; //used for %= cross product
	void operator %=(const Vector3 &vector); //cross product
	float magnitude();
	float sqrmagnitude();
	void invert();
	void scale(float);
	void clear();
	Vector3 normalize();
	Vector3 normalize(const Vector3&);
	void makeOrthonormalBasis(Vector3 *a, Vector3 *b, Vector3 *c);
	void addScaledVector (const Vector3 vector, float scale);
	float GetX(){return x;}
	float GetY(){return y;}
	float GetZ(){return z;}
	void SetX(float xIn){x = xIn;}
	void SetY(float yIn){y = yIn; }
	void SetZ(float zIn){z = zIn; }
};
//
class Vector2
{
public:
	float x, y;
	Vector2();
	Vector2(float xVal, float yVal); //ctor
//	Vector2 Perp();
//	Vector2& operator=(const Vector2 &rhs);
//	bool operator ==(const Vector2 &rhs) const;
//	Vector2 operator-= (const Vector2 &rhs);
//	Vector2 operator+= (const Vector2 &rhs);
//	Vector2 operator- (const Vector2 &rhs);
//	Vector2 operator+ (const Vector2 &rhs);
//	float operator* (const Vector2 &rhs); //dot product
//	Vector2 operator* (const float &rhs); //scalar product
//	Vector2 operator*= (const float &rhs);
//	bool operator<(const Vector2& other) const;
//	Vector2 operator%(const Vector2 &vector)const; //cross product
//	Vector2 vectorProduct(const Vector2 &vector)const; //used for %= cross product
//	void operator %=(const Vector2 &vector); //cross product
//	float magnitude();
//	float sqrmagnitude();
//	void invert();
//	void scale(float);
//	void clear();
//	Vector2 normalize();
//	Vector2 normalize(const Vector2&);
//	void makeOrthonormalBasis(Vector2 *a, Vector2 *b, Vector2 *c);
//	void addScaledVector (const Vector2 vector, float scale);
	//float GetX(){return x;}
	//float GetY(){return y;}
};