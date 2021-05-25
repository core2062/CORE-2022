#include "TurretSubsystem.h"

TurretSubsystem::TurretSubsystem(): m_turret(TURRET_PORT),
                                    m_KP("KP", 0.005),
                                    m_KI("KI", 0),
                                    m_KD("KD", 0),
                                    m_KF("KF", 1.5),
                                    m_turretSpeed("Turret Speed", 0.40),
                                    m_DistCoefA("DistCoefA", 0),
                                    m_DistCoefB("DistCoefB", 0),
                                    corePID(0, 0, 0, 0) {
}

void TurretSubsystem::robotInit() {
    m_startupTurretPosition = m_turret.GetSelectedSensorPosition(0);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::A_BUTTON);
    operatorJoystick->RegisterAxis(CORE::COREJoystick::LEFT_STICK_X);
    InitTalons();
    // start NetworkTables
    ntinst = nt::NetworkTableInstance::GetDefault();
    ntinst.StartClientTeam(2062);
    m_turret.SetNeutralMode(motorcontrol::NeutralMode::Brake);
}

void TurretSubsystem::teleopInit() {
}

void TurretSubsystem::teleop() {
    double manualInput = -operatorJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_X);
    bool aButtonPressed = operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::A_BUTTON);
    m_motorPercent = 0;
    bool atLeftStop = m_turret.GetSelectedSensorPosition(0) < (m_startupTurretPosition - 7000.0);
    bool atRightStop = m_turret.GetSelectedSensorPosition(0) > (m_startupTurretPosition + 7000.0);

    if (aButtonPressed) {
        m_motorPercent = VisionMove(atLeftStop, atRightStop);
    } else if ((!atRightStop && manualInput < 0) || (!atLeftStop && manualInput > 0)) {
         nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode",1);
         nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("camMode",1);
        // manual turret position
        double turretSpeed = m_turretSpeed.Get();
        m_motorPercent = turretSpeed * manualInput;
    }
    SetTurret(m_motorPercent);

    SmartDashboard::PutNumber("Distance from target", GetDistance());
    SmartDashboard::PutNumber("Turret position", m_turret.GetSelectedSensorPosition(0));
    SmartDashboard::PutBoolean("At Left Stop", atLeftStop);
    SmartDashboard::PutBoolean("At Right Stop", atRightStop);
    SmartDashboard::PutBoolean("A Button Pressed", operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::A_BUTTON));
}

double TurretSubsystem::turretPosition() {
    return m_turret.GetSelectedSensorPosition(0);
}

double TurretSubsystem::VisionMove(bool atLeftStop, bool atRightStop) {
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("ledMode",3);
    nt::NetworkTableInstance::GetDefault().GetTable("limelight")->PutNumber("camMode",0);
    return m_motorPercent = CalculateMotorFromVision(atLeftStop, atRightStop);
}

double TurretSubsystem::CalculateMotorFromVision(bool atLeftStop, bool atRightStop) {
    // auto turret position
    corePID.SetDerivativeConstant(m_KD.Get());
    corePID.SetFeedForwardConstant(m_KF.Get());
    corePID.SetIntegralConstant(m_KI.Get());
    corePID.SetProportionalConstant(m_KP.Get());
    auto table = ntinst.GetTable("limelight");
    hasCenterX = table->GetNumber("tv", 0.0) == 1;
    double conversion = 4096 / -360; // convert degrees to ticks
    // calculate center error as a percent output for the motor
    centerError = table->GetNumber("tx", 0.0) * conversion;

    SmartDashboard::PutNumber("Center Error", centerError);
    SmartDashboard::PutBoolean("HasTable", hasCenterX);

    if (hasCenterX && ((!atRightStop && centerError < 0) || (!atLeftStop && centerError > 0))) {
        return corePID.Calculate(centerError);
    } else {
        return 0;
    }
}

double TurretSubsystem::GetDistance() {
    auto table = ntinst.GetTable("limelight");
    double x = table->GetNumber("thor", 0.0);
    double a = m_DistCoefA.Get(), b = m_DistCoefB.Get();
    //double distance = a * (x * x * x) + b * (x * x) + c * x + d;
    double distance = a * pow(x, b);
    return distance;
}

void TurretSubsystem::InitTalons() {
	// Sets up talons
	m_turret.Set(ControlMode::PercentOutput, 0);
    // Zero the sensor
    m_turret.SetSelectedSensorPosition(0, 0, 10);
    m_turret.SetInverted(true);
    m_turret.SetSensorPhase(true);
}

void TurretSubsystem::SetTurret(double turretPercent) {
    m_turret.Set(ControlMode::PercentOutput, turretPercent);
}
