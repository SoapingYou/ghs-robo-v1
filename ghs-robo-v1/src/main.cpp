#include "main.h"
#include "GHSChassis.h"
#include "Odometry.h"
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button()
{
	static bool pressed = false;
	pressed = !pressed;
	if (pressed)
	{
		pros::lcd::set_text(2, "I was pressed!");
	}
	else
	{
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
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

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

struct Params
{
	std::shared_ptr<pros::Controller> master;
	std::shared_ptr<pros::adi::DigitalOut> piston;
};

void clamptask(void *param)
{
	Params *myParams = static_cast<Params *>(param);
	std::shared_ptr<pros::Controller> master = myParams->master;
	std::shared_ptr<pros::adi::DigitalOut> piston = myParams->piston;
	bool prevState = false;
	bool clamp = false;
	int dummy = 0;
	while (true)
	{
		if (master->get_digital(pros::E_CONTROLLER_DIGITAL_B))
			clamp = true;
		else
			clamp = false;

		if (prevState != clamp)
			piston->set_value(clamp);
		prevState = clamp;
		// if (dummy % 10)
		// {
		// 	if ((dummy / 10) % 2)
		// 		pros::lcd::set_text((dummy / 10) % 8, "i got a brand new saxophone");
		// 	else
		// 		pros::lcd::set_text((dummy / 10) % 8, "i just jumped the band director");
		// }
		// dummy++;
		pros::delay(20);
	}
}
void odometrytask(void *param)
{
	auto odom = static_cast<std::shared_ptr<Odometry> *>(param);
	while (true)
	{
		(*odom)->runOdometry(true);
		std::cout << "testing odom runs. " << std::endl;
		pros::delay(20);
	}
}
void opcontrol()
{
	auto master = std::make_shared<pros::Controller>(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup left_mg({-11, 12, -13}); // Creates a motor group with forwards ports 12 and reversed ports 11 & 13
	pros::MotorGroup right_mg({-16, -17, 18});

	// the drivetrain at sophie's house
	auto left_mg_s = std::make_shared<pros::MotorGroup>(std::vector<std::int8_t>{11});
	auto right_mg_s = std::make_shared<pros::MotorGroup>(std::vector<std::int8_t>{-20});

	left_mg_s->set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);
	right_mg_s->set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);

	auto odometry = std::make_shared<Odometry>(left_mg_s, right_mg_s, 14, 2.0, 0);
	auto chassisController = std::make_shared<GHSChassis>(master, left_mg_s, right_mg_s, 200);

	auto intake = std::make_shared<pros::Motor>(5);
	bool intake_bool = true;

	auto piston = std::make_shared<pros::adi::DigitalOut>('A');
	bool clamp = false;

	Params params;
	params.master = master;
	params.piston = piston;
	pros::Task clamp_task(clamptask, &params);

	pros::Task odometry_task(odometrytask, &odometry);

	while (true)
	{
		// Arcade control scheme
		chassisController->runDrivetrain(true); // Sets right motor voltage

		if (master->get_digital(pros::E_CONTROLLER_DIGITAL_X))
		{
			chassisController->typeOfScale = !chassisController->typeOfScale;
			std::cout << "changed" << std::endl;
		}
		// if (master->get_digital(pros::E_CONTROLLER_DIGITAL_B))
		// {
		// 	piston->set_value(!clamp);
		// 	clamp = !clamp;
		// 	pros::delay(5);
		// }
		// if (master->get_digital(pros::E_CONTROLLER_DIGITAL_A))
		// {
		// 	intake->move_velocity(100);
		// }
		// else
		// {
		// 	intake->move_velocity(0);
		// }

		pros::delay(20); // Run for 20 ms then update
	}
}