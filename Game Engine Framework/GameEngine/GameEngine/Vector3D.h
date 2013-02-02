#ifndef VECTOR3D_H
#define VECTOR3D_H

//default template Vector3D
template<class T>
struct Vector3D
{
	T x, y, z;

	//T constructors
	Vector3D()
	{
		//do nothing
	}
	Vector3D(T val)
	{
		x = val;
		y = val;
		z = val;
	}
	Vector3D(T x, T y, T z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	~Vector3D()
	{
		//do nothing
	}

	//Vector3D operators
	T operator[] (unsigned i)
	{
		if(i == 0)		return x;
		else if(i == 1)	return y;
		else			return z;
	}
	bool operator== (const Vector3D& rhs)
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
		else
		{
			return true;
		}
	}
	bool operator!= (const Vector3D& rhs)
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
		else
		{
			return false;
		}
	}
};

//float specific Vector3D
template<>
struct Vector3D<float>
{
	float x, y, z;

	//float constructors
	Vector3D();
	Vector3D(float val);
	Vector3D(float x, float y, float z);
	~Vector3D();
	//Vector3D array operator
	float operator[] (unsigned i);
	//Vector3D - Vector3D operators
	Vector3D operator+ (const Vector3D& rhs);
	Vector3D operator- (const Vector3D& rhs);
	Vector3D operator* (const Vector3D& rhs);
	Vector3D operator/ (const Vector3D& rhs);
	Vector3D operator+= (const Vector3D& rhs);
	Vector3D operator-= (const Vector3D& rhs);
	Vector3D operator*= (const Vector3D& rhs);
	Vector3D operator/= (const Vector3D& rhs);
	bool operator== (const Vector3D& rhs);
	bool operator!= (const Vector3D& rhs);
	//Vector3D - float operators
	Vector3D operator+ (const float& rhs);
	Vector3D operator- (const float& rhs);
	Vector3D operator* (const float& rhs);
	Vector3D operator/ (const float& rhs);
	Vector3D operator+= (const float& rhs);
	Vector3D operator-= (const float& rhs);
	Vector3D operator*= (const float& rhs);
	Vector3D operator/= (const float& rhs);
	bool operator== (const float& rhs);
	bool operator!= (const float& rhs);
	//Vector3D math functions
	float Dot(const Vector3D& rhs);
	Vector3D<float> Cross(const Vector3D& rhs);
	float Magnitude();
	float MagnitudeSquared();
	void Normalize();
	Vector3D Normalized();
	void Invert();
	Vector3D Inverted();
	Vector3D Orthonormal(Vector3D& A, Vector3D& B);
};

//double specific Vector3D
template<>
struct Vector3D<double>
{
	double x, y, z;

	//double constructors
	Vector3D();
	Vector3D(double val);
	Vector3D(double x, double y, double z);
	~Vector3D();
	//Vector3D array operator
	double operator[] (unsigned i);
	//Vector3D - Vector3D operators
	Vector3D operator+ (const Vector3D& rhs);
	Vector3D operator- (const Vector3D& rhs);
	Vector3D operator* (const Vector3D& rhs);
	Vector3D operator/ (const Vector3D& rhs);
	Vector3D operator+= (const Vector3D& rhs);
	Vector3D operator-= (const Vector3D& rhs);
	Vector3D operator*= (const Vector3D& rhs);
	Vector3D operator/= (const Vector3D& rhs);
	bool operator== (const Vector3D& rhs);
	bool operator!= (const Vector3D& rhs);
	//Vector3D - float operators
	Vector3D operator+ (const double& rhs);
	Vector3D operator- (const double& rhs);
	Vector3D operator* (const double& rhs);
	Vector3D operator/ (const double& rhs);
	Vector3D operator+= (const double& rhs);
	Vector3D operator-= (const double& rhs);
	Vector3D operator*= (const double& rhs);
	Vector3D operator/= (const double& rhs);
	bool operator== (const double& rhs);
	bool operator!= (const double& rhs);
	//Vector3D math functions
	double Dot(const Vector3D<double>& rhs);
	Vector3D<double> Cross(const Vector3D<double>& rhs);
	double Magnitude();
	double MagnitudeSquared();
	void Normalize();
	Vector3D Normalized();
	void Invert();
	Vector3D Inverted();
	Vector3D Orthonormal(Vector3D& A, Vector3D& B);
};

#endif //Vector3D_H