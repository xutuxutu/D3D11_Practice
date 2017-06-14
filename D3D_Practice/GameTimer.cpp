#include "GameTimer.h"
#include <Windows.h>



GameTimer::GameTimer() : mSecondPerCount(0), mDeltaTime(-1.0), mBaseTime(0), mPauseTime(0), mPrevTime(0), mCurrTime(0), mStopped(false)
{
	__int64 countsPerSec;
	//���� Ÿ�̸��� ���ļ�(�ʴ� ����) ȹ��
	//�ʴ� �� ���� ī��Ʈ�� �ϴ��� -> �ý��� ���ý� ���� ��
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&countsPerSec));
	//1 ī��Ʈ�� ��ŭ�� �и��ʰ� �ɸ������� ���. (1�� / ���� Ÿ�̸��� ���ļ�)
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

	//���α׷��� �������ִ� ���
	if (mStopped)
	{
		//������ �ð� - ������ ������ �ð��� �Ͻ����� �ð��� ����.
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
	//���� �����ӿ��� ���� �����ӱ����� �ɸ� �ð�.
	mDeltaTime = (mCurrTime - mPrevTime) * mSecondPerCount;
	mPrevTime = mCurrTime;

	if (mDeltaTime < 0.0)
		mDeltaTime = 0.0;
}