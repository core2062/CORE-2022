// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/trajectory/constraint/DifferentialDriveKinematicsConstraint.h>
// #include <units/units.h>
#include <units/voltage.h>
#include <units/velocity.h>
#include <units/angle.h>
#include <units/acceleration.h>
#include <wpi/numbers>
// All of these values should be updated according to what works with the characterization tool


namespace DriveConstants {
constexpr auto kTrackwidth = 0.60325_m; 
extern const frc::DifferentialDriveKinematics kDriveKinematics;

constexpr int kEncoderCPR = 2048;
constexpr double kGearReduction = 0.23333333333;
// constexpr double kGearReduction = 4.2857;
constexpr double kWheelDiameterInches = 6;
constexpr double kEncoderDistancePerPulse =
    // Assumes the encoders are directly mounted on the wheel shafts
    (kWheelDiameterInches * wpi::numbers::pi) / (static_cast<double>(kEncoderCPR) * kGearReduction);

constexpr bool kGyroReversed = true;

constexpr auto ks = 0.86138_V;
constexpr auto kv = 1.7522 * 1_V * 1_s / 1_m;
constexpr auto ka = 0.36649 * 1_V * 1_s * 1_s / 1_m;

constexpr double kPDriveVel = 2.6183;
}

namespace AutoConstants {
constexpr auto kMaxSpeed = 3_mps;
constexpr auto kMaxAcceleration = 3_mps_sq;


constexpr auto kRamseteB = 2.0 * 1_rad * 1_rad / (1_m * 1_m);
constexpr auto kRamseteZeta = 0.7 / 1_rad;
}  // namespace AutoConstants
