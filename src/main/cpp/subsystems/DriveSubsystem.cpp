// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/DriveSubsystem.h"

DriveSubsystem::DriveSubsystem() :
		ahrs(SerialPort::Port::kUSB1),
        m_driveShifter(DRIVE_SHIFTER_PCM,PneumaticsModuleType::CTREPCM,DRIVE_SHIFTER_LOW_GEAR_PORT,DRIVE_SHIFTER_HIGH_GEAR_PORT),
        m_compressor(COMPRESSOR_PCM,PneumaticsModuleType::CTREPCM),
		m_odometry(ahrs.GetRotation2d()),
		m_leftMaster(LEFT_FRONT_PORT),
		m_rightMaster(RIGHT_FRONT_PORT),
		m_leftSlave(LEFT_BACK_PORT),
		m_rightSlave(RIGHT_BACK_PORT)
   {
  // Implementation of subsystem constructor goes here.
  initTalons();
  m_compressor.EnableDigital();
  m_rightMotors.SetInverted(true);

  m_rightMaster.SetInverted(true);
  m_rightSlave.SetInverted(true);

  ResetEncoders();

  m_highGear = false;
	cout << "INFO: Starting Heading: " << ahrs.GetFusedHeading() << "\n";
}

void DriveSubsystem::Periodic() {
  // Implementation of subsystem periodic method goes here.
  
  m_odometry.Update(ahrs.GetRotation2d(),units::meter_t(nativeUnitsToDistanceMeters(m_leftMaster.GetSelectedSensorPosition(0))),units::meter_t(nativeUnitsToDistanceMeters(m_rightMaster.GetSelectedSensorPosition(0))));
}

void DriveSubsystem::etherDrive(double fwd, double rot){
	// cout << "INFO: Rot: " << rot << "\n";
	
	VelocityPair speeds = EtherDrive::Calculate(fwd, rot, true, .1);
	setMotorSpeed(speeds.left, speeds.right);
}

void DriveSubsystem::setMotorSpeed(double speedInFraction, DriveSide whichSide) {
	// Sets motor speed based on drive side and desired speed
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::RIGHT) {
		m_rightMaster.Set(ControlMode::PercentOutput, speedInFraction*.75);
		m_rightSlave.Set(ControlMode::PercentOutput, speedInFraction*.75);
	}
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::LEFT) {
		m_leftMaster.Set(ControlMode::PercentOutput, speedInFraction*.75);
		m_leftSlave.Set(ControlMode::PercentOutput, speedInFraction*.75);
	}
	m_drive.Feed();
}

void DriveSubsystem::setMotorSpeed(double leftPercent, double rightPercent) {
	// Sets speed based on percent output desired

	setMotorSpeed(leftPercent, DriveSide::LEFT);
	setMotorSpeed(rightPercent, DriveSide::RIGHT);
	// m_drive.Feed();
}

void DriveSubsystem::TankDriveVolts(units::volt_t left, units::volt_t right) {
	
	cout << "INFO: Left Voltage: " << left.value() << "\n";
	cout << "INFO: Right Voltage: " << right.value() << "\n";
	cout << "INFO: Left Distance: " << nativeUnitsToDistanceMeters(m_leftMaster.GetSelectedSensorPosition(0)) << "\n";
	cout << "INFO: Turn Rate: " << ahrs.GetRate() << "\n";
	cout << "INFO: Heading: " << ahrs.GetFusedHeading() << "\n";

	m_leftMaster.SetVoltage(left);
	m_leftSlave.SetVoltage(left);

	m_rightMaster.SetVoltage(right);
	m_rightSlave.SetVoltage(right);

    m_drive.Feed();
}

double DriveSubsystem::getRobotPosition(){
	return m_leftMaster.GetSelectedSensorPosition();
}

void DriveSubsystem::SetMaxOutput(double maxOutput) {
    m_drive.SetMaxOutput(maxOutput);
}

double DriveSubsystem::GetAverageEncoderDistance() {
	return ((m_leftMaster.GetSelectedSensorPosition(0) + m_rightMaster.GetSelectedSensorPosition(0)) / 2.0);
}

frc::Pose2d DriveSubsystem::GetPose() {
	return m_odometry.GetPose();
}

double DriveSubsystem::GetTurnRate() {
	return ahrs.GetRate();
}

void DriveSubsystem::SimulationPeriodic() {
  // Implementation of subsystem simulation periodic method goes here.
}


void DriveSubsystem::initTalons() {
	// Sets up talons
	m_leftMaster.Set(ControlMode::PercentOutput, 0);
	m_leftSlave.Set(ControlMode::PercentOutput, 0);
	m_rightMaster.Set(ControlMode::PercentOutput, 0);
	m_rightSlave.Set(ControlMode::PercentOutput, 0);

	// Encoder Functions
    m_leftSlave.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
    m_rightMaster.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);

    m_leftSlave.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::IntegratedSensor, 0, 0);
    m_rightMaster.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::IntegratedSensor, 0, 0);

	m_leftSlave.SetSensorPhase(false);
    m_rightMaster.SetSensorPhase(false);

}


void DriveSubsystem::ResetEncoders() {
    m_leftSlave.SetSelectedSensorPosition(0,0,50);
    m_rightMaster.SetSelectedSensorPosition(0,0,50);
}
frc::DifferentialDriveWheelSpeeds DriveSubsystem::GetWheelSpeeds() {
	return {units::meters_per_second_t(nativeUnitsToDistanceMeters(m_leftMaster.GetSelectedSensorPosition(0))),
			units::meters_per_second_t(nativeUnitsToDistanceMeters(m_rightMaster.GetSelectedSensorPosition(0)))};
}

void DriveSubsystem::ResetOdometry(frc::Pose2d pose) {
    ResetEncoders();
    m_odometry.ResetPosition(pose, ahrs.GetRotation2d());
}

void DriveSubsystem::toggleGear() {
	// Shifts from high gear to low gear or vice versa
	if (m_highGear) {
		m_driveShifter.Set(DoubleSolenoid::Value::kForward);
		m_highGear = false;
	} else {
		m_driveShifter.Set(DoubleSolenoid::Value::kReverse);
		m_highGear = true;
	}

}

units::degree_t DriveSubsystem::GetHeading() const {
  return ahrs.GetRotation2d().Degrees();
}

double DriveSubsystem::nativeUnitsToDistanceMeters(double sensorCounts){
    double motorRotations = (double)sensorCounts / DriveConstants::kEncoderCPR;
    double wheelRotations = motorRotations / DriveConstants::kGearReduction;
    double positionMeters = wheelRotations * (2 * wpi::numbers::pi * (DriveConstants::kWheelDiameterInches/39.37));
    return positionMeters;
  }
