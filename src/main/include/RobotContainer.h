// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/Joystick.h>
#include <frc2/command/Command.h>
#include <frc/controller/PIDController.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/PIDCommand.h>
#include <frc2/command/ParallelRaceGroup.h>
#include <frc2/command/RunCommand.h>
#include <frc2/command/button/JoystickButton.h>

#include "Constants.h"


// #include "commands/ExampleCommand.h"
#include "commands/ShiftDriveGear.h"
// #include "subsystems/ExampleSubsystem.h"
#include "subsystems/DriveSubsystem.h"


// using namespace AutoConstants;
/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  frc2::Command* GetAutonomousCommand();

 private:
  // Drive controller
  Joystick driverJoystick;
  // Operator controller
  Joystick operatorJoystick;


  // The robot's subsystems and commands are defined here...
  DriveSubsystem m_driveSubsystem;
  ShiftDriveGear m_shiftDriveGear;

  // ExampleSubsystem m_subsystem;
  // ExampleCommand m_autonomousCommand;

  void ConfigureButtonBindings();
};
