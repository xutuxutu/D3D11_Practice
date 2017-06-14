#pragma once
class GameTimer
{
private:
	double mSecondPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mPauseTime;				//응용 프로그램이 정지한 총 시간.
	__int64 mStopTime;				//응용 프로그램이 정지한 시간.
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;					//응용 프로그램의 정지 여부
public:
	GameTimer();
	~GameTimer();

	float TotalTime() const;
	float DeltaTime() const;
	
	void Reset();
	void Start();
	void Stop();
	void Tick();
};

