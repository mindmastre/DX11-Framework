#include "Vector2D.h"
#include <cmath>

/////////////////////////////////////////////////
//               float template
/////////////////////////////////////////////////
Vector2D<float>::Vector2D()
{
	//do nothing
}
Vector2D<float>::Vector2D(float val)
{
	x = val;
	y = val;
}
Vector2D<float>::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vector2D<float>::~Vector2D()
{
	//do nothing
}
float Vector2D<float>::operator[](unsigned i)
{
	if(i == 0) return x;
	else	   return y;
}
Vector2D<float> Vector2D<float>::operator+(const Vector2D& rhs)
{
	return Vector2D<float>(*this) += rhs;
}
Vector2D<float> Vector2D<float>::operator-(const Vector2D& rhs)
{
	return Vector2D<float>(*this) -= rhs;
}
Vector2D<float> Vector2D<float>::operator*(const Vector2D& rhs)
{
	return Vector2D<float>(*this) *= rhs;
}
Vector2D<float> Vector2D<float>::operator/(const Vector2D& rhs)
{
	return Vector2D<float>(*this) /= rhs;
}
Vector2D<float> Vector2D<float>::operator+=(const Vector2D& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}
Vector2D<float> Vector2D<float>::operator-=(const Vector2D& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}
Vector2D<float> Vector2D<float>::operator*=(const Vector2D& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}
Vector2D<float> Vector2D<float>::operator/=(const Vector2D& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}
bool Vector2D<float>::operator==(const Vector2D& rhs)
{
	return x == rhs.x && y == rhs.y;
}
bool Vector2D<float>::operator!=(const Vector2D& rhs)
{
	return x != rhs.x || y != rhs.y;
}
Vector2D<float> Vector2D<float>::operator+(const float& rhs)
{
	return Vector2D<float>(*this) += rhs;
}
Vector2D<float> Vector2D<float>::operator-(const float& rhs)
{
	return Vector2D<float>(*this) -= rhs;
}
Vector2D<float> Vector2D<float>::operator*(const float& rhs)
{
	return Vector2D<float>(*this) *= rhs;
}
Vector2D<float> Vector2D<float>::operator/(const float& rhs)
{
	return Vector2D<float>(*this) /= rhs;
}
Vector2D<float> Vector2D<float>::operator+=(const float& rhs)
{
	x += rhs;
	y += rhs;
	return *this;
}
Vector2D<float> Vector2D<float>::operator-=(const float& rhs)
{
	x -= rhs;
	y -= rhs;
	return *this;
}
Vector2D<float> Vector2D<float>::operator*=(const float& rhs)
{
	x *= rhs;
	y *= rhs;
	return *this;
}
Vector2D<float> Vector2D<float>::operator/=(const float& rhs)
{
	x /= rhs;
	y /= rhs;
	return *this;
}
bool Vector2D<float>::operator==(const float& rhs)
{
	return x == rhs && y == rhs;
}
bool Vector2D<float>::operator!=(const float& rhs)
{
	return x != rhs || y != rhs;
}
float Vector2D<float>::Dot(const Vector2D<float>& rhs)
{
	return x * rhs.x + y * rhs.y;
}
float Vector2D<float>::Cross(const Vector2D<float>& rhs)
{
	return x * rhs.y - y * rhs.x;
}
float Vector2D<float>::Magnitude()
{
	return sqrt(MagnitudeSquared());
}
float Vector2D<float>::MagnitudeSquared()
{
	return x * x + y * y;
}
void Vector2D<float>::Normalize()
{
	if(*this != 0.0f)
	{
		float M = Magnitude();
		x /= M;
		y /= M;
	}
}
Vector2D<float> Vector2D<float>::Normalized()
{
	Vector2D<float> temp(*this);
	temp.Normalize();
	return temp;
}
void Vector2D<float>::Invert()
{
	*this *= -1.0f;
}
Vector2D<float> Vector2D<float>::Inverted()
{
	Vector2D<float> temp(*this);
	temp.Invert();
	return temp;
}
/////////////////////////////////////////////////
//                double template
/////////////////////////////////////////////////
Vector2D<double>::Vector2D()
{
	//do nothing
}
Vector2D<double>::Vector2D(double val)
{
	x = val;
	y = val;
}
Vector2D<double>::Vector2D(double x, double y)
{
	this->x = x;
	this->y = y;
}
Vector2D<double>::~Vector2D()
{
	//do nothing
}
double Vector2D<double>::operator[](unsigned i)
{
	if(i == 0) return x;
	else	   return y;
}
Vector2D<double> Vector2D<double>::operator+(const Vector2D& rhs)
{
	return Vector2D<double>(*this) += rhs;
}
Vector2D<double> Vector2D<double>::operator-(const Vector2D& rhs)
{
	return Vector2D<double>(*this) -= rhs;
}
Vector2D<double> Vector2D<double>::operator*(const Vector2D& rhs)
{
	return Vector2D<double>(*this) *= rhs;
}
Vector2D<double> Vector2D<double>::operator/(const Vector2D& rhs)
{
	return Vector2D<double>(*this) /= rhs;
}
Vector2D<double> Vector2D<double>::operator+=(const Vector2D& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}
Vector2D<double> Vector2D<double>::operator-=(const Vector2D& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}
Vector2D<double> Vector2D<double>::operator*=(const Vector2D& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}
Vector2D<double> Vector2D<double>::operator/=(const Vector2D& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}
bool Vector2D<double>::operator==(const Vector2D& rhs)
{
	return x == rhs.x && y == rhs.y;
}
bool Vector2D<double>::operator!=(const Vector2D& rhs)
{
	return x != rhs.x || y != rhs.y;
}
Vector2D<double> Vector2D<double>::operator+(const double& rhs)
{
	return Vector2D<double>(*this) += rhs;
}
Vector2D<double> Vector2D<double>::operator-(const double& rhs)
{
	return Vector2D<double>(*this) -= rhs;
}
Vector2D<double> Vector2D<double>::operator*(const double& rhs)
{
	return Vector2D<double>(*this) *= rhs;
}
Vector2D<double> Vector2D<double>::operator/(const double& rhs)
{
	return Vector2D<double>(*this) /= rhs;
}
Vector2D<double> Vector2D<double>::operator+=(const double& rhs)
{
	x += rhs;
	y += rhs;
	return *this;
}
Vector2D<double> Vector2D<double>::operator-=(const double& rhs)
{
	x -= rhs;
	y -= rhs;
	return *this;
}
Vector2D<double> Vector2D<double>::operator*=(const double& rhs)
{
	x *= rhs;
	y *= rhs;
	return *this;
}
Vector2D<double> Vector2D<double>::operator/=(const double& rhs)
{
	x /= rhs;
	y /= rhs;
	return *this;
}
bool Vector2D<double>::operator==(const double& rhs)
{
	return x == rhs && y == rhs;
}
bool Vector2D<double>::operator!=(const double& rhs)
{
	return x != rhs || y != rhs;
}
double Vector2D<double>::Dot(const Vector2D<double>& rhs)
{
	return x * rhs.x + y * rhs.y;
}
double Vector2D<double>::Cross(const Vector2D<double>& rhs)
{
	return x * rhs.y - y * rhs.x;
}
double Vector2D<double>::Magnitude()
{
	return sqrt(MagnitudeSquared());
}
double Vector2D<double>::MagnitudeSquared()
{
	return x * x + y * y;
}
void Vector2D<double>::Normalize()
{
	if(*this != 0.0f)
	{
		double M = Magnitude();
		x /= M;
		y /= M;
	}
}
Vector2D<double> Vector2D<double>::Normalized()
{
	Vector2D<double> temp(*this);
	temp.Normalize();
	return temp;
}
void Vector2D<double>::Invert()
{
	*this *= -1.0;
}
Vector2D<double> Vector2D<double>::Inverted()
{
	Vector2D<double> temp(*this);
	temp.Invert();
	return temp;
}