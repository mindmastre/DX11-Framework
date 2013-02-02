#include "Quaternion.h"
#include <cmath>

/////////////////////////////////////////////////
//               float template
/////////////////////////////////////////////////
Quaternion<float>::Quaternion()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 1.0f;
}
Quaternion<float>::Quaternion(float val)
{
	x = val;
	y = val;
	z = val;
	w = val;
}
Quaternion<float>::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
Quaternion<float>::Quaternion(Vector3D<float> vec3D, float w)
{
	x = vec3D.x;
	y = vec3D.y;
	z = vec3D.z;
	this->w = w;
}
Quaternion<float>::~Quaternion()
{
	//do nothing
}
Quaternion<float> Quaternion<float>::operator+(const Quaternion& rhs)
{
	return Quaternion<float>(*this) += rhs;
}
Quaternion<float> Quaternion<float>::operator-(const Quaternion& rhs)
{
	return Quaternion<float>(*this) -= rhs;
}
Quaternion<float> Quaternion<float>::operator*(const Quaternion& rhs)
{
	return Quaternion<float>(*this) *= rhs;
}
Quaternion<float> Quaternion<float>::operator/(const Quaternion& rhs)
{
	return Quaternion<float>(*this) /= rhs;
}
Quaternion<float> Quaternion<float>::operator+=(const Quaternion& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	return *this;
}
Quaternion<float> Quaternion<float>::operator-=(const Quaternion& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
	return *this;
}
Quaternion<float> Quaternion<float>::operator*=(const Quaternion& rhs)
{
	float tx = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
	float ty = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
	float tz = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;
	float tw = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
	x = tx;
	y = ty;
	z = tz;
	w = tw;
	return *this;
}
Quaternion<float> Quaternion<float>::operator/=(const Quaternion& rhs)
{
	Quaternion<float> temp(rhs);
	float M = temp.MagnitudeSquared();
	temp.Conjugate();
	temp.x /= M;
	temp.y /= M;
	temp.z /= M;
	temp.w /= M;
	return *this *= temp;
}
bool Quaternion<float>::operator==(const Quaternion& rhs)
{
	return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
}
bool Quaternion<float>::operator!=(const Quaternion& rhs)
{
	return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
}
Quaternion<float> Quaternion<float>::operator*(const Vector3D<float>& rhs)
{
	return Quaternion<float>(*this) *= rhs;
}
Quaternion<float> Quaternion<float>::operator*=(const Vector3D<float>& rhs)
{
	Quaternion<float> temp(rhs, 0.0f);
	*this *= temp;
	return *this;
}
bool Quaternion<float>::operator==(const float& rhs)
{
	return x == rhs && y == rhs && z == rhs && w == rhs;
}
bool Quaternion<float>::operator!=(const float& rhs)
{
	return x != rhs || y != rhs || z != rhs || w != rhs;
}
void Quaternion<float>::Conjugate()
{
	x *= -1.0f;
	y *= -1.0f;
	z *= -1.0f;
}
Quaternion<float> Quaternion<float>::Conjugated()
{
	Quaternion<float> temp(*this);
	temp.Conjugate();
	return temp;
}
float Quaternion<float>::Magnitude()
{
	return sqrt(MagnitudeSquared());
}
float Quaternion<float>::MagnitudeSquared()
{
	return x * x + y * y + z * z + w * w;
}
void Quaternion<float>::Normalize()
{
	if(*this != 0.0f)
	{
		float M = Magnitude();
		x /= M;
		y /= M;
		z /= M;
		w /= M;
	}
	else
	{
		w = 1.0f;
	}
}
Quaternion<float> Quaternion<float>::normalized()
{
	Quaternion<float> temp(*this);
	temp.Normalize();
	return temp;
}
void Quaternion<float>::AddScaledVector(Vector3D<float> vec3D, float scale)
{
	Quaternion<float> temp(vec3D * scale, 0.0f);
	temp *= *this;
	x += temp.x * 0.5f;
	y += temp.y * 0.5f;
	z += temp.z * 0.5f;
	w += temp.w * 0.5f;
}
/////////////////////////////////////////////////
//                double template
/////////////////////////////////////////////////
Quaternion<double>::Quaternion()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
	w = 1.0;
}
Quaternion<double>::Quaternion(double val)
{
	x = val;
	y = val;
	z = val;
	w = val;
}
Quaternion<double>::Quaternion(double x, double y, double z, double w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
Quaternion<double>::Quaternion(Vector3D<double> vec3D, double w)
{
	x = vec3D.x;
	y = vec3D.y;
	z = vec3D.z;
	this->w = w;
}
Quaternion<double>::~Quaternion()
{
	//do nothing
}
Quaternion<double> Quaternion<double>::operator+(const Quaternion& rhs)
{
	return Quaternion<double>(*this) += rhs;
}
Quaternion<double> Quaternion<double>::operator-(const Quaternion& rhs)
{
	return Quaternion<double>(*this) -= rhs;
}
Quaternion<double> Quaternion<double>::operator*(const Quaternion& rhs)
{
	return Quaternion<double>(*this) *= rhs;
}
Quaternion<double> Quaternion<double>::operator/(const Quaternion& rhs)
{
	return Quaternion<double>(*this) /= rhs;
}
Quaternion<double> Quaternion<double>::operator+=(const Quaternion& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	return *this;
}
Quaternion<double> Quaternion<double>::operator-=(const Quaternion& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
	return *this;
}
Quaternion<double> Quaternion<double>::operator*=(const Quaternion& rhs)
{
	double tx = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
	double ty = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
	double tz = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;
	double tw = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
	x = tx;
	y = ty;
	z = tz;
	w = tw;
	return *this;
}
Quaternion<double> Quaternion<double>::operator/=(const Quaternion& rhs)
{
	Quaternion<double> temp(rhs);
	double M = temp.MagnitudeSquared();
	temp.Conjugate();
	temp.x /= M;
	temp.y /= M;
	temp.z /= M;
	temp.w /= M;
	return *this *= temp;
}
bool Quaternion<double>::operator==(const Quaternion& rhs)
{
	return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
}
bool Quaternion<double>::operator!=(const Quaternion& rhs)
{
	return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
}
Quaternion<double> Quaternion<double>::operator*(const Vector3D<double>& rhs)
{
	return Quaternion<double>(*this) *= rhs;
}
Quaternion<double> Quaternion<double>::operator*=(const Vector3D<double>& rhs)
{
	Quaternion<double> temp(rhs, 0.0f);
	*this *= temp;
	return *this;
}
bool Quaternion<double>::operator==(const double& rhs)
{
	return x == rhs && y == rhs && z == rhs && w == rhs;
}
bool Quaternion<double>::operator!=(const double& rhs)
{
	return x != rhs || y != rhs || z != rhs || w != rhs;
}
void Quaternion<double>::Conjugate()
{
	x *= -1.0;
	y *= -1.0;
	z *= -1.0;
}
Quaternion<double> Quaternion<double>::Conjugated()
{
	Quaternion<double> temp(*this);
	temp.Conjugate();
	return temp;
}
double Quaternion<double>::Magnitude()
{
	return sqrt(MagnitudeSquared());
}
double Quaternion<double>::MagnitudeSquared()
{
	return x * x + y * y + z * z + w * w;
}
void Quaternion<double>::Normalize()
{
	if(*this != 0.0f)
	{
		double M = Magnitude();
		x /= M;
		y /= M;
		z /= M;
		w /= M;
	}
	else
	{
		w = 1.0f;
	}
}
Quaternion<double> Quaternion<double>::normalized()
{
	Quaternion<double> temp(*this);
	temp.Normalize();
	return temp;
}
void Quaternion<double>::AddScaledVector(Vector3D<double> vec3D, double scale)
{
	Quaternion<double> temp(vec3D * scale, 0.0f);
	temp *= *this;
	x += temp.x * 0.5;
	y += temp.y * 0.5;
	z += temp.z * 0.5;
	w += temp.w * 0.5;
}