#ifndef SPINSHOOTERWHEELPID_H
#define SPINSHOOTERWHEELPID_H

#include "../CommandBase.h"
#include "PIDController.h"
#include "../RobotMap.h"

/* Spins shooter wheel using PID controller to correct for
 * and smooth out error (we're not at the target speed, so we
 * compensate by going faster or slower). */

class SpinShooterWheelPID : public CommandBase 
{
public:
	SpinShooterWheelPID();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	PIDController* control;
};

#endif
