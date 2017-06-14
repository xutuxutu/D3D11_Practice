#pragma once
class GameTimer
{
private:
	double mSecondPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mPauseTime;				//���� ���α׷��� ������ �� �ð�.
	__int64 mStopTime;				//���� ���α׷��� ������ �ð�.
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;					//���� ���α׷��� ���� ����
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

