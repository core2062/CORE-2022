// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc/controller/PIDController.h>
#include <frc/controller/RamseteController.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/trajectory/Trajectory.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/RamseteCommand.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/button/JoystickButton.h>

#include "Constants.h"

RobotContainer::RobotContainer() : driverJoystick(0),
                                   operatorJoystick(1),
                                   m_shiftDriveGear(&m_driveSubsystem) /*: m_autonomousCommand(&m_subsystem)*/ {
  // Initialize all of your commands and subsystems here
  // Configure the button bindings
  ConfigureButtonBindings();
   m_driveSubsystem.SetDefaultCommand(frc2::RunCommand(
      [this] {
        double mag = -driverJoystick.GetRawAxis(1);
	    double rot = driverJoystick.GetRawAxis(4);
        m_driveSubsystem.etherDrive(mag, rot);
      },
      {&m_driveSubsystem}));
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  frc2::JoystickButton(&driverJoystick,6)
    .WhenPressed(&m_shiftDriveGear);
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // Create a voltage constraint to ensure we don't accelerate too fast
  frc::DifferentialDriveVoltageConstraint autoVoltageConstraint(
      frc::SimpleMotorFeedforward<units::meters>(
          DriveConstants::ks, DriveConstants::kv, DriveConstants::ka),
      DriveConstants::kDriveKinematics, 10_V);

  // Set up config for trajectory
  frc::TrajectoryConfig config(AutoConstants::kMaxSpeed,
                               AutoConstants::kMaxAcceleration);
  // Add kinematics to ensure max speed is actually obeyed
  config.SetKinematics(DriveConstants::kDriveKinematics);
  // Apply the voltage constraint
  config.AddConstraint(autoVoltageConstraint);

  // An example trajectory to follow.  All units in meters.
  auto exampleTrajectory = frc::TrajectoryGenerator::GenerateTrajectory(
      // Start at the origin facing the +X direction
      frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
      // Pass through these two interior waypoints, making an 's' curve path
      {frc::Translation2d(1_m, 1_m)},
      // End 3 meters straight ahead of where we started, facing forward
      frc::Pose2d(2_m, 1_m, frc::Rotation2d(0_deg)),
      // Pass the config
      config);

  frc2::RamseteCommand ramseteCommand(
      exampleTrajectory, [this]() { return m_driveSubsystem.GetPose(); },
      frc::RamseteController(AutoConstants::kRamseteB,
                             AutoConstants::kRamseteZeta),
      frc::SimpleMotorFeedforward<units::meters>(
          DriveConstants::ks, DriveConstants::kv, DriveConstants::ka),
      DriveConstants::kDriveKinematics,
      [this] { return m_driveSubsystem.GetWheelSpeeds(); },
      frc2::PIDController(DriveConstants::kPDriveVel, 0, 0),
      frc2::PIDController(DriveConstants::kPDriveVel, 0, 0),
      [this](auto left, auto right) { m_driveSubsystem.TankDriveVolts(left, right); },
      {&m_driveSubsystem});

  // Reset odometry to the starting pose of the trajectory.
  m_driveSubsystem.ResetOdometry(exampleTrajectory.InitialPose());

  // no auto
  return new frc2::SequentialCommandGroup(
      std::move(ramseteCommand),
      frc2::InstantCommand([this] { m_driveSubsystem.TankDriveVolts(0_V, 0_V); }, {}));
}