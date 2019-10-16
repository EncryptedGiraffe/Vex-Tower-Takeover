#include "main.h"
#include "Controllers.hpp"

void opcontrol()
{
	//////////Temporary Testing Code//////////
	Motor c_frontLeft(1);
	Motor c_frontRight(2);
	Motor c_backLeft(3);
	Motor c_backRight(4);
	Motor i_left(5);
	Motor i_right(6);
	Motor a_arm(7);
	Motor d_deploy(8);
	Controller master(ControllerId::master);
	ControllerButton intakeBtn(ControllerDigital::A);
	ControllerButton intakeBack(ControllerDigital::X);
	bool isIntakeRunning = false;
	bool isIntakeBackwards = false;

	while(true)
	{
		//deploy motor - basic on/off
		if(master.getDigital(ControllerDigital::R1))
		{
			d_deploy.moveVoltage(5000);
		}
		else if(master.getDigital(ControllerDigital::R2))
		{
			d_deploy.moveVoltage(-5000);
		}
		else
		{
			d_deploy.moveVoltage(0);
		}
		//check if the intake is running
		if(isIntakeRunning)
		{
			//run
			if(isIntakeBackwards)
			{
				i_left.moveVoltage(12000);
				i_right.moveVoltage(-12000);
			}
			else
			{
				i_left.moveVoltage(-12000);
				i_right.moveVoltage(12000);
			}
		}
		else
		{
			i_left.moveVoltage(0);
			i_right.moveVoltage(0);
		}
		if(intakeBtn.changedToReleased())
		{
			isIntakeRunning = !isIntakeRunning;
		}
		if(intakeBack.changedToReleased())
		{
			isIntakeBackwards = !isIntakeBackwards;
		}

		//arm control - postion based
		if(master.getDigital(ControllerDigital::L1))
		{
			//move it
			a_arm.moveRelative(5, 200);
		}
		else if(master.getDigital(ControllerDigital::L2))
		{
			//move it
			a_arm.moveRelative(-5, 200);
		}



		//set motors for mecanum drive
		float ch1 = master.getAnalog(ControllerAnalog::rightX);
		float ch4 = master.getAnalog(ControllerAnalog::leftX);
		float ch3 = master.getAnalog(ControllerAnalog::leftY);
		c_frontLeft.move_voltage(12000 * (ch3 + ch1 + ch4));
		c_frontRight.move_voltage(-12000 * (ch3 - ch1 - ch4));
		c_backLeft.move_voltage(12000 * (ch3 + ch1 - ch4));
		c_backRight.move_voltage(-12000 * (ch3 - ch1 + ch4));

		pros::delay(20);
	}
}
