#ifndef STOPSHOOTERWHEEL_H
#define STOPSHOOTERWHEEL_H

#include "../CommandBase.h"

/* Description */

class StopShooterWheel : public CommandBase 
{
public:
	StopShooterWheel();
	StopShooterWheel(bool runContinuously);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool isFinished;
	bool runsForever;
};

#endif
