#include "ShooterWheel.h"
#include "StopShooterWheel.h"

ShooterWheel::ShooterWheel() : Subsystem("ShooterWheel")
{
	leftWheel = RobotMap::shooterLeftWheel;
	rightWheel = RobotMap::shooterRightWheel;
	leftWheelEncoder = RobotMap::shooterLeftWheelEncoder;
}

void ShooterWheel::Set(float power){
	leftWheel->Set(power);
	rightWheel->Set(power);
}

void ShooterWheel::Stop(){
	Set(0.0);
}

CANJaguar* ShooterWheel::GetLeftWheel(){
	return leftWheel;
}

CANJaguar* ShooterWheel::GetRightWheel(){
	return rightWheel;
}

CANJagQuadEncoder* ShooterWheel::GetCANJagQuadEncoder(){
	return leftWheelEncoder;
}

ShooterWheel::~ShooterWheel()
{
	
}

void ShooterWheel::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new StopShooterWheel(true));
}
