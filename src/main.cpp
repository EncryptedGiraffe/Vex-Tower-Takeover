#include "drivers.hpp"

void initialize()
{
	//initialize PANS
	PANS::Core::Initialize();
}
void disabled() {}
void competition_initialize() {}
void autonomous() {}

void opcontrol()
{
	auto controller = ChassisControllerBuilder()
	.withMotors(1,2)
	.build();
	PANS::UISystem::MessageBrain("Opcontrol starting");
	while (true)
	{
		//open-loop drive control
		//Chassis::controller->getModel()->arcade(Core::master.getAnalog(ControllerAnalog::leftY), Core::master.getAnalog(ControllerAnalog::leftX));
		pros::delay(20);
	}
}
