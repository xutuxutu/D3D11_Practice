#include "GameTimer.h"
#include <Windows.h>



GameTimer::GameTimer() : mSecondPerCount(0), mDeltaTime(-1.0), mBaseTime(0), mPauseTime(0), mPrevTime(0), mCurrTime(0), mStopped(false)
{
	__int64 countsPerSec;
	//성능 타이머의 주파수(초당 개수) 획득
	//초당 몇 개의 카운트를 하느냐 -> 시스템 부팅시 결정 됨
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&countsPerSec));
	//1 카운트당 얼만큼의 밀리초가 걸리는지를 계산. (1초 / 성능 타이머의 주파수)
	mSecondPerCount = 1.0 / static_cast<double>(countsPerSec);
}

GameTimer::~GameTimer()
{
}

float GameTimer::TotalTime() const
{
	if (mStopped)
	{
		return static_cast<float>(((mStopTime - mPauseTime) - mBaseTime) * mSecondPerCount);
	}
	else
	{
		return static_cast<float>(((mCurrTime - mPauseTime) - mBaseTime) * mSecondPerCount);
	}
}

float GameTimer::DeltaTime() const
{
	return static_cast<float>(mDeltaTime);
}

void GameTimer::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime));

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;
}

void GameTimer::Start()
{
	__int64 startTime;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&startTime));

	//프로그램이 정지해있는 경우
	if (mStopped)
	{
		//시작한 시간 - 정지를 시작한 시간을 일시정지 시간에 더함.
		mPauseTime += (startTime - mStopTime);

		mPrevTime = startTime;
		mStopTime = 0;
		mStopped = false;
	}
}

void GameTimer::Stop()
{
	if (!mStopped)
	{
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&mStopTime));
		mStopped = true;
	}
}

void GameTimer::Tick()
{
	if (mStopped)
	{
		mDeltaTime = 0;
		return;
	}

	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&mCurrTime));
	//이전 프레임에서 현재 프레임까지의 걸린 시간.
	mDeltaTime = (mCurrTime - mPrevTime) * mSecondPerCount;
	mPrevTime = mCurrTime;

	if (mDeltaTime < 0.0)
		mDeltaTime = 0.0;
}