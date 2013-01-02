#include "WPILib.h"
#include "Joystick.h"
#include "CANJaguar.h"
#include "RobotConfiguration.h"
#include "DigitalInput.h"
#include "Relay.h"
#include "Solenoid.h"
#include "CAN_VPID_Controller.h"
#include "CK15_Auton.h"
#include "BallConveyor.h"
#include "Timer.h"
#include "CSVReader.h"
/**
 * Disabled Mode:
 * - Once per second, print (on the console) the number of seconds the robot has been disabled.
 *
 * Autonomous Mode:
 * - When enabled in autonomous mode, check the compressor
 *
 * Teleop Mode:
 * - Do stuff
 * 
 * This code assumes the following connections:
 * - Driver Station:
 *   - USB 1 - The "right" joystick.  Used for arcade drive
 *   - USB 3 - The "shooter" joystick. Used for shooter control
 */
class CK15_Main : public IterativeRobot
{
	// Declare variable for the robot drive system
	RobotDrive *m_robotDrive;
	
	// robot will use CAN bus for motor control
	CANJaguar *Front_R, *Front_L, *Rear_R, *Rear_L;
	CANJaguar *Lower_Conveyor, *Upper_Conveyor;
	CANJaguar *Shooter_Azimuth, *Shooter_Elev;
	CANJaguar *Shooter_Wheel_L, *Shooter_Wheel_R;
	CANJaguar *Ball_Collector;
	// Relay for compressor operation
	Relay *Compressor;
	
	// Digital Input pin for the pressure switch
	DigitalInput *Pressure_SW;
	
	// Solenoid for gear shifting
	Solenoid *High_Gear, *Low_Gear;
	Solenoid *Ball_Collector_Up, *Ball_Collector_Down;

	// Declare a variable to use to access the driver station object
	DriverStation *m_ds;						// driver station object
	UINT32 m_priorPacketNumber;					// keep track of the most recent packet number from the DS
	UINT8 m_dsPacketsReceivedInCurrentSecond;	// keep track of the ds packets received in the current second

	// Declare variables for the two joysticks being used
	Joystick *Drive_Stick;			// joystick 1 (arcade stick)
	Joystick *Shooter_Stick;        // joystick 3 (shooter controls)

	// Local variables to count the number of periodic loops performed
	UINT32 m_autoPeriodicLoops;
	UINT32 m_disabledPeriodicLoops;
	UINT32 m_telePeriodicLoops;
	
	// PID loop to control the shooter wheel
	CAN_VPID_Controller *Shooter_PID;
	
	
	CK15_Auton *auton;
	BallConveyor *ballConveyor;
	//CANJaguar *ShooterRight;
	//CANJaguar *ShooterLeft;

	CSVReader *m_config;

public:
/**
 * Constructor for this "CK15_Main" Class.
 *
 * The constructor creates all of the objects used for the different inputs and outputs of
 * the robot.  Essentially, the constructor defines the input/output mapping for the robot,
 * providing named objects for each of the robot interfaces.
 */
	CK15_Main(void)	{
		printf("CK15_Main Constructor Started\n");

		printf("Loading configuration file...");
		m_config = new CSVReader("RobotConfig.csv");
		
		// Initialize the Jaguars as using CAN bus
		Front_R = new CANJaguar(RobotConfiguration::FR_CAN_ID);
		Front_L = new CANJaguar(RobotConfiguration::FL_CAN_ID);
		Rear_R  = new CANJaguar(RobotConfiguration::RR_CAN_ID);
		Rear_L  = new CANJaguar(RobotConfiguration::RL_CAN_ID);
		// ball conveyor
		ballConveyor = new BallConveyor();
		Lower_Conveyor = new CANJaguar(RobotConfiguration::LOWER_CONVEYOR_ID);
		Upper_Conveyor = new CANJaguar(RobotConfiguration::UPPER_CONVEYOR_ID);
		
		Shooter_Azimuth = new CANJaguar(RobotConfiguration::SHOOTER_AZ_ID);//, CANJaguar::kPosition);
		//Shooter_Elev    = new CANJaguar(RobotConfiguration::SHOOTER_ELEV_ID);
		
		Shooter_Wheel_L = new CANJaguar(RobotConfiguration::SHOOTER_WHEEL_L_ID);
		Shooter_Wheel_R = new CANJaguar(RobotConfiguration::SHOOTER_WHEEL_R_ID);
		
		Ball_Collector = new CANJaguar(RobotConfiguration::BALL_COLLECTOR_ID);
		
		// Initialize pressure switch input channel
		Pressure_SW = new DigitalInput(RobotConfiguration::PRESSURE_SWITCH_CHANNEL);
		
		// Initialize compressor relay
		Compressor = new Relay(RobotConfiguration::COMPRESSOR_RELAY_CHANNEL);
		
		// Initialize shifter solenoid channel
		High_Gear = new Solenoid(RobotConfiguration::SOLENOID_SHIFTER_HIGH);
		Low_Gear  = new Solenoid(RobotConfiguration::SOLENOID_SHIFTER_LOW);
		
		Ball_Collector_Up   = new Solenoid(RobotConfiguration::SOLENOID_BALL_COLLECTOR_UP);
		Ball_Collector_Down = new Solenoid(RobotConfiguration::SOLENOID_BALL_COLLECTOR_DOWN);

		// Initialize the robot drive system using the Jaguars
		m_robotDrive = new RobotDrive(Front_L, Rear_L, Front_R, Rear_R);
		
		// Initialize the PID loop to control the shooter wheel speed
		Shooter_PID = new CAN_VPID_Controller(
				            m_config->GetValue("shooter_p"),	// P
				            m_config->GetValue("shooter_i"), 	// I
				            m_config->GetValue("shooter_d"),    // D                 
				            Shooter_Wheel_L,                   // Input Jag
				            Shooter_Wheel_L, Shooter_Wheel_R); // Output Jags

		// Acquire the Driver Station object
		m_ds = DriverStation::GetInstance();
		m_priorPacketNumber = 0;
		m_dsPacketsReceivedInCurrentSecond = 0;

		// Define joysticks being used at USB port #1 on the Drivers Station
		Drive_Stick = new Joystick(1);
		Shooter_Stick = new Joystick(3);

		// Initialize counters to record the number of loops completed in autonomous and teleop modes
		m_autoPeriodicLoops = 0;
		m_disabledPeriodicLoops = 0;
		m_telePeriodicLoops = 0;
		//
		auton = new CK15_Auton(Front_R,Front_L,Rear_R,Rear_L,ballConveyor,Shooter_Azimuth,Shooter_PID, m_config);
		
		printf("CK15_Main Constructor Completed -- Jess\n");
	}


