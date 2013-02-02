#include "Vector3D.h"
#include <cmath>

/////////////////////////////////////////////////
//               float template
/////////////////////////////////////////////////
Vector3D<float>::Vector3D()
{
	//do nothing
}
Vector3D<float>::Vector3D(float val)
{
	x = val;
	y = val;
	z = val;
}
Vector3D<float>::Vector3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector3D<float>::~Vector3D()
{
	//do nothing
}
float Vector3D<float>::operator[](unsigned i)
{
	if(i == 0)		return x;
	else if(i == 1) return y;
	else			return z;
}
Vector3D<float> Vector3D<float>::operator+(const Vector3D& rhs)
{
	return Vector3D<float>(*this) += rhs;
}
Vector3D<float> Vector3D<float>::operator-(const Vector3D& rhs)
{
	return Vector3D<float>(*this) -= rhs;
}
Vector3D<float> Vector3D<float>::operator*(const Vector3D& rhs)
{
	return Vector3D<float>(*this) *= rhs;
}
Vector3D<float> Vector3D<float>::operator/(const Vector3D& rhs)
{
	return Vector3D<float>(*this) /= rhs;
}
Vector3D<float> Vector3D<float>::operator+=(const Vector3D& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}
Vector3D<float> Vector3D<float>::operator-=(const Vector3D& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}
Vector3D<float> Vector3D<float>::operator*=(const Vector3D& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}
Vector3D<float> Vector3D<float>::operator/=(const Vector3D& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	return *this;
}
bool Vector3D<float>::operator==(const Vector3D& rhs)
{
	return x == rhs.x && y == rhs.y && z == rhs.z;
}
bool Vector3D<float>::operator!=(const Vector3D& rhs)
{
	return x != rhs.x || y != rhs.y || z != rhs.z;
}
Vector3D<float> Vector3D<float>::operator+(const float& rhs)
{
	return Vector3D<float>(*this) += rhs;
}
Vector3D<float> Vector3D<float>::operator-(const float& rhs)
{
	return Vector3D<float>(*this) -= rhs;
}
Vector3D<float> Vector3D<float>::operator*(const float& rhs)
{
	return Vector3D<float>(*this) *= rhs;
}
Vector3D<float> Vector3D<float>::operator/(const float& rhs)
{
	return Vector3D<float>(*this) /= rhs;
}
Vector3D<float> Vector3D<float>::operator+=(const float& rhs)
{
	x += rhs;
	y += rhs;
	z += rhs;
	return *this;
}
Vector3D<float> Vector3D<float>::operator-=(const float& rhs)
{
	x -= rhs;
	y -= rhs;
	z -= rhs;
	return *this;
}
Vector3D<float> Vector3D<float>::operator*=(const float& rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}
Vector3D<float> Vector3D<float>::operator/=(const float& rhs)
{
	x /= rhs;
	y /= rhs;
	z /= rhs;
	return *this;
}
bool Vector3D<float>::operator==(const float& rhs)
{
	return x == rhs && y == rhs && z == rhs;
}
bool Vector3D<float>::operator!=(const float& rhs)
{
	return x != rhs || y != rhs || z != rhs;
}
float Vector3D<float>::Dot(const Vector3D<float>& rhs)
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}
Vector3D<float> Vector3D<float>::Cross(const Vector3D<float>& rhs)
{
	Vector3D<float> temp;
	temp.x = y * rhs.z - z * rhs.y;
	temp.y = z * rhs.x - x * rhs.z;
	temp.z = x * rhs.y - y * rhs.x;
	return temp;
}
float Vector3D<float>::Magnitude()
{
	return sqrt(MagnitudeSquared());
}
float Vector3D<float>::MagnitudeSquared()
{
	return x * x + y * y + z * z;
}
void Vector3D<float>::Normalize()
{
	if(*this != 0.0f)
	{
		float M = Magnitude();
		x /= M;
		y /= M;
		z /= M;
	}
}
Vector3D<float> Vector3D<float>::Normalized()
{
	Vector3D<float> temp(*this);
	temp.Normalize();
	return temp;
}
void Vector3D<float>::Invert()
{
	*this *= -1.0f;
}
Vector3D<float> Vector3D<float>::Inverted()
{
	Vector3D<float> temp(*this);
	temp.Invert();
	return temp;
}
Vector3D<float> Vector3D<float>::Orthonormal(Vector3D<float>& A, Vector3D<float>& B)
{
	Vector3D<float> C;
	C = A.Cross(B);
	if(C == 0.0f)
	{
		return Vector3D(0.0f, 0.0f, 0.0f);
	}
	B = C.Cross(A);
	A.Normalize();
	B.Normalize();
	C.Normalize();
	return C;
}
/////////////////////////////////////////////////
//                double template
/////////////////////////////////////////////////
Vector3D<double>::Vector3D()
{
	//do nothing
}
Vector3D<double>::Vector3D(double val)
{
	x = val;
	y = val;
	z = val;
}
Vector3D<double>::Vector3D(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector3D<double>::~Vector3D()
{
	//do nothing
}
double Vector3D<double>::operator[](unsigned i)
{
	if(i == 0)		return x;
	else if(i == 1) return y;
	else			return z;
}
Vector3D<double> Vector3D<double>::operator+(const Vector3D& rhs)
{
	return Vector3D<double>(*this) += rhs;
}
Vector3D<double> Vector3D<double>::operator-(const Vector3D& rhs)
{
	return Vector3D<double>(*this) -= rhs;
}
Vector3D<double> Vector3D<double>::operator*(const Vector3D& rhs)
{
	return Vector3D<double>(*this) *= rhs;
}
Vector3D<double> Vector3D<double>::operator/(const Vector3D& rhs)
{
	return Vector3D<double>(*this) /= rhs;
}
Vector3D<double> Vector3D<double>::operator+=(const Vector3D& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}
Vector3D<double> Vector3D<double>::operator-=(const Vector3D& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}
Vector3D<double> Vector3D<double>::operator*=(const Vector3D& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}
Vector3D<double> Vector3D<double>::operator/=(const Vector3D& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	return *this;
}
bool Vector3D<double>::operator==(const Vector3D& rhs)
{
	return x == rhs.x && y == rhs.y && z == rhs.z;
}
bool Vector3D<double>::operator!=(const Vector3D& rhs)
{
	return x != rhs.x || y != rhs.y || z != rhs.z;
}
Vector3D<double> Vector3D<double>::operator+(const double& rhs)
{
	return Vector3D<double>(*this) += rhs;
}
Vector3D<double> Vector3D<double>::operator-(const double& rhs)
{
	return Vector3D<double>(*this) -= rhs;
}
Vector3D<double> Vector3D<double>::operator*(const double& rhs)
{
	return Vector3D<double>(*this) *= rhs;
}
Vector3D<double> Vector3D<double>::operator/(const double& rhs)
{
	return Vector3D<double>(*this) /= rhs;
}
Vector3D<double> Vector3D<double>::operator+=(const double& rhs)
{
	x += rhs;
	y += rhs;
	z += rhs;
	return *this;
}
Vector3D<double> Vector3D<double>::operator-=(const double& rhs)
{
	x -= rhs;
	y -= rhs;
	z -= rhs;
	return *this;
}
Vector3D<double> Vector3D<double>::operator*=(const double& rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}
Vector3D<double> Vector3D<double>::operator/=(const double& rhs)
{
	x /= rhs;
	y /= rhs;
	z /= rhs;
	return *this;
}
bool Vector3D<double>::operator==(const double& rhs)
{
	return x == rhs && y == rhs && z == rhs;
}
bool Vector3D<double>::operator!=(const double& rhs)
{
	return x != rhs || y != rhs || z != rhs;
}
double Vector3D<double>::Dot(const Vector3D<double>& rhs)
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}
Vector3D<double> Vector3D<double>::Cross(const Vector3D<double>& rhs)
{
	Vector3D<double> temp;
	temp.x = y * rhs.z - z * rhs.y;
	temp.y = z * rhs.x - x * rhs.z;
	temp.z = x * rhs.y - y * rhs.x;
	return temp;
}
double Vector3D<double>::Magnitude()
{
	return sqrt(MagnitudeSquared());
}
double Vector3D<double>::MagnitudeSquared()
{
	return x * x + y * y + z * z;
}
void Vector3D<double>::Normalize()
{
	if(*this != 0.0f)
	{
		double M = Magnitude();
		x /= M;
		y /= M;
		z /= M;
	}
}
Vector3D<double> Vector3D<double>::Normalized()
{
	Vector3D<double> temp(*this);
	temp.Normalize();
	return temp;
}
void Vector3D<double>::Invert()
{
	*this *= -1.0;
}
Vector3D<double> Vector3D<double>::Inverted()
{
	Vector3D<double> temp(*this);
	temp.Invert();
	return temp;
}
Vector3D<double> Vector3D<double>::Orthonormal(Vector3D<double>& A, Vector3D<double>& B)
{
	Vector3D<double> C;
	C = A.Cross(B);
	if(C == 0.0f)
	{
		return Vector3D(0.0f, 0.0f, 0.0f);
	}
	B = C.Cross(A);
	A.Normalize();
	B.Normalize();
	C.Normalize();
	return C;
}