#ifndef VECTOR4D_H
#define VECTOR4D_H

#include "Vector3D.h"

//default template Vector4D
template<class T>
struct Vector4D
{
	T x, y, z, w;

	//T constructors
	Vector4D()
	{
		//do nothing
	}
	Vector4D(T val)
	{
		x = val;
		y = val;
		z = val;
		w = val;
	}
	Vector4D(T x, T y, T z, T w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	Vector4D(Vector3D<T> vec3, T w)
	{
		x = vec3.x;
		y = vec3.y;
		z = vec3.z;
		this->w = w;
	}
	~Vector4D()
	{
		//do nothing
	}

	//Vector4D operators
	T operator[] (unsigned i)
	{
		if(i == 0)		return x;
		else if(i == 1)	return y;
		else if(i == 2)	return z;
		else			return w;
	}
	bool operator== (const Vector4D& rhs)
	{
		if(x != rhs.x)
		{
			return false;
		}
		else if(y != rhs.y)
		{
			return false;
		}
		else if(z != rhs.z)
		{
			return false;
		}
		else if(w != rhs.w)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	bool operator!= (const Vector4D& rhs)
	{
		if(x != rhs.x)
		{
			return true;
		}
		else if(y != rhs.y)
		{
			return true;
		}
		else if(z != rhs.z)
		{
			return true;
		}
		else if(w != rhs.w)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator== (const T& rhs)
	{
		if(x != rhs)
		{
			return false;
		}
		else if(y != rhs)
		{
			return false;
		}
		else if(z != rhs)
		{
			return false;
		}
		else if(w != rhs)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	bool operator!= (const T& rhs)
	{
		if(x != rhs)
		{
			return true;
		}
		else if(y != rhs)
		{
			return true;
		}
		else if(z != rhs)
		{
			return true;
		}
		else if(w != rhs)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//return function
	Vector3D<T> GetVec3()
	{
		return Vector3D<T>(x, y, z);
	}
};

//float specific Vector4D
template<>
struct Vector4D<float>
{
	float x, y, z, w;

	//float constructors
	Vector4D();
	Vector4D(float val);
	Vector4D(float x, float y, float z, float w);
	~Vector4D();
	//Vector4D array operator
	float operator[] (unsigned i);
	//Vector4D - Vector4D operators
	Vector4D operator+ (const Vector4D& rhs);
	Vector4D operator- (const Vector4D& rhs);
	Vector4D operator* (const Vector4D& rhs);
	Vector4D operator/ (const Vector4D& rhs);
	Vector4D operator+= (const Vector4D& rhs);
	Vector4D operator-= (const Vector4D& rhs);
	Vector4D operator*= (const Vector4D& rhs);
	Vector4D operator/= (const Vector4D& rhs);
	bool operator== (const Vector4D& rhs);
	bool operator!= (const Vector4D& rhs);
	//Vector4D - float operators
	Vector4D operator+ (const float& rhs);
	Vector4D operator- (const float& rhs);
	Vector4D operator* (const float& rhs);
	Vector4D operator/ (const float& rhs);
	Vector4D operator+= (const float& rhs);
	Vector4D operator-= (const float& rhs);
	Vector4D operator*= (const float& rhs);
	Vector4D operator/= (const float& rhs);
	bool operator== (const float& rhs);
	bool operator!= (const float& rhs);
	//Vector4D math functions
	float Dot(const Vector4D& rhs);
	float Magnitude();
	float MagnitudeSquared();
	void Normalize();
	Vector4D Normalized();
	void Invert();
	Vector4D Inverted();
	//return function
	Vector3D<float> GetVec3();
};

//double specific Vector4D
template<>
struct Vector4D<double>
{
	double x, y, z, w;

	//double constructors
	Vector4D();
	Vector4D(double val);
	Vector4D(double x, double y, double z, double w);
	~Vector4D();
	//Vector4D array operator
	double operator[] (unsigned i);
	//Vector4D - Vector4D operators
	Vector4D operator+ (const Vector4D& rhs);
	Vector4D operator- (const Vector4D& rhs);
	Vector4D operator* (const Vector4D& rhs);
	Vector4D operator/ (const Vector4D& rhs);
	Vector4D operator+= (const Vector4D& rhs);
	Vector4D operator-= (const Vector4D& rhs);
	Vector4D operator*= (const Vector4D& rhs);
	Vector4D operator/= (const Vector4D& rhs);
	bool operator== (const Vector4D& rhs);
	bool operator!= (const Vector4D& rhs);
	//Vector4D - float operators
	Vector4D operator+ (const double& rhs);
	Vector4D operator- (const double& rhs);
	Vector4D operator* (const double& rhs);
	Vector4D operator/ (const double& rhs);
	Vector4D operator+= (const double& rhs);
	Vector4D operator-= (const double& rhs);
	Vector4D operator*= (const double& rhs);
	Vector4D operator/= (const double& rhs);
	bool operator== (const double& rhs);
	bool operator!= (const double& rhs);
	//Vector4D math functions
	double Dot(const Vector4D<double>& rhs);
	double Magnitude();
	double MagnitudeSquared();
	void Normalize();
	Vector4D Normalized();
	void Invert();
	Vector4D Inverted();
	//return function
	Vector3D<double> GetVec3();
};

#endif //VECTOR4D_H