#pragma once

#include <frc/Compressor.h>
#include <frc/DoubleSolenoid.h>
#include <ctre/Phoenix.h>
#include <AHRS.h>
#include <CORERobotLib.h>
#include <COREFramework/COREScheduler.h>
#include <COREUtilities/CORETimer.h>
#include "Config.h"
#include <networktables/NetworkTableInstance.h>

using namespace CORE;
using namespace frc;

enum class DriveSide{LEFT = 1, RIGHT = 2, BOTH = 3};

class DriveSubsystem : public CORESubsystem {
public:
	DriveSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void teleopEnd() override;
	
	double getRobotPosition();
	void initTalons();
	void setMotorSpeed(double speedInFraction, DriveSide whichSide);
	void setMotorSpeed(double leftPercent, double rightPercent);
	void toggleGear();
	void visionTracking();
	COREVector path;
	COREConstant<double> drivingSpeed;
	AHRS ahrs;

private:
    TalonFX m_leftMaster, m_rightMaster, m_leftSlave, m_rightSlave;
    COREConstant<double> m_etherAValue, m_etherBValue, m_etherQuickTurnValue, m_ticksPerInch;
    DoubleSolenoid m_leftDriveShifter, m_rightDriveShifter;
    bool m_highGear;
    nt::NetworkTableInstance ntinst;
    Compressor m_compressor;
	double m_requestedHeading, m_currentHeading, m_turnAmount;

};
