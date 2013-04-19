#include "SpinShooterWheel.h"

SpinShooterWheel::SpinShooterWheel()
{
	SpinShooterWheel(false);
}

SpinShooterWheel::SpinShooterWheel(bool runContinuously) : CommandBase("SpinShooterWheel")
{
	Requires(shooterWheel);
	runsForever = runContinuously;
}

// Called just before this Command runs the first time
void SpinShooterWheel::Initialize()
{
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void SpinShooterWheel::Execute()
{
	// Run this infinitely so that something else has to stop it.
	shooterWheel->Set(SHOOTER_POWER);
	
	if(!runsForever){
		isFinished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool SpinShooterWheel::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void SpinShooterWheel::End()
{
	printf("SpinShooterWheel End()\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpinShooterWheel::Interrupted()
{
	printf("SpinShooterWheel Interrupted()\n");
}
