#pragma once

#include <ctre/Phoenix.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Compressor.h>
#include <CORERobotLib.h>
#include "Config.h"

using namespace CORE;
using namespace frc;


class ClimberSubsystem : public CORESubsystem {
public:
	ClimberSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void climberSolenoid(bool climberPin);

    void climberMotor(double speed);


private:
    TalonFX m_rightTalon, m_leftTalon;
    COREConstant<double> m_climberOutSpeed,m_climberInSpeed,m_climberSoftStop;
    DoubleSolenoid m_climberSolinoid;
    bool m_climberPin;
    Compressor m_climberCompressor;
};
