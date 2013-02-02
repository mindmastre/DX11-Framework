#include "Matrix4D.h"
#include <cmath>

/////////////////////////////////////////////////
//               float template
/////////////////////////////////////////////////
Matrix4D<float>::Matrix4D()
{
	matrix[0][0] = 0.0f;
	matrix[0][1] = 0.0f;
	matrix[0][2] = 0.0f;
	matrix[0][3] = 0.0f;
	matrix[1][0] = 0.0f;
	matrix[1][1] = 0.0f;
	matrix[1][2] = 0.0f;
	matrix[1][3] = 0.0f;
	matrix[2][0] = 0.0f;
	matrix[2][1] = 0.0f;
	matrix[2][2] = 0.0f;
	matrix[2][3] = 0.0f;
	matrix[3][0] = 0.0f;
	matrix[3][1] = 0.0f;
	matrix[3][2] = 0.0f;
	matrix[3][3] = 0.0f;
}
Matrix4D<float>::Matrix4D(float val)
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
Matrix4D<float>::Matrix4D(float Ixx, float Ixy, float Ixz, float Ixw,
						  float Iyx, float Iyy, float Iyz, float Iyw,
						  float Izx, float Izy, float Izz, float Izw,
						  float Iwx, float Iwy, float Iwz, float Iww)
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
Matrix4D<float>::Matrix4D(Vector4D<float> column0,
						  Vector4D<float> column1,
						  Vector4D<float> column2,
						  Vector4D<float> column3)
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
Matrix4D<float>::~Matrix4D()
{
	//do nothing
}
float Matrix4D<float>::operator[](unsigned i)
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
Matrix4D<float> Matrix4D<float>::operator+(const Matrix4D& rhs)
{
	return Matrix4D<float>(*this) += rhs;
}
Matrix4D<float> Matrix4D<float>::operator-(const Matrix4D& rhs)
{
	return Matrix4D<float>(*this) -= rhs;
}
Matrix4D<float> Matrix4D<float>::operator*(const Matrix4D& rhs)
{
	return Matrix4D<float>(*this) *= rhs;
}
Matrix4D<float> Matrix4D<float>::operator/(const Matrix4D& rhs)
{
	return Matrix4D<float>(*this) /= rhs;
}
Matrix4D<float> Matrix4D<float>::operator+=(const Matrix4D& rhs)
{
	matrix[0][0] += rhs.matrix[0][0];
	matrix[0][1] += rhs.matrix[0][1];
	matrix[0][2] += rhs.matrix[0][2];
	matrix[0][3] += rhs.matrix[0][3];
	matrix[1][0] += rhs.matrix[1][0];
	matrix[1][1] += rhs.matrix[1][1];
	matrix[1][2] += rhs.matrix[1][2];
	matrix[1][3] += rhs.matrix[1][3];
	matrix[2][0] += rhs.matrix[2][0];
	matrix[2][1] += rhs.matrix[2][1];
	matrix[2][2] += rhs.matrix[2][2];
	matrix[2][3] += rhs.matrix[2][3];
	matrix[3][0] += rhs.matrix[3][0];
	matrix[3][1] += rhs.matrix[3][1];
	matrix[3][2] += rhs.matrix[3][2];
	matrix[3][3] += rhs.matrix[3][3];
	return *this;
}
Matrix4D<float> Matrix4D<float>::operator-=(const Matrix4D& rhs)
{
	matrix[0][0] -= rhs.matrix[0][0];
	matrix[0][1] -= rhs.matrix[0][1];
	matrix[0][2] -= rhs.matrix[0][2];
	matrix[0][3] -= rhs.matrix[0][3];
	matrix[1][0] -= rhs.matrix[1][0];
	matrix[1][1] -= rhs.matrix[1][1];
	matrix[1][2] -= rhs.matrix[1][2];
	matrix[1][3] -= rhs.matrix[1][3];
	matrix[2][0] -= rhs.matrix[2][0];
	matrix[2][1] -= rhs.matrix[2][1];
	matrix[2][2] -= rhs.matrix[2][2];
	matrix[2][3] -= rhs.matrix[2][3];
	matrix[3][0] -= rhs.matrix[3][0];
	matrix[3][1] -= rhs.matrix[3][1];
	matrix[3][2] -= rhs.matrix[3][2];
	matrix[3][3] -= rhs.matrix[3][3];
	return *this;
}
Matrix4D<float> Matrix4D<float>::operator*=(const Matrix4D& rhs)
{
	matrix[0][0] *= rhs.matrix[0][0];
	matrix[0][1] *= rhs.matrix[0][1];
	matrix[0][2] *= rhs.matrix[0][2];
	matrix[0][3] *= rhs.matrix[0][3];
	matrix[1][0] *= rhs.matrix[1][0];
	matrix[1][1] *= rhs.matrix[1][1];
	matrix[1][2] *= rhs.matrix[1][2];
	matrix[1][3] *= rhs.matrix[1][3];
	matrix[2][0] *= rhs.matrix[2][0];
	matrix[2][1] *= rhs.matrix[2][1];
	matrix[2][2] *= rhs.matrix[2][2];
	matrix[2][3] *= rhs.matrix[2][3];
	matrix[3][0] *= rhs.matrix[3][0];
	matrix[3][1] *= rhs.matrix[3][1];
	matrix[3][2] *= rhs.matrix[3][2];
	matrix[3][3] *= rhs.matrix[3][3];
	return *this;
}
Matrix4D<float> Matrix4D<float>::operator/=(const Matrix4D& rhs)
{
	matrix[0][0] /= rhs.matrix[0][0];
	matrix[0][1] /= rhs.matrix[0][1];
	matrix[0][2] /= rhs.matrix[0][2];
	matrix[0][3] /= rhs.matrix[0][3];
	matrix[1][0] /= rhs.matrix[1][0];
	matrix[1][1] /= rhs.matrix[1][1];
	matrix[1][2] /= rhs.matrix[1][2];
	matrix[1][3] /= rhs.matrix[1][3];
	matrix[2][0] /= rhs.matrix[2][0];
	matrix[2][1] /= rhs.matrix[2][1];
	matrix[2][2] /= rhs.matrix[2][2];
	matrix[2][3] /= rhs.matrix[2][3];
	matrix[3][0] /= rhs.matrix[3][0];
	matrix[3][1] /= rhs.matrix[3][1];
	matrix[3][2] /= rhs.matrix[3][2];
	matrix[3][3] /= rhs.matrix[3][3];
	return *this;
}
bool Matrix4D<float>::operator==(const Matrix4D& rhs)
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
bool Matrix4D<float>::operator!=(const Matrix4D& rhs)
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
Vector4D<float> Matrix4D<float>::operator*(const Vector4D<float>& rhs)
{
	return Vector4D<float>(rhs.x * matrix[0][0] + rhs.y * matrix[0][1] + rhs.z * matrix[0][2] + rhs.w * matrix[0][3],
						   rhs.x * matrix[1][0] + rhs.y * matrix[1][1] + rhs.z * matrix[1][2] + rhs.w * matrix[1][3],
						   rhs.x * matrix[2][0] + rhs.y * matrix[2][1] + rhs.z * matrix[2][2] + rhs.w * matrix[2][3],
						   rhs.x * matrix[3][0] + rhs.y * matrix[3][1] + rhs.z * matrix[3][2] + rhs.w * matrix[3][3]);
}
Matrix4D<float> Matrix4D<float>::operator* (const float& rhs)
{
	return Matrix4D<float>(*this) *= rhs;
}
Matrix4D<float> Matrix4D<float>::operator*= (const float& rhs)
{
	return Matrix4D<float>(matrix[0][0] * rhs, matrix[0][1] * rhs, matrix[0][2] * rhs, matrix[0][3] * rhs,
						   matrix[1][0] * rhs, matrix[1][1] * rhs, matrix[1][2] * rhs, matrix[1][3] * rhs,
						   matrix[2][0] * rhs, matrix[2][1] * rhs, matrix[2][2] * rhs, matrix[2][3] * rhs,
						   matrix[3][0] * rhs, matrix[3][1] * rhs, matrix[3][2] * rhs, matrix[3][3]);
}
bool Matrix4D<float>::operator== (const float& rhs)
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
bool Matrix4D<float>::operator!= (const float& rhs)
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
void Matrix4D<float>::Identity()
{
	matrix[0][0] = 1.0f;
	matrix[0][1] = 0.0f;
	matrix[0][2] = 0.0f;
	matrix[0][3] = 0.0f;
	matrix[1][0] = 0.0f;
	matrix[1][1] = 1.0f;
	matrix[1][2] = 0.0f;
	matrix[1][3] = 0.0f;
	matrix[2][0] = 0.0f;
	matrix[2][1] = 0.0f;
	matrix[2][2] = 1.0f;
	matrix[2][3] = 0.0f;
	matrix[3][0] = 0.0f;
	matrix[3][1] = 0.0f;
	matrix[3][2] = 0.0f;
	matrix[3][3] = 1.0f;
}
void Matrix4D<float>::SetDiagonal(const float& Ixx, const float& Iyy, const float& Izz, const float& Iww)
{
	matrix[0][0] = Ixx;
	matrix[1][1] = Iyy;
	matrix[2][2] = Izz;
	matrix[3][3] = Iww;
}
Vector4D<float> Matrix4D<float>::Transform(const Vector4D<float>& rhs)
{
	return *this * rhs;
}
Vector4D<float> Matrix4D<float>::TransformTranspose(const Vector4D<float>& rhs)
{
	return Vector4D<float>(matrix[0][0] * rhs.x + matrix[1][0] * rhs.y + matrix[2][0] * rhs.z + matrix[3][0] * rhs.w,
						   matrix[0][1] * rhs.x + matrix[1][1] * rhs.y + matrix[2][1] * rhs.z + matrix[3][1] * rhs.w,
						   matrix[0][2] * rhs.x + matrix[1][2] * rhs.y + matrix[2][2] * rhs.z + matrix[3][2] * rhs.w,
						   matrix[0][3] * rhs.x + matrix[1][3] * rhs.y + matrix[2][3] * rhs.z + matrix[3][3] * rhs.w);
}
Vector4D<float> Matrix4D<float>::GetRow(unsigned i)
{
	return Vector4D<float>(matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3]);
}
Vector4D<float> Matrix4D<float>::GetColumn(unsigned i)
{
	return Vector4D<float>(matrix[0][i], matrix[1][i], matrix[2][i], matrix[3][i]);
}
void Matrix4D<float>::Invert()
{
	float Ixx = matrix[0][0];
	float Ixy = matrix[0][1];
	float Ixz = matrix[0][2];
	float Ixw = matrix[0][3];
	float Iyx = matrix[1][0];
	float Iyy = matrix[1][1];
	float Iyz = matrix[1][2];
	float Iyw = matrix[1][3];
	float Izx = matrix[2][0];
	float Izy = matrix[2][1];
	float Izz = matrix[2][2];
	float Izw = matrix[2][3];
	float Iwx = matrix[3][0];
	float Iwy = matrix[3][1];
	float Iwz = matrix[3][2];
	float Iww = matrix[3][3];
	float M = Ixw*Iyz*Izy*Iwx - Ixz*Iyw*Izy*Iwx - Ixw*Iyy*Izz*Iwx + Ixy*Iyw*Izz*Iwx +
			  Ixz*Iyy*Izw*Iwx - Ixy*Iyz*Izw*Iwx - Ixw*Iyz*Izx*Iwy + Ixz*Iyw*Izx*Iwy +
			  Ixw*Iyx*Izz*Iwy - Ixx*Iyw*Izz*Iwy - Ixz*Iyx*Izw*Iwy + Ixx*Iyz*Izw*Iwy +
			  Ixw*Iyy*Izx*Iwz - Ixy*Iyw*Izx*Iwz - Ixw*Iyx*Izy*Iwz + Ixx*Iyw*Izy*Iwz +
			  Ixy*Iyx*Izw*Iwz - Ixx*Iyy*Izw*Iwz - Ixz*Iyy*Izx*Iww + Ixy*Iyz*Izx*Iww +
			  Ixz*Iyx*Izy*Iww - Ixx*Iyz*Izy*Iww - Ixy*Iyx*Izz*Iww + Ixx*Iyy*Izz*Iww;

	matrix[0][0] = (Iyz*Izw*Iwy - Iyw*Izz*Iwy + Iyw*Izy*Iwz - Iyy*Izw*Iwz - Iyz*Izy*Iww + Iyy*Izz*Iww) / M;
	matrix[0][1] = (Ixw*Izz*Iwy - Ixz*Izw*Iwy - Ixw*Izy*Iwz + Ixy*Izw*Iwz + Ixz*Izy*Iww - Ixy*Izz*Iww) / M;
	matrix[0][2] = (Ixz*Iyw*Iwy - Ixw*Iyz*Iwy + Ixw*Iyy*Iwz - Ixy*Iyw*Iwz - Ixz*Iyy*Iww + Ixy*Iyz*Iww) / M;
	matrix[0][3] = (Ixw*Iyz*Izy - Ixz*Iyw*Izy - Ixw*Iyy*Izz + Ixy*Iyw*Izz + Ixz*Iyy*Izw - Ixy*Iyz*Izw) / M;
	matrix[1][0] = (Iyw*Izz*Iwx - Iyz*Izw*Iwx - Iyw*Izx*Iwz + Iyx*Izw*Iwz + Iyz*Izx*Iww - Iyx*Izz*Iww) / M;
	matrix[1][1] = (Ixz*Izw*Iwx - Ixw*Izz*Iwx + Ixw*Izx*Iwz - Ixx*Izw*Iwz - Ixz*Izx*Iww + Ixx*Izz*Iww) / M;
	matrix[1][2] = (Ixw*Iyz*Iwx - Ixz*Iyw*Iwx - Ixw*Iyx*Iwz + Ixx*Iyw*Iwz + Ixz*Iyx*Iww - Ixx*Iyz*Iww) / M;
	matrix[1][3] = (Ixz*Iyw*Izx - Ixw*Iyz*Izx + Ixw*Iyx*Izz - Ixx*Iyw*Izz - Ixz*Iyx*Izw + Ixx*Iyz*Izw) / M;
	matrix[2][0] = (Iyy*Izw*Iwx - Iyw*Izy*Iwx + Iyw*Izx*Iwy - Iyx*Izw*Iwy - Iyy*Izx*Iww + Iyx*Izy*Iww) / M;
	matrix[2][1] = (Ixw*Izy*Iwx - Ixy*Izw*Iwx - Ixw*Izx*Iwy + Ixx*Izw*Iwy + Ixy*Izx*Iww - Ixx*Izy*Iww) / M;
	matrix[2][2] = (Ixy*Iyw*Iwx - Ixw*Iyy*Iwx + Ixw*Iyx*Iwy - Ixx*Iyw*Iwy - Ixy*Iyx*Iww + Ixx*Iyy*Iww) / M;
	matrix[2][3] = (Ixw*Iyy*Izx - Ixy*Iyw*Izx - Ixw*Iyx*Izy + Ixx*Iyw*Izy + Ixy*Iyx*Izw - Ixx*Iyy*Izw) / M;
	matrix[3][0] = (Iyz*Izy*Iwx - Iyy*Izz*Iwx - Iyz*Izx*Iwy + Iyx*Izz*Iwy + Iyy*Izx*Iwz - Iyx*Izy*Iwz) / M;
	matrix[3][1] = (Ixy*Izz*Iwx - Ixz*Izy*Iwx + Ixz*Izx*Iwy - Ixx*Izz*Iwy - Ixy*Izx*Iwz + Ixx*Izy*Iwz) / M;
	matrix[3][2] = (Ixz*Iyy*Iwx - Ixy*Iyz*Iwx - Ixz*Iyx*Iwy + Ixx*Iyz*Iwy + Ixy*Iyx*Iwz - Ixx*Iyy*Iwz) / M;
	matrix[3][3] = (Ixy*Iyz*Izx - Ixz*Iyy*Izx + Ixz*Iyx*Izy - Ixx*Iyz*Izy - Ixy*Iyx*Izz + Ixx*Iyy*Izz) / M;
}
Matrix4D<float> Matrix4D<float>::Inverted()
{
	Matrix4D<float> temp(*this);
	temp.Invert();
	return temp;
}
void Matrix4D<float>::Transpose()
{
	float Ixy = matrix[0][1];
	float Ixz = matrix[0][2];
	float Ixw = matrix[0][3];
	float Iyz = matrix[1][2];
	float Iyw = matrix[1][3];
	float Izw = matrix[2][3];
	
	matrix[0][1] = matrix[1][0];
	matrix[0][2] = matrix[2][0];
	matrix[0][3] = matrix[3][0];
	matrix[1][2] = matrix[2][1];
	matrix[1][3] = matrix[3][1];
	matrix[2][3] = matrix[3][2];

	matrix[1][0] = Ixy;
	matrix[2][0] = Ixz;
	matrix[3][0] = Ixw;
	matrix[2][1] = Iyz;
	matrix[3][1] = Iyw;
	matrix[3][2] = Izw;
}
Matrix4D<float> Matrix4D<float>::Transposed()
{
	Matrix4D<float> temp(*this);
	temp.Transpose();
	return temp;
}
Matrix4D<float> Matrix4D<float>::Lerp(const Matrix4D& rhs, const float& prop)
{
	Matrix4D<float> temp(*this);
	temp.matrix[0][0] = matrix[0][0] * (1.0f-prop) + rhs.matrix[0][0] * prop;
	temp.matrix[0][1] = matrix[0][1] * (1.0f-prop) + rhs.matrix[0][1] * prop;
	temp.matrix[0][2] = matrix[0][2] * (1.0f-prop) + rhs.matrix[0][2] * prop;
	temp.matrix[0][3] = matrix[0][3] * (1.0f-prop) + rhs.matrix[0][3] * prop;
	temp.matrix[1][0] = matrix[1][0] * (1.0f-prop) + rhs.matrix[1][0] * prop;
	temp.matrix[1][1] = matrix[1][1] * (1.0f-prop) + rhs.matrix[1][1] * prop;
	temp.matrix[1][2] = matrix[1][2] * (1.0f-prop) + rhs.matrix[1][2] * prop;
	temp.matrix[1][3] = matrix[1][3] * (1.0f-prop) + rhs.matrix[1][3] * prop;
	temp.matrix[2][0] = matrix[2][0] * (1.0f-prop) + rhs.matrix[2][0] * prop;
	temp.matrix[2][1] = matrix[2][1] * (1.0f-prop) + rhs.matrix[2][1] * prop;
	temp.matrix[2][2] = matrix[2][2] * (1.0f-prop) + rhs.matrix[2][2] * prop;
	temp.matrix[2][3] = matrix[2][3] * (1.0f-prop) + rhs.matrix[2][3] * prop;
	temp.matrix[3][0] = matrix[3][0] * (1.0f-prop) + rhs.matrix[3][0] * prop;
	temp.matrix[3][1] = matrix[3][1] * (1.0f-prop) + rhs.matrix[3][1] * prop;
	temp.matrix[3][2] = matrix[3][2] * (1.0f-prop) + rhs.matrix[3][2] * prop;
	temp.matrix[3][3] = matrix[3][3] * (1.0f-prop) + rhs.matrix[3][3] * prop;
	return temp;
}
void Matrix4D<float>::Translate(const Vector3D<float>& rhs)
{
	Identity();
	matrix[3][0] = rhs.x;
	matrix[3][1] = rhs.y;
	matrix[3][2] = rhs.z;
}
Matrix4D<float> Matrix4D<float>::Translated(const Vector3D<float>& rhs)
{
	Matrix4D<float> temp(*this);
	temp.Translate(rhs);
	return temp;
}
void Matrix4D<float>::Scale(const Vector3D<float>& rhs)
{
	Identity();
	matrix[0][0] = rhs.x;
	matrix[1][1] = rhs.y;
	matrix[2][2] = rhs.z;
}
Matrix4D<float> Matrix4D<float>::Scaled(const Vector3D<float>& rhs)
{
	Matrix4D<float> temp(*this);
	temp.Scale(rhs);
	return temp;
}
void Matrix4D<float>::RotateX(const float& rhs)
{
	Identity();
	matrix[1][1] = cos(rhs);
	matrix[2][2] = cos(rhs);
	matrix[1][2] = sin(rhs);
	matrix[2][1] = -sin(rhs);
}
Matrix4D<float> Matrix4D<float>::RotatedX(const float& rhs)
{
	Matrix4D<float> temp(*this);
	temp.RotateX(rhs);
	return temp;
}
void Matrix4D<float>::RotateY(const float& rhs)
{
	Identity();
	matrix[0][0] = cos(rhs);
	matrix[2][2] = cos(rhs);
	matrix[0][2] = -sin(rhs);
	matrix[2][0] = sin(rhs);
}
Matrix4D<float> Matrix4D<float>::RotatedY(const float& rhs)
{
	Matrix4D<float> temp(*this);
	temp.RotateY(rhs);
	return temp;
}
void Matrix4D<float>::RotateZ(const float& rhs)
{
	Identity();
	matrix[0][0] = cos(rhs);
	matrix[1][1] = cos(rhs);
	matrix[0][1] = sin(rhs);
	matrix[1][0] = -sin(rhs);
}
Matrix4D<float> Matrix4D<float>::RotatedZ(const float& rhs)
{
	Matrix4D<float> temp(*this);
	temp.RotateZ(rhs);
	return temp;
}
void Matrix4D<float>::RotateYawPitchRoll(const Vector3D<float>& rhs)
{
	Identity();
	matrix[0][0] = cos(rhs.z)*cos(rhs.y) + sin(rhs.z)*sin(rhs.x)*sin(rhs.y);
	matrix[0][1] = sin(rhs.z)*cos(rhs.x);
	matrix[0][2] = cos(rhs.z)*(-sin(rhs.y)) + sin(rhs.z)*sin(rhs.x)*sin(rhs.y);
	matrix[1][0] = (-sin(rhs.z))*cos(rhs.y) + cos(rhs.z)*sin(rhs.x)*sin(rhs.y);
	matrix[1][1] = cos(rhs.z)*cos(rhs.x);
	matrix[1][2] = sin(rhs.z)*sin(rhs.y) + cos(rhs.z)*sin(rhs.x)*cos(rhs.y);
	matrix[2][0] = cos(rhs.x)*sin(rhs.y);
	matrix[2][1] = -sin(rhs.x);
	matrix[2][2] = cos(rhs.x)*cos(rhs.y);
}
Matrix4D<float> Matrix4D<float>::RotatedYawPitchRoll(const Vector3D<float>& rhs)
{
	Matrix4D<float> temp(*this);
	temp.RotateYawPitchRoll(rhs);
	return temp;
}
void Matrix4D<float>::RotateQuaternion(const Quaternion<float>& rhs)
{
	Identity();
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
Matrix4D<float> Matrix4D<float>::RotatedQuaternion(const Quaternion<float>& rhs)
{
	Matrix4D<float> temp(*this);
	temp.RotateQuaternion(rhs);
	return temp;
}
Matrix3D<float> Matrix4D<float>::GetMatrix3()
{
	return Matrix3D<float>(matrix[0][0], matrix[0][1], matrix[0][2],
						   matrix[1][0], matrix[1][1], matrix[1][2],
						   matrix[2][0], matrix[2][1], matrix[2][2]);
}
/////////////////////////////////////////////////
//               double template
/////////////////////////////////////////////////
Matrix4D<double>::Matrix4D()
{
	matrix[0][0] = 0.0;
	matrix[0][1] = 0.0;
	matrix[0][2] = 0.0;
	matrix[0][3] = 0.0;
	matrix[1][0] = 0.0;
	matrix[1][1] = 0.0;
	matrix[1][2] = 0.0;
	matrix[1][3] = 0.0;
	matrix[2][0] = 0.0;
	matrix[2][1] = 0.0;
	matrix[2][2] = 0.0;
	matrix[2][3] = 0.0;
	matrix[3][0] = 0.0;
	matrix[3][1] = 0.0;
	matrix[3][2] = 0.0;
	matrix[3][3] = 0.0;
}
Matrix4D<double>::Matrix4D(double val)
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
Matrix4D<double>::Matrix4D(double Ixx, double Ixy, double Ixz, double Ixw,
						  double Iyx, double Iyy, double Iyz, double Iyw,
						  double Izx, double Izy, double Izz, double Izw,
						  double Iwx, double Iwy, double Iwz, double Iww)
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
Matrix4D<double>::Matrix4D(Vector4D<double> column0,
						  Vector4D<double> column1,
						  Vector4D<double> column2,
						  Vector4D<double> column3)
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
Matrix4D<double>::~Matrix4D()
{
	//do nothing
}
double Matrix4D<double>::operator[](unsigned i)
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
Matrix4D<double> Matrix4D<double>::operator+(const Matrix4D& rhs)
{
	return Matrix4D<double>(*this) += rhs;
}
Matrix4D<double> Matrix4D<double>::operator-(const Matrix4D& rhs)
{
	return Matrix4D<double>(*this) -= rhs;
}
Matrix4D<double> Matrix4D<double>::operator*(const Matrix4D& rhs)
{
	return Matrix4D<double>(*this) *= rhs;
}
Matrix4D<double> Matrix4D<double>::operator/(const Matrix4D& rhs)
{
	return Matrix4D<double>(*this) /= rhs;
}
Matrix4D<double> Matrix4D<double>::operator+=(const Matrix4D& rhs)
{
	matrix[0][0] += rhs.matrix[0][0];
	matrix[0][1] += rhs.matrix[0][1];
	matrix[0][2] += rhs.matrix[0][2];
	matrix[0][3] += rhs.matrix[0][3];
	matrix[1][0] += rhs.matrix[1][0];
	matrix[1][1] += rhs.matrix[1][1];
	matrix[1][2] += rhs.matrix[1][2];
	matrix[1][3] += rhs.matrix[1][3];
	matrix[2][0] += rhs.matrix[2][0];
	matrix[2][1] += rhs.matrix[2][1];
	matrix[2][2] += rhs.matrix[2][2];
	matrix[2][3] += rhs.matrix[2][3];
	matrix[3][0] += rhs.matrix[3][0];
	matrix[3][1] += rhs.matrix[3][1];
	matrix[3][2] += rhs.matrix[3][2];
	matrix[3][3] += rhs.matrix[3][3];
	return *this;
}
Matrix4D<double> Matrix4D<double>::operator-=(const Matrix4D& rhs)
{
	matrix[0][0] -= rhs.matrix[0][0];
	matrix[0][1] -= rhs.matrix[0][1];
	matrix[0][2] -= rhs.matrix[0][2];
	matrix[0][3] -= rhs.matrix[0][3];
	matrix[1][0] -= rhs.matrix[1][0];
	matrix[1][1] -= rhs.matrix[1][1];
	matrix[1][2] -= rhs.matrix[1][2];
	matrix[1][3] -= rhs.matrix[1][3];
	matrix[2][0] -= rhs.matrix[2][0];
	matrix[2][1] -= rhs.matrix[2][1];
	matrix[2][2] -= rhs.matrix[2][2];
	matrix[2][3] -= rhs.matrix[2][3];
	matrix[3][0] -= rhs.matrix[3][0];
	matrix[3][1] -= rhs.matrix[3][1];
	matrix[3][2] -= rhs.matrix[3][2];
	matrix[3][3] -= rhs.matrix[3][3];
	return *this;
}
Matrix4D<double> Matrix4D<double>::operator*=(const Matrix4D& rhs)
{
	matrix[0][0] *= rhs.matrix[0][0];
	matrix[0][1] *= rhs.matrix[0][1];
	matrix[0][2] *= rhs.matrix[0][2];
	matrix[0][3] *= rhs.matrix[0][3];
	matrix[1][0] *= rhs.matrix[1][0];
	matrix[1][1] *= rhs.matrix[1][1];
	matrix[1][2] *= rhs.matrix[1][2];
	matrix[1][3] *= rhs.matrix[1][3];
	matrix[2][0] *= rhs.matrix[2][0];
	matrix[2][1] *= rhs.matrix[2][1];
	matrix[2][2] *= rhs.matrix[2][2];
	matrix[2][3] *= rhs.matrix[2][3];
	matrix[3][0] *= rhs.matrix[3][0];
	matrix[3][1] *= rhs.matrix[3][1];
	matrix[3][2] *= rhs.matrix[3][2];
	matrix[3][3] *= rhs.matrix[3][3];
	return *this;
}
Matrix4D<double> Matrix4D<double>::operator/=(const Matrix4D& rhs)
{
	matrix[0][0] /= rhs.matrix[0][0];
	matrix[0][1] /= rhs.matrix[0][1];
	matrix[0][2] /= rhs.matrix[0][2];
	matrix[0][3] /= rhs.matrix[0][3];
	matrix[1][0] /= rhs.matrix[1][0];
	matrix[1][1] /= rhs.matrix[1][1];
	matrix[1][2] /= rhs.matrix[1][2];
	matrix[1][3] /= rhs.matrix[1][3];
	matrix[2][0] /= rhs.matrix[2][0];
	matrix[2][1] /= rhs.matrix[2][1];
	matrix[2][2] /= rhs.matrix[2][2];
	matrix[2][3] /= rhs.matrix[2][3];
	matrix[3][0] /= rhs.matrix[3][0];
	matrix[3][1] /= rhs.matrix[3][1];
	matrix[3][2] /= rhs.matrix[3][2];
	matrix[3][3] /= rhs.matrix[3][3];
	return *this;
}
bool Matrix4D<double>::operator==(const Matrix4D& rhs)
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
bool Matrix4D<double>::operator!=(const Matrix4D& rhs)
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
Vector4D<double> Matrix4D<double>::operator*(const Vector4D<double>& rhs)
{
	return Vector4D<double>(rhs.x * matrix[0][0] + rhs.y * matrix[0][1] + rhs.z * matrix[0][2] + rhs.w * matrix[0][3],
						   rhs.x * matrix[1][0] + rhs.y * matrix[1][1] + rhs.z * matrix[1][2] + rhs.w * matrix[1][3],
						   rhs.x * matrix[2][0] + rhs.y * matrix[2][1] + rhs.z * matrix[2][2] + rhs.w * matrix[2][3],
						   rhs.x * matrix[3][0] + rhs.y * matrix[3][1] + rhs.z * matrix[3][2] + rhs.w * matrix[3][3]);
}
Matrix4D<double> Matrix4D<double>::operator* (const double& rhs)
{
	return Matrix4D<double>(*this) *= rhs;
}
Matrix4D<double> Matrix4D<double>::operator*= (const double& rhs)
{
	return Matrix4D<double>(matrix[0][0] * rhs, matrix[0][1] * rhs, matrix[0][2] * rhs, matrix[0][3] * rhs,
						   matrix[1][0] * rhs, matrix[1][1] * rhs, matrix[1][2] * rhs, matrix[1][3] * rhs,
						   matrix[2][0] * rhs, matrix[2][1] * rhs, matrix[2][2] * rhs, matrix[2][3] * rhs,
						   matrix[3][0] * rhs, matrix[3][1] * rhs, matrix[3][2] * rhs, matrix[3][3]);
}
bool Matrix4D<double>::operator== (const double& rhs)
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
bool Matrix4D<double>::operator!= (const double& rhs)
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
void Matrix4D<double>::Identity()
{
	matrix[0][0] = 1.0;
	matrix[0][1] = 0.0;
	matrix[0][2] = 0.0;
	matrix[0][3] = 0.0;
	matrix[1][0] = 0.0;
	matrix[1][1] = 1.0;
	matrix[1][2] = 0.0;
	matrix[1][3] = 0.0;
	matrix[2][0] = 0.0;
	matrix[2][1] = 0.0;
	matrix[2][2] = 1.0;
	matrix[2][3] = 0.0;
	matrix[3][0] = 0.0;
	matrix[3][1] = 0.0;
	matrix[3][2] = 0.0;
	matrix[3][3] = 1.0;
}
void Matrix4D<double>::SetDiagonal(const double& Ixx, const double& Iyy, const double& Izz, const double& Iww)
{
	matrix[0][0] = Ixx;
	matrix[1][1] = Iyy;
	matrix[2][2] = Izz;
	matrix[3][3] = Iww;
}
Vector4D<double> Matrix4D<double>::Transform(const Vector4D<double>& rhs)
{
	return *this * rhs;
}
Vector4D<double> Matrix4D<double>::TransformTranspose(const Vector4D<double>& rhs)
{
	return Vector4D<double>(matrix[0][0] * rhs.x + matrix[1][0] * rhs.y + matrix[2][0] * rhs.z + matrix[3][0] * rhs.w,
						   matrix[0][1] * rhs.x + matrix[1][1] * rhs.y + matrix[2][1] * rhs.z + matrix[3][1] * rhs.w,
						   matrix[0][2] * rhs.x + matrix[1][2] * rhs.y + matrix[2][2] * rhs.z + matrix[3][2] * rhs.w,
						   matrix[0][3] * rhs.x + matrix[1][3] * rhs.y + matrix[2][3] * rhs.z + matrix[3][3] * rhs.w);
}
Vector4D<double> Matrix4D<double>::GetRow(unsigned i)
{
	return Vector4D<double>(matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3]);
}
Vector4D<double> Matrix4D<double>::GetColumn(unsigned i)
{
	return Vector4D<double>(matrix[0][i], matrix[1][i], matrix[2][i], matrix[3][i]);
}
void Matrix4D<double>::Invert()
{
	double Ixx = matrix[0][0];
	double Ixy = matrix[0][1];
	double Ixz = matrix[0][2];
	double Ixw = matrix[0][3];
	double Iyx = matrix[1][0];
	double Iyy = matrix[1][1];
	double Iyz = matrix[1][2];
	double Iyw = matrix[1][3];
	double Izx = matrix[2][0];
	double Izy = matrix[2][1];
	double Izz = matrix[2][2];
	double Izw = matrix[2][3];
	double Iwx = matrix[3][0];
	double Iwy = matrix[3][1];
	double Iwz = matrix[3][2];
	double Iww = matrix[3][3];
	double M = Ixw*Iyz*Izy*Iwx - Ixz*Iyw*Izy*Iwx - Ixw*Iyy*Izz*Iwx + Ixy*Iyw*Izz*Iwx +
			   Ixz*Iyy*Izw*Iwx - Ixy*Iyz*Izw*Iwx - Ixw*Iyz*Izx*Iwy + Ixz*Iyw*Izx*Iwy +
			   Ixw*Iyx*Izz*Iwy - Ixx*Iyw*Izz*Iwy - Ixz*Iyx*Izw*Iwy + Ixx*Iyz*Izw*Iwy +
			   Ixw*Iyy*Izx*Iwz - Ixy*Iyw*Izx*Iwz - Ixw*Iyx*Izy*Iwz + Ixx*Iyw*Izy*Iwz +
			   Ixy*Iyx*Izw*Iwz - Ixx*Iyy*Izw*Iwz - Ixz*Iyy*Izx*Iww + Ixy*Iyz*Izx*Iww +
			   Ixz*Iyx*Izy*Iww - Ixx*Iyz*Izy*Iww - Ixy*Iyx*Izz*Iww + Ixx*Iyy*Izz*Iww;

	matrix[0][0] = (Iyz*Izw*Iwy - Iyw*Izz*Iwy + Iyw*Izy*Iwz - Iyy*Izw*Iwz - Iyz*Izy*Iww + Iyy*Izz*Iww) / M;
	matrix[0][1] = (Ixw*Izz*Iwy - Ixz*Izw*Iwy - Ixw*Izy*Iwz + Ixy*Izw*Iwz + Ixz*Izy*Iww - Ixy*Izz*Iww) / M;
	matrix[0][2] = (Ixz*Iyw*Iwy - Ixw*Iyz*Iwy + Ixw*Iyy*Iwz - Ixy*Iyw*Iwz - Ixz*Iyy*Iww + Ixy*Iyz*Iww) / M;
	matrix[0][3] = (Ixw*Iyz*Izy - Ixz*Iyw*Izy - Ixw*Iyy*Izz + Ixy*Iyw*Izz + Ixz*Iyy*Izw - Ixy*Iyz*Izw) / M;
	matrix[1][0] = (Iyw*Izz*Iwx - Iyz*Izw*Iwx - Iyw*Izx*Iwz + Iyx*Izw*Iwz + Iyz*Izx*Iww - Iyx*Izz*Iww) / M;
	matrix[1][1] = (Ixz*Izw*Iwx - Ixw*Izz*Iwx + Ixw*Izx*Iwz - Ixx*Izw*Iwz - Ixz*Izx*Iww + Ixx*Izz*Iww) / M;
	matrix[1][2] = (Ixw*Iyz*Iwx - Ixz*Iyw*Iwx - Ixw*Iyx*Iwz + Ixx*Iyw*Iwz + Ixz*Iyx*Iww - Ixx*Iyz*Iww) / M;
	matrix[1][3] = (Ixz*Iyw*Izx - Ixw*Iyz*Izx + Ixw*Iyx*Izz - Ixx*Iyw*Izz - Ixz*Iyx*Izw + Ixx*Iyz*Izw) / M;
	matrix[2][0] = (Iyy*Izw*Iwx - Iyw*Izy*Iwx + Iyw*Izx*Iwy - Iyx*Izw*Iwy - Iyy*Izx*Iww + Iyx*Izy*Iww) / M;
	matrix[2][1] = (Ixw*Izy*Iwx - Ixy*Izw*Iwx - Ixw*Izx*Iwy + Ixx*Izw*Iwy + Ixy*Izx*Iww - Ixx*Izy*Iww) / M;
	matrix[2][2] = (Ixy*Iyw*Iwx - Ixw*Iyy*Iwx + Ixw*Iyx*Iwy - Ixx*Iyw*Iwy - Ixy*Iyx*Iww + Ixx*Iyy*Iww) / M;
	matrix[2][3] = (Ixw*Iyy*Izx - Ixy*Iyw*Izx - Ixw*Iyx*Izy + Ixx*Iyw*Izy + Ixy*Iyx*Izw - Ixx*Iyy*Izw) / M;
	matrix[3][0] = (Iyz*Izy*Iwx - Iyy*Izz*Iwx - Iyz*Izx*Iwy + Iyx*Izz*Iwy + Iyy*Izx*Iwz - Iyx*Izy*Iwz) / M;
	matrix[3][1] = (Ixy*Izz*Iwx - Ixz*Izy*Iwx + Ixz*Izx*Iwy - Ixx*Izz*Iwy - Ixy*Izx*Iwz + Ixx*Izy*Iwz) / M;
	matrix[3][2] = (Ixz*Iyy*Iwx - Ixy*Iyz*Iwx - Ixz*Iyx*Iwy + Ixx*Iyz*Iwy + Ixy*Iyx*Iwz - Ixx*Iyy*Iwz) / M;
	matrix[3][3] = (Ixy*Iyz*Izx - Ixz*Iyy*Izx + Ixz*Iyx*Izy - Ixx*Iyz*Izy - Ixy*Iyx*Izz + Ixx*Iyy*Izz) / M;
}
Matrix4D<double> Matrix4D<double>::Inverted()
{
	Matrix4D<double> temp(*this);
	temp.Invert();
	return temp;
}
void Matrix4D<double>::Transpose()
{
	double Ixy = matrix[0][1];
	double Ixz = matrix[0][2];
	double Ixw = matrix[0][3];
	double Iyz = matrix[1][2];
	double Iyw = matrix[1][3];
	double Izw = matrix[2][3];
	
	matrix[0][1] = matrix[1][0];
	matrix[0][2] = matrix[2][0];
	matrix[0][3] = matrix[3][0];
	matrix[1][2] = matrix[2][1];
	matrix[1][3] = matrix[3][1];
	matrix[2][3] = matrix[3][2];

	matrix[1][0] = Ixy;
	matrix[2][0] = Ixz;
	matrix[3][0] = Ixw;
	matrix[2][1] = Iyz;
	matrix[3][1] = Iyw;
	matrix[3][2] = Izw;
}
Matrix4D<double> Matrix4D<double>::Transposed()
{
	Matrix4D<double> temp(*this);
	temp.Transpose();
	return temp;
}
Matrix4D<double> Matrix4D<double>::Lerp(const Matrix4D& rhs, const double& prop)
{
	Matrix4D<double> temp(*this);
	temp.matrix[0][0] = matrix[0][0] * (1.0-prop) + rhs.matrix[0][0] * prop;
	temp.matrix[0][1] = matrix[0][1] * (1.0-prop) + rhs.matrix[0][1] * prop;
	temp.matrix[0][2] = matrix[0][2] * (1.0-prop) + rhs.matrix[0][2] * prop;
	temp.matrix[0][3] = matrix[0][3] * (1.0-prop) + rhs.matrix[0][3] * prop;
	temp.matrix[1][0] = matrix[1][0] * (1.0-prop) + rhs.matrix[1][0] * prop;
	temp.matrix[1][1] = matrix[1][1] * (1.0-prop) + rhs.matrix[1][1] * prop;
	temp.matrix[1][2] = matrix[1][2] * (1.0-prop) + rhs.matrix[1][2] * prop;
	temp.matrix[1][3] = matrix[1][3] * (1.0-prop) + rhs.matrix[1][3] * prop;
	temp.matrix[2][0] = matrix[2][0] * (1.0-prop) + rhs.matrix[2][0] * prop;
	temp.matrix[2][1] = matrix[2][1] * (1.0-prop) + rhs.matrix[2][1] * prop;
	temp.matrix[2][2] = matrix[2][2] * (1.0-prop) + rhs.matrix[2][2] * prop;
	temp.matrix[2][3] = matrix[2][3] * (1.0-prop) + rhs.matrix[2][3] * prop;
	temp.matrix[3][0] = matrix[3][0] * (1.0-prop) + rhs.matrix[3][0] * prop;
	temp.matrix[3][1] = matrix[3][1] * (1.0-prop) + rhs.matrix[3][1] * prop;
	temp.matrix[3][2] = matrix[3][2] * (1.0-prop) + rhs.matrix[3][2] * prop;
	temp.matrix[3][3] = matrix[3][3] * (1.0-prop) + rhs.matrix[3][3] * prop;
	return temp;
}
void Matrix4D<double>::Translate(const Vector3D<double>& rhs)
{
	Identity();
	matrix[3][0] = rhs.x;
	matrix[3][1] = rhs.y;
	matrix[3][2] = rhs.z;
}
Matrix4D<double> Matrix4D<double>::Translated(const Vector3D<double>& rhs)
{
	Matrix4D<double> temp(*this);
	temp.Translate(rhs);
	return temp;
}
void Matrix4D<double>::Scale(const Vector3D<double>& rhs)
{
	Identity();
	matrix[0][0] = rhs.x;
	matrix[1][1] = rhs.y;
	matrix[2][2] = rhs.z;
}
Matrix4D<double> Matrix4D<double>::Scaled(const Vector3D<double>& rhs)
{
	Matrix4D<double> temp(*this);
	temp.Scale(rhs);
	return temp;
}
void Matrix4D<double>::RotateX(const double& rhs)
{
	Identity();
	matrix[1][1] = cos(rhs);
	matrix[2][2] = cos(rhs);
	matrix[1][2] = sin(rhs);
	matrix[2][1] = -sin(rhs);
}
Matrix4D<double> Matrix4D<double>::RotatedX(const double& rhs)
{
	Matrix4D<double> temp(*this);
	temp.RotateX(rhs);
	return temp;
}
void Matrix4D<double>::RotateY(const double& rhs)
{
	Identity();
	matrix[0][0] = cos(rhs);
	matrix[2][2] = cos(rhs);
	matrix[0][2] = -sin(rhs);
	matrix[2][0] = sin(rhs);
}
Matrix4D<double> Matrix4D<double>::RotatedY(const double& rhs)
{
	Matrix4D<double> temp(*this);
	temp.RotateY(rhs);
	return temp;
}
void Matrix4D<double>::RotateZ(const double& rhs)
{
	Identity();
	matrix[0][0] = cos(rhs);
	matrix[1][1] = cos(rhs);
	matrix[0][1] = sin(rhs);
	matrix[1][0] = -sin(rhs);
}
Matrix4D<double> Matrix4D<double>::RotatedZ(const double& rhs)
{
	Matrix4D<double> temp(*this);
	temp.RotateZ(rhs);
	return temp;
}
void Matrix4D<double>::RotateYawPitchRoll(const Vector3D<double>& rhs)
{
	Identity();
	matrix[0][0] = cos(rhs.z)*cos(rhs.y) + sin(rhs.z)*sin(rhs.x)*sin(rhs.y);
	matrix[0][1] = sin(rhs.z)*cos(rhs.x);
	matrix[0][2] = cos(rhs.z)*(-sin(rhs.y)) + sin(rhs.z)*sin(rhs.x)*sin(rhs.y);
	matrix[1][0] = (-sin(rhs.z))*cos(rhs.y) + cos(rhs.z)*sin(rhs.x)*sin(rhs.y);
	matrix[1][1] = cos(rhs.z)*cos(rhs.x);
	matrix[1][2] = sin(rhs.z)*sin(rhs.y) + cos(rhs.z)*sin(rhs.x)*cos(rhs.y);
	matrix[2][0] = cos(rhs.x)*sin(rhs.y);
	matrix[2][1] = -sin(rhs.x);
	matrix[2][2] = cos(rhs.x)*cos(rhs.y);
}
Matrix4D<double> Matrix4D<double>::RotatedYawPitchRoll(const Vector3D<double>& rhs)
{
	Matrix4D<double> temp(*this);
	temp.RotateYawPitchRoll(rhs);
	return temp;
}
void Matrix4D<double>::RotateQuaternion(const Quaternion<double>& rhs)
{
	Identity();
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
Matrix4D<double> Matrix4D<double>::RotatedQuaternion(const Quaternion<double>& rhs)
{
	Matrix4D<double> temp(*this);
	temp.RotateQuaternion(rhs);
	return temp;
}
Matrix3D<double> Matrix4D<double>::GetMatrix3()
{
	return Matrix3D<double>(matrix[0][0], matrix[0][1], matrix[0][2],
							matrix[1][0], matrix[1][1], matrix[1][2],
							matrix[2][0], matrix[2][1], matrix[2][2]);
}