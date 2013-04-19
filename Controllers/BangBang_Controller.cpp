#include "BangBang_Controller.h"

void BangBang_Controller::Calculate()
{	
	if(!enable)
	{
		return;
	}

	//If speed is < desired speed, then output = 1.0
	//If speed is anything else, output = 0.0 (STOP)
	if(fabs(motor->GetSpeed()) >= targetSpeed){
		motor->Set(0.0);
	} else {
		motor->Set(reverse?-1.0:1.0);
	}
}

/**
 * Call the Calculate method as a non-static method. This avoids having to prepend
 * all local variables in that method with the class pointer. This way the "this"
 * pointer will be set up and class variables can be called more easily.
 * This method is static and called by the Notifier class.
 * @param controller the address of the Bang Bang controller object to use in the background loop
 */
void BangBang_Controller::CallCalculate(void *controller)
{
	BangBang_Controller *control = (BangBang_Controller*) controller;
	control->Calculate();
}

BangBang_Controller::BangBang_Controller(CANJaguar *referenceMotor, float period)
{
//	m_controlLoop = new Notifier(BangBang_Controller::CallCalculate, this);
	
	motor = referenceMotor;
	enable = false;
	reverse = false;
	targetSpeed = 0.0;
	m_period = period;
	
//	m_controlLoop->StartPeriodic(m_period);
}

void BangBang_Controller::SetSetpoint(float controlVelocity)
{
	targetSpeed = fabs(controlVelocity);
}

float BangBang_Controller::Get()
{
	return motor->GetSpeed();
}

void BangBang_Controller::Enable()
{
	enable = true;
}

void BangBang_Controller::Disable()
{
	enable = false;
}
void BangBang_Controller::Reverse()
{
	reverse = true;
}

