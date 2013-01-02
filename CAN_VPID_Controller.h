
#ifndef CANVPIDCONTROLLER_H_
#define CANVPIDCONTROLLER_H_

#include "Base.h"
#include "semLib.h"

class PIDOutput;
class Notifier;
class CANJaguar;

/**
 * Class implements a PID Control Loop.
 * 
 * Creates a separate thread which reads the given PIDSource and takes
 * care of the integral calculations, as well as writing the given
 * PIDOutput
 */
class CAN_VPID_Controller
{
public:
	// TODO Modify to take the two references to PIDOutput
	CAN_VPID_Controller(float Kp, float Ki, float Kd,
					   CANJaguar *source, PIDOutput *output1,
					   PIDOutput *output2, bool InvertOutputs=false,
					   float period=0.05, float kF = 0.0);
	virtual ~CAN_VPID_Controller();
	virtual float Get();
	virtual void SetContinuous(bool continuous = true);
	virtual void SetInputRange(float minimumInput, float maximumInput);
	virtual void SetOutputRange(float mimimumOutput, float maximumOutput);
	virtual void SetPID(float p, float i, float d);
	virtual float GetP();
	virtual float GetI();
	virtual float GetD();
	
	virtual void SetSetpoint(float setpoint);
	virtual float GetSetpoint();

	virtual float GetError();
	
	virtual void SetTolerance(float percent);
	virtual bool OnTarget();
	
	virtual void Enable();
	virtual void Disable();
	virtual bool IsEnabled();
	
	virtual void Reset();

private:
	float m_P;			// factor for "proportional" control
	float m_I;			// factor for "integral" control
	float m_D;			// factor for "derivative" control
	float m_maximumOutput;	// |maximum output|
	float m_minimumOutput;	// |minimum output|
	float m_maximumInput;		// maximum input - limit setpoint to this
	float m_minimumInput;		// minimum input - limit setpoint to this
	bool m_continuous;	// do the endpoints wrap around? eg. Absolute encoder
	bool m_enabled; 			//is the pid controller enabled
	float m_prevError;	// the prior sensor input (used to compute velocity)
	double m_totalError; //the sum of the errors for use in the integral calc
	float m_tolerance;	//the percetage error that is considered on target
	float m_setpoint;
	float m_error;
	float m_result;
	float m_period;
	bool m_InvertOutputs;
	float m_prevPosition;
	float m_F; // Feed forward constant, defaults to 0
	float m_previousResult;
	
	SEM_ID m_semaphore;
	
	CANJaguar *m_pidInput;
	PIDOutput *m_pidOutput1;
	PIDOutput *m_pidOutput2;
	Notifier *m_controlLoop;

	static void CallCalculate(void *controller);
	void Calculate();
	DISALLOW_COPY_AND_ASSIGN(CAN_VPID_Controller);
};

#endif
