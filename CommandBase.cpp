#include "CommandBase.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}

OI* CommandBase::oi = NULL;
ShooterWheel* CommandBase::shooterWheel = NULL;

void CommandBase::init() {
    // Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	
	oi = new OI();
	shooterWheel = new ShooterWheel();
}
