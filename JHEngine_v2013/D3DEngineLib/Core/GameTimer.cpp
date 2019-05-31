#include "..\Common.h"
#include "GameTimer.h"


CGameTimer::CGameTimer()
	: mSecondsPerCount(0.0), mDeltaTime(-1.0), mBaseTime(0),
	mPausedTime(0), mPrevTime(0), mCurrTime(0), mStopped(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / (double)countsPerSec;
}


CGameTimer::~CGameTimer()
{
}

float CGameTimer::TotalTime() const
{
	//���� Ÿ�̸Ӱ� �ߴ� �����̸� �ߴܵ� �ķκ��� �帥 �ð��� ������� ���ƾ� �Ѵ�.
	//���� ������ �Ͻ� ������ ���� �ִٸ� �� �ð��� ��ü �ð��� ���Խ�Ű�� ���ƾ� �Ѵ�.
	//�̸� ���� mStopTime���� �Ͻ����� �ð��� ����.
	//
	//                     |<--paused time-->|
	// ----*---------------*-----------------*------------*------------*------> time
	//  mBaseTime       mStopTime        startTime     mStopTime    mCurrTime

	if (mStopped)
	{
		return (float)(((mStopTime - mPausedTime) - mBaseTime)*mSecondsPerCount);
	}

	//�ð��� mCurrTime - mBaseTime���� �Ͻ� ������ �ð��� ���ԵǾ� �ִ�.
	//�̸� ��ü �ð��� ���Խ�Ű�� �ȵǹǷ�, �� �ð��� mCurrTime���� ���Ѵ�.
	//
	//  (mCurrTime - mPausedTime) - mBaseTime 
	//
	//                     |<--paused time-->|
	// ----*---------------*-----------------*------------*------> time
	//  mBaseTime       mStopTime        startTime     mCurrTime

	else
	{
		return (float)(((mCurrTime - mPausedTime) - mBaseTime)*mSecondsPerCount);
	}

}

float CGameTimer::DeltaTime() const
{
	return (float)mDeltaTime;
}

DWORD CGameTimer::CurrentTime() const
{
	return (DWORD)mCurrTime;
}

void CGameTimer::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;

	//�� �Լ��� �޽��� ���� ������ ȣ��ǹǷ�
	//�޽��� ���� ���� mPrevTime�� �ʱ�ȭ �����ش�.
}

void CGameTimer::Start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	//�ߴܰ� ���� ���̿� �帥 �ð��� �����Ѵ�.
	//
	//                     |<-------d------->|
	// ----*---------------*-----------------*------------> time
	//  mBaseTime       mStopTime        startTime     

	//�ߴ� ���¿��� Ÿ�̸Ӹ� �ٽ� �簳�ϴ� �����
	if (mStopped)
	{
		//�Ͻ����� �ð��� �����Ѵ�.
		mPausedTime += (startTime - mStopTime);

		//Ÿ�̸Ӹ� �ٽ� �����ϴ� ���̹Ƿ� mPrevTime(�����ð�)�� ���� ����
		//��ȿ���� �ʴ�
		//���� ���� �ð����� �ٽ� �����Ѵ�.
		mPrevTime = startTime;

		//�� �̻��� �ߴ� ���°� �ƴ�
		mStopTime = 0;
		mStopped = false;
	}
}

void CGameTimer::Stop()
{
	//�̹� ���� ���¸�ƹ� �ϵ� ���� �ʴ´�.
	if (!mStopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		//�׷��� �ʴٸ� �Ͻ� ������ ������ �ð��� �����ϰ�,
		//Ÿ�̸Ӱ� �ߴܵǾ����� ���ϴ� bool �÷��׸� �����Ѵ�.
		mStopTime = currTime;
		mStopped = true;
	}
}

void CGameTimer::Tick()
{
	if (mStopped)
	{
		mDeltaTime = 0.0;
		return;
	}

	//�̹� �������� �ð��� ��´�
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mCurrTime = currTime;

	//�� �ð��� ���� �������� �ð��� ���̸� ���Ѵ�.
	mDeltaTime = (mCurrTime - mPrevTime) * mSecondsPerCount;

	//���� �������� �غ��Ѵ�.
	mPrevTime = mCurrTime;

	//������ ���� �ʰ� �Ѵ�. SDK ����ȭ�� CDXUTTimer �׸� ������,
	//���μ����� ���� ���� ���ų� �ٸ� ���μ����� ��Ű�� ���
	//mDeltaTime�� ������ �� �� �ִ�.
	if (mDeltaTime < 0.0)
	{
		mDeltaTime = 0.0;
	}

}