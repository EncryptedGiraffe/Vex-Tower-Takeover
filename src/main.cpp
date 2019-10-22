#include "drivers.hpp"

void initialize()
{
	PANS::Core::Initialize();
	Chassis::Initialize();
	Arm::Initialize();
}
void disabled() {}
void competition_initialize() {}
void autonomous() {}

//opcontrol constants
const int arm_increment = 30;

//opcontrol state variables
bool isIntakeRunning = false;
bool isDriveSlow = true;
bool isDeployed = false;
int arm_pos = 0;

//buttons
ControllerButton intakeToggle(ControllerDigital::R1);
ControllerButton intakeReverse(ControllerDigital::R2);
ControllerButton driveSpeedToggle(ControllerDigital::B);
ControllerButton deployToggle(ControllerDigital::Y);
ControllerButton armUp(ControllerDigital::L1);
ControllerButton armDown(ControllerDigital::L2);

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

void opcontrol()
{
	PANS::UISystem::MessageBrain("Opcontrol starting");
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
				Intake::Start();
				isIntakeRunning = true;
			}
		}
		if (intakeReverse.isPressed())
		{
			Intake::SetBackwards();
		}
		else
		{
			Intake::SetForwards();
		}
		//deploy
		if(deployToggle.changedToPressed())
		{
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
		}
		if(armUp.isPressed())
		{
			arm_pos += arm_increment;
			ArmBounds();
			Arm::SetPosition(arm_pos);
			PANS::UISystem::MessageBrain(std::to_string(arm_pos));
		}
		else if(armDown.isPressed())
		{
			arm_pos -= arm_increment;
			ArmBounds();
			Arm::SetPosition(arm_pos);
			PANS::UISystem::MessageBrain(std::to_string(arm_pos));
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
