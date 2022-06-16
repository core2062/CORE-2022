#pragma once

#include <frc/Compressor.h>
#include <frc/DoubleSolenoid.h>
#include <frc/AnalogInput.h>
#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/TalonFXSensorCollection.h>
#include <AHRS.h>
#include <CORERobotLib.h>
#include <COREControl/COREPID.h>
#include <COREFramework/COREScheduler.h>
#include <networktables/NetworkTableInstance.h>
#include <COREUtilities/CORETimer.h>
#include "Config.h"

using namespace CORE;
using namespace frc;

enum class DriveSide{LEFT = 1, RIGHT = 2, BOTH = 3};

class DriveSubsystem : public CORESubsystem {
public:
	DriveSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	
	double getRobotPosition();
	void initTalons();
	void setMotorSpeed(double speedInFraction, DriveSide whichSide);
	void setMotorSpeed(double leftPercent, double rightPercent);
	void toggleGear();
	void resetEncoder();
	void SetTalonMode(NeutralMode mode);
	double CalculateMotorFromVision();
	void visionMovement();
    nt::NetworkTableInstance ntinst;
	COREConstant<double> m_KP, m_KI, m_KD, m_KF;
	COREVector path;
    COREPID corePID;
	AHRS ahrs;

private:
	//m_analogSupplyVoltage used in calculation to get current PSI
	AnalogInput m_analogPressureInput, m_analogSupplyVoltage;
    bool m_highGear;
    TalonFX m_leftMaster, m_rightMaster, m_leftSlave, m_rightSlave;
 	double m_centerError;
    bool m_hasCenterX;
    COREConstant<double> m_etherAValue, m_etherBValue, m_etherQuickTurnValue, m_ticksPerInch, m_driveSpeedModifier;
    DoubleSolenoid m_driveShifter;
    Compressor m_compressor;
};
