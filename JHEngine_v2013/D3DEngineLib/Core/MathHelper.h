#pragma once

#ifndef _MATH_HELPER_H_
#define _MATH_HELPER_H_

#include <Windows.h>
#include <xnamath.h>

class CMathHelper
{
public:
	CMathHelper();
	~CMathHelper();

public:
	// Returns random float in [0, 1).
	static float RandF()
	{
		return (float)(rand()) / (float)RAND_MAX;
	}

	// Returns random float in [a, b).
	static float RandF(float a, float b)
	{
		return a + RandF()*(b - a);
	}

	template<typename T>
	static T Min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}

	template<typename T>
	static T Max(const T& a, const T& b)
	{
		return a > b ? a : b;
	}

	template<typename T>
	static T Lerp(const T& a, const T& b, float t)
	{
		return a + (b - a)*t;
	}

	template<typename T>
	static T Clamp(const T& x, const T& low, const T& high)
	{
		return x < low ? low : (x > high ? high : x);
	}


	static XMMATRIX InverseTranspose(CXMMATRIX M)
	{
		// Inverse-transpose is just applied to normals.  So zero out 
		// translation row so that it doesn't get into our inverse-transpose
		// calculation--we don't want the inverse-transpose of the translation.
		XMMATRIX A = M;
		A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

		XMVECTOR det = XMMatrixDeterminant(A);
		return XMMatrixTranspose(XMMatrixInverse(&det, A));
	}
	
	

	static void quat_2_euler_d3d(const XMFLOAT4& q, float& pitch, float& yaw, float& roll)
	{
		float sqw = q.w*q.w;
		float sqx = q.x*q.x;
		float sqy = q.y*q.y;
		float sqz = q.z*q.z;
		pitch = asinf(2.0f * (q.w*q.x - q.y*q.z)); // rotation about x-axis
		yaw = atan2f(2.0f * (q.x*q.z + q.w*q.y), (-sqx - sqy + sqz + sqw)); // rotation about y-axis
		roll = atan2f(2.0f * (q.x*q.y + q.w*q.z), (-sqx + sqy - sqz + sqw)); // rotation about z-axis
	}

	XMFLOAT4 & euler_2_quat_d3d(XMFLOAT4 &q, const float yaw, const float pitch, const float roll)
	{
		XMFLOAT4 qpitch(1, 0, 0, pitch), qyaw(0, 1, 0, yaw), qroll(0, 0, 1, roll);

		XMVECTOR qXM = XMLoadFloat4(&qyaw) * XMLoadFloat4(&qpitch) * XMLoadFloat4(&qroll);
		XMStoreFloat4(&q, qXM);
		return q;
	}



	static const float Pi;
	static const float Infinity;
};


#endif // !_MATH_HELPER_H_