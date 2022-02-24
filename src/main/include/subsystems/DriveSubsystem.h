// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/Compressor.h>
#include <frc/DoubleSolenoid.h>

// Pathfinder includes
#include <frc/Encoder.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/geometry/Pose2d.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc2/command/SubsystemBase.h>
#include <units/voltage.h>

#include "Constants.h"

#include "EtherDrive.h"
#include "Config.h"

#include <ctre/Phoenix.h>
#include <AHRS.h>

#include <frc2/command/SubsystemBase.h>

#include <iostream>

using namespace frc;
using namespace frc2;
using namespace std;

enum class DriveSide{LEFT = 1, RIGHT = 2, BOTH = 3};

class DriveSubsystem : public frc2::SubsystemBase {
 public:
    DriveSubsystem();

    /**
     * Will be called periodically whenever the CommandScheduler runs.
     */
    void Periodic() override;

    /**
     * Will be called periodically whenever the CommandScheduler runs during
     * simulation.
     */
    void SimulationPeriodic() override;

    double getRobotPosition();
	void initTalons();
	void etherDrive(double fwd, double rot);
	void setMotorSpeed(double speedInFraction, DriveSide whichSide);
	void setMotorSpeed(double leftPercent, double rightPercent);
	void toggleGear();

	void TankDriveVolts(units::volt_t left, units::volt_t right);

	double GetAverageEncoderDistance();
	frc::Encoder& GetRightEncoder();
	frc::Encoder& GetLeftEncoder();

	void SetMaxOutput(double maxOutput);
	units::degree_t GetHeading() const;

	double GetTurnRate();
	frc::Pose2d GetPose();

    frc::DifferentialDriveWheelSpeeds GetWheelSpeeds();

	void ResetEncoders();
	void ResetOdometry(frc::Pose2d pose);

    double nativeUnitsToDistanceMeters(double sensorCounts);

	// COREVector path;

	AHRS ahrs;

 private:
    // Components (e.g. motor controllers and sensors) should generally be
    // declared private and exposed only through public methods.
    // COREConstant<double> m_etherAValue, m_etherBValue, m_etherQuickTurnValue, m_ticksPerInch;
    DoubleSolenoid m_driveShifter;
    bool m_highGear;
    Compressor m_compressor;

	frc::DifferentialDriveOdometry m_odometry;

	WPI_TalonFX m_leftMaster, m_rightMaster, m_leftSlave, m_rightSlave;
	
    frc::MotorControllerGroup m_leftMotors{m_leftMaster,m_leftSlave};
    frc::MotorControllerGroup m_rightMotors{m_rightMaster,m_rightSlave};

    frc::DifferentialDrive m_drive{m_leftMotors,m_rightMotors};

};
