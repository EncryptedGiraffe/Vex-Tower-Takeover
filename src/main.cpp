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
		//////////Legal but kinda not autonomous routine//////////
		//start with preload angled in goal zone
		//deploy
		Core::Initialize();
		//forward
		Motors::Chassis::frontLeft.moveVoltage(5000);
		Motors::Chassis::frontRight.moveVoltage(-5000);
		Motors::Chassis::backLeft.moveVoltage(5000);
		Motors::Chassis::backRight.moveVoltage(-5000);
		pros::delay(1500);
		Motors::Chassis::frontLeft.moveVoltage(0);
		Motors::Chassis::frontRight.moveVoltage(0);
		Motors::Chassis::backLeft.moveVoltage(0);
		Motors::Chassis::backRight.moveVoltage(0);
		pros::delay(500);
		//intake off
		Intake::Stop();
		//////////End of legal but kinda not autonomous routine//////////
	}
	else
	{
		//////////Legal but kinda not autonomous routine//////////
		//start with preload angled in goal zone
		//deploy
		Core::Initialize();
		//forward
		Motors::Chassis::frontLeft.moveVoltage(5000);
    Motors::Chassis::frontRight.moveVoltage(-5000);
    Motors::Chassis::backLeft.moveVoltage(5000);
    Motors::Chassis::backRight.moveVoltage(-5000);
		pros::delay(1500);
		Motors::Chassis::frontLeft.moveVoltage(0);
    Motors::Chassis::frontRight.moveVoltage(0);
    Motors::Chassis::backLeft.moveVoltage(0);
    Motors::Chassis::backRight.moveVoltage(0);
		pros::delay(500);
		//intake off
		Intake::Stop();
		//////////End of legal but kinda not autonomous routine//////////
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
ControllerButton deployMid(ControllerDigital::B);
ControllerButton highTower(ControllerDigital::up);
ControllerButton lowTower(ControllerDigital::left);
ControllerButton armBottom(ControllerDigital::down);
ControllerButton deployRetract(ControllerDigital::A);

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
	Deploy::Move(0.30F);
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
<<<<<<< Updated upstream
			Deploy::SetSpeed(100);
			if(isDeployed)
			{
				Deploy::Move(0.00F);
				isDeployed = false;
			}
			else
			{
				Deploy::Move(1.00F);
				isDeployed = true;
			}
=======
			//set the intake to its fully deployed target
			Deploy::Move(1.00);
			//figure out where it is to adjust the speed
		}
		else if(deployExtend.changedToReleased())
		{
			//stop the intake moving
			Deploy::Move(Deploy::GetPosition());
>>>>>>> Stashed changes
		}
		if(deployMid.changedToPressed())
		{
			SetDeployMiddle();
		}
		if(deployRetract.changedToPressed())
		{
			//full speed and retract
			Deploy::SetSpeed(200);
			Deploy::Move(0.00F);
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
