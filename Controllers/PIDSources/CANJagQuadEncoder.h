#ifndef CANJAGQUADENCODER_H
#define CANJAGQUADENCODER_H

#include "CANJaguar.h"
#include "PIDSource.h"
#include "LiveWindow/LiveWindowSendable.h"
#include "tables/ITable.h"

class CANJagQuadEncoder : public PIDSource, public LiveWindowSendable
{
public:
	typedef enum {kSpeed, kPosition}ControlMode;
	
	CANJagQuadEncoder(CANJaguar *referenceJag, 
			ControlMode controlType, int ticsPerRev);

	void InitEncoder();
	
	double GetSpeed();
	double GetPosition();
	
	double PIDGet();
	
	void InitTable(ITable* subtable);
	ITable* GetTable();
	std::string GetSmartDashboardType();
	
	void UpdateTable();
	void StartLiveWindowMode();
	void StopLiveWindowMode();
	
private:
	CANJaguar* jaguar;
	ControlMode controlMode;
	int ticsPerRev;
	ITable *m_table;
};

#endif
