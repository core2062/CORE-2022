#include "TurretTrackingAction.h"
#include "Robot.h"

TurretTrackingAction::TurretTrackingAction(turretTrackingAction requestedTurretTrackingAction) {
    m_turretTrackingAction = requestedTurretTrackingAction;
}

void TurretTrackingAction::ActionInit() {
    TurretSubsystem* turretSubsystem = &Robot::GetInstance()->turretSubsystem;
    m_turretStartupPosition = turretSubsystem->turretPosition();
}

CORE::COREAutonAction::actionStatus TurretTrackingAction::Action() {
    TurretSubsystem* turretSubsystem = &Robot::GetInstance()->turretSubsystem;
    m_turretPosition = turretSubsystem->turretPosition();
    bool atLeftStop = false; //m_turretPosition < (m_turretStartupPosition - 7000.0);
    bool atRightStop = false; //m_turretPosition > (m_turretStartupPosition + 7000.0);
    switch(m_turretTrackingAction) {
        case TRACKING_ON: {
            double motorPercent = turretSubsystem->VisionMove(atLeftStop, atRightStop);
            cout << "Center Error" << turretSubsystem->centerError << endl;
            if (turretSubsystem->hasCenterX) {
                if (abs(turretSubsystem->centerError) > 10) {
                    turretSubsystem->SetTurret(motorPercent);
                    break;
                } else {
                    turretSubsystem->SetTurret(0.0);
                    return COREAutonAction::actionStatus::END;
                }
            }
            break;
        }
        case TRACKING_OFF: {
            turretSubsystem->SetTurret(0.0);
            return COREAutonAction::actionStatus::END;
        }
        default: break;
    }
    return COREAutonAction::actionStatus::CONTINUE;
} 

void TurretTrackingAction::ActionEnd() {

}
