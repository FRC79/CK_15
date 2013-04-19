#include "RobotMap.h"

CANJaguar* RobotMap::shooterLeftWheel = NULL;
CANJaguar* RobotMap::shooterRightWheel = NULL;
CANJagQuadEncoder* RobotMap::shooterLeftWheelEncoder = NULL;

void RobotMap::init()
{
	shooterLeftWheel = new CANJaguar(6);
	shooterRightWheel = new CANJaguar(7);
	shooterLeftWheelEncoder = new CANJagQuadEncoder(shooterLeftWheel, 
			CANJagQuadEncoder::kSpeed, TICS_PER_REV);
	
}
