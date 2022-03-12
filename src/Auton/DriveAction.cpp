#include "DriveAction.h"
#include "Robot.h"

DriveAction::DriveAction(driveAction requestedDriveAction) : 
                                        m_distAutonMoveEncoderTicks("Auton Movement", 12000) {
                                        m_driveAction = requestedDriveAction;
                                        m_turnAmount = 0;
}

DriveAction::DriveAction(driveAction requestedDriveAction, double turnAmount) : 
                                        m_distAutonMoveEncoderTicks("Auton Movement", 12000) {
                                        m_driveAction = requestedDriveAction;
                                        m_turnAmount = turnAmount;

}

void DriveAction::ActionInit() {
    DriveSubsystem* driveSubsystem = &Robot::GetInstance()->driveSubsystem;
    m_encoderStartUpPosition =  driveSubsystem->getRobotPosition();
    m_navXStartingHeading = driveSubsystem->ahrs.GetFusedHeading(); //Starting heading of NavX; Used for TURN_RIGHT and TURN_LEFT
}

CORE::COREAutonAction::actionStatus DriveAction::Action() {
    DriveSubsystem* driveSubsystem = &Robot::GetInstance()->driveSubsystem;
    double currentHeading;
    double encoderValue = driveSubsystem->getRobotPosition();
    switch(m_driveAction) {
        case FORWARD:
            Robot::GetInstance()->driveSubsystem.setMotorSpeed(0.3, DriveSide::BOTH);
            if(encoderValue < m_distAutonMoveEncoderTicks.Get() + m_encoderStartUpPosition){
                driveSubsystem->setMotorSpeed(0.3, DriveSide::BOTH);
                return COREAutonAction::actionStatus::CONTINUE;
            } else{
                driveSubsystem->setMotorSpeed(0.0, DriveSide::BOTH);
            }
            break;
        case BACKWARD:
            if(encoderValue > m_encoderStartUpPosition - m_distAutonMoveEncoderTicks.Get()){
                driveSubsystem->setMotorSpeed(-0.3, DriveSide::BOTH);
                return COREAutonAction::actionStatus::CONTINUE;
            } else{
                driveSubsystem->setMotorSpeed(0.0, DriveSide::BOTH);
            }
            break;
        case RIGHT_TURN:
            m_requestedHeading = m_navXStartingHeading + m_turnAmount; // Calculates the requested heading to turn to
            if (m_requestedHeading >= 360) { // If Requested heading is not in a possible range of movement, subtracts 360 to loop it back between 0-359
                m_requestedHeading -= 360;
            } 
            currentHeading = driveSubsystem->ahrs.GetFusedHeading();
            if(currentHeading != (m_requestedHeading-5) || currentHeading != (m_requestedHeading+5)){ // Deadband of 5°
                driveSubsystem->setMotorSpeed(0.1, DriveSide::LEFT);
                driveSubsystem->setMotorSpeed(-0.1, DriveSide::RIGHT);
                return COREAutonAction::actionStatus::CONTINUE;
            } else{
                driveSubsystem->setMotorSpeed(0.0, DriveSide::BOTH);
            }
            break;
        case LEFT_TURN:
            m_requestedHeading = m_navXStartingHeading - m_turnAmount; // Calculates the requested heading to turn to
            if (m_requestedHeading < 0) { // If Requested heading is not in a possible range of movement, adds 360 to loop it back between 0-359
                m_requestedHeading += 360;
            } 
            currentHeading = driveSubsystem->ahrs.GetFusedHeading();
            if(currentHeading != (m_requestedHeading-5) || currentHeading != (m_requestedHeading+5)){ // Deadband of 5°
                driveSubsystem->setMotorSpeed(-0.1, DriveSide::LEFT);
                driveSubsystem->setMotorSpeed(0.1, DriveSide::RIGHT);
                return COREAutonAction::actionStatus::CONTINUE;
            } else{
                driveSubsystem->setMotorSpeed(0.0, DriveSide::BOTH);
            }
            break;
    }
    return COREAutonAction::actionStatus::END;
}

void DriveAction::ActionEnd() {

}