#include "SpinShooterWheelBB.h"

SpinShooterWheelBB::SpinShooterWheelBB() : CommandBase("SpinShooterWheelBB")
{
	Requires(shooterWheel);
	control = new BangBang_Controller(shooterWheel->GetLeftWheel()); // Init new BB controller for shooter wheel
	control->Reverse(); // We need to change the direction
}

// Called just before this Command runs the first time
void SpinShooterWheelBB::Initialize()
{
	control->SetSetpoint(SHOOTER_RPMS - 100.0); // Set the target speed
	control->Enable(); // Enable the controller
	printf("BangBang inited\n");
}

// Called repeatedly when this Command is scheduled to run
void SpinShooterWheelBB::Execute()
{
	// Run this infinitely so that something else has to stop it.
	control->Calculate();
	shooterWheel->GetRightWheel()->Set(shooterWheel->GetLeftWheel()->Get()); // Set right motor to left motor output
}

// Make this return true when this Command no longer needs to run execute()
bool SpinShooterWheelBB::IsFinished()
{
	return false; // This must be stopped by an outside force.
}

// Called once after isFinished returns true
void SpinShooterWheelBB::End()
{
	control->Disable(); // Disable the controller
	printf("SpinShooterWheelBB End()\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpinShooterWheelBB::Interrupted()
{
	control->Disable(); // Disable the controller
	printf("SpinShooterWheelBB Interrupted()\n");
}
