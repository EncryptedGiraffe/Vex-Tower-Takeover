#include "main.h"

void opcontrol()
{
	Motor left(1);
	Motor right(2);
	Controller master(ControllerId::master);

	while(true)
	{
		if(master.getDigital(ControllerDigital::X))
		{
			left.moveVoltage(12000);
			right.moveVoltage(-12000);
		}
		else if(master.getDigital(ControllerDigital::Y))
		{
			left.moveVoltage(-12000);
			right.moveVoltage(12000);
		}
		else
		{
			left.moveVoltage(0);
			right.moveVoltage(0);
		}

		pros::delay(20);
	}
}
