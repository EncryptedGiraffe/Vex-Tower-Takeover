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
	while (true)
	{
		pros::delay(20);
	}
}
