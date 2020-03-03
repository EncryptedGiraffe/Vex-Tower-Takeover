#include "drivers.hpp"

void initialize()
{
	PANS::Core::Initialize();
	Chassis::Initialize();
	Arm::Initialize();
	Deploy::Initialize();
}
void disabled() {}

bool isAutoRed = false;
bool isAutoDouble = false;
void competition_initialize()
{
	// select colour
	PANS::UISystem::ConfigDialog("Select team:", "Red", []{isAutoRed = true;}, "Blue", []{isAutoRed = false;});
	// select starting position
	PANS::UISystem::ConfigDialog("Select starting position:", "Single goal", []{isAutoDouble = false;}, "Double goal", []{isAutoDouble = true;});
}

void autonomous()
{
	// Core::Initialize();
	if(isAutoDouble)
	{
		//////////AUTONOMOUS FOR THE DOUBLE GOAL STARTING POSITION//////////
		// *programmed on blue*
		// drive back
		Motors::Chassis::frontLeft.moveVoltage(-7000);
    Motors::Chassis::frontRight.moveVoltage(7000);
    Motors::Chassis::backLeft.moveVoltage(-7000);
    Motors::Chassis::backRight.moveVoltage(7000);
		pros::delay(300);
		// strife sideways to align with cube (right on blue)
		Motors::Chassis::frontLeft.moveVoltage(7000);
    Motors::Chassis::frontRight.moveVoltage(7000);
    Motors::Chassis::backLeft.moveVoltage(-7000);
    Motors::Chassis::backRight.moveVoltage(-7000);
		pros::delay(300);
		// deploy ramp + rollers
		Core::Initialize();
		pros::delay(700);
		// drive forwards and slurp up preload in front
		Motors::Chassis::frontLeft.moveVoltage(6000);
    Motors::Chassis::frontRight.moveVoltage(-6000);
    Motors::Chassis::backLeft.moveVoltage(6000);
    Motors::Chassis::backRight.moveVoltage(-6000);
		Intake::SetForwards();
		Intake::SetSpeed(1.0F);
		Intake::Start();
		pros::delay(500);
		Intake::Stop();
		// rotate clockwise for cube to left of tower
		Motors::Chassis::frontLeft.moveVoltage(7000);
    Motors::Chassis::frontRight.moveVoltage(7000);
    Motors::Chassis::backLeft.moveVoltage(7000);
    Motors::Chassis::backRight.moveVoltage(7000);
		pros::delay(500);
		// drive forwards and slurp cube to left of tower
		Motors::Chassis::frontLeft.moveVoltage(6000);
    Motors::Chassis::frontRight.moveVoltage(-6000);
    Motors::Chassis::backLeft.moveVoltage(6000);
    Motors::Chassis::backRight.moveVoltage(-6000);
		Intake::SetForwards();
		Intake::SetSpeed(1.0F);
		Intake::Start();
		pros::delay(500);
		Intake::Stop();
		// // drive back
		// Motors::Chassis::frontLeft.moveVoltage(-7000);
    // Motors::Chassis::frontRight.moveVoltage(7000);
    // Motors::Chassis::backLeft.moveVoltage(-7000);
    // Motors::Chassis::backRight.moveVoltage(7000);
		// pros::delay(700);
		// // rotate clockwise to have back parallel to wall
		// Motors::Chassis::frontLeft.moveVoltage(7000);
    // Motors::Chassis::frontRight.moveVoltage(7000);
    // Motors::Chassis::backLeft.moveVoltage(7000);
    // Motors::Chassis::backRight.moveVoltage(7000);
		// pros::delay(800);
		// // stife to align with cubes (right for blue)
		// Motors::Chassis::frontLeft.moveVoltage(7000);
    // Motors::Chassis::frontRight.moveVoltage(7000);
    // Motors::Chassis::backLeft.moveVoltage(-7000);
    // Motors::Chassis::backRight.moveVoltage(-7000);
		// pros::delay(700);
		// // drive forwards and slurp
		// Motors::Chassis::frontLeft.moveVoltage(6000);
    // Motors::Chassis::frontRight.moveVoltage(-6000);
    // Motors::Chassis::backLeft.moveVoltage(6000);
    // Motors::Chassis::backRight.moveVoltage(-6000);
		// Intake::SetForwards();
		// Intake::SetSpeed(1.0F);
		// Intake::Start();
		// pros::delay(800);
		// Intake::Stop();
		// // 90 clockwise turn towards cube
		// Motors::Chassis::frontLeft.moveVoltage(7000);
    // Motors::Chassis::frontRight.moveVoltage(7000);
    // Motors::Chassis::backLeft.moveVoltage(7000);
    // Motors::Chassis::backRight.moveVoltage(7000);
		// pros::delay(800);
		// // drive forwards and slurp
		// Motors::Chassis::frontLeft.moveVoltage(6000);
    // Motors::Chassis::frontRight.moveVoltage(-6000);
    // Motors::Chassis::backLeft.moveVoltage(6000);
    // Motors::Chassis::backRight.moveVoltage(-6000);
		// Intake::SetForwards();
		// Intake::SetSpeed(1.0F);
		// Intake::Start();
		// pros::delay(800);
		// Intake::Stop();
		// // 45 clockwise turn towards deploy
		// Motors::Chassis::frontLeft.moveVoltage(7000);
		// Motors::Chassis::frontRight.moveVoltage(7000);
		// Motors::Chassis::backLeft.moveVoltage(7000);
		// Motors::Chassis::backRight.moveVoltage(7000);
		// pros::delay(600);
		// // drive forwards
		// Motors::Chassis::frontLeft.moveVoltage(7000);
		// Motors::Chassis::frontRight.moveVoltage(-7000);
		// Motors::Chassis::backLeft.moveVoltage(7000);
		// Motors::Chassis::backRight.moveVoltage(-7000);
		// pros::delay(800);
		// // deploy
		// Deploy::SetSpeed(120);
		// Deploy::SetTarget(1.0F);
		// pros::delay(5000);
		// //set the intake to release the stack
		// Intake::SetBackwards();
		// Intake::Start();
		// // reverse back but not all the way
		// Motors::Chassis::frontLeft.moveVoltage(-7000);
		// Motors::Chassis::frontRight.moveVoltage(7000);
		// Motors::Chassis::backLeft.moveVoltage(-7000);
		// Motors::Chassis::backRight.moveVoltage(7000);
		// pros::delay(600);
		// //stop everything
		// Motors::Chassis::frontLeft.moveVoltage(0);
		// Motors::Chassis::frontRight.moveVoltage(0);
		// Motors::Chassis::backLeft.moveVoltage(0);
		// Motors::Chassis::backRight.moveVoltage(0);
		// Intake::Stop();
	}
	else
	{
		/////////AUTONOMOUS FOR THE SINGLE GOAL STARTING POSITION/////////
		Core::Initialize();
		pros::delay(700);
		// drive forwards to slurp up 4 cubes
		Motors::Chassis::frontLeft.moveVoltage(5000);
    Motors::Chassis::frontRight.moveVoltage(-5000);
    Motors::Chassis::backLeft.moveVoltage(5000);
    Motors::Chassis::backRight.moveVoltage(-5000);
		Intake::SetForwards();
		Intake::SetSpeed(1.0F);
		Intake::Start();
		pros::delay(2700);
		// reverse back but not all the way
		Motors::Chassis::frontLeft.moveVoltage(-7000);
    Motors::Chassis::frontRight.moveVoltage(7000);
    Motors::Chassis::backLeft.moveVoltage(-7000);
    Motors::Chassis::backRight.moveVoltage(7000);
		pros::delay(350);
		Intake::Stop();
		pros::delay(700);
		// check which side we are on so we know which way to rotate
		if(isAutoRed)
		{
			// rotate clockwise to face small goal zone corner
			Motors::Chassis::frontLeft.moveVoltage(7000);
			Motors::Chassis::frontRight.moveVoltage(7000);
			Motors::Chassis::backLeft.moveVoltage(7000);
			Motors::Chassis::backRight.moveVoltage(7000);
		}
		else
		{
			// rotate counter clockwise to face small goal zone corner
			Motors::Chassis::frontLeft.moveVoltage(-7000);
	    Motors::Chassis::frontRight.moveVoltage(-7000);
	    Motors::Chassis::backLeft.moveVoltage(-7000);
	    Motors::Chassis::backRight.moveVoltage(-7000);
		}
		pros::delay(1100);
		// drive forwards to meet edge of goal zone
		Motors::Chassis::frontLeft.moveVoltage(7000);
    Motors::Chassis::frontRight.moveVoltage(-7000);
    Motors::Chassis::backLeft.moveVoltage(7000);
    Motors::Chassis::backRight.moveVoltage(-7000);
		pros::delay(700);
		Motors::Chassis::frontLeft.moveVoltage(0);
    Motors::Chassis::frontRight.moveVoltage(0);
    Motors::Chassis::backLeft.moveVoltage(0);
    Motors::Chassis::backRight.moveVoltage(0);
		// deploy
		Deploy::SetSpeed(120);
		Deploy::SetTarget(1.0F);
		pros::delay(5000);
		//set the intake to release the stack
		Intake::SetBackwards();
		Intake::Start();
		// reverse back but not all the way
		Motors::Chassis::frontLeft.moveVoltage(-7000);
		Motors::Chassis::frontRight.moveVoltage(7000);
		Motors::Chassis::backLeft.moveVoltage(-7000);
		Motors::Chassis::backRight.moveVoltage(7000);
		pros::delay(600);
		//stop everything
		Motors::Chassis::frontLeft.moveVoltage(0);
		Motors::Chassis::frontRight.moveVoltage(0);
		Motors::Chassis::backLeft.moveVoltage(0);
		Motors::Chassis::backRight.moveVoltage(0);
		Intake::Stop();
	}
}

