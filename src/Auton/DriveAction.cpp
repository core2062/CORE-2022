#include "DriveAction.h"
#include "Robot.h"

DriveAction::DriveAction(driveAction requestedDriveAction) : 
                                        m_distAutonMoveEncoderTicks("Auton Movement", 24) {
                                        m_driveAction = requestedDriveAction;
                                        m_turnAmount = 0;
}

DriveAction::DriveAction(driveAction requestedDriveAction, double turnAmount) : 
                                        m_distAutonMoveEncoderTicks("Auton Movement", 24) {
                                        m_driveAction = requestedDriveAction;
                                        m_turnAmount = turnAmount;

}

void DriveAction::ActionInit() {
    DriveSubsystem* driveSubsystem = &Robot::GetInstance()->driveSubsystem;
    driveSubsystem->initTalons();
    driveSubsystem->setBrakeMode();
    std::cout << m_distAutonMoveEncoderTicks.Get() << " Dist CORE Constant" << endl;
    m_requestedDriveDistance = ((m_distAutonMoveEncoderTicks.Get()*33540)/(6*3.14159265358979323));
    m_encoderStartUpPosition =  driveSubsystem->getRobotPosition();
    std::cout << m_encoderStartUpPosition << " right encoder at startup" << endl; // should be zero
    m_navXStartingHeading = driveSubsystem->ahrs.GetFusedHeading(); //Starting heading of NavX; Used for TURN_RIGHT and TURN_LEFT
}

CORE::COREAutonAction::actionStatus DriveAction::Action() {
    DriveSubsystem* driveSubsystem = &Robot::GetInstance()->driveSubsystem;
    m_encoderValue = driveSubsystem->getRobotPosition();
    switch(m_driveAction) {
        case FORWARD:
            Robot::GetInstance()->driveSubsystem.setMotorSpeed(0.3, DriveSide::BOTH);
            if(m_encoderValue < m_requestedDriveDistance + m_encoderStartUpPosition){
                driveSubsystem->setMotorSpeed(0.3, DriveSide::BOTH);
                return COREAutonAction::actionStatus::CONTINUE;
            } else{
                driveSubsystem->setMotorSpeed(0.0, DriveSide::BOTH);
            }
            break;
        case BACKWARD:
            if(m_encoderValue > m_encoderStartUpPosition - m_requestedDriveDistance){
                driveSubsystem->setMotorSpeed(-0.3, DriveSide::BOTH);
                cout << "Encoder Value: "    << m_encoderValue << endl
                     << "Start position: "   << m_encoderStartUpPosition << endl 
                     << "Movement setting: " << m_requestedDriveDistance << endl;
                return COREAutonAction::actionStatus::CONTINUE;
            } else{
                cout << "Stopping back up" << endl;
                driveSubsystem->setMotorSpeed(0.0, DriveSide::BOTH);
            }
            break;
        case RIGHT_TURN:
            m_requestedHeading = m_navXStartingHeading + m_turnAmount; // Calculates the requested heading to turn to
            if (m_requestedHeading >= 360) { // If Requested heading is not in a possible range of movement, subtracts 360 to loop it back between 0-359
                m_requestedHeading -= 360;
            } 
            m_currentHeading = driveSubsystem->ahrs.GetFusedHeading();
            if(m_currentHeading != (m_requestedHeading-5) || m_currentHeading != (m_requestedHeading+5)){ // Deadband of 5°
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
            m_currentHeading = driveSubsystem->ahrs.GetFusedHeading();
            if(m_currentHeading != (m_requestedHeading-5) || m_currentHeading != (m_requestedHeading+5)){ // Deadband of 5°
                driveSubsystem->setMotorSpeed(-0.3, DriveSide::LEFT);
                driveSubsystem->setMotorSpeed(0.3, DriveSide::RIGHT);
                return COREAutonAction::actionStatus::CONTINUE;
            } else{
                driveSubsystem->setMotorSpeed(0.0, DriveSide::BOTH);
            }
            break;
    }
    return COREAutonAction::actionStatus::END;
}

void DriveAction::ActionEnd() {
    DriveSubsystem* driveSubsystem = &Robot::GetInstance()->driveSubsystem;
    std::cout << driveSubsystem->getRobotPosition() << " left encoder at end" << endl; // should be zero

}