#include "drivers.hpp"

void initialize()
{
	//initialize PANS
	PANS::Core::Initialize();
}
void disabled() {}
void competition_initialize() {}
void autonomous() {}

//state variables
bool isIntakeRunning = false;

//buttons
ControllerButton intakeToggle(ControllerDigital::R1);
ControllerButton intakeReverse(ControllerDigital::R2);

void opcontrol()
{
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
		pros::delay(20);
	}
}
