#include "DriveSubsystem.h"

DriveSubsystem::DriveSubsystem() :
		ahrs(SerialPort::kUSB1),
		m_leftMaster(LEFT_FRONT_PORT),
		m_rightMaster(RIGHT_FRONT_PORT),
		m_leftSlave(LEFT_BACK_PORT),
		m_rightSlave(RIGHT_BACK_PORT),
		m_etherAValue("Ether A Value", .6),
        m_etherBValue("Ether B Value", .4),
		m_etherQuickTurnValue("Ether Quick Turn Value", 1.0),
        m_ticksPerInch("Ticks Per Inch", (4 * 3.1415) / 1024),
        m_leftDriveShifter(frc::PneumaticsModuleType::REVPH, LEFT_DRIVE_SHIFTER_HIGH_GEAR_PORT, LEFT_DRIVE_SHIFTER_LOW_GEAR_PORT),
        m_rightDriveShifter(frc::PneumaticsModuleType::REVPH, RIGHT_DRIVE_SHIFTER_HIGH_GEAR_PORT, RIGHT_DRIVE_SHIFTER_LOW_GEAR_PORT),
		m_compressor(frc::PneumaticsModuleType::REVPH),
		drivingSpeed("Vision Driving Speed", 0.2) {
}

void DriveSubsystem::robotInit() {
	// Registers joystick axis and buttons, does inital setup for talons
	driverJoystick->RegisterAxis(CORE::COREJoystick::LEFT_STICK_Y);
	driverJoystick->RegisterAxis(CORE::COREJoystick::RIGHT_STICK_X);
	driverJoystick->RegisterButton(CORE::COREJoystick::RIGHT_TRIGGER);
	driverJoystick->RegisterButton(CORE::COREJoystick::A_BUTTON);
	
    ntinst = nt::NetworkTableInstance::GetDefault();
    ntinst.StartClientTeam(2062);
    initTalons();
}

void DriveSubsystem::teleopInit() {
	// Sets ether drive values, inits talons
	COREEtherDrive::SetAB(m_etherAValue.Get(), m_etherBValue.Get());
	COREEtherDrive::SetQuickturn(m_etherQuickTurnValue.Get());
	initTalons();
	m_compressor.EnableDigital();
	SmartDashboard::PutString("Drive Controls", " Forward/Back: Left Stick \n Right/Left: Right Stick \n Shift: Right Trigger");
}

void DriveSubsystem::teleop() {
	// Code for teleop. Sets motor speed based on the values for the joystick, runs compressor,
	// toggles gears
    double mag = -driverJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_Y);
	double rot = driverJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::RIGHT_STICK_X);

	VelocityPair speeds = COREEtherDrive::Calculate(mag, rot, .1);
	setMotorSpeed(speeds.left, speeds.right);
	SmartDashboard::PutNumber("Left side speed", speeds.left);
	SmartDashboard::PutNumber("Right side speed", speeds.right);
	SmartDashboard::PutNumber("Left side encoder", m_leftMaster.GetSelectedSensorPosition(0));
	SmartDashboard::PutNumber("Right side encoder", m_rightMaster.GetSelectedSensorPosition(0));

	if(driverJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::RIGHT_TRIGGER)) {
		toggleGear();
	}
	if (driverJoystick->GetButton(CORE::COREJoystick::JoystickButton::A_BUTTON)){
		visionTracking();
	}
}

void DriveSubsystem::setMotorSpeed(double speedInFraction, DriveSide whichSide) {
	// Sets motor speed based on drive side and desired speed
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::RIGHT) {
		m_rightMaster.Set(ControlMode::PercentOutput, speedInFraction);
		m_rightSlave.Set(ControlMode::PercentOutput, speedInFraction);
	}
	if (whichSide == DriveSide::BOTH || whichSide == DriveSide::LEFT) {
		m_leftMaster.Set(ControlMode::PercentOutput, speedInFraction);
		m_leftSlave.Set(ControlMode::PercentOutput, speedInFraction);
	}
}

void DriveSubsystem::setMotorSpeed(double leftPercent, double rightPercent) {
	// Sets speed based on percent output desired
	setMotorSpeed(leftPercent, DriveSide::LEFT);
	setMotorSpeed(rightPercent, DriveSide::RIGHT);
}

double DriveSubsystem::getRobotPosition(){
	return m_leftMaster.GetSelectedSensorPosition();
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

	// Motor Inversion
	m_leftMaster.SetInverted(false);
	m_leftSlave.SetInverted(false);
	m_rightMaster.SetInverted(true);
	m_rightSlave.SetInverted(true);
}

void DriveSubsystem::teleopEnd() {
	m_compressor.Disable();
}

void DriveSubsystem::toggleGear() {
	// Shifts from high gear to low gear or vice versa
	if (m_highGear) {
		m_leftDriveShifter.Set(DoubleSolenoid::Value::kForward);
		m_rightDriveShifter.Set(DoubleSolenoid::Value::kForward);
		m_highGear = false;
	} else {
		m_leftDriveShifter.Set(DoubleSolenoid::Value::kReverse);
		m_rightDriveShifter.Set(DoubleSolenoid::Value::kReverse);
		m_highGear = true;
	}
}
void DriveSubsystem::visionTracking() {
    auto table = ntinst.GetTable("limelight");
	m_turnAmount = table->GetNumber("tx", 0.0);
    bool hasCenterX = table->GetNumber("tv", 0.0) == 1;
	if (hasCenterX){
   		 m_currentHeading = ahrs.GetFusedHeading();
			m_requestedHeading = m_currentHeading + m_turnAmount; // Calculates the requested heading to turn to
            while (m_requestedHeading >= 360) { // If Requested heading is not in a possible range of movement, subtracts 360 to loop it back between 0-359
                m_requestedHeading -= 360;
            } 
            if(m_currentHeading < (m_requestedHeading-5) && (m_turnAmount > 0)){ // Deadband of 5°
                setMotorSpeed(0.1, DriveSide::LEFT);
                setMotorSpeed(-0.1, DriveSide::RIGHT);
			} else if (m_currentHeading > (m_requestedHeading+5) && (m_turnAmount < 0)){
				setMotorSpeed(0.1, DriveSide::LEFT);
                setMotorSpeed(-0.1, DriveSide::RIGHT);
			} else {
				setMotorSpeed(0.0, DriveSide::BOTH);
			}
	}
}