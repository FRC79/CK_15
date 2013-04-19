#ifndef SHOOTERWHEEL_H
#define SHOOTERWHEEL_H

#include "Commands/Subsystem.h"
#include "CANJaguar.h"
#include "../Controllers/PIDSources/CANJagQuadEncoder.h"
#include "../RobotMap.h"

class ShooterWheel : public Subsystem
{
public:
	ShooterWheel();
	~ShooterWheel();
	
	void Set(float power);
	void Stop();
	
	CANJaguar* GetLeftWheel();
	CANJaguar* GetRightWheel();
	CANJagQuadEncoder* GetCANJagQuadEncoder();
	
	void InitDefaultCommand();
	
private:
	CANJaguar *leftWheel, *rightWheel;
	CANJagQuadEncoder* leftWheelEncoder;
};

#endif
