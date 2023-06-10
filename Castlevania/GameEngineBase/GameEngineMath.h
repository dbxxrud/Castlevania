#pragma once
#include <cmath>
#include "GameEngineDebug.h"

// 설명 :
class GameEngineMath
{
};

class float4
{
public:
	static const float4 ZERO;
	static const float4 LEFT;
	static const float4 RIGHT;
	static const float4 UP;
	static const float4 DOWN;

	// 전부다 public일때 생성자도 없으면 리스트이니셜라이저(초기화)가 가능하다
	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;
	float W = 1.0f;

	// 값 형을 형변환 할때는 static_cast가 기본이다
	inline int iX() const
	{
		return static_cast<int>(X);
	}

	inline int iY() const
	{
		return static_cast<int>(Y);
	}

	inline float hX() const
	{
		return X * 0.5f;
	}

	inline float hY() const
	{
		return Y * 0.5f;
	}


	inline int ihX() const
	{
		return static_cast<int>(hX());
	}

	inline int ihY() const
	{
		return static_cast<int>(hY());
	}

	inline float4 Half() const
	{
		return { hX(), hY(), Z, W };
	}

	/*
	 +=, *= 연산자를 float4 클래스의 멤버 함수로 구현하고 있으며, 레퍼런스를 반환하여 객체의 값을 직접 변경할 수 있도록 하고 있음
	 함수의 인자가 8바이트 초과면 레퍼런스나 포인터, 8바이트 이하는 그냥 쓴다.
	*/
	float4 operator-() const
	{
		float4 ReturnValue = *this;

		ReturnValue.X = -ReturnValue.X;
		ReturnValue.Y = -ReturnValue.Y;
		ReturnValue.Z = -ReturnValue.Z;
		return ReturnValue;
	}

	float4 operator-(const float4& _Other) const
	{
		float4 ReturnValue;

		ReturnValue.X = X - _Other.X;
		ReturnValue.Y = Y - _Other.Y;
		ReturnValue.Z = Z - _Other.Z;

		return ReturnValue;
	}

	float4 operator+(const float4& _Other) const
	{
		float4 ReturnValue;

		ReturnValue.X = X + _Other.X;
		ReturnValue.Y = Y + _Other.Y;
		ReturnValue.Z = Z + _Other.Z;

		return ReturnValue;
	}

	float4 operator*(const float4& _Other) const
	{
		float4 ReturnValue;

		ReturnValue.X = X * _Other.X;
		ReturnValue.Y = Y * _Other.Y;
		ReturnValue.Z = Z * _Other.Z;

		return ReturnValue;
	}


	float4 operator*(const float _Value) const
	{
		float4 ReturnValue;

		ReturnValue.X = X * _Value;
		ReturnValue.Y = Y * _Value;
		ReturnValue.Z = Z * _Value;

		return ReturnValue;
	}

	float4& operator+=(const float4& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		Z += _Other.Z;

		return *this;
	}


	float4& operator-=(const float4& _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;
		Z -= _Other.Z;

		return *this;
	}

	float4& operator*=(const float4& _Other)
	{
		X *= _Other.X;
		Y *= _Other.Y;
		Z *= _Other.Z;

		return *this;
	}

	float4& operator*=(const float _Value)
	{
		X *= _Value;
		Y *= _Value;
		Z *= _Value;

		return *this;
	}

	bool operator==(const float4 _Value) const
	{
		return X == _Value.X &&
			Y == _Value.Y &&
			Z == _Value.Z;
	}

	inline void Normalize()
	{
		// 길이를 1로만드는 함수이다
		float Len = Size();

		if (0 >= Len)
		{
			MsgBoxAssert("0으로 나누려고 했습니다.");
		}

		X /= Len;
		Y /= Len;
		Z /= Len;
	}

	inline float4 NormalizeReturn()
	{
		float4 Result = *this;

		Result.Normalize();

		return Result; // 자기자신은 바꾸지 않고 자기자신을 기반으로 길이 1짜리를 만들어서 리턴해준다
	}


	inline float Size()
	{
		float Value = X * X + Y * Y; // == 빗변 * 빗변

		// 제곱수이다
		// 제곱을 풀어서 제곱근이라고 한다
		// Value => 빗변 * 빗변
		return sqrtf(Value); // 여기서 나오는 값이 제곱근! 즉 빗변의 길이
	}

	float Max2D() const
	{
		return X > Y ? X : Y;
	}

	std::string ToString()
	{
		char ArrReturn[256];

		sprintf_s(ArrReturn, " x: %f, y: %f, z: %f, w: %f", X, Y, Z, W);

		return std::string(ArrReturn);
	}

};