#ifndef MATRIX3D_H
#define MATRIX3D_H

#include "Vector3D.h"
#include "Quaternion.h"

//default template Matrix3D
template<class T>
struct Matrix3D
{
	T matrix[3][3];

	//T constructors
	Matrix3D()
	{
		matrix[0][0] = 0;
		matrix[0][1] = 0;
		matrix[0][2] = 0;
		matrix[1][0] = 0;
		matrix[1][1] = 0;
		matrix[1][2] = 0;
		matrix[2][0] = 0;
		matrix[2][1] = 0;
		matrix[2][2] = 0;
	}
	Matrix3D(T val)
	{
		matrix[0][0] = val;
		matrix[0][1] = val;
		matrix[0][2] = val;
		matrix[1][0] = val;
		matrix[1][1] = val;
		matrix[1][2] = val;
		matrix[2][0] = val;
		matrix[2][1] = val;
		matrix[2][2] = val;
	}
	Matrix3D(T Ixx, T Ixy, T Ixz,
			 T Iyx, T Iyy, T Iyz,
			 T Izx, T Izy, T Izz)
	{
		matrix[0][0] = Ixx;
		matrix[0][1] = Ixy;
		matrix[0][2] = Ixz;
		matrix[1][0] = Iyx;
		matrix[1][1] = Iyy;
		matrix[1][2] = Iyz;
		matrix[2][0] = Izx;
		matrix[2][1] = Izy;
		matrix[2][2] = Izz;
	}
	Matrix3D(Vector3D<T> column0,
			 Vector3D<T> column1,
			 Vector3D<T> column2)
	{
		matrix[0][0] = column0.x;
		matrix[0][1] = column1.x;
		matrix[0][2] = column2.x;
		matrix[1][0] = column0.y;
		matrix[1][1] = column1.y;
		matrix[1][2] = column2.y;
		matrix[2][0] = column0.z;
		matrix[2][1] = column1.z;
		matrix[2][2] = column2.z;
	}
	~Matrix3D()
	{
		//do nothing
	}

