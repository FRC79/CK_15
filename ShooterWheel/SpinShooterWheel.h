#ifndef SPINSHOOTERWHEEL_H
#define SPINSHOOTERWHEEL_H

#include "../CommandBase.h"
#include "../RobotMap.h"

/* Spin shooter wheel according to a voltage percentage. */

class SpinShooterWheel : public CommandBase 
{
public:
	SpinShooterWheel();
	SpinShooterWheel(bool runContinuously);
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
