// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ShiftDriveGear.h"

ShiftDriveGear::ShiftDriveGear(DriveSubsystem* subsystem)
    : m_driveSubsystem{subsystem} {}
    
void ShiftDriveGear::Initialize() {
    m_driveSubsystem->toggleGear();
}

bool ShiftDriveGear::IsFinished() {
    return true;
}