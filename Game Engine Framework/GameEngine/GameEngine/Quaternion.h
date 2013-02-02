#ifndef QUATERNION_H
#define QUATERNION_H

#include"Vector3D.h"

//default template Quaternion
template<class T>
struct Quaternion
{
	T x, y, z, w;

	//T constructors
	Quaternion()
	{
		//do nothing
	}
	Quaternion(T val)
	{
		x = val;
		y = val;
		z = val;
		w = val;
	}
	Quaternion(T x, T y, T z, T w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	Quaternion(Vector3D<T> vec3D, T w)
	{
		x = vec3D.x;
		y = vec3D.y;
		z = vec3D.z;
		this->w = w;
	}
	~Quaternion()
	{
		//do nothing
	}

	//Quaternion operators
	bool operator== (const Quaternion& rhs)
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
	bool operator!= (const Quaternion& rhs)
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
};

//float specific Quaternion
template<>
struct Quaternion<float>
{
	float x, y, z, w;

	//float constructors
	Quaternion();
	Quaternion(float val);
	Quaternion(float x, float y, float z, float w);
	Quaternion(Vector3D<float> vec3D, float w);
	~Quaternion();
	//Quaternion - Quaternion operators
	Quaternion operator+ (const Quaternion& rhs);
	Quaternion operator- (const Quaternion& rhs);
	Quaternion operator* (const Quaternion& rhs);
	Quaternion operator/ (const Quaternion& rhs);
	Quaternion operator+= (const Quaternion& rhs);
	Quaternion operator-= (const Quaternion& rhs);
	Quaternion operator*= (const Quaternion& rhs);
	Quaternion operator/= (const Quaternion& rhs);
	bool operator== (const Quaternion& rhs);
	bool operator!= (const Quaternion& rhs);
	//Quaternion - Vector3D operators
	Quaternion operator* (const Vector3D<float>& rhs);
	Quaternion operator*= (const Vector3D<float>& rhs);
	//Quaternion - float operators
	bool operator== (const float& rhs);
	bool operator!= (const float& rhs);
	//Quaternion math functions
	void Conjugate();
	Quaternion Conjugated();
	float Magnitude();
	float MagnitudeSquared();
	void Normalize();
	Quaternion normalized();
	void AddScaledVector(Vector3D<float> vec3D, float scale);
};

//double specific Quaternion
template<>
struct Quaternion<double>
{
	double x, y, z, w;

	//double constructors
	Quaternion();
	Quaternion(double val);
	Quaternion(double x, double y, double z, double w);
	Quaternion(Vector3D<double> vec3D, double w);
	~Quaternion();
	//Quaternion - Quaternion operators
	Quaternion operator+ (const Quaternion& rhs);
	Quaternion operator- (const Quaternion& rhs);
	Quaternion operator* (const Quaternion& rhs);
	Quaternion operator/ (const Quaternion& rhs);
	Quaternion operator+= (const Quaternion& rhs);
	Quaternion operator-= (const Quaternion& rhs);
	Quaternion operator*= (const Quaternion& rhs);
	Quaternion operator/= (const Quaternion& rhs);
	bool operator== (const Quaternion& rhs);
	bool operator!= (const Quaternion& rhs);
	//Quaternion - Vector3D operators
	Quaternion operator* (const Vector3D<double>& rhs);
	Quaternion operator*= (const Vector3D<double>& rhs);
	//Quaternion - double operators
	bool operator== (const double& rhs);
	bool operator!= (const double& rhs);
	//Quaternion math functions
	void Conjugate();
	Quaternion Conjugated();
	double Magnitude();
	double MagnitudeSquared();
	void Normalize();
	Quaternion normalized();
	void AddScaledVector(Vector3D<double> vec3D, double scale);
};

#endif //QUATERNION_H