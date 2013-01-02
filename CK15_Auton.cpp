#include "CK15_Auton.h"
#include "BallConveyor.h"	
#include "Timer.h"
	double startTime;
	CK15_Auton::	CK15_Auton(CANJaguar *frontL,CANJaguar *rearL,CANJaguar *frontR, CANJaguar *rearR,BallConveyor *ballconveyor, CANJaguar *shooterAzimuth, CAN_VPID_Controller *m_shooter, CSVReader *m_csv)
	{
		frontLeft = frontL;
		rearLeft = rearL;
		frontRight = frontR;
		rearRight = rearR;
		//controllerIntake = intake;
		loadShooter = ballconveyor;
		shooter = m_shooter;
		config = m_csv;
		m_shooterAzimuth = shooterAzimuth;
		
	}
	
	void CK15_Auton::initialize(){
		startTime = GetClock();
		config->ReloadValues();
		shooter->Enable();
		shooter->SetSetpoint(0.0);
		//m_shooterAzimuth->EnableControl();
		//m_shooterAzimuth->Set(m_shooterAzimuth->GetPosition());

	}
	
	void CK15_Auton::autonStartClock()
	{
		startTime = GetClock();
	}
	
	//Function is used to move forward and lower arm onto bridge
	void CK15_Auton::step(int stepNum){
		shooter->Enable();
		
		//Approx 40 steps = 1 second
		//Move robot at full power for three seconds
		//if(stepNum < 80){
		//Reset();//Must call timer
		double currentTime = GetClock()-startTime;
		
		if(config->GetValueWithDefault("auton_high",1.0)==1.0)
		{
			shooter->SetSetpoint(config->GetValueWithDefault("key_high", 5.5));
		}
		else
		{
			shooter->SetSetpoint(config->GetValueWithDefault("key_mid", 4.091));
		}
		//printf("Shooter Setpoint: %4.5f", shooter->GetSetpoint());

		if(currentTime>config->GetValue("auton_delay") && currentTime < config->GetValueWithDefault("end_shooting", 15.0)){
			loadShooter->enableRollers();
		}
		if(currentTime > config->GetValueWithDefault("end_shooting", 15.0))
		{
			loadShooter->disableRollers();
			shooter->SetSetpoint(0.0);
			printf("Stopping shooting...\r\n");
			//This is where we'd drive later
			//m_shooterAzimuth->Set(config->GetValueWithDefault("turret_center", 1.47604));
		}
	}
	
	
