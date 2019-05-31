#pragma once

#ifndef _GAME_TIMER_H_
#define _GAME_TIMER_H_

#include "Singleton.h"

#define g_pGameTimer CGameTimer::GetInstance()

class CGameTimer : public CSingleton<CGameTimer>
{
public:
	CGameTimer();
	~CGameTimer();

	float TotalTime() const;	//�ʴ���, ���� ���α׷��� ���۵� ���Ŀ� �帥�ð�(�Ͻ� ������ �ð��� ����)
	float DeltaTime() const;	//�ʴ���
	DWORD CurrentTime() const;

	void Reset();	//�޽��� ���� ������ ȣ���ؾ� ��
	void Start();	//Ÿ�̸� ����, �簳 �� ȣ���ؾ� ��
	void Stop();	//�Ͻ����� �� ȣ���ؾ� ��
	void Tick();	//�� �����Ӹ��� ȣ���ؾ� ��

private:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;		//TotalTime�� ���ϱ� ���� ���� 
							//mBaseTime�� Reset()�� ȣ��� �� ���� �ð����� �ʱ�ȭ�ȴ�.
							//�̸� ���� ���α׷��� ������ �ð����� �����Ѵ�.
	__int64 mPausedTime;	//TotalTime�� ���ϱ� ���� ����
							//mPausedTime�� Ÿ�̸Ӱ� �Ͻ�  ������ ���� ����ؼ� �����ȴ�.
	__int64 mStopTime;		//TotalTime�� ���ϱ� ���� ����
							//mStopTime�� Ÿ�̸Ӱ� �Ͻ������� ������ �ð�����, �Ͻ����� ���� �ð��� ����ϴµ� ���
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;
};

#endif //_GAME_TIMER_H_