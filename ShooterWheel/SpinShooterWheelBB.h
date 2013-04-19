#ifndef SPINSHOOTERWHEELBB_H
#define SPINSHOOTERWHEELBB_H

#include "../CommandBase.h"
#include "../Controllers/BangBang_Controller.h"
#include "../RobotMap.h"

/* Spin shooter wheel under BangBang control(on/off oscillation)
 * depending on what speed the wheels are spinning. */

class SpinShooterWheelBB : public CommandBase 
{
public:
	SpinShooterWheelBB();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	BangBang_Controller* control;
};

#endif
