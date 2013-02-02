#ifndef MATRIX2D_H
#define MATRIX2D_H

#include "Vector2D.h"

//default template Matrix2D
template<class T>
struct Matrix2D
{
	T matrix[2][2];

	//T constructors
	Matrix2D()
	{
		matrix[0][0] = 0;
		matrix[0][1] = 0;
		matrix[1][0] = 0;
		matrix[1][1] = 0;
	}
	Matrix2D(T val)
	{
		matrix[0][0] = val;
		matrix[0][1] = val;
		matrix[1][0] = val;
		matrix[1][1] = val;
	}
	Matrix2D(T Ixx, T Ixy, T Iyx, T Iyy)
	{
		matrix[0][0] = Ixx;
		matrix[0][1] = Ixy;
		matrix[1][0] = Iyx;
		matrix[1][1] = Iyy;
	}
	Matrix2D(Vector2D<T> column0, Vector2D<T> column1)
	{
		matrix[0][0] = column0.x;
		matrix[0][1] = column1.x;
		matrix[1][0] = column0.y;
		matrix[1][1] = column1.y;
	}
	~Matrix2D()
	{
		//do nothing
	}

	//Matrix2D operators
	T operator[] (unsigned i)
	{
		if(i == 0)		return matrix[0][0];
		else if(i == 1) return matrix[0][1];
		else if(i == 2) return matrix[1][0];
		else			return matrix[1][1];
	}
	bool operator== (const Matrix2D& rhs)
	{
		if(matrix[0][0] != rhs.matrix[0][0])
		{
			return false;
		}
		else if(matrix[0][1] != rhs.matrix[0][1])
		{
			return false;
		}
		else if(matrix[1][0] != rhs.matrix[1][0])
		{
			return false;
		}
		else if(matrix[1][1] != rhs.matrix[1][1])
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	bool operator!= (const Matrix2D& rhs)
	{
		if(matrix[0][0] != rhs.matrix[0][0])
		{
			return true;
		}
		else if(matrix[0][1] != rhs.matrix[0][1])
		{
			return true;
		}
		else if(matrix[1][0] != rhs.matrix[1][0])
		{
			return true;
		}
		else if(matrix[1][1] != rhs.matrix[1][1])
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
		if(matrix[0][0] != rhs)
		{
			return false;
		}
		else if(matrix[0][1] != rhs)
		{
			return false;
		}
		else if(matrix[1][0] != rhs)
		{
			return false;
		}
		else if(matrix[1][1] != rhs)
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
		if(matrix[0][0] != rhs)
		{
			return true;
		}
		else if(matrix[0][1] != rhs)
		{
			return true;
		}
		else if(matrix[1][0] != rhs)
		{
			return true;
		}
		else if(matrix[1][1] != rhs)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

//float specific Matrix2D
template<>
struct Matrix2D<float>
{
	float matrix[2][2];

	//float constructors
	Matrix2D();
	Matrix2D(float val);
	Matrix2D(float Ixx, float Ixy, float Iyx, float Iyy);
	Matrix2D(Vector2D<float> column0, Vector2D<float> column1);
	~Matrix2D();
	
	//Matrix2D array operators
	float operator[] (unsigned i);
	//Matrix2D - Matrix2D operators
	Matrix2D operator+ (const Matrix2D& rhs);
	Matrix2D operator- (const Matrix2D& rhs);
	Matrix2D operator* (const Matrix2D& rhs);
	Matrix2D operator/ (const Matrix2D& rhs);
	Matrix2D operator+= (const Matrix2D& rhs);
	Matrix2D operator-= (const Matrix2D& rhs);
	Matrix2D operator*= (const Matrix2D& rhs);
	Matrix2D operator/= (const Matrix2D& rhs);
	bool operator== (const Matrix2D& rhs);
	bool operator!= (const Matrix2D& rhs);
	//Matrix2D - Vector2D operators
	Vector2D<float> operator* (const Vector2D<float>& rhs);
	//Matrix2D - float operators
	Matrix2D operator* (const float& rhs);
	Matrix2D operator*= (const float& rhs);
	bool operator== (const float& rhs);
	bool operator!= (const float& rhs);
	//Matrix2D math functions
	void Identity();
	void SetDiagonal(const float& Ixx, const float& Iyy);
	Vector2D<float> Transform(const Vector2D<float>& rhs);
	Vector2D<float> TransformTranspose(const Vector2D<float>& rhs);
	Vector2D<float> GetRow(unsigned i);
	Vector2D<float> GetColumn(unsigned i);
	void Invert();
	Matrix2D Inverted();
	void Transpose();
	Matrix2D Transposed();
	Matrix2D Lerp(const Matrix2D& rhs, const float& prop);
};

//double specific Matrix2D
template<>
struct Matrix2D<double>
{
	double matrix[2][2];

	//double constructors
	Matrix2D();
	Matrix2D(double val);
	Matrix2D(double Ixx, double Ixy, double Iyx, double Iyy);
	Matrix2D(Vector2D<double> column0, Vector2D<double> column1);
	~Matrix2D();
	
	//Matrix2D array operators
	double operator[] (unsigned i);
	//Matrix2D - Matrix2D operators
	Matrix2D operator+ (const Matrix2D& rhs);
	Matrix2D operator- (const Matrix2D& rhs);
	Matrix2D operator* (const Matrix2D& rhs);
	Matrix2D operator/ (const Matrix2D& rhs);
	Matrix2D operator+= (const Matrix2D& rhs);
	Matrix2D operator-= (const Matrix2D& rhs);
	Matrix2D operator*= (const Matrix2D& rhs);
	Matrix2D operator/= (const Matrix2D& rhs);
	bool operator== (const Matrix2D& rhs);
	bool operator!= (const Matrix2D& rhs);
	//Matrix2D - Vector2D operators
	Vector2D<double> operator* (const Vector2D<double>& rhs);
	//Matrix2D - double operators
	Matrix2D operator* (const double& rhs);
	Matrix2D operator*= (const double& rhs);
	bool operator== (const double& rhs);
	bool operator!= (const double& rhs);
	//Matrix2D math functions
	void Identity();
	void SetDiagonal(const double& Ixx, const double& Iyy);
	Vector2D<double> Transform(const Vector2D<double>& rhs);
	Vector2D<double> TransformTranspose(const Vector2D<double>& rhs);
	Vector2D<double> GetRow(unsigned i);
	Vector2D<double> GetColumn(unsigned i);
	void Invert();
	Matrix2D Inverted();
	void Transpose();
	Matrix2D Transposed();
	Matrix2D Lerp(const Matrix2D& rhs, const double& prop);
};

#endif //MATRIX2D_H