	//Matrix3D operators
	T operator[] (unsigned i)
	{
		if(i == 0)		return matrix[0][0];
		else if(i == 1) return matrix[0][1];
		else if(i == 2) return matrix[0][2];
		else if(i == 3) return matrix[1][0];
		else if(i == 4) return matrix[1][1];
		else if(i == 5) return matrix[1][2];
		else if(i == 6) return matrix[2][0];
		else if(i == 7) return matrix[2][1];
		else			return matrix[2][2];
	}
	bool operator== (const Matrix3D& rhs)
	{
		if(matrix[0][0] != rhs.matrix[0][0])
		{
			return false;
		}
		else if(matrix[0][1] != rhs.matrix[0][1])
		{
			return false;
		}
		else if(matrix[0][2] != rhs.matrix[0][2])
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
		else if(matrix[1][2] != rhs.matrix[1][2])
		{
			return false;
		}
		else if(matrix[2][0] != rhs.matrix[2][0])
		{
			return false;
		}
		else if(matrix[2][1] != rhs.matrix[2][1])
		{
			return false;
		}
		else if(matrix[2][2] != rhs.matrix[2][2])
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	bool operator!= (const Matrix3D& rhs)
	{
		if(matrix[0][0] != rhs.matrix[0][0])
		{
			return true;
		}
		else if(matrix[0][1] != rhs.matrix[0][1])
		{
			return true;
		}
		else if(matrix[0][2] != rhs.matrix[0][2])
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
		else if(matrix[1][2] != rhs.matrix[1][2])
		{
			return true;
		}
		else if(matrix[2][0] != rhs.matrix[2][0])
		{
			return true;
		}
		else if(matrix[2][1] != rhs.matrix[2][1])
		{
			return true;
		}
		else if(matrix[2][2] != rhs.matrix[2][2])
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
		else if(matrix[0][2] != rhs)
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
		else if(matrix[1][2] != rhs)
		{
			return false;
		}
		else if(matrix[2][0] != rhs)
		{
			return false;
		}
		else if(matrix[2][1] != rhs)
		{
			return false;
		}
		else if(matrix[2][2] != rhs)
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
		else if(matrix[0][2] != rhs)
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
		else if(matrix[1][2] != rhs)
		{
			return true;
		}
		else if(matrix[2][0] != rhs)
		{
			return true;
		}
		else if(matrix[2][1] != rhs)
		{
			return true;
		}
		else if(matrix[2][2] != rhs)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

//float specific Matrix3D
template<>
struct Matrix3D<float>
{
	float matrix[3][3];

	//float constructors
	Matrix3D();
	Matrix3D(float val);
	Matrix3D(float Ixx, float Ixy, float Ixz,
			 float Iyx, float Iyy, float Iyz,
			 float Izx, float Izy, float Izz);
	Matrix3D(Vector3D<float> column0,
			 Vector3D<float> column1,
			 Vector3D<float> column2);
	~Matrix3D();
	
	//Matrix3D array operators
	float operator[] (unsigned i);
	//Matrix3D - Matrix3D operators
	Matrix3D operator+ (const Matrix3D& rhs);
	Matrix3D operator- (const Matrix3D& rhs);
	Matrix3D operator* (const Matrix3D& rhs);
	Matrix3D operator/ (const Matrix3D& rhs);
	Matrix3D operator+= (const Matrix3D& rhs);
	Matrix3D operator-= (const Matrix3D& rhs);
	Matrix3D operator*= (const Matrix3D& rhs);
	Matrix3D operator/= (const Matrix3D& rhs);
	bool operator== (const Matrix3D& rhs);
	bool operator!= (const Matrix3D& rhs);
	//Matrix3D - Vector2D operators
	Vector3D<float> operator* (const Vector3D<float>& rhs);
	//Matrix3D - float operators
	Matrix3D operator* (const float& rhs);
	Matrix3D operator*= (const float& rhs);
	bool operator== (const float& rhs);
	bool operator!= (const float& rhs);
	//Matrix3D math functions
	void Identity();
	void SetDiagonal(const float& Ixx, const float& Iyy, const float& Izz);
	Vector3D<float> Transform(const Vector3D<float>& rhs);
	Vector3D<float> TransformTranspose(const Vector3D<float>& rhs);
	void SetRotation(const Quaternion<float>& rhs);
	Vector3D<float> GetRow(unsigned i);
	Vector3D<float> GetColumn(unsigned i);
	void Invert();
	Matrix3D Inverted();
	void Transpose();
	Matrix3D Transposed();
	Matrix3D Lerp(const Matrix3D& rhs, const float& prop);
};

//double specific Matrix3D
template<>
struct Matrix3D<double>
{
	double matrix[3][3];

	//double constructors
	Matrix3D();
	Matrix3D(double val);
	Matrix3D(double Ixx, double Ixy, double Ixz,
			 double Iyx, double Iyy, double Iyz,
			 double Izx, double Izy, double Izz);
	Matrix3D(Vector3D<double> column0,
			 Vector3D<double> column1,
			 Vector3D<double> column2);
	~Matrix3D();
	
	//Matrix3D array operators
	double operator[] (unsigned i);
	//Matrix3D - Matrix3D operators
	Matrix3D operator+ (const Matrix3D& rhs);
	Matrix3D operator- (const Matrix3D& rhs);
	Matrix3D operator* (const Matrix3D& rhs);
	Matrix3D operator/ (const Matrix3D& rhs);
	Matrix3D operator+= (const Matrix3D& rhs);
	Matrix3D operator-= (const Matrix3D& rhs);
	Matrix3D operator*= (const Matrix3D& rhs);
	Matrix3D operator/= (const Matrix3D& rhs);
	bool operator== (const Matrix3D& rhs);
	bool operator!= (const Matrix3D& rhs);
	//Matrix3D - Vector2D operators
	Vector3D<double> operator* (const Vector3D<double>& rhs);
	//Matrix3D - double operators
	Matrix3D operator* (const double& rhs);
	Matrix3D operator*= (const double& rhs);
	bool operator== (const double& rhs);
	bool operator!= (const double& rhs);
	//Matrix3D math functions
	void Identity();
	void SetDiagonal(const double& Ixx, const double& Iyy, const double& Izz);
	Vector3D<double> Transform(const Vector3D<double>& rhs);
	Vector3D<double> TransformTranspose(const Vector3D<double>& rhs);
	void SetRotation(const Quaternion<double>& rhs);
	Vector3D<double> GetRow(unsigned i);
	Vector3D<double> GetColumn(unsigned i);
	void Invert();
	Matrix3D Inverted();
	void Transpose();
	Matrix3D Transposed();
	Matrix3D Lerp(const Matrix3D& rhs, const double& prop);
};

#endif //MATRIX3D_H