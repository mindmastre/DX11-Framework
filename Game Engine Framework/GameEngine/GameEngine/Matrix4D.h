#ifndef MATRIX4D_H
#define MATRIX4D_H

#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix3D.h"
#include "Quaternion.h"

//default template Matrix4D
template<class T>
struct Matrix4D
{
	T matrix[4][4];

	//T constructors
	Matrix4D()
	{
		matrix[0][0] = 0;
		matrix[0][1] = 0;
		matrix[0][2] = 0;
		matrix[0][3] = 0;
		matrix[1][0] = 0;
		matrix[1][1] = 0;
		matrix[1][2] = 0;
		matrix[1][3] = 0;
		matrix[2][0] = 0;
		matrix[2][1] = 0;
		matrix[2][2] = 0;
		matrix[2][3] = 0;
		matrix[3][0] = 0;
		matrix[3][1] = 0;
		matrix[3][2] = 0;
		matrix[3][3] = 0;
	}
	Matrix4D(T val)
	{
		matrix[0][0] = val;
		matrix[0][1] = val;
		matrix[0][2] = val;
		matrix[0][3] = val;
		matrix[1][0] = val;
		matrix[1][1] = val;
		matrix[1][2] = val;
		matrix[1][3] = val;
		matrix[2][0] = val;
		matrix[2][1] = val;
		matrix[2][2] = val;
		matrix[2][3] = val;
		matrix[3][0] = val;
		matrix[3][1] = val;
		matrix[3][2] = val;
		matrix[3][3] = val;
	}
	Matrix4D(T Ixx, T Ixy, T Ixz, T Ixw,
			 T Iyx, T Iyy, T Iyz, T Iyw,
			 T Izx, T Izy, T Izz, T Izw,
			 T Iwx, T Iwy, T Iwz, T Iww)
	{
		matrix[0][0] = Ixx;
		matrix[0][1] = Ixy;
		matrix[0][2] = Ixz;
		matrix[0][3] = Ixw;
		matrix[1][0] = Iyx;
		matrix[1][1] = Iyy;
		matrix[1][2] = Iyz;
		matrix[1][3] = Iyw;
		matrix[2][0] = Izx;
		matrix[2][1] = Izy;
		matrix[2][2] = Izz;
		matrix[2][3] = Izw;
		matrix[3][0] = Iwx;
		matrix[3][1] = Iwy;
		matrix[3][2] = Iwz;
		matrix[3][3] = Iww;
	}
	Matrix4D(Vector4D<T> column0,
			 Vector4D<T> column1,
			 Vector4D<T> column2,
			 Vector4D<T> column3)
	{
		matrix[0][0] = column0.x;
		matrix[0][1] = column1.x;
		matrix[0][2] = column2.x;
		matrix[0][3] = column3.x;
		matrix[1][0] = column0.y;
		matrix[1][1] = column1.y;
		matrix[1][2] = column2.y;
		matrix[1][3] = column3.y;
		matrix[2][0] = column0.z;
		matrix[2][1] = column1.z;
		matrix[2][2] = column2.z;
		matrix[2][3] = column3.z;
		matrix[3][0] = column0.w;
		matrix[3][1] = column1.w;
		matrix[3][2] = column2.w;
		matrix[3][3] = column3.w;
	}
	~Matrix4D()
	{
		//do nothing
	}