//opcontrol constants
const int arm_increment = 30;

//opcontrol state variables
bool isIntakeRunning = false;
bool isDriveSlow = true;
int arm_pos = 0;

//buttons
ControllerButton intakeToggle(ControllerDigital::R1);
ControllerButton intakeReverse(ControllerDigital::R2);
ControllerButton driveSpeedToggle(ControllerDigital::X);
ControllerButton deployExtend(ControllerDigital::Y);
ControllerButton armUp(ControllerDigital::L1);
ControllerButton armDown(ControllerDigital::L2);
ControllerButton deployMid(ControllerDigital::A);
ControllerButton highTower(ControllerDigital::up);
ControllerButton lowTower(ControllerDigital::left);
ControllerButton armBottom(ControllerDigital::down);
ControllerButton deployRetract(ControllerDigital::B);

//drive variables
float ch1;
float ch3;
float ch4;
float driveSpeed = 0.50;

//opcontrol functions
void ArmBounds()
{
	if(arm_pos < 0)
	{
		arm_pos = 0;
	}
	else if(arm_pos > Arm::maxHeight)
	{
		arm_pos = Arm::maxHeight;
	}
}

void SetDeployMiddle()
{
	Deploy::SetTarget(0.30F);
}

void opcontrol()
{
	PANS::UISystem::MessageBrain("Opcontrol starting");
	Core::Initialize();
	while (true)
	{
		//intake controller
		if (intakeToggle.changedToPressed())
		{
			if(isIntakeRunning)
			{
				Intake::Stop();
				isIntakeRunning = false;
			}
			else
			{
				Intake::SetSpeed(1.0);
				Intake::SetForwards();
				Intake::Start();
				isIntakeRunning = true;
			}
		}
		if (intakeReverse.changedToPressed())
		{
			Intake::SetBackwards();
			Intake::SetSpeed(1.0);
			Intake::Start();
		}
		else if(intakeReverse.changedToReleased())
		{
			Intake::SetForwards();
			Intake::Stop();
		}
		//deploy
		if(deployExtend.isPressed())
		{
			//figure out where it is to adjust the speed
			if(Deploy::GetActualPosition() < 0.6)
			{
				//full speed
				Deploy::SetSpeed(200);
			}
			else if(Deploy::GetActualPosition() < 0.85)
			{
				//half speed
				Deploy::SetSpeed(100);
			}
			else
			{
				//quarter speed
				Deploy::SetSpeed(50);
			}
			//set the intake to its fully deployed target
			Deploy::SetTarget(1.00);
		}
		if(deployExtend.changedToReleased())
		{
			//stop the intake moving
			Deploy::SetSpeed(100);
			Deploy::SetTarget(Deploy::GetActualPosition());
		}
		if(deployMid.changedToPressed())
		{
			Deploy::SetSpeed(100);
			SetDeployMiddle();
		}
		if(deployRetract.changedToPressed())
		{
			//full speed and retract
			Deploy::SetSpeed(200);
			Deploy::SetTarget(0.00F);
		}
		//arm control
		if(armUp.isPressed())
		{
			arm_pos += arm_increment;
			ArmBounds();
			Arm::SetPosition(arm_pos);
		}
		else if(armDown.isPressed())
		{
			arm_pos -= arm_increment;
			ArmBounds();
			Arm::SetPosition(arm_pos);
		}
		if(lowTower.changedToPressed())
		{
			arm_pos = Arm::lowTower;
			Arm::SetPosition(arm_pos);
		}
		if(highTower.changedToPressed())
		{
			arm_pos = Arm::highTower;
			Arm::SetPosition(arm_pos);
		}
		if(armBottom.changedToPressed())
		{
			arm_pos = 0;
			Arm::SetPosition(arm_pos);
		}
		//drive speed
		if(driveSpeedToggle.changedToPressed())
		{
			if(isDriveSlow)
			{
				isDriveSlow = false;
				driveSpeed = 1.00;
			}
			else
			{
				isDriveSlow = true;
				driveSpeed = 0.65;
			}
		}
		//open-loop drive control
		ch1 = Core::master.getAnalog(ControllerAnalog::rightX);
		ch3 = Core::master.getAnalog(ControllerAnalog::leftY);
		ch4 = Core::master.getAnalog(ControllerAnalog::leftX);
		Motors::Chassis::frontLeft.moveVoltage(12000 * (ch3 + ch1 + ch4) * driveSpeed);
		Motors::Chassis::frontRight.moveVoltage(-12000 * (ch3 - ch1 - ch4) * driveSpeed);
		Motors::Chassis::backLeft.moveVoltage(12000 * (ch3 + ch1 - ch4) * driveSpeed);
		Motors::Chassis::backRight.moveVoltage(-12000 * (ch3 - ch1 + ch4) * driveSpeed);
		//Chassis::controller->getModel()->tank(Core::master.getAnalog(ControllerAnalog::leftY), Core::master.getAnalog(ControllerAnalog::rightY));
		pros::delay(20);
	}
}
