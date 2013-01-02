#include "BallConveyor.h"

BallConveyor::BallConveyor()
{
	lowerRollers = new CANJaguar(RobotConfiguration::LOWER_CONVEYOR_ID);
	upperRollers = new CANJaguar(RobotConfiguration::UPPER_CONVEYOR_ID);
	lowerSensor = new DigitalInput(RobotConfiguration::LOWER_CONVEYOR_SWITCH);
	upperSensor = new DigitalInput(RobotConfiguration::UPPER_CONVEYOR_SWITCH);
}
void BallConveyor::setBallCount(UINT8 newBallCount)
{
	ballCount = newBallCount;
}
UINT8 BallConveyor::getBallCount()
{
	return ballCount;
}
void BallConveyor::Initialize()
{
	ballCount = prevBallCount = 0;
	isReversed = false;
	prevUpperState = prevLowerState = false;
}
void BallConveyor::enableLowerRollers()
{
	isReversed = false;
	lowerRollers->Set(1.0);
}
void BallConveyor::enableUpperRollers()
{
	isReversed = false;
	upperRollers->Set(1.0);
}

void BallConveyor::enableRollers()
{
	enableLowerRollers();
	enableUpperRollers();
}

void BallConveyor::disableLowerRollers()
{
	isReversed = false;
	lowerRollers->Set(0.0);
}

void BallConveyor::disableUpperRollers()
{
	isReversed = false;
	upperRollers->Set(0.0);
}

void BallConveyor::reverseRollers()
{
	upperRollers->Set(-1.0);
	lowerRollers->Set(-1.0);
	isReversed = true;
}

void BallConveyor::disableRollers()
{
	disableUpperRollers();
	disableLowerRollers();
}

void BallConveyor::grabBall()
{	
	//If we don't have a ball in the thing
	if(upperSensor->Get())
	{
		enableRollers();
	}
	else
	{	
		disableUpperRollers();
		enableLowerRollers();
	}
}

void BallConveyor::processBallStates()
{
	if(!isReversed){
	//(upperSensor->Get()!=prevUpperState)? prevUpperState == 1 ? ballCount-- : ballCount++ : 
		if(upperSensor->Get()!=prevUpperState)
		{
			prevUpperState == 1 ? ballCount-- : ballCount++;
		}
		if(lowerSensor->Get()!=prevLowerState)
		{
			prevLowerState == 0 ? ballCount++:ballCount;
		}
	}
	else
	{
		if(upperSensor->Get()!=prevUpperState)
		{
			prevUpperState == 1 ? ballCount++ : ballCount--;
		}
		if(lowerSensor->Get()!=prevLowerState)
		{
			prevLowerState == 0 ? ballCount--:ballCount;
		}
	}

	prevLowerState = lowerSensor->Get();
	prevUpperState = upperSensor->Get();

}