	//Matrix4D operators
	T operator[] (unsigned i)
	{
		if(i == 0)		return matrix[0][0];
		else if(i == 1) return matrix[0][1];
		else if(i == 2) return matrix[0][2];
		else if(i == 3) return matrix[0][3];
		else if(i == 4) return matrix[1][0];
		else if(i == 5) return matrix[1][1];
		else if(i == 6) return matrix[1][2];
		else if(i == 7) return matrix[1][3];
		else if(i == 8) return matrix[2][0];
		else if(i == 9) return matrix[2][1];
		else if(i == 10)return matrix[2][2];
		else if(i == 11)return matrix[2][3];
		else if(i == 12)return matrix[3][0];
		else if(i == 13)return matrix[3][1];
		else if(i == 14)return matrix[3][2];
		else			return matrix[3][3];
	}
	bool operator== (const Matrix4D& rhs)
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
		else if(matrix[0][3] != rhs.matrix[0][3])
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
		else if(matrix[1][3] != rhs.matrix[1][3])
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
		else if(matrix[2][3] != rhs.matrix[2][3])
		{
			return false;
		}
		else if(matrix[3][0] != rhs.matrix[3][0])
		{
			return false;
		}
		else if(matrix[3][1] != rhs.matrix[3][1])
		{
			return false;
		}
		else if(matrix[3][2] != rhs.matrix[3][2])
		{
			return false;
		}
		else if(matrix[3][3] != rhs.matrix[3][3])
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	bool operator!= (const Matrix4D& rhs)
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
		else if(matrix[0][3] != rhs.matrix[0][3])
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
		else if(matrix[1][3] != rhs.matrix[1][3])
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
		else if(matrix[2][3] != rhs.matrix[2][3])
		{
			return true;
		}
		else if(matrix[3][0] != rhs.matrix[3][0])
		{
			return true;
		}
		else if(matrix[3][1] != rhs.matrix[3][1])
		{
			return true;
		}
		else if(matrix[3][2] != rhs.matrix[3][2])
		{
			return true;
		}
		else if(matrix[3][3] != rhs.matrix[3][3])
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
		else if(matrix[0][3] != rhs)
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
		else if(matrix[1][3] != rhs)
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
		else if(matrix[2][3] != rhs)
		{
			return false;
		}
		else if(matrix[3][0] != rhs)
		{
			return false;
		}
		else if(matrix[3][1] != rhs)
		{
			return false;
		}
		else if(matrix[3][2] != rhs)
		{
			return false;
		}
		else if(matrix[3][3] != rhs)
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
		else if(matrix[0][3] != rhs)
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
		else if(matrix[1][3] != rhs)
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
		else if(matrix[2][3] != rhs)
		{
			return true;
		}
		else if(matrix[3][0] != rhs)
		{
			return true;
		}
		else if(matrix[3][1] != rhs)
		{
			return true;
		}
		else if(matrix[3][2] != rhs)
		{
			return true;
		}
		else if(matrix[3][3] != rhs)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//return operator
	Matrix3D<T> GetMatrix3()
	{
		return Matrix3D<T>(matrix[0][0], matrix[0][1], matrix[0][2],
						   matrix[1][0], matrix[1][1], matrix[1][2],
						   matrix[2][0], matrix[2][1], matrix[2][2]);
	}
};

//float specific Matrix4D
template<>
struct Matrix4D<float>
{
	float matrix[4][4];

	//float constructors
	Matrix4D();
	Matrix4D(float val);
	Matrix4D(float Ixx, float Ixy, float Ixz, float Ixw,
			 float Iyx, float Iyy, float Iyz, float Iyw,
			 float Izx, float Izy, float Izz, float Izw,
			 float Iwx, float Iwy, float Iwz, float Iww);
	Matrix4D(Vector4D<float> column0,
			 Vector4D<float> column1,
			 Vector4D<float> column2,
			 Vector4D<float> column3);
	~Matrix4D();
	
	//Matrix4D array operators
	float operator[] (unsigned i);
	//Matrix4D - Matrix4D operators
	Matrix4D operator+ (const Matrix4D& rhs);
	Matrix4D operator- (const Matrix4D& rhs);
	Matrix4D operator* (const Matrix4D& rhs);
	Matrix4D operator/ (const Matrix4D& rhs);
	Matrix4D operator+= (const Matrix4D& rhs);
	Matrix4D operator-= (const Matrix4D& rhs);
	Matrix4D operator*= (const Matrix4D& rhs);
	Matrix4D operator/= (const Matrix4D& rhs);
	bool operator== (const Matrix4D& rhs);
	bool operator!= (const Matrix4D& rhs);
	//Matrix4D - Vector2D operators
	Vector4D<float> operator* (const Vector4D<float>& rhs);
	//Matrix4D - float operators
	Matrix4D operator* (const float& rhs);
	Matrix4D operator*= (const float& rhs);
	bool operator== (const float& rhs);
	bool operator!= (const float& rhs);
	//Matrix4D math functions
	void Identity();
	void SetDiagonal(const float& Ixx, const float& Iyy, const float& Izz, const float& Iww);
	Vector4D<float> Transform(const Vector4D<float>& rhs);
	Vector4D<float> TransformTranspose(const Vector4D<float>& rhs);
	Vector4D<float> GetRow(unsigned i);
	Vector4D<float> GetColumn(unsigned i);
	void Invert();
	Matrix4D Inverted();
	void Transpose();
	Matrix4D Transposed();
	Matrix4D Lerp(const Matrix4D& rhs, const float& prop);
	//transform matrix
	void Translate(const Vector3D<float>& rhs);
	Matrix4D<float> Translated(const Vector3D<float>& rhs);
	void Scale(const Vector3D<float>& rhs);
	Matrix4D<float> Scaled(const Vector3D<float>& rhs);
	void RotateX(const float& rhs);
	Matrix4D<float> RotatedX(const float& rhs);
	void RotateY(const float& rhs);
	Matrix4D<float> RotatedY(const float& rhs);
	void RotateZ(const float& rhs);
	Matrix4D<float> RotatedZ(const float& rhs);
	void RotateYawPitchRoll(const Vector3D<float>& rhs);
	Matrix4D<float> RotatedYawPitchRoll(const Vector3D<float>& rhs);
	void RotateQuaternion(const Quaternion<float>& rhs);
	Matrix4D<float> RotatedQuaternion(const Quaternion<float>& rhs);
	//return function
	Matrix3D<float> GetMatrix3();
};

