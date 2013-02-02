#include "Vector4D.h"
#include <cmath>

/////////////////////////////////////////////////
//               float template
/////////////////////////////////////////////////
Vector4D<float>::Vector4D()
{
	//do nothing
}
Vector4D<float>::Vector4D(float val)
{
	x = val;
	y = val;
	z = val;
	w = val;
}
Vector4D<float>::Vector4D(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
Vector4D<float>::~Vector4D()
{
	//do nothing
}
float Vector4D<float>::operator[](unsigned i)
{
	if(i == 0)		return x;
	else if(i == 1) return y;
	else if(i == 2)	return z;
	else			return w;
}
Vector4D<float> Vector4D<float>::operator+(const Vector4D& rhs)
{
	return Vector4D<float>(*this) += rhs;
}
Vector4D<float> Vector4D<float>::operator-(const Vector4D& rhs)
{
	return Vector4D<float>(*this) -= rhs;
}
Vector4D<float> Vector4D<float>::operator*(const Vector4D& rhs)
{
	return Vector4D<float>(*this) *= rhs;
}
Vector4D<float> Vector4D<float>::operator/(const Vector4D& rhs)
{
	return Vector4D<float>(*this) /= rhs;
}
Vector4D<float> Vector4D<float>::operator+=(const Vector4D& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	return *this;
}
Vector4D<float> Vector4D<float>::operator-=(const Vector4D& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
	return *this;
}
Vector4D<float> Vector4D<float>::operator*=(const Vector4D& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	w *= rhs.w;
	return *this;
}
Vector4D<float> Vector4D<float>::operator/=(const Vector4D& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	w /= rhs.w;
	return *this;
}
bool Vector4D<float>::operator==(const Vector4D& rhs)
{
	return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
}
bool Vector4D<float>::operator!=(const Vector4D& rhs)
{
	return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
}
Vector4D<float> Vector4D<float>::operator+(const float& rhs)
{
	return Vector4D<float>(*this) += rhs;
}
Vector4D<float> Vector4D<float>::operator-(const float& rhs)
{
	return Vector4D<float>(*this) -= rhs;
}
Vector4D<float> Vector4D<float>::operator*(const float& rhs)
{
	return Vector4D<float>(*this) *= rhs;
}
Vector4D<float> Vector4D<float>::operator/(const float& rhs)
{
	return Vector4D<float>(*this) /= rhs;
}
Vector4D<float> Vector4D<float>::operator+=(const float& rhs)
{
	x += rhs;
	y += rhs;
	z += rhs;
	w += rhs;
	return *this;
}
Vector4D<float> Vector4D<float>::operator-=(const float& rhs)
{
	x -= rhs;
	y -= rhs;
	z -= rhs;
	w -= rhs;
	return *this;
}
Vector4D<float> Vector4D<float>::operator*=(const float& rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	w *= rhs;
	return *this;
}
Vector4D<float> Vector4D<float>::operator/=(const float& rhs)
{
	x /= rhs;
	y /= rhs;
	z /= rhs;
	w /= rhs;
	return *this;
}
bool Vector4D<float>::operator==(const float& rhs)
{
	return x == rhs && y == rhs && z == rhs && w == rhs;
}
bool Vector4D<float>::operator!=(const float& rhs)
{
	return x != rhs || y != rhs || z != rhs || w != rhs;
}
float Vector4D<float>::Dot(const Vector4D<float>& rhs)
{
	return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}
float Vector4D<float>::Magnitude()
{
	return sqrt(MagnitudeSquared());
}
float Vector4D<float>::MagnitudeSquared()
{
	return x * x + y * y + z * z + w * w;
}
void Vector4D<float>::Normalize()
{
	if(*this != 0.0f)
	{
		float M = Magnitude();
		x /= M;
		y /= M;
		z /= M;
		w /= M;
	}
}
Vector4D<float> Vector4D<float>::Normalized()
{
	Vector4D<float> temp(*this);
	temp.Normalize();
	return temp;
}
void Vector4D<float>::Invert()
{
	*this *= -1.0f;
}
Vector4D<float> Vector4D<float>::Inverted()
{
	Vector4D<float> temp(*this);
	temp.Invert();
	return temp;
}
Vector3D<float> Vector4D<float>::GetVec3()
{
	return Vector3D<float>(x, y, z);
}
/////////////////////////////////////////////////
//                double template
/////////////////////////////////////////////////
Vector4D<double>::Vector4D()
{
	//do nothing
}
Vector4D<double>::Vector4D(double val)
{
	x = val;
	y = val;
	z = val;
	w = val;
}
Vector4D<double>::Vector4D(double x, double y, double z, double w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
Vector4D<double>::~Vector4D()
{
	//do nothing
}
double Vector4D<double>::operator[](unsigned i)
{
	if(i == 0)		return x;
	else if(i == 1) return y;
	else if(i == 2)	return z;
	else			return w;
}
Vector4D<double> Vector4D<double>::operator+(const Vector4D& rhs)
{
	return Vector4D<double>(*this) += rhs;
}
Vector4D<double> Vector4D<double>::operator-(const Vector4D& rhs)
{
	return Vector4D<double>(*this) -= rhs;
}
Vector4D<double> Vector4D<double>::operator*(const Vector4D& rhs)
{
	return Vector4D<double>(*this) *= rhs;
}
Vector4D<double> Vector4D<double>::operator/(const Vector4D& rhs)
{
	return Vector4D<double>(*this) /= rhs;
}
Vector4D<double> Vector4D<double>::operator+=(const Vector4D& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	return *this;
}
Vector4D<double> Vector4D<double>::operator-=(const Vector4D& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
	return *this;
}
Vector4D<double> Vector4D<double>::operator*=(const Vector4D& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	w *= rhs.w;
	return *this;
}
Vector4D<double> Vector4D<double>::operator/=(const Vector4D& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	w /= rhs.w;
	return *this;
}
bool Vector4D<double>::operator==(const Vector4D& rhs)
{
	return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
}
bool Vector4D<double>::operator!=(const Vector4D& rhs)
{
	return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
}
Vector4D<double> Vector4D<double>::operator+(const double& rhs)
{
	return Vector4D<double>(*this) += rhs;
}
Vector4D<double> Vector4D<double>::operator-(const double& rhs)
{
	return Vector4D<double>(*this) -= rhs;
}
Vector4D<double> Vector4D<double>::operator*(const double& rhs)
{
	return Vector4D<double>(*this) *= rhs;
}
Vector4D<double> Vector4D<double>::operator/(const double& rhs)
{
	return Vector4D<double>(*this) /= rhs;
}
Vector4D<double> Vector4D<double>::operator+=(const double& rhs)
{
	x += rhs;
	y += rhs;
	z += rhs;
	w += rhs;
	return *this;
}
Vector4D<double> Vector4D<double>::operator-=(const double& rhs)
{
	x -= rhs;
	y -= rhs;
	z -= rhs;
	w -= rhs;
	return *this;
}
Vector4D<double> Vector4D<double>::operator*=(const double& rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	w *= rhs;
	return *this;
}
Vector4D<double> Vector4D<double>::operator/=(const double& rhs)
{
	x /= rhs;
	y /= rhs;
	z /= rhs;
	w /= rhs;
	return *this;
}
bool Vector4D<double>::operator==(const double& rhs)
{
	return x == rhs && y == rhs && z == rhs && w == rhs;
}
bool Vector4D<double>::operator!=(const double& rhs)
{
	return x != rhs || y != rhs || z != rhs || w != rhs;
}
double Vector4D<double>::Dot(const Vector4D<double>& rhs)
{
	return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}
double Vector4D<double>::Magnitude()
{
	return sqrt(MagnitudeSquared());
}
double Vector4D<double>::MagnitudeSquared()
{
	return x * x + y * y + z * z + w * w;
}
void Vector4D<double>::Normalize()
{
	if(*this != 0.0f)
	{
		double M = Magnitude();
		x /= M;
		y /= M;
		z /= M;
		w /= M;
	}
}
Vector4D<double> Vector4D<double>::Normalized()
{
	Vector4D<double> temp(*this);
	temp.Normalize();
	return temp;
}
void Vector4D<double>::Invert()
{
	*this *= -1.0;
}
Vector4D<double> Vector4D<double>::Inverted()
{
	Vector4D<double> temp(*this);
	temp.Invert();
	return temp;
}
Vector3D<double> Vector4D<double>::GetVec3()
{
	return Vector3D<double>(x, y, z);
}