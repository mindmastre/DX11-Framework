#include "Matrix3D.h"

/////////////////////////////////////////////////
//               float template
/////////////////////////////////////////////////
Matrix3D<float>::Matrix3D()
{
	matrix[0][0] = 0.0f;
	matrix[0][1] = 0.0f;
	matrix[0][2] = 0.0f;
	matrix[1][0] = 0.0f;
	matrix[1][1] = 0.0f;
	matrix[1][2] = 0.0f;
	matrix[2][0] = 0.0f;
	matrix[2][1] = 0.0f;
	matrix[2][2] = 0.0f;
}
Matrix3D<float>::Matrix3D(float val)
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
Matrix3D<float>::Matrix3D(float Ixx, float Ixy, float Ixz,
						  float Iyx, float Iyy, float Iyz,
						  float Izx, float Izy, float Izz)
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
Matrix3D<float>::Matrix3D(Vector3D<float> column0,
						  Vector3D<float> column1,
						  Vector3D<float> column2)
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
Matrix3D<float>::~Matrix3D()
{
	//do nothing
}
float Matrix3D<float>::operator[](unsigned i)
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
Matrix3D<float> Matrix3D<float>::operator+(const Matrix3D& rhs)
{
	return Matrix3D<float>(*this) += rhs;
}
Matrix3D<float> Matrix3D<float>::operator-(const Matrix3D& rhs)
{
	return Matrix3D<float>(*this) -= rhs;
}
Matrix3D<float> Matrix3D<float>::operator*(const Matrix3D& rhs)
{
	return Matrix3D<float>(*this) *= rhs;
}
Matrix3D<float> Matrix3D<float>::operator/(const Matrix3D& rhs)
{
	return Matrix3D<float>(*this) /= rhs;
}
Matrix3D<float> Matrix3D<float>::operator+=(const Matrix3D& rhs)
{
	matrix[0][0] += rhs.matrix[0][0];
	matrix[0][1] += rhs.matrix[0][1];
	matrix[0][2] += rhs.matrix[0][2];
	matrix[1][0] += rhs.matrix[1][0];
	matrix[1][1] += rhs.matrix[1][1];
	matrix[1][2] += rhs.matrix[1][2];
	matrix[2][0] += rhs.matrix[2][0];
	matrix[2][1] += rhs.matrix[2][1];
	matrix[2][2] += rhs.matrix[2][2];
	return *this;
}
Matrix3D<float> Matrix3D<float>::operator-=(const Matrix3D& rhs)
{
	matrix[0][0] -= rhs.matrix[0][0];
	matrix[0][1] -= rhs.matrix[0][1];
	matrix[0][2] -= rhs.matrix[0][2];
	matrix[1][0] -= rhs.matrix[1][0];
	matrix[1][1] -= rhs.matrix[1][1];
	matrix[1][2] -= rhs.matrix[1][2];
	matrix[2][0] -= rhs.matrix[2][0];
	matrix[2][1] -= rhs.matrix[2][1];
	matrix[2][2] -= rhs.matrix[2][2];
	return *this;
}
Matrix3D<float> Matrix3D<float>::operator*=(const Matrix3D& rhs)
{
	matrix[0][0] *= rhs.matrix[0][0];
	matrix[0][1] *= rhs.matrix[0][1];
	matrix[0][2] *= rhs.matrix[0][2];
	matrix[1][0] *= rhs.matrix[1][0];
	matrix[1][1] *= rhs.matrix[1][1];
	matrix[1][2] *= rhs.matrix[1][2];
	matrix[2][0] *= rhs.matrix[2][0];
	matrix[2][1] *= rhs.matrix[2][1];
	matrix[2][2] *= rhs.matrix[2][2];
	return *this;
}
Matrix3D<float> Matrix3D<float>::operator/=(const Matrix3D& rhs)
{
	matrix[0][0] /= rhs.matrix[0][0];
	matrix[0][1] /= rhs.matrix[0][1];
	matrix[0][2] /= rhs.matrix[0][2];
	matrix[1][0] /= rhs.matrix[1][0];
	matrix[1][1] /= rhs.matrix[1][1];
	matrix[1][2] /= rhs.matrix[1][2];
	matrix[2][0] /= rhs.matrix[2][0];
	matrix[2][1] /= rhs.matrix[2][1];
	matrix[2][2] /= rhs.matrix[2][2];
	return *this;
}
bool Matrix3D<float>::operator==(const Matrix3D& rhs)
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
bool Matrix3D<float>::operator!=(const Matrix3D& rhs)
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
Vector3D<float> Matrix3D<float>::operator*(const Vector3D<float>& rhs)
{
	return Vector3D<float>(rhs.x * matrix[0][0] + rhs.y * matrix[0][1] + rhs.z * matrix[0][2],
						   rhs.x * matrix[1][0] + rhs.y * matrix[1][1] + rhs.z * matrix[1][2],
						   rhs.x * matrix[2][0] + rhs.y * matrix[2][1] + rhs.z * matrix[2][2]);
}
Matrix3D<float> Matrix3D<float>::operator* (const float& rhs)
{
	return Matrix3D<float>(*this) *= rhs;
}
Matrix3D<float> Matrix3D<float>::operator*= (const float& rhs)
{
	return Matrix3D<float>(matrix[0][0] * rhs, matrix[0][1] * rhs, matrix[0][2] * rhs,
						   matrix[1][0] * rhs, matrix[1][1] * rhs, matrix[1][2] * rhs,
						   matrix[2][0] * rhs, matrix[2][1] * rhs, matrix[2][2] * rhs);
}
bool Matrix3D<float>::operator== (const float& rhs)
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
bool Matrix3D<float>::operator!= (const float& rhs)
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
void Matrix3D<float>::Identity()
{
	matrix[0][0] = 1.0f;
	matrix[0][1] = 0.0f;
	matrix[0][2] = 0.0f;
	matrix[1][0] = 0.0f;
	matrix[1][1] = 1.0f;
	matrix[1][2] = 0.0f;
	matrix[2][0] = 0.0f;
	matrix[2][1] = 0.0f;
	matrix[2][2] = 1.0f;
}
void Matrix3D<float>::SetDiagonal(const float& Ixx, const float& Iyy, const float& Izz)
{
	matrix[0][0] = Ixx;
	matrix[1][1] = Iyy;
	matrix[2][2] = Izz;
}
Vector3D<float> Matrix3D<float>::Transform(const Vector3D<float>& rhs)
{
	return *this * rhs;
}
Vector3D<float> Matrix3D<float>::TransformTranspose(const Vector3D<float>& rhs)
{
	return Vector3D<float>(matrix[0][0] * rhs.x + matrix[1][0] * rhs.y + matrix[2][0] * rhs.z,
						   matrix[0][1] * rhs.x + matrix[1][1] * rhs.y + matrix[2][1] * rhs.z,
						   matrix[0][2] * rhs.x + matrix[1][2] * rhs.y + matrix[2][2] * rhs.z);
}
void Matrix3D<float>::SetRotation(const Quaternion<float>& rhs)
{
	matrix[0][0] = 1.0f - (2.0f * rhs.y * rhs.y + 2.0f * rhs.z * rhs.z);
	matrix[0][1] = 2.0f * rhs.x * rhs.y + 2.0f * rhs.z * rhs.w;
	matrix[0][2] = 2.0f * rhs.x * rhs.z - 2.0f * rhs.y * rhs.w;
	matrix[1][0] = 2.0f * rhs.x * rhs.y - 2.0f * rhs.z * rhs.w;
	matrix[1][1] = 1.0f - (2.0f * rhs.x * rhs.x + 2.0f * rhs.z * rhs.z);
	matrix[1][2] = 2.0f * rhs.y * rhs.z + 2.0f * rhs.x * rhs.w;
	matrix[2][0] = 2.0f * rhs.x * rhs.z + 2.0f * rhs.y * rhs.w;
	matrix[2][1] = 2.0f * rhs.y * rhs.z - 2.0f * rhs.x * rhs.w;
	matrix[2][2] = 1.0f - (2.0f * rhs.x * rhs.x + 2.0f * rhs.y * rhs.y);
}
Vector3D<float> Matrix3D<float>::GetRow(unsigned i)
{
	return Vector3D<float>(matrix[i][0], matrix[i][1], matrix[i][2]);
}
Vector3D<float> Matrix3D<float>::GetColumn(unsigned i)
{
	return Vector3D<float>(matrix[0][i], matrix[1][i], matrix[2][i]);
}
void Matrix3D<float>::Invert()
{
	float Ixx = matrix[0][0];
	float Ixy = matrix[0][1];
	float Ixz = matrix[0][2];
	float Iyx = matrix[1][0];
	float Iyy = matrix[1][1];
	float Iyz = matrix[1][2];
	float Izx = matrix[2][0];
	float Izy = matrix[2][1];
	float Izz = matrix[2][2];
	float M = Ixx * (Iyy * Izz - Izy * Iyz) -
			  Ixy * (Iyx * Izz - Izx * Iyz) +
			  Ixz * (Iyx * Izy - Izx * Iyy);

	matrix[0][0] = (Iyy * Izz - Izy * Iyz) / M;
	matrix[0][1] = (Ixz * Izy - Izz * Ixy) / M;
	matrix[0][2] = (Ixy * Iyz - Iyy * Ixz) / M;
	matrix[1][0] = (Iyz * Izx - Izz * Iyx) / M;
	matrix[1][1] = (Ixx * Izz - Izx * Ixz) / M;
	matrix[1][2] = (Ixz * Iyx - Iyz * Ixx) / M;
	matrix[2][0] = (Iyx * Izy - Izx * Iyy) / M;
	matrix[2][1] = (Ixy * Izx - Izy * Ixx) / M;
	matrix[2][2] = (Ixx * Iyy - Iyx * Ixy) / M;
}
Matrix3D<float> Matrix3D<float>::Inverted()
{
	Matrix3D<float> temp(*this);
	temp.Invert();
	return temp;
}
void Matrix3D<float>::Transpose()
{
	float Ixy = matrix[0][1];
	float Ixz = matrix[0][2];
	float Iyz = matrix[1][2];
	
	matrix[0][1] = matrix[1][0];
	matrix[0][2] = matrix[2][0];
	matrix[1][2] = matrix[2][1];

	matrix[1][0] = Ixy;
	matrix[2][0] = Ixz;
	matrix[2][1] = Iyz;
}
Matrix3D<float> Matrix3D<float>::Transposed()
{
	Matrix3D<float> temp(*this);
	temp.Transpose();
	return temp;
}
Matrix3D<float> Matrix3D<float>::Lerp(const Matrix3D& rhs, const float& prop)
{
	Matrix3D<float> temp(*this);
	temp.matrix[0][0] = matrix[0][0] * (1.0f-prop) + rhs.matrix[0][0] * prop;
	temp.matrix[0][1] = matrix[0][1] * (1.0f-prop) + rhs.matrix[0][1] * prop;
	temp.matrix[0][2] = matrix[0][2] * (1.0f-prop) + rhs.matrix[0][2] * prop;
	temp.matrix[1][0] = matrix[1][0] * (1.0f-prop) + rhs.matrix[1][0] * prop;
	temp.matrix[1][1] = matrix[1][1] * (1.0f-prop) + rhs.matrix[1][1] * prop;
	temp.matrix[1][2] = matrix[1][2] * (1.0f-prop) + rhs.matrix[1][2] * prop;
	temp.matrix[2][0] = matrix[2][0] * (1.0f-prop) + rhs.matrix[2][0] * prop;
	temp.matrix[2][1] = matrix[2][1] * (1.0f-prop) + rhs.matrix[2][1] * prop;
	temp.matrix[2][2] = matrix[2][2] * (1.0f-prop) + rhs.matrix[2][2] * prop;
	return temp;
}
/////////////////////////////////////////////////
//               double template
/////////////////////////////////////////////////
Matrix3D<double>::Matrix3D()
{
	matrix[0][0] = 0.0;
	matrix[0][1] = 0.0;
	matrix[0][2] = 0.0;
	matrix[1][0] = 0.0;
	matrix[1][1] = 0.0;
	matrix[1][2] = 0.0;
	matrix[2][0] = 0.0;
	matrix[2][1] = 0.0;
	matrix[2][2] = 0.0;
}
Matrix3D<double>::Matrix3D(double val)
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
Matrix3D<double>::Matrix3D(double Ixx, double Ixy, double Ixz,
						  double Iyx, double Iyy, double Iyz,
						  double Izx, double Izy, double Izz)
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
Matrix3D<double>::Matrix3D(Vector3D<double> column0,
						  Vector3D<double> column1,
						  Vector3D<double> column2)
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
Matrix3D<double>::~Matrix3D()
{
	//do nothing
}
double Matrix3D<double>::operator[](unsigned i)
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
Matrix3D<double> Matrix3D<double>::operator+(const Matrix3D& rhs)
{
	return Matrix3D<double>(*this) += rhs;
}
Matrix3D<double> Matrix3D<double>::operator-(const Matrix3D& rhs)
{
	return Matrix3D<double>(*this) -= rhs;
}
Matrix3D<double> Matrix3D<double>::operator*(const Matrix3D& rhs)
{
	return Matrix3D<double>(*this) *= rhs;
}
Matrix3D<double> Matrix3D<double>::operator/(const Matrix3D& rhs)
{
	return Matrix3D<double>(*this) /= rhs;
}
Matrix3D<double> Matrix3D<double>::operator+=(const Matrix3D& rhs)
{
	matrix[0][0] += rhs.matrix[0][0];
	matrix[0][1] += rhs.matrix[0][1];
	matrix[0][2] += rhs.matrix[0][2];
	matrix[1][0] += rhs.matrix[1][0];
	matrix[1][1] += rhs.matrix[1][1];
	matrix[1][2] += rhs.matrix[1][2];
	matrix[2][0] += rhs.matrix[2][0];
	matrix[2][1] += rhs.matrix[2][1];
	matrix[2][2] += rhs.matrix[2][2];
	return *this;
}
Matrix3D<double> Matrix3D<double>::operator-=(const Matrix3D& rhs)
{
	matrix[0][0] -= rhs.matrix[0][0];
	matrix[0][1] -= rhs.matrix[0][1];
	matrix[0][2] -= rhs.matrix[0][2];
	matrix[1][0] -= rhs.matrix[1][0];
	matrix[1][1] -= rhs.matrix[1][1];
	matrix[1][2] -= rhs.matrix[1][2];
	matrix[2][0] -= rhs.matrix[2][0];
	matrix[2][1] -= rhs.matrix[2][1];
	matrix[2][2] -= rhs.matrix[2][2];
	return *this;
}
Matrix3D<double> Matrix3D<double>::operator*=(const Matrix3D& rhs)
{
	matrix[0][0] *= rhs.matrix[0][0];
	matrix[0][1] *= rhs.matrix[0][1];
	matrix[0][2] *= rhs.matrix[0][2];
	matrix[1][0] *= rhs.matrix[1][0];
	matrix[1][1] *= rhs.matrix[1][1];
	matrix[1][2] *= rhs.matrix[1][2];
	matrix[2][0] *= rhs.matrix[2][0];
	matrix[2][1] *= rhs.matrix[2][1];
	matrix[2][2] *= rhs.matrix[2][2];
	return *this;
}
Matrix3D<double> Matrix3D<double>::operator/=(const Matrix3D& rhs)
{
	matrix[0][0] /= rhs.matrix[0][0];
	matrix[0][1] /= rhs.matrix[0][1];
	matrix[0][2] /= rhs.matrix[0][2];
	matrix[1][0] /= rhs.matrix[1][0];
	matrix[1][1] /= rhs.matrix[1][1];
	matrix[1][2] /= rhs.matrix[1][2];
	matrix[2][0] /= rhs.matrix[2][0];
	matrix[2][1] /= rhs.matrix[2][1];
	matrix[2][2] /= rhs.matrix[2][2];
	return *this;
}
bool Matrix3D<double>::operator==(const Matrix3D& rhs)
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
bool Matrix3D<double>::operator!=(const Matrix3D& rhs)
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
Vector3D<double> Matrix3D<double>::operator*(const Vector3D<double>& rhs)
{
	return Vector3D<double>(rhs.x * matrix[0][0] + rhs.y * matrix[0][1] + rhs.z * matrix[0][2],
						   rhs.x * matrix[1][0] + rhs.y * matrix[1][1] + rhs.z * matrix[1][2],
						   rhs.x * matrix[2][0] + rhs.y * matrix[2][1] + rhs.z * matrix[2][2]);
}
Matrix3D<double> Matrix3D<double>::operator* (const double& rhs)
{
	return Matrix3D<double>(*this) *= rhs;
}
Matrix3D<double> Matrix3D<double>::operator*= (const double& rhs)
{
	return Matrix3D<double>(matrix[0][0] * rhs, matrix[0][1] * rhs, matrix[0][2] * rhs,
						   matrix[1][0] * rhs, matrix[1][1] * rhs, matrix[1][2] * rhs,
						   matrix[2][0] * rhs, matrix[2][1] * rhs, matrix[2][2] * rhs);
}
bool Matrix3D<double>::operator== (const double& rhs)
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
bool Matrix3D<double>::operator!= (const double& rhs)
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
void Matrix3D<double>::Identity()
{
	matrix[0][0] = 1.0;
	matrix[0][1] = 0.0;
	matrix[0][2] = 0.0;
	matrix[1][0] = 0.0;
	matrix[1][1] = 1.0;
	matrix[1][2] = 0.0;
	matrix[2][0] = 0.0;
	matrix[2][1] = 0.0;
	matrix[2][2] = 1.0;
}
void Matrix3D<double>::SetDiagonal(const double& Ixx, const double& Iyy, const double& Izz)
{
	matrix[0][0] = Ixx;
	matrix[1][1] = Iyy;
	matrix[2][2] = Izz;
}
Vector3D<double> Matrix3D<double>::Transform(const Vector3D<double>& rhs)
{
	return *this * rhs;
}
Vector3D<double> Matrix3D<double>::TransformTranspose(const Vector3D<double>& rhs)
{
	return Vector3D<double>(matrix[0][0] * rhs.x + matrix[1][0] * rhs.y + matrix[2][0] * rhs.z,
						   matrix[0][1] * rhs.x + matrix[1][1] * rhs.y + matrix[2][1] * rhs.z,
						   matrix[0][2] * rhs.x + matrix[1][2] * rhs.y + matrix[2][2] * rhs.z);
}
void Matrix3D<double>::SetRotation(const Quaternion<double>& rhs)
{
	matrix[0][0] = 1.0 - (2.0 * rhs.y * rhs.y + 2.0 * rhs.z * rhs.z);
	matrix[0][1] = 2.0 * rhs.x * rhs.y + 2.0 * rhs.z * rhs.w;
	matrix[0][2] = 2.0 * rhs.x * rhs.z - 2.0 * rhs.y * rhs.w;
	matrix[1][0] = 2.0 * rhs.x * rhs.y - 2.0 * rhs.z * rhs.w;
	matrix[1][1] = 1.0 - (2.0 * rhs.x * rhs.x + 2.0 * rhs.z * rhs.z);
	matrix[1][2] = 2.0 * rhs.y * rhs.z + 2.0 * rhs.x * rhs.w;
	matrix[2][0] = 2.0 * rhs.x * rhs.z + 2.0 * rhs.y * rhs.w;
	matrix[2][1] = 2.0 * rhs.y * rhs.z - 2.0 * rhs.x * rhs.w;
	matrix[2][2] = 1.0 - (2.0 * rhs.x * rhs.x + 2.0 * rhs.y * rhs.y);
}
Vector3D<double> Matrix3D<double>::GetRow(unsigned i)
{
	return Vector3D<double>(matrix[i][0], matrix[i][1], matrix[i][2]);
}
Vector3D<double> Matrix3D<double>::GetColumn(unsigned i)
{
	return Vector3D<double>(matrix[0][i], matrix[1][i], matrix[2][i]);
}
void Matrix3D<double>::Invert()
{
	double Ixx = matrix[0][0];
	double Ixy = matrix[0][1];
	double Ixz = matrix[0][2];
	double Iyx = matrix[1][0];
	double Iyy = matrix[1][1];
	double Iyz = matrix[1][2];
	double Izx = matrix[2][0];
	double Izy = matrix[2][1];
	double Izz = matrix[2][2];
	double M = Ixx * (Iyy * Izz - Izy * Iyz) -
			  Ixy * (Iyx * Izz - Izx * Iyz) +
			  Ixz * (Iyx * Izy - Izx * Iyy);

	matrix[0][0] = (Iyy * Izz - Izy * Iyz) / M;
	matrix[0][1] = (Ixz * Izy - Izz * Ixy) / M;
	matrix[0][2] = (Ixy * Iyz - Iyy * Ixz) / M;
	matrix[1][0] = (Iyz * Izx - Izz * Iyx) / M;
	matrix[1][1] = (Ixx * Izz - Izx * Ixz) / M;
	matrix[1][2] = (Ixz * Iyx - Iyz * Ixx) / M;
	matrix[2][0] = (Iyx * Izy - Izx * Iyy) / M;
	matrix[2][1] = (Ixy * Izx - Izy * Ixx) / M;
	matrix[2][2] = (Ixx * Iyy - Iyx * Ixy) / M;
}
Matrix3D<double> Matrix3D<double>::Inverted()
{
	Matrix3D<double> temp(*this);
	temp.Invert();
	return temp;
}
void Matrix3D<double>::Transpose()
{
	double Ixy = matrix[0][1];
	double Ixz = matrix[0][2];
	double Iyz = matrix[1][2];
	
	matrix[0][1] = matrix[1][0];
	matrix[0][2] = matrix[2][0];
	matrix[1][2] = matrix[2][1];

	matrix[1][0] = Ixy;
	matrix[2][0] = Ixz;
	matrix[2][1] = Iyz;
}
Matrix3D<double> Matrix3D<double>::Transposed()
{
	Matrix3D<double> temp(*this);
	temp.Transpose();
	return temp;
}
Matrix3D<double> Matrix3D<double>::Lerp(const Matrix3D& rhs, const double& prop)
{
	Matrix3D<double> temp(*this);
	temp.matrix[0][0] = matrix[0][0] * (1.0-prop) + rhs.matrix[0][0] * prop;
	temp.matrix[0][1] = matrix[0][1] * (1.0-prop) + rhs.matrix[0][1] * prop;
	temp.matrix[0][2] = matrix[0][2] * (1.0-prop) + rhs.matrix[0][2] * prop;
	temp.matrix[1][0] = matrix[1][0] * (1.0-prop) + rhs.matrix[1][0] * prop;
	temp.matrix[1][1] = matrix[1][1] * (1.0-prop) + rhs.matrix[1][1] * prop;
	temp.matrix[1][2] = matrix[1][2] * (1.0-prop) + rhs.matrix[1][2] * prop;
	temp.matrix[2][0] = matrix[2][0] * (1.0-prop) + rhs.matrix[2][0] * prop;
	temp.matrix[2][1] = matrix[2][1] * (1.0-prop) + rhs.matrix[2][1] * prop;
	temp.matrix[2][2] = matrix[2][2] * (1.0-prop) + rhs.matrix[2][2] * prop;
	return temp;
}