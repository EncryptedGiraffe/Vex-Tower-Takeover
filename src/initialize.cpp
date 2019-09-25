#include "main.h"
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	/* PANS Library Initialization Functions:
		* Uncomment the first function if no V5 Vision Sensor is being used.
		* Uncomment the second function if the V5 Vision Sensor is being used, and pass the port it is plugged into.
		* Only one function can be run at a time, so comment the function you're not using.
	*/
	PANS::Core::Initialize(); //initialization without the vision sensor
	//PANS::Core::InitializeAll(0); //initializzation with the vision sensor - pass port
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
