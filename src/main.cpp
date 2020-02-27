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
void SetBlueAuto()
{
	isAutoRed = false;
}
void SetRedAuto()
{
	isAutoRed = true;
}
void competition_initialize()
{
	PANS::UISystem::ConfigDialog("Select team:", "Red", SetRedAuto, "Blue", SetBlueAuto);
}

void autonomous()
{
	// Core::Initialize();
	if(isAutoRed)
	{
		Core::Initialize();
	}
	else
	{
		Core::Initialize();
		pros::delay(1000);
		////////close blue *NEEDS TESTING*////////
		// drive forwards to slurp up 4 cubes
		Motors::Chassis::frontLeft.moveVoltage(5000);
    Motors::Chassis::frontRight.moveVoltage(-5000);
    Motors::Chassis::backLeft.moveVoltage(5000);
    Motors::Chassis::backRight.moveVoltage(-5000);
		Intake::SetForwards();
		Intake::SetSpeed(1.0F);
		Intake::Start();
		pros::delay(2500);
		Intake::Stop();
		// reverse back but not all the way
		Motors::Chassis::frontLeft.moveVoltage(-7000);
    Motors::Chassis::frontRight.moveVoltage(7000);
    Motors::Chassis::backLeft.moveVoltage(-7000);
    Motors::Chassis::backRight.moveVoltage(7000);
		pros::delay(1000);
		// rotate counter clockwise to face small goal zone corner
		Motors::Chassis::frontLeft.moveVoltage(-7000);
    Motors::Chassis::frontRight.moveVoltage(-7000);
    Motors::Chassis::backLeft.moveVoltage(-7000);
    Motors::Chassis::backRight.moveVoltage(-7000);
		pros::delay(1200);
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
		Deploy::SetTarget(1.0F);
		Deploy::SetSpeed(120);
		pros::delay(4000);
		////////end of close blue////////
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
				driveSpeed = 0.50;
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
