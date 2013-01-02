#ifndef Include_RobotConfiguration_H
#define Include_RobotConfiguration_H
class RobotConfiguration
{
public:
	// CAN bus IDs for Jaguars
	static const UINT8 FR_CAN_ID = 2;
	static const UINT8 FL_CAN_ID = 5;
	static const UINT8 RR_CAN_ID = 3;
	static const UINT8 RL_CAN_ID = 4;
	static const UINT8 SHOOTER_WHEEL_L_ID = 6;
	static const UINT8 SHOOTER_WHEEL_R_ID = 7;
	static const UINT8 SHOOTER_ELEV_ID = 8;
	static const UINT8 SHOOTER_AZ_ID = 9;
	static const UINT8 LOWER_CONVEYOR_ID = 10;
	static const UINT8 UPPER_CONVEYOR_ID = 11;
	static const UINT8 BALL_COLLECTOR_ID = 12;
	
	// Joystick buttons for various functions
	static const UINT8 BTN_CONVEYOR_REVERSE = 8;
	static const UINT8 BTN_LOWER_CONVEYOR   = 7;
	static const UINT8 BTN_UPPER_CONVEYOR   = 6;
	static const UINT8 BTN_LOW_GEAR         = 6;
	static const UINT8 BTN_HIGH_GEAR        = 7;
	static const UINT8 BTN_COLLECTOR_DOWN   = 9;
	static const UINT8 BTN_COLLECTOR_MOTOR  = 9;
	// Cypress Board Controllers
	/* TODO make sure this information for shooter
	wheel speed is correct*/
	//static const UINT8 SHOOTER_WHEEL_SPEED = 3;
	// Digital I/O definitions -- Inputs
	static const UINT8 PRESSURE_SWITCH_CHANNEL = 1;
	
	// Digital I/O definitions -- Outputs
	
	
	// Relay output definitions
	static const UINT8 COMPRESSOR_RELAY_CHANNEL = 8;
	
	// Solenoid output definitions
	static const UINT8 SOLENOID_SHIFTER_HIGH = 8;
	static const UINT8 SOLENOID_SHIFTER_LOW  = 7;
	static const UINT8 SOLENOID_BALL_COLLECTOR_UP = 4;
	static const UINT8 SOLENOID_BALL_COLLECTOR_DOWN = 3;
	//Added stuff (motors that were not included
	//TODO may have to switch 13 and 14
	static const UINT8 LOWER_CONVEYOR_SWITCH = 13;
	static const UINT8 UPPER_CONVEYOR_SWITCH = 14;
	
};
#endif

