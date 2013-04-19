
#ifndef BANGBANG_CONTROLLER_H
#define BANGBANG_CONTROLLER_H

#include "CANJaguar.h"
#include "Base.h"
#include "semLib.h"
#include "Controller.h"
#include "LiveWindow/LiveWindow.h"
#include "Notifier.h"
#include "PIDOutput.h"
#include "Math.h"


class LiveWindowSendable ;
class Controller         ;
class ITableListener     ;


class BangBang_Controller
{
public:
	
    void Calculate();
    BangBang_Controller(CANJaguar *referenceMotor, float period=0.05);
    void SetSetpoint(float controlVelocity);
    float Get();
    void Enable();
    void Disable();
    void Reverse();
private:
    bool enable;
    bool reverse;
    float targetSpeed;
	CANJaguar *motor;
	float m_period;
	Notifier *m_controlLoop;
	
	static void CallCalculate(void *controller);
    DISALLOW_COPY_AND_ASSIGN(BangBang_Controller);
};
#endif
