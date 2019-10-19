#include "drivers.hpp"

void initialize()
{
	//initialize PANS
	PANS::Core::Initialize();
}
void disabled() {}
void competition_initialize() {}
void autonomous() {}

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
			Intake::Start();
		}
		if (intakeReverse.isPressed())
		{
			Intake::SetBackwards();
		}
		pros::delay(20);
	}
}
