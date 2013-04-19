#include "StopShooterWheel.h"

StopShooterWheel::StopShooterWheel()
{
	StopShooterWheel(false);
}

StopShooterWheel::StopShooterWheel(bool runContinuously)
{
	Requires(shooterWheel);
	runsForever = runContinuously;
}

// Called just before this Command runs the first time
void StopShooterWheel::Initialize()
{
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void StopShooterWheel::Execute()
{
	shooterWheel->Stop();
	
	if(!runsForever){
		isFinished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool StopShooterWheel::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void StopShooterWheel::End()
{
	printf("StopShooterWheel End()\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopShooterWheel::Interrupted()
{
	printf("StopShooterWheel Interrupted()\n");
}
