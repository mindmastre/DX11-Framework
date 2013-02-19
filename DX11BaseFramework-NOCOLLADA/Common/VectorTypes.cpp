#include "VectorTypes.h"

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float xVal, float yVal, float zVal) //ctor
{
	x = xVal;
	y = yVal;
	z = zVal;
}
//returns a perpendicular 
Vector3 Vector3::Perp()
{
  return Vector3(-y, x, z);
}

Vector3& Vector3::operator=(const Vector3 &rhs)
{

    // Only do assignment if RHS is a different object from this.
    if (this != &rhs) {
       x = rhs.x;
	   y = rhs.y;
	   z = rhs.z;
    }
    return *this;
  }
bool Vector3::operator==(const Vector3 &rhs) const
{
	  return x ==rhs.x &&
             y == rhs.y && z == rhs.z;
}
Vector3 Vector3::operator-= (const Vector3 &rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vector3 Vector3::operator- (const Vector3 &rhs)
{
	return Vector3(*this) -= rhs;
}

Vector3 Vector3::operator+= (const Vector3 &rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector3 Vector3::operator+ (const Vector3 &rhs)
{
	return Vector3(*this) += rhs;
}

float Vector3::operator* (const Vector3 &rhs)
{
	x = x * rhs.x;
	y = y * rhs.y;
	z = z * rhs.z;
	return x + y + z;
}

Vector3 Vector3::operator+ (const float &rhs)
{
	x += rhs;
	y += rhs;
	z +=rhs;
	return Vector3(x , y , z);
}

Vector3 Vector3::operator* (const float &rhs)
{
	Vector3 temp;
	temp.x = x * rhs;
	temp.y = y * rhs;
	temp.z = z * rhs;
	return temp;
}

Vector3 Vector3::operator*= (const float &rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}

Vector3 Vector3::operator%(const Vector3 &vector)const
{
	return Vector3(y*vector.z-z*vector.y,
					z*vector.x-x*vector.z,
					x*vector.y-y*vector.x);
}

Vector3 Vector3::vectorProduct(const Vector3 &vector)const
{
	return Vector3(y*vector.z-z*vector.y, z*vector.x-x*vector.z, x*vector.y-y*vector.x);
}

void Vector3::operator %=(const Vector3 &vector)
{
	*this = vectorProduct(vector);
}

float Vector3::magnitude()
{
	return sqrt(sqrmagnitude());
}

float Vector3::sqrmagnitude()
{
	return x * x + y * y + z * z;
}

void Vector3::invert()
{
	x*=-1;
	y*=-1;
	z*=-1;
}

void Vector3::scale(float speed)
{
	x *= speed;
	y *= speed;
	z *= speed;
}

void Vector3::clear()
{
	x=0;
	y=0;
	z=0;
}
bool Vector3::operator<(const Vector3& other) const
{
            return x < other.x && y < other.y && z < other.z;
}
Vector3 Vector3::operator/ (const float &rhs)
{
	return Vector3(x/rhs,y/rhs,z/rhs);
}
Vector3 Vector3::normalize()
{
	//A is the magnitude of the vector
	float A = magnitude();
	if (A == 0)
		A = 1;

	//vector components being normalized
	x = x/A;
	y = y/A;
	z = z/A;
	return *this;
}
Vector3 Vector3::normalize(const Vector3& v)
{
  Vector3 vec = v;

  float vector_length = vec.magnitude();

  if (vector_length == 0)
	  vector_length = 1;
  {
    vec.x /= vector_length;
    vec.y /= vector_length;
	vec.z /= vector_length;
  }

  return vec;
}

void Vector3::makeOrthonormalBasis(Vector3 *a, Vector3 *b, Vector3 *c)
{
	a->normalize();
	(*c) = (*a)%(*b);
	//if (c->sqrmagnitude() == 0.0) return; //Or generate an error. this is the textbook version
	if (c->sqrmagnitude() == 0.0)
	{
		b->x += 1;
		(*c) = (*a)%(*b);
	}
	c->normalize();
	(*b) = (*c) % (*a);
}

void Vector3::addScaledVector (const Vector3 vector, float scale)
{
	x += vector.x * scale;
	y += vector.y * scale;
	z += vector.z * scale;
}

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float xVal, float yVal) //ctor
{
	x = xVal;
	y = yVal;
}
////returns a perpendicular 
//Vector2 Vector2::Perp()
//{
//  return Vector2(-y, x);
//}
//
//Vector2& Vector2::operator=(const Vector2 &rhs)
//{
//
//    // Only do assignment if RHS is a different object from this.
//    if (this != &rhs) {
//       x = rhs.x;
//	   y = rhs.y;
//    }
//    return *this;
//  }
//bool Vector2::operator==(const Vector2 &rhs) const
//{
//	  return x ==rhs.x &&
//             y == rhs.y;
//}
//Vector2 Vector2::operator-= (const Vector2 &rhs)
//{
//	x -= rhs.x;
//	y -= rhs.y;
//	return *this;
//}
//
//Vector2 Vector2::operator- (const Vector2 &rhs)
//{
//	return Vector2(*this) -= rhs;
//}
//
//Vector2 Vector2::operator+= (const Vector2 &rhs)
//{
//	x += rhs.x;
//	y += rhs.y;
//	return *this;
//}
//
//Vector2 Vector2::operator+ (const Vector2 &rhs)
//{
//	return Vector2(*this) += rhs;
//}
//
//float Vector2::operator* (const Vector2 &rhs)
//{
//	x = x * rhs.x;
//	y = y * rhs.y;
//	return x + y;
//}
//
//Vector2 Vector2::operator* (const float &rhs)
//{
//	Vector2 temp;
//	temp.x = x * rhs;
//	temp.y = y * rhs;
//	return temp;
//}
//
//Vector2 Vector2::operator*= (const float &rhs)
//{
//	x *= rhs;
//	y *= rhs;
//	return *this;
//}
//
//Vector2 Vector2::operator%(const Vector2 &vector)const
//{
//	return Vector2(0,0);//(y*vector.y,//x*vector.y-y*vector.x);
//}
//
//Vector2 Vector2::vectorProduct(const Vector2 &vector)const
//{
//	return Vector2(0,0);//Vector2(y*vector.z-z*vector.y, z*vector.x-x*vector.z, x*vector.y-y*vector.x);
//}
//
//void Vector2::operator %=(const Vector2 &vector)
//{
//	*this = vectorProduct(vector);
//}
//
//float Vector2::magnitude()
//{
//	return sqrt(sqrmagnitude());
//}
//
//float Vector2::sqrmagnitude()
//{
//	return x * x + y * y ;
//}
//
//void Vector2::invert()
//{
//	x*=-1;
//	y*=-1;
//}
//
//void Vector2::scale(float speed)
//{
//	x *= speed;
//	y *= speed;
//}
//
//void Vector2::clear()
//{
//	x=0;
//	y=0;
//}
//bool Vector2::operator<(const Vector2& other) const
//{
//            return false;//x < other.x && y < other. < other.z;
//}
//Vector2 Vector2::normalize()
//{
//	//A is the magnitude of the vector
//	float A = magnitude();
//	if (A == 0)
//		A = 1;
//
//	//vector components being normalized
//	x = x/A;
//	y = y/A;
//	return *this;
//}
//Vector2 Vector2::normalize(const Vector2& v)
//{
//  Vector2 vec = v;
//
//  float vector_length = vec.magnitude();
//
//  if (vector_length == 0)
//	  vector_length = 1;
//  {
//    vec.x /= vector_length;
//    vec.y /= vector_length;
//  }
//
//  return vec;
//}
//
//void Vector2::makeOrthonormalBasis(Vector2 *a, Vector2 *b, Vector2 *c)
//{
//	a->normalize();
//	(*c) = (*a)%(*b);
//	//if (c->sqrmagnitude() == 0.0) return; //Or generate an error. this is the textbook version
//	if (c->sqrmagnitude() == 0.0)
//	{
//		b->x += 1;
//		(*c) = (*a)%(*b);
//	}
//	c->normalize();
//	(*b) = (*c) % (*a);
//}
//
//void Vector2::addScaledVector (const Vector2 vector, float scale)
//{
//	x += vector.x * scale;
//	y += vector.y * scale;
//}