//double specific Matrix4D
template<>
struct Matrix4D<double>
{
	double matrix[4][4];

	//double constructors
	Matrix4D();
	Matrix4D(double val);
	Matrix4D(double Ixx, double Ixy, double Ixz, double Ixw,
			 double Iyx, double Iyy, double Iyz, double Iyw,
			 double Izx, double Izy, double Izz, double Izw,
			 double Iwx, double Iwy, double Iwz, double Iww);
	Matrix4D(Vector4D<double> column0,
			 Vector4D<double> column1,
			 Vector4D<double> column2,
			 Vector4D<double> column3);
	~Matrix4D();
	
	//Matrix4D array operators
	double operator[] (unsigned i);
	//Matrix4D - Matrix4D operators
	Matrix4D operator+ (const Matrix4D& rhs);
	Matrix4D operator- (const Matrix4D& rhs);
	Matrix4D operator* (const Matrix4D& rhs);
	Matrix4D operator/ (const Matrix4D& rhs);
	Matrix4D operator+= (const Matrix4D& rhs);
	Matrix4D operator-= (const Matrix4D& rhs);
	Matrix4D operator*= (const Matrix4D& rhs);
	Matrix4D operator/= (const Matrix4D& rhs);
	bool operator== (const Matrix4D& rhs);
	bool operator!= (const Matrix4D& rhs);
	//Matrix4D - Vector2D operators
	Vector4D<double> operator* (const Vector4D<double>& rhs);
	//Matrix4D - double operators
	Matrix4D operator* (const double& rhs);
	Matrix4D operator*= (const double& rhs);
	bool operator== (const double& rhs);
	bool operator!= (const double& rhs);
	//Matrix4D math functions
	void Identity();
	void SetDiagonal(const double& Ixx, const double& Iyy, const double& Izz, const double& Iww);
	Vector4D<double> Transform(const Vector4D<double>& rhs);
	Vector4D<double> TransformTranspose(const Vector4D<double>& rhs);
	Vector4D<double> GetRow(unsigned i);
	Vector4D<double> GetColumn(unsigned i);
	void Invert();
	Matrix4D Inverted();
	void Transpose();
	Matrix4D Transposed();
	Matrix4D Lerp(const Matrix4D& rhs, const double& prop);
	//transform matrix
	void Translate(const Vector3D<double>& rhs);
	Matrix4D<double> Translated(const Vector3D<double>& rhs);
	void Scale(const Vector3D<double>& rhs);
	Matrix4D<double> Scaled(const Vector3D<double>& rhs);
	void RotateX(const double& rhs);
	Matrix4D<double> RotatedX(const double& rhs);
	void RotateY(const double& rhs);
	Matrix4D<double> RotatedY(const double& rhs);
	void RotateZ(const double& rhs);
	Matrix4D<double> RotatedZ(const double& rhs);
	void RotateYawPitchRoll(const Vector3D<double>& rhs);
	Matrix4D<double> RotatedYawPitchRoll(const Vector3D<double>& rhs);
	void RotateQuaternion(const Quaternion<double>& rhs);
	Matrix4D<double> RotatedQuaternion(const Quaternion<double>& rhs);
	//return function
	Matrix3D<double> GetMatrix3();
};

#endif //MATRIX4D_H