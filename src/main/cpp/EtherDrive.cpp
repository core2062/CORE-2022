#include "EtherDrive.h"
#include "ctre/Phoenix.h"

double EtherDrive::m_a = 0.6;
double EtherDrive::m_b = 0.4;
double EtherDrive::m_quickTurn = 1.0;

EtherDrive::EtherDrive(TalonSRX * leftMotor1, TalonSRX * leftMotor2,
		TalonSRX * rightMotor1, TalonSRX * rightMotor2, double a, double b,
		double quickTurn) :
		m_leftMotor1(leftMotor1), m_leftMotor2(leftMotor2), m_rightMotor1(
				rightMotor1), m_rightMotor2(rightMotor2) {
	m_a = a;
	m_b = b;
	m_quickTurn = quickTurn;

}

/**
 * Sets variables "a" and "b"
 * @param a Unsure what "a" is for
 * @param b Unsure what "b" is for
 */
void EtherDrive::SetAB(double a, double b) {
	m_a = a;
	m_b = b;
}


void EtherDrive::SetQuickturn(double q) {
	m_quickTurn = q;
}


/**
 * Calculates the left and right drivetrain values using the x and y inputs from the joysticks
 * @param mag The magnitude of the joystick
 * @param rot The rotation of the joystick
 * @param deadband The deadband of the joystick
 * @return VelocityPair {left,right}; The VelocityPair value returned are left and right sides of the drivetrain
 */
VelocityPair EtherDrive::Calculate(double mag, double rot, bool squareInputs, double deadband) {
  mag = std::clamp(mag, -1.0, 1.0);
  rot = std::clamp(rot, -1.0, 1.0);

  // Square the inputs (while preserving the sign) to increase fine control
  // while permitting full power.
  if (squareInputs) {
    mag = std::copysign(mag * mag, mag);
    rot = std::copysign(rot * rot, rot);
  }

  double leftSpeed;
  double rightSpeed;

  double maxInput =
      std::copysign(std::max(std::abs(mag), std::abs(rot)), mag);

  if (mag >= 0.0) {
    // First quadrant, else second quadrant
    if (rot >= 0.0) {
      leftSpeed = maxInput;
      rightSpeed = mag - rot;
    } else {
      leftSpeed = mag + rot;
      rightSpeed = maxInput;
    }
  } else {
    // Third quadrant, else fourth quadrant
    if (rot >= 0.0) {
      leftSpeed = mag + rot;
      rightSpeed = maxInput;
    } else {
      leftSpeed = maxInput;
      rightSpeed = mag - rot;
    }
  }

  // Normalize the wheel speeds
  double maxMagnitude = std::max(std::abs(leftSpeed), std::abs(rightSpeed));
  if (maxMagnitude > 1.0) {
    leftSpeed /= maxMagnitude;
    rightSpeed /= maxMagnitude;
  }

  return {leftSpeed, rightSpeed};
}



/**
 * Calculates the Ether Value for the left side of the drivetrain
 * @param  fwd Magnitude
 * @param  rcw Rotation
 * @param  a Unsure
 * @param  b Unsure
 * @return Value of EtherDrive Left
 */
double EtherDrive::EtherL(double fwd, double rcw, double a, double b) {
	return fwd + b * rcw * (1 - fwd);
}

/**
 * Calculates the Ether Value for the right side of the drivetrain
 * @param  fwd Magnitude
 * @param  rcw Rotation
 * @param  a Unsure
 * @param  b Unsure
 * @return Value of EtherDrive right
 */
double EtherDrive::EtherR(double fwd, double rcw, double a, double b) {
	return fwd - b * rcw + fwd * rcw * (b - a - 1);
}