	/********************************** Init Routines *************************************/

	void RobotInit(void) {
		// Actions which would be performed once (and only once) upon initialization of the
		// robot would be put here.		printf("Initializing drive wheel encoders...\n");

		// Set each front drive motor to have a quadrature encoder attached
		Front_R->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
		Front_L->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);

		// Set the encoders to 360 counts per revolution
		Front_R->ConfigEncoderCodesPerRev(360);
		Front_L->ConfigEncoderCodesPerRev(360);
		
		// Set the shooter azimuth and elevation to use potentiometers
		// as a position reference
		Shooter_Azimuth->SetPositionReference(CANJaguar::kPosRef_Potentiometer);
		//Shooter_Elev->SetPositionReference(CANJaguar::kPosRef_Potentiometer);
		
		// Set the number of turns for the potentiometers
		Shooter_Azimuth->ConfigPotentiometerTurns(10);
		//Shooter_Elev->ConfigPotentiometerTurns(10);
		//Shooter_Azimuth->SetPID(1.0,0.5,0.0);
		
		// Set the shooter wheel left motor to have a quadrature encoder
		Shooter_Wheel_L->SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
		Shooter_Wheel_L->ConfigEncoderCodesPerRev(360);
		
		Shooter_PID->SetOutputRange(0.0, 1.0);
		
		// Set to low gear
		SetHighGear();
		
		// Raise the ball collector
		CollectorUp();

