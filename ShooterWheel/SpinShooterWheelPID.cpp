#include "SpinShooterWheelPID.h"

SpinShooterWheelPID::SpinShooterWheelPID() : CommandBase("SpinShooterWheelPID")
{
	Requires(shooterWheel);
	control = new PIDController(1.0, 0.0, 0.0, 
			shooterWheel->GetCANJagQuadEncoder(), 
			shooterWheel->GetLeftWheel()); // Init new PID to control shooter wheel speed
}

// Called just before this Command runs the first time
void SpinShooterWheelPID::Initialize()
{
	control->SetSetpoint(SHOOTER_RPMS * -1.0); // We want to reverse it.
	control->Enable();
}

// Called repeatedly when this Command is scheduled to run
void SpinShooterWheelPID::Execute()
{
	// The PIDController runs in the background.
	shooterWheel->GetRightWheel()->Set(shooterWheel->GetLeftWheel()->Get()); // Set right wheel to left motor out
}

// Make this return true when this Command no longer needs to run execute()
bool SpinShooterWheelPID::IsFinished()
{
	return false; // This command must be canceled by an outside force.
}

// Called once after isFinished returns true
void SpinShooterWheelPID::End()
{
	// Disable and reset the PID loop.
	control->Reset();
	printf("SpinShooterWheelPID End()\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpinShooterWheelPID::Interrupted()
{
	// Disable and reset the PID loop.
	control->Reset();
	printf("SpinShooterWheelPID Interrupted()\n");
}
