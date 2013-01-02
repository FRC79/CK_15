#ifndef BALLCONVEYOR_H_
#define BALLCONVEYOR_H_
#include <WPILib.h>
#include <CANJaguar.h>
#include <DigitalInput.h>
#include "RobotConfiguration.h"

class BallConveyor
{
	private: 
		CANJaguar *lowerRollers;
		CANJaguar *upperRollers;
		DigitalInput *lowerSensor;
		DigitalInput *upperSensor;
		UINT8 ballCount, prevBallCount;
		bool prevLowerState, prevUpperState, isReversed;
	public:
		BallConveyor();
		void setBallCount(UINT8 newBallCount);
		UINT8 getBallCount();
		void Initialize();
		void enableLowerRollers();
		void enableUpperRollers();
		void enableRollers();
		void disableLowerRollers();
		void disableUpperRollers();
		void disableRollers();
		void reverseRollers();
		void grabBall();
		void processBallStates();
};
#endif
