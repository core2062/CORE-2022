#pragma once

#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/trajectory/constraint/DifferentialDriveKinematicsConstraint.h>
#include <units/units.h>
#include <wpi/math>
// All of these values should be updated according to what works with the characterization tool


namespace DriveConstants {
// constexpr auto kTrackwidth = _m; // Not sure if this is correct or if we need to manually measure
extern const frc::DifferentialDriveKinematics kDriveKinematics;

constexpr int kEncoderCPR = 2048;
constexpr double kGearReduction = 4.28571;
constexpr double kWheelDiameterInches = 6;
constexpr double kEncoderDistancePerPulse =
    // Assumes the encoders are directly mounted on the wheel shafts
    (kWheelDiameterInches * wpi::math::pi) / (static_cast<double>(kEncoderCPR) * kGearReduction);

constexpr bool kGyroReversed = true;

constexpr auto ks = 0.60452_V;
constexpr auto kv = 0.0013063 * 1_V * 1_s / 1_m;
constexpr auto ka = 0.00020757 * 1_V * 1_s * 1_s / 1_m;

