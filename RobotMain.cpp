#include "WPILib.h"
#include "Commands/Command.h"
#include "CommandBase.h"

#include "ShooterWheel/SpinShooterWheel.h"
#include "ShooterWheel/SpinShooterWheelBB.h"
#include "ShooterWheel/SpinShooterWheelPID.h"

class CommandBasedRobot : public IterativeRobot {
private:
	LiveWindow *lw;
	
	virtual void RobotInit() {
		RobotMap::init();
		CommandBase::init();
		
		lw = LiveWindow::GetInstance();

		printf("RobotInit() completed.\n");
	}
	
	virtual void AutonomousInit() {
	}
	
	virtual void AutonomousPeriodic() {
	}
	
	virtual void TeleopInit() {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
	}
	
	virtual void TeleopPeriodic() {
		// So that we can look at the speed in a graph and the other way doesn't work.
				SmartDashboard::PutNumber("WheelSpeed", 
						CommandBase::shooterWheel->GetCANJagQuadEncoder()->GetSpeed());
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TestInit(){
		// Put Test Buttons
//		SmartDashboard::PutData(Scheduler::GetInstance());
//		SmartDashboard::PutData(CommandBase::shooterWheel);
//		SmartDashboard::PutData(new SpinShooterWheel(true));
		SmartDashboard::PutData(new SpinShooterWheelBB());
//		SmartDashboard::PutData(new SpinShooterWheelPID());
		printf("TestInit() done\n");
	}
	
	virtual void TestPeriodic() {
		lw->Run();
		
//		Scheduler::GetInstance()->Run();
	}
};

START_ROBOT_CLASS(CommandBasedRobot);

