#include "WPILib.h"
#include "CANJaguar.h"
//#include "Intake.h"
#include "BallConveyor.h"
#include "Timer.h"
#include "CAN_VPID_Controller.h"
#include "CSVReader.h"

class CK15_Auton
{
	
	CANJaguar *frontLeft, *rearLeft, *rearRight, *frontRight, *m_shooterAzimuth ;
	CAN_VPID_Controller *shooter;
	CSVReader *config;
	//Intake *controllerIntake;
	BallConveyor *loadShooter;
public:
	CK15_Auton(CANJaguar *frontL,CANJaguar *rearL,CANJaguar *frontR, CANJaguar *rearR,BallConveyor *ballconveyor, CANJaguar *shooterAzimuth, CAN_VPID_Controller *m_shooter, CSVReader *m_csv);
	void initialize();
	void step(int stepNum);
	void CK15_Auton::autonStartClock();
		
};
