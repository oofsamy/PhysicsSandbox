#pragma once
#include "Includes.hpp"

#define GRAVITATIONAL_CONSTANT (float)9.81

template<typename VectorType>
struct Vector2
{
	VectorType x;
	VectorType y;

public:
	Vector2<VectorType>& operator += (const Vector2<VectorType>& Other)
	{
		this->x += Other.x;
		this->y += Other.y;

		return *this;
	}

	Vector2<VectorType>& operator -= (const Vector2<VectorType>& Other)
	{
		this->x -= Other.x;
		this->y -= Other.y;

		return *this;
	}

	inline Vector2<VectorType> operator + (const Vector2<VectorType>& Other)
	{
		return Vector2<VectorType>{this->x + Other.x, this->y + Other.y};
	}

	inline Vector2<VectorType> operator + (const VectorType Other)
	{
		return Vector2<VectorType>{this->x + Other, this->y + Other};
	}

	inline Vector2<VectorType> operator - (const Vector2<VectorType>& Other)
	{
		return Vector2<VectorType>{this->x - Other.x, this->y - Other.y};
	}

	inline Vector2<VectorType> operator - (const VectorType Other)
	{
		return Vector2<VectorType>{this->x - Other, this->y - Other};
	}

	inline Vector2<VectorType> operator * (const Vector2<VectorType>& Other)
	{
		return Vector2<VectorType>{this->x * Other.x, this->y * Other.y};
	}

	inline Vector2<VectorType> operator * (const VectorType Other)
	{
		return Vector2<VectorType>{this->x * Other, this->y * Other};
	}

	inline Vector2<VectorType> operator / (const Vector2<VectorType>& Other)
	{
		return Vector2<VectorType>{this->x / Other.x, this->y / Other.y};
	}

	inline Vector2<VectorType> operator / (const VectorType Other)
	{
		return Vector2<VectorType>{this->x / Other, this->y / Other};
	}

public:
	float GetMagnitude()
	{
		float Magnitude = pow(((this.x ^ 2) + (this.y ^ 2)), (1 / 2));

		return Magnitude;
	}

	VectorType GetNormalised()
	{
		float Magnitude = this->GetMagnitude();
		
		return VectorType{ this->x / Magnitude, this->y / Magnitude };
	}

	static VectorType DotProduct(Vector2<VectorType> VectorA, Vector2<VectorType> VectorB)
	{
		return (VectorA.x + VectorB.x + VectorA.y + VectorB.y);
	}
};