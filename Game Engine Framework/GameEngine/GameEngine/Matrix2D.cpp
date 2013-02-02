#include "Matrix2D.h"

/////////////////////////////////////////////////
//               float template
/////////////////////////////////////////////////
Matrix2D<float>::Matrix2D()
{
	matrix[0][0] = 0.0f;
	matrix[0][1] = 0.0f;
	matrix[1][0] = 0.0f;
	matrix[1][1] = 0.0f;
}
Matrix2D<float>::Matrix2D(float val)
{
	matrix[0][0] = val;
	matrix[0][1] = val;
	matrix[1][0] = val;
	matrix[1][1] = val;
}
Matrix2D<float>::Matrix2D(float Ixx, float Ixy, float Iyx, float Iyy)
{
	matrix[0][0] = Ixx;
	matrix[0][1] = Ixy;
	matrix[1][0] = Iyx;
	matrix[1][1] = Iyy;
}
Matrix2D<float>::Matrix2D(Vector2D<float> column0, Vector2D<float> column1)
{
	matrix[0][0] = column0.x;
	matrix[0][1] = column1.x;
	matrix[1][0] = column0.y;
	matrix[1][1] = column1.y;
}
Matrix2D<float>::~Matrix2D()
{
	//do nothing
}
float Matrix2D<float>::operator[](unsigned i)
{
	if(i == 0)		return matrix[0][0];
	else if(i == 1) return matrix[0][1];
	else if(i == 2) return matrix[1][0];
	else			return matrix[1][1];
}
Matrix2D<float> Matrix2D<float>::operator+(const Matrix2D& rhs)
{
	return Matrix2D<float>(*this) += rhs;
}
Matrix2D<float> Matrix2D<float>::operator-(const Matrix2D& rhs)
{
	return Matrix2D<float>(*this) -= rhs;
}
Matrix2D<float> Matrix2D<float>::operator*(const Matrix2D& rhs)
{
	return Matrix2D<float>(*this) *= rhs;
}
Matrix2D<float> Matrix2D<float>::operator/(const Matrix2D& rhs)
{
	return Matrix2D<float>(*this) /= rhs;
}
Matrix2D<float> Matrix2D<float>::operator+=(const Matrix2D& rhs)
{
	matrix[0][0] += rhs.matrix[0][0];
	matrix[0][1] += rhs.matrix[0][1];
	matrix[1][0] += rhs.matrix[1][0];
	matrix[1][1] += rhs.matrix[1][1];
	return *this;
}
Matrix2D<float> Matrix2D<float>::operator-=(const Matrix2D& rhs)
{
	matrix[0][0] -= rhs.matrix[0][0];
	matrix[0][1] -= rhs.matrix[0][1];
	matrix[1][0] -= rhs.matrix[1][0];
	matrix[1][1] -= rhs.matrix[1][1];
	return *this;
}
Matrix2D<float> Matrix2D<float>::operator*=(const Matrix2D& rhs)
{
	matrix[0][0] *= rhs.matrix[0][0];
	matrix[0][1] *= rhs.matrix[0][1];
	matrix[1][0] *= rhs.matrix[1][0];
	matrix[1][1] *= rhs.matrix[1][1];
	return *this;
}
Matrix2D<float> Matrix2D<float>::operator/=(const Matrix2D& rhs)
{
	matrix[0][0] /= rhs.matrix[0][0];
	matrix[0][1] /= rhs.matrix[0][1];
	matrix[1][0] /= rhs.matrix[1][0];
	matrix[1][1] /= rhs.matrix[1][1];
	return *this;
}
bool Matrix2D<float>::operator==(const Matrix2D& rhs)
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
bool Matrix2D<float>::operator!=(const Matrix2D& rhs)
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
Vector2D<float> Matrix2D<float>::operator*(const Vector2D<float>& rhs)
{
	return Vector2D<float>(rhs.x * matrix[0][0] + rhs.y * matrix[0][1], rhs.x * matrix[1][0] + rhs.y * matrix[1][1]);
}
Matrix2D<float> Matrix2D<float>::operator* (const float& rhs)
{
	return Matrix2D<float>(*this) *= rhs;
}
Matrix2D<float> Matrix2D<float>::operator*= (const float& rhs)
{
	return Matrix2D<float>(matrix[0][0] * rhs, matrix[0][1] * rhs,
						   matrix[1][0] * rhs, matrix[1][1] * rhs);
}
bool Matrix2D<float>::operator== (const float& rhs)
{
	return matrix[0][0] == rhs && matrix[0][1] == rhs
		&& matrix[1][0] == rhs && matrix[1][1] == rhs;
}
bool Matrix2D<float>::operator!= (const float& rhs)
{
	return matrix[0][0] != rhs || matrix[0][1] != rhs
		|| matrix[1][0] != rhs || matrix[1][1] != rhs;
}
void Matrix2D<float>::Identity()
{
	matrix[0][0] = 1.0f;
	matrix[0][1] = 0.0f;
	matrix[1][0] = 0.0f;
	matrix[1][1] = 1.0f;
}
void Matrix2D<float>::SetDiagonal(const float& Ixx, const float& Iyy)
{
	matrix[0][0] = Ixx;
	matrix[1][1] = Iyy;
}
Vector2D<float> Matrix2D<float>::Transform(const Vector2D<float>& rhs)
{
	return *this * rhs;
}
Vector2D<float> Matrix2D<float>::TransformTranspose(const Vector2D<float>& rhs)
{
	return Vector2D<float>(matrix[0][0] * rhs.x + matrix[1][0] * rhs.y,
						   matrix[0][1] * rhs.x + matrix[1][1] * rhs.y);
}
Vector2D<float> Matrix2D<float>::GetRow(unsigned i)
{
	return Vector2D<float>(matrix[i][0], matrix[i][1]);
}
Vector2D<float> Matrix2D<float>::GetColumn(unsigned i)
{
	return Vector2D<float>(matrix[0][i], matrix[1][i]);
}
void Matrix2D<float>::Invert()
{
	float Ixx = matrix[0][0];
	float Ixy = matrix[0][1];
	float Iyx = matrix[1][0];
	float Iyy = matrix[1][1];
	float M = Ixx * Iyy - Iyx * Ixy;

	matrix[0][0] = Iyy / M;
	matrix[0][1] = -Ixy / M;
	matrix[1][0] = -Iyx / M;
	matrix[1][1] = Ixx / M;
}
Matrix2D<float> Matrix2D<float>::Inverted()
{
	Matrix2D<float> temp(*this);
	temp.Invert();
	return temp;
}
void Matrix2D<float>::Transpose()
{
	float Ixy = matrix[0][1];
	matrix[0][1] = matrix[1][0];
	matrix[1][0] = Ixy;
}
Matrix2D<float> Matrix2D<float>::Transposed()
{
	Matrix2D<float> temp(*this);
	temp.Transpose();
	return temp;
}
Matrix2D<float> Matrix2D<float>::Lerp(const Matrix2D& rhs, const float& prop)
{
	Matrix2D<float> temp(*this);
	temp.matrix[0][0] = matrix[0][0] * (1.0f-prop) + rhs.matrix[0][0] * prop;
	temp.matrix[0][1] = matrix[0][1] * (1.0f-prop) + rhs.matrix[0][1] * prop;
	temp.matrix[1][0] = matrix[1][0] * (1.0f-prop) + rhs.matrix[1][0] * prop;
	temp.matrix[1][1] = matrix[1][1] * (1.0f-prop) + rhs.matrix[1][1] * prop;
	return temp;
}
/////////////////////////////////////////////////
//               double template
/////////////////////////////////////////////////
Matrix2D<double>::Matrix2D()
{
	matrix[0][0] = 0.0;
	matrix[0][1] = 0.0;
	matrix[1][0] = 0.0;
	matrix[1][1] = 0.0;
}
Matrix2D<double>::Matrix2D(double val)
{
	matrix[0][0] = val;
	matrix[0][1] = val;
	matrix[1][0] = val;
	matrix[1][1] = val;
}
Matrix2D<double>::Matrix2D(double Ixx, double Ixy, double Iyx, double Iyy)
{
	matrix[0][0] = Ixx;
	matrix[0][1] = Ixy;
	matrix[1][0] = Iyx;
	matrix[1][1] = Iyy;
}
Matrix2D<double>::Matrix2D(Vector2D<double> column0, Vector2D<double> column1)
{
	matrix[0][0] = column0.x;
	matrix[0][1] = column1.x;
	matrix[1][0] = column0.y;
	matrix[1][1] = column1.y;
}
Matrix2D<double>::~Matrix2D()
{
	//do nothing
}
double Matrix2D<double>::operator[](unsigned i)
{
	if(i == 0)		return matrix[0][0];
	else if(i == 1) return matrix[0][1];
	else if(i == 2) return matrix[1][0];
	else			return matrix[1][1];
}
Matrix2D<double> Matrix2D<double>::operator+(const Matrix2D& rhs)
{
	return Matrix2D<double>(*this) += rhs;
}
Matrix2D<double> Matrix2D<double>::operator-(const Matrix2D& rhs)
{
	return Matrix2D<double>(*this) -= rhs;
}
Matrix2D<double> Matrix2D<double>::operator*(const Matrix2D& rhs)
{
	return Matrix2D<double>(*this) *= rhs;
}
Matrix2D<double> Matrix2D<double>::operator/(const Matrix2D& rhs)
{
	return Matrix2D<double>(*this) /= rhs;
}
Matrix2D<double> Matrix2D<double>::operator+=(const Matrix2D& rhs)
{
	matrix[0][0] += rhs.matrix[0][0];
	matrix[0][1] += rhs.matrix[0][1];
	matrix[1][0] += rhs.matrix[1][0];
	matrix[1][1] += rhs.matrix[1][1];
	return *this;
}
Matrix2D<double> Matrix2D<double>::operator-=(const Matrix2D& rhs)
{
	matrix[0][0] -= rhs.matrix[0][0];
	matrix[0][1] -= rhs.matrix[0][1];
	matrix[1][0] -= rhs.matrix[1][0];
	matrix[1][1] -= rhs.matrix[1][1];
	return *this;
}
Matrix2D<double> Matrix2D<double>::operator*=(const Matrix2D& rhs)
{
	matrix[0][0] *= rhs.matrix[0][0];
	matrix[0][1] *= rhs.matrix[0][1];
	matrix[1][0] *= rhs.matrix[1][0];
	matrix[1][1] *= rhs.matrix[1][1];
	return *this;
}
Matrix2D<double> Matrix2D<double>::operator/=(const Matrix2D& rhs)
{
	matrix[0][0] /= rhs.matrix[0][0];
	matrix[0][1] /= rhs.matrix[0][1];
	matrix[1][0] /= rhs.matrix[1][0];
	matrix[1][1] /= rhs.matrix[1][1];
	return *this;
}
bool Matrix2D<double>::operator==(const Matrix2D& rhs)
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
bool Matrix2D<double>::operator!=(const Matrix2D& rhs)
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
Vector2D<double> Matrix2D<double>::operator*(const Vector2D<double>& rhs)
{
	return Vector2D<double>(rhs.x * matrix[0][0] + rhs.y * matrix[0][1], rhs.x * matrix[1][0] + rhs.y * matrix[1][1]);
}
Matrix2D<double> Matrix2D<double>::operator* (const double& rhs)
{
	return Matrix2D<double>(*this) *= rhs;
}
Matrix2D<double> Matrix2D<double>::operator*= (const double& rhs)
{
	return Matrix2D<double>(matrix[0][0] * rhs, matrix[0][1] * rhs,
						   matrix[1][0] * rhs, matrix[1][1] * rhs);
}
bool Matrix2D<double>::operator== (const double& rhs)
{
	return matrix[0][0] == rhs && matrix[0][1] == rhs
		&& matrix[1][0] == rhs && matrix[1][1] == rhs;
}
bool Matrix2D<double>::operator!= (const double& rhs)
{
	return matrix[0][0] != rhs || matrix[0][1] != rhs
		|| matrix[1][0] != rhs || matrix[1][1] != rhs;
}
void Matrix2D<double>::Identity()
{
	matrix[0][0] = 1.0;
	matrix[0][1] = 0.0;
	matrix[1][0] = 0.0;
	matrix[1][1] = 1.0;
}
void Matrix2D<double>::SetDiagonal(const double& Ixx, const double& Iyy)
{
	matrix[0][0] = Ixx;
	matrix[1][1] = Iyy;
}
Vector2D<double> Matrix2D<double>::Transform(const Vector2D<double>& rhs)
{
	return *this * rhs;
}
Vector2D<double> Matrix2D<double>::TransformTranspose(const Vector2D<double>& rhs)
{
	return Vector2D<double>(matrix[0][0] * rhs.x + matrix[1][0] * rhs.y,
							matrix[0][1] * rhs.x + matrix[1][1] * rhs.y);
}
Vector2D<double> Matrix2D<double>::GetRow(unsigned i)
{
	return Vector2D<double>(matrix[i][0], matrix[i][1]);
}
Vector2D<double> Matrix2D<double>::GetColumn(unsigned i)
{
	return Vector2D<double>(matrix[0][i], matrix[1][i]);
}
void Matrix2D<double>::Invert()
{
	double Ixx = matrix[0][0];
	double Ixy = matrix[0][1];
	double Iyx = matrix[1][0];
	double Iyy = matrix[1][1];
	double M = Ixx * Iyy - Iyx * Ixy;

	matrix[0][0] = Iyy / M;
	matrix[0][1] = -Ixy / M;
	matrix[1][0] = -Iyx / M;
	matrix[1][1] = Ixx / M;
}
Matrix2D<double> Matrix2D<double>::Inverted()
{
	Matrix2D<double> temp(*this);
	temp.Invert();
	return temp;
}
void Matrix2D<double>::Transpose()
{
	double Ixy = matrix[0][1];
	matrix[0][1] = matrix[1][0];
	matrix[1][0] = Ixy;
}
Matrix2D<double> Matrix2D<double>::Transposed()
{
	Matrix2D<double> temp(*this);
	temp.Transpose();
	return temp;
}
Matrix2D<double> Matrix2D<double>::Lerp(const Matrix2D& rhs, const double& prop)
{
	Matrix2D<double> temp(*this);
	temp.matrix[0][0] = matrix[0][0] * (1.0-prop) + rhs.matrix[0][0] * prop;
	temp.matrix[0][1] = matrix[0][1] * (1.0-prop) + rhs.matrix[0][1] * prop;
	temp.matrix[1][0] = matrix[1][0] * (1.0-prop) + rhs.matrix[1][0] * prop;
	temp.matrix[1][1] = matrix[1][1] * (1.0-prop) + rhs.matrix[1][1] * prop;
	return temp;
}