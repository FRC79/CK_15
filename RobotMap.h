#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "CANJaguar.h"
#include "Controllers/PIDSources/CANJagQuadEncoder.h"

#define TICS_PER_REV 250
#define SHOOTER_POWER (-0.60)
#define SHOOTER_RPMS (900.0)

class RobotMap
{
public:
	static CANJaguar* shooterLeftWheel;
	static CANJaguar* shooterRightWheel;
	static CANJagQuadEncoder* shooterLeftWheelEncoder;
	
	static void init();
};

#endif