		printf("RobotInit() completed.\n");
	}

	void DisabledInit(void) {
		m_disabledPeriodicLoops = 0;			// Reset the loop counter for disabled mode
		// Move the cursor down a few, since we'll move it back up in periodic.
		printf("\x1b[2B");
	}

	void AutonomousInit(void) {
		m_autoPeriodicLoops = 0;				// Reset the loop counter for autonomous mode
		auton->initialize();
	}

	void TeleopInit(void) {
		m_telePeriodicLoops = 0;				// Reset the loop counter for teleop mode
		m_dsPacketsReceivedInCurrentSecond = 0;	// Reset the number of dsPackets in current second
		// If we are in debug mode we want to reload these values every time we enable
		// Otherwise we don't reload them. The default is to hopefully load some numbers in when 
		// we didn't get data.
		if((int)m_config->GetValueWithDefault("Debug_Mode",1.0))
		{
			m_config->ReloadValues(); // Refreshes the config values
		}
		Shooter_Azimuth->ChangeControlMode(CANJaguar::kPercentVbus);
		
		Shooter_PID->Enable();
		SetHighGear();
	}

	/********************************** Periodic Routines *************************************/

	void DisabledPeriodic(void)  {
		static INT32 printSec = (INT32)GetClock() + 1;
		static const INT32 startSec = (INT32)GetClock();


		// increment the number of disabled periodic loops completed
		m_disabledPeriodicLoops++;
		auton->autonStartClock();
		// while disabled, printout the duration of current disabled mode in seconds
		if (GetClock() > printSec) {
			// Move the cursor back to the previous line and clear it.
			printf("\x1b[1A\x1b[2K");
			printf("Disabled seconds: %d\r\n", printSec - startSec);
			printSec++;
		}
	}

	void AutonomousPeriodic(void) {

		m_autoPeriodicLoops++;
		//Reset();
		GetWatchdog().Feed();
		auton->step(m_autoPeriodicLoops);
		
		// Check the pressure switch and drive the compressor accordingly
		Compressor->Set((!Pressure_SW->Get() ? Relay::kForward : Relay::kOff));
	}


	void TeleopPeriodic(void) {

		// increment the number of teleop periodic loops completed
		m_telePeriodicLoops++;

		GetWatchdog().Feed();
		
		// Check the pressure switch and drive the compressor accordingly
	    Compressor->Set((!Pressure_SW->Get() ? Relay::kForward : Relay::kOff));

		/*
		 * Code placed in here will be called only when a new packet of information
		 * has been received by the Driver Station.  Any code which needs new information
		 * from the DS should go in here
		 */

		m_dsPacketsReceivedInCurrentSecond++;					// increment DS packets received

		// put Driver Station-dependent code here

		m_robotDrive->ArcadeDrive(Drive_Stick);			// drive with arcade style (use right stick)

		// Lower conveyor button
	    if (Shooter_Stick->GetRawButton(RobotConfiguration::BTN_LOWER_CONVEYOR)) {
			Lower_Conveyor->Set(m_config->GetValue("LConveyor_In"));
		} else if (Shooter_Stick->GetRawButton(RobotConfiguration::BTN_CONVEYOR_REVERSE)) {
			Lower_Conveyor->Set(m_config->GetValue("LConveyor_Out"));
		} else {
			Lower_Conveyor->Set(0.0);
		}
		
		// Upper conveyor button
		if (Shooter_Stick->GetRawButton(RobotConfiguration::BTN_UPPER_CONVEYOR)) {
			Upper_Conveyor->Set(m_config->GetValue("UConveyor_In"));
		} else if (Shooter_Stick->GetRawButton(RobotConfiguration::BTN_CONVEYOR_REVERSE)) {
			Upper_Conveyor->Set(m_config->GetValue("UConveyor_Out"));
		} else {
			Upper_Conveyor->Set(0.0);
		}
		
		// Gear changing buttons
		if (m_ds->GetDigitalIn(5)) {
			SetHighGear();
		} else {
			SetLowGear();
		}
		
		// Collector control (up or down)
		if (m_ds->GetEnhancedIO().GetDigital(10)) {
			CollectorDown();
		} else {
			CollectorUp();
		}
	
		// Collector motor control
		if (Shooter_Stick->GetRawButton(RobotConfiguration::BTN_COLLECTOR_MOTOR)) {
			Ball_Collector->Set(-1.0);
		} else {
			Ball_Collector->Set(0.0);
		}
		
		// Shooter controls
		Shooter_Azimuth->Set(Shooter_Stick->GetX());
		//Shooter_Elev->Set(Shooter_Stick->GetY() / 4);
	
		// Shooter wheel speed
		{
			//float pct = (-Shooter_Stick->GetThrottle() + 1.0) / 2;
			float pct = m_ds->GetAnalogIn((int)m_config->GetValueWithDefault("Range_Knob",3.0)) * m_config->GetValueWithDefault("Range_Scale",0.303);
			if (pct <  m_config->GetValueWithDefault("Range_Deadband",0.25) *  m_config->GetValueWithDefault("Range_Scale",0.303)) { pct = 0;}
			Shooter_PID->SetSetpoint( m_config->GetValueWithDefault("Speed_Scale",10.0)*pct);	
			//Shooter_Wheel_L->Set(pct);
			//Shooter_Wheel_R->Set(pct);
		}
		
		if(!m_ds->GetEnhancedIO().GetDigital((int)m_config->GetValue("Fender_Mid_Btn")))
		{
			Shooter_PID->SetSetpoint(m_config->GetValue("Fender_Mid"));
		}
		if(!m_ds->GetEnhancedIO().GetDigital((int)m_config->GetValue("Fender_High_Btn")))
		{
			Shooter_PID->SetSetpoint(m_config->GetValue("Fender_High"));
		} 
		if(!m_ds->GetEnhancedIO().GetDigital((int)m_config->GetValue("Key_Mid_Btn")))
		{
			Shooter_PID->SetSetpoint(m_config->GetValue("Key_Mid"));
		}
		if(!m_ds->GetEnhancedIO().GetDigital((int)m_config->GetValue("Key_High_Btn")))
		{
			Shooter_PID->SetSetpoint(m_config->GetValue("Key_High"));
		}



		printf("Turret Position: %4.5f", Shooter_Azimuth->GetPosition());
						/* //TODO set according to whatever knob is being used
		 * Shooter_Azimuth->Set();
		
		 */
	} // TeleopPeriodic(void)


/********************************** Miscellaneous Routines *************************************/

	void SetHighGear(void) {
		High_Gear->Set(true);
		Low_Gear->Set(false);
	}
	
	void SetLowGear(void) {
		High_Gear->Set(false);
		Low_Gear->Set(true);
	}
	
	void CollectorUp(void) {
		Ball_Collector_Up->Set(true);
		Ball_Collector_Down->Set(false);
	}
	
	void CollectorDown(void) {
		Ball_Collector_Up->Set(false);
		Ball_Collector_Down->Set(true);
	}

}; // end of class CK15_Main

START_ROBOT_CLASS(CK15_Main);
