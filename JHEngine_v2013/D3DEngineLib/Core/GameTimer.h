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

	float TotalTime() const;	//초단위, 응용 프로그램이 시작된 이후에 흐른시간(일시 정지된 시간은 제외)
	float DeltaTime() const;	//초단위
	DWORD CurrentTime() const;

	void Reset();	//메시지 루프 이전에 호출해야 함
	void Start();	//타이머 시작, 재개 시 호출해야 함
	void Stop();	//일시정지 시 호출해야 함
	void Tick();	//매 프레임마다 호출해야 함

private:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;		//TotalTime을 구하기 위한 변수 
							//mBaseTime은 Reset()이 호출될 때 현재 시간으로 초기화된다.
							//이를 응용 프로그램이 시작한 시간으로 생각한다.
	__int64 mPausedTime;	//TotalTime을 구하기 위한 변수
							//mPausedTime은 타이머가 일시  정지된 동안 계속해서 누적된다.
	__int64 mStopTime;		//TotalTime을 구하기 위한 변수
							//mStopTime은 타이머가 일시정지된 시점의 시간으로, 일시정지 누적 시간을 계산하는데 사용
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;
};

#endif //_GAME_TIMER_H_