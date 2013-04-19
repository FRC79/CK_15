#include "CANJagQuadEncoder.h"

CANJagQuadEncoder::CANJagQuadEncoder(CANJaguar *referenceJag, 
		ControlMode controlType, int ticsPerRev)
{
	// Init components
	jaguar = referenceJag;
	controlMode = controlType;
	this->ticsPerRev = ticsPerRev;
	
	InitEncoder();
}

void CANJagQuadEncoder::InitEncoder()
{
	jaguar->ConfigEncoderCodesPerRev(ticsPerRev); // Config encoder tics per rev
	
	// Set speed or postiion reference
	switch(controlMode){
	case kPosition:
		jaguar->SetPositionReference(CANJaguar::kPosRef_QuadEncoder);
		break;
	case kSpeed:
		jaguar->SetSpeedReference(CANJaguar::kSpeedRef_QuadEncoder);
		break;
	default:
		break;
	}
}

double CANJagQuadEncoder::GetSpeed(){
	return jaguar->GetSpeed();
}

double CANJagQuadEncoder::GetPosition(){
	return jaguar->GetPosition();
}

double CANJagQuadEncoder::PIDGet(){
	switch(controlMode){
	case kPosition:
		return GetPosition();
	case kSpeed:
		return GetSpeed();
	default:
		return 0.0;
	}
}

void CANJagQuadEncoder::InitTable(ITable* subtable)
{
	// Init table to input table
	m_table = subtable;
	
	// Output what control mode is being used
	UpdateTable();
}

ITable* CANJagQuadEncoder::GetTable(){
	return m_table;
}

std::string CANJagQuadEncoder::GetSmartDashboardType(){
	return "CANJagQuadEncoder";
}

void CANJagQuadEncoder::UpdateTable(){
	if(m_table != NULL){
		switch(controlMode){
		case kPosition:
			m_table->PutString("Control", "Position");
			m_table->PutNumber("Value", GetPosition());
			break;
		case kSpeed:
			m_table->PutString("Control", "Speed");
			m_table->PutNumber("Value", GetSpeed());
			break;
		default:
			m_table->PutString("Control", "None");
			m_table->PutNumber("Value", 0.0);
		}
	}
}

void CANJagQuadEncoder::StartLiveWindowMode(){}

void CANJagQuadEncoder::StopLiveWindowMode(){}





















