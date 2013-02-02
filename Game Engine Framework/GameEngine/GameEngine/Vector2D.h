#ifndef VECTOR2D_H
#define VECTOR2D_H

//default template Vector2D
template<class T>
struct Vector2D
{
	T x, y;

	//T constructors
	Vector2D()
	{
		//do nothing
	}
	Vector2D(T val)
	{
		x = val;
		y = val;
	}
	Vector2D(T x, T y)
	{
		this->x = x;
		this->y = y;
	}
	~Vector2D()
	{
		//do nothing
	}

	//Vector2D operators
	T operator[] (unsigned i)
	{
		if(i == 0)	return x;
		else		return y;
	}
	bool operator== (const Vector2D& rhs)
	{
		if(x != rhs.x)
		{
			return false;
		}
		else if(y != rhs.y)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	bool operator!= (const Vector2D& rhs)
	{
		if(x != rhs.x)
		{
			return true;
		}
		else if(y != rhs.y)
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
		else
		{
			return false;
		}
	}
};

//float specific Vector2D
template<>
struct Vector2D<float>
{
	float x, y;

	//float constructors
	Vector2D();
	Vector2D(float val);
	Vector2D(float x, float y);
	~Vector2D();
	//Vector2D array operator
	float operator[] (unsigned i);
	//Vector2D - Vector2D operators
	Vector2D operator+ (const Vector2D& rhs);
	Vector2D operator- (const Vector2D& rhs);
	Vector2D operator* (const Vector2D& rhs);
	Vector2D operator/ (const Vector2D& rhs);
	Vector2D operator+= (const Vector2D& rhs);
	Vector2D operator-= (const Vector2D& rhs);
	Vector2D operator*= (const Vector2D& rhs);
	Vector2D operator/= (const Vector2D& rhs);
	bool operator== (const Vector2D& rhs);
	bool operator!= (const Vector2D& rhs);
	//Vector2D - float operators
	Vector2D operator+ (const float& rhs);
	Vector2D operator- (const float& rhs);
	Vector2D operator* (const float& rhs);
	Vector2D operator/ (const float& rhs);
	Vector2D operator+= (const float& rhs);
	Vector2D operator-= (const float& rhs);
	Vector2D operator*= (const float& rhs);
	Vector2D operator/= (const float& rhs);
	bool operator== (const float& rhs);
	bool operator!= (const float& rhs);
	//Vector2D math functions
	float Dot(const Vector2D<float>& rhs);
	float Cross(const Vector2D<float>& rhs);
	float Magnitude();
	float MagnitudeSquared();
	void Normalize();
	Vector2D Normalized();
	void Invert();
	Vector2D Inverted();
};

//double specific Vector2D
template<>
struct Vector2D<double>
{
	double x, y;

	//float constructors
	Vector2D();
	Vector2D(double val);
	Vector2D(double x, double y);
	~Vector2D();
	//Vector2D array operator
	double operator[] (unsigned i);
	//Vector2D - Vector2D operators
	Vector2D operator+ (const Vector2D& rhs);
	Vector2D operator- (const Vector2D& rhs);
	Vector2D operator* (const Vector2D& rhs);
	Vector2D operator/ (const Vector2D& rhs);
	Vector2D operator+= (const Vector2D& rhs);
	Vector2D operator-= (const Vector2D& rhs);
	Vector2D operator*= (const Vector2D& rhs);
	Vector2D operator/= (const Vector2D& rhs);
	bool operator== (const Vector2D& rhs);
	bool operator!= (const Vector2D& rhs);
	//Vector2D - float operators
	Vector2D operator+ (const double& rhs);
	Vector2D operator- (const double& rhs);
	Vector2D operator* (const double& rhs);
	Vector2D operator/ (const double& rhs);
	Vector2D operator+= (const double& rhs);
	Vector2D operator-= (const double& rhs);
	Vector2D operator*= (const double& rhs);
	Vector2D operator/= (const double& rhs);
	bool operator== (const double& rhs);
	bool operator!= (const double& rhs);
	//Vector2D math functions
	double Dot(const Vector2D<double>& rhs);
	double Cross(const Vector2D<double>& rhs);
	double Magnitude();
	double MagnitudeSquared();
	void Normalize();
	Vector2D Normalized();
	void Invert();
	Vector2D Inverted();
};

#endif //VECTOR2D_H