#include "drivers.hpp"

namespace Core
{
  //create the controllers
  Controller master(ControllerId::master);
  Controller partner(ControllerId::partner);
  int isInitialized = false;
  void Initialize()
  {
    if(isInitialized)
      return;
<<<<<<< Updated upstream
=======
      //arm up
      Arm::SetPosition(4000);
      Deploy::Move(0.2);
      pros::Task::delay(1200);
      //arm down
      Arm::SetPosition(0);
      Deploy::Move(0);
      pros::Task::delay(1000);
      // move forwards
      Motors::Chassis::frontLeft.moveVoltage(5000);
      Motors::Chassis::frontRight.moveVoltage(-5000);
      Motors::Chassis::backLeft.moveVoltage(5000);
      Motors::Chassis::backRight.moveVoltage(-5000);
      pros::delay(500);

>>>>>>> Stashed changes
    //move forwards
    Motors::Chassis::frontLeft.moveVoltage(7000);
    Motors::Chassis::frontRight.moveVoltage(-7000);
    Motors::Chassis::backLeft.moveVoltage(7000);
    Motors::Chassis::backRight.moveVoltage(-7000);
    pros::delay(400);
    //move backward
    Motors::Chassis::frontLeft.moveVoltage(-7000);
    Motors::Chassis::frontRight.moveVoltage(7000);
    Motors::Chassis::backLeft.moveVoltage(-7000);
    Motors::Chassis::backRight.moveVoltage(7000);
    pros::delay(400);
    //move backwards
    Motors::Chassis::frontLeft.moveVoltage(0);
    Motors::Chassis::frontRight.moveVoltage(0);
    Motors::Chassis::backLeft.moveVoltage(0);
    Motors::Chassis::backRight.moveVoltage(0);
    //deploy up
    Deploy::Move(0.30);
    pros::delay(500);
    //arm up
    Arm::SetPosition(800);
    pros::delay(500);
    //arm down
    Arm::SetPosition(0);
    //deploy down
    Deploy::Move(0.00);
    isInitialized = true;
  }
}

namespace Auto
{
  void RedAuto()
  {
    //drive forwards to slurp up
    Motors::Chassis::frontLeft.moveVoltage(6000);
    Motors::Chassis::frontRight.moveVoltage(-6000);
    Motors::Chassis::backLeft.moveVoltage(6000);
    Motors::Chassis::backRight.moveVoltage(-6000);
    pros::Task::delay(500);
  }
  void BlueAuto()
  {

  }
}

namespace Motors
{
  namespace Chassis
  {
    Motor frontLeft(Ports::Chassis::frontLeft);
    Motor frontRight(Ports::Chassis::frontRight);
    Motor backLeft(Ports::Chassis::backLeft);
    Motor backRight(Ports::Chassis::backRight);
  }
  Motor deploy(Ports::deploy);
  MotorGroup intake({Ports::Intake::left, -Ports::Intake::right});
  Motor arm(Ports::arm);
}

namespace Chassis
{
  //the controller
  std::shared_ptr<ChassisController> controller;
  //init
  void Initialize()
  {
    //create the controller
    controller = ChassisControllerBuilder()
    .withMotors(Ports::Chassis::frontLeft, -Ports::Chassis::frontRight, -Ports::Chassis::backRight, Ports::Chassis::backLeft)
    .withGearset(AbstractMotor::gearset::green)
    .withDimensions({{4_in, 14.25_in}, imev5GreenTPR})
    .build();
  }
  /*
  ControllerBuilder()
  .withMotors(Ports::Chassis::frontLeft, -Ports::Chassis::frontRight, Ports::Chassis::backLeft, -Ports::Chassis::backRight)
  .withGearset(AbstractMotor::gearset::green)
  .withDimensions({{4_in, 14.25_in}, imev5GreenTPR})
  .build();
  */
}

namespace Intake
{
  //intake state: 1 = forward, -1 = backward
  int state = 1;
  //intake mode: 1 = running, 0 = stopped
  int mode = 0;
  //intake speed, represented as a decimal percantage from 0.00 (off) to 1.00 (full speed)
  float speed = 1.00F;
  //functions
  void SetMotor()
  {
    Motors::intake.moveVoltage(12000 * mode * state * speed);
  }
  void Start()
  {
    mode = 1;
    SetMotor();
  }
  void Stop()
  {
    mode = 0;
    SetMotor();
  }
  void SetForwards()
  {
    state = 1;
    SetMotor();
  }
  void SetBackwards()
  {
    state = -1;
    SetMotor();
  }
  void SetSpeed(float value)
  {
    if (value < 0)
    {
      speed = 0.00;
    }
    else if (value > 1)
    {
      speed = 1.00;
    }
    else {
      speed = value;
    }
    SetMotor();
  }
}

namespace Deploy
{
  int cur_pos = 0;
  //get the position of the ramp
  int GetPosition()
  {
    return cur_pos / finalPosition;
  }
  //percent is a decimal percentage of the deploy system's total movement
  void Move(float percent)
  {
    float per;
    //check percent
    if(percent > 1.00)
      per = 1.00;
    else if(percent < 0.00)
      per = 0.00;
    else
      per = percent;
    //calculate new position
    cur_pos = per * finalPosition;
    //set the motor
    Motors::deploy.moveAbsolute(-cur_pos, maxSpeed);
  }
  //task state variables
  bool isDeploying = false;
  // bool isWide = false;
  bool isFinished = false;

  //internal async deploy sequence
  void _deploy(void* param)
  {
    while(true)
    {
      if(isDeploying)
      {
          //////////Deploy code for wide goal//////////
          //BOTH ISH
<<<<<<< Updated upstream
=======
          //move backwards
          Motors::Chassis::frontLeft.moveVoltage(-1300);
          Motors::Chassis::frontRight.moveVoltage(1300);
          Motors::Chassis::backLeft.moveVoltage(-1300);
          Motors::Chassis::backRight.moveVoltage(1300);
          pros::Task::delay(400);
          Motors::Chassis::frontLeft.moveVoltage(0);
          Motors::Chassis::frontRight.moveVoltage(0);
          Motors::Chassis::backLeft.moveVoltage(0);
          Motors::Chassis::backRight.moveVoltage(0);
          // slurp
          Intake::SetForwards();
          Intake::SetSpeed(0.3);
          Intake::Start();
          pros::Task::delay(600);
>>>>>>> Stashed changes
          //move the intake
          Intake::SetBackwards();
          Intake::SetSpeed(0.3);
          Intake::Start();
          pros::Task::delay(100);
          if(!isDeploying) //check for abort
            continue;
          //move the intake
          Intake::Stop();
          //move the ramp
          Deploy::Move(0.95F);
          pros::Task::delay(3300);
          if(!isDeploying) //check for abort
            continue;
          //move the intake
          Intake::SetBackwards();
          Intake::SetSpeed(0.4);
          Intake::Start();
          pros::Task::delay(600);
          //move the ramp
<<<<<<< Updated upstream
          Deploy::Move(0.9);
          pros::Task::delay(200);
=======
          Deploy::Move(0.8);
          pros::Task::delay(400);
>>>>>>> Stashed changes
          //move forwards
          Motors::Chassis::frontLeft.moveVoltage(1500);
          Motors::Chassis::frontRight.moveVoltage(-1500);
          Motors::Chassis::backLeft.moveVoltage(1500);
          Motors::Chassis::backRight.moveVoltage(-1500);
          pros::delay(300);
          Intake::Stop();
          if(!isDeploying) //check for abort
            continue;
          // pros::delay(1300);
          // pros::delay(1500);
          //start the intake
          Intake::Start();
          //move the deploy
          Deploy::Move(0.00F);
          pros::delay(1500);
          //move backwards
          Motors::Chassis::frontLeft.moveVoltage(-2000);
          Motors::Chassis::frontRight.moveVoltage(2000);
          Motors::Chassis::backLeft.moveVoltage(-2000);
          Motors::Chassis::backRight.moveVoltage(2000);
          pros::Task::delay(3000);
          if(!isDeploying) //check for abort
            continue;
          Deploy::Move(0.0F);
          Intake::SetForwards();
          Intake::SetSpeed(1.00);
          Intake::Stop();
          Arm::controller->setTarget(0);
          //finish
          isDeploying = false;
          isFinished = true;
          //////////End of wide goal deploy code//////////
      }
      else
      {
          pros::Task::delay(20);
      }
    }
  }
  //run the deploy sequence
  void Deploy()
  {
    //start the sequence
    isDeploying = true;
    isFinished = false;
    // isWide = false;
    Deploy::Move(0.00F);
    Arm::SetPosition(0);
    while(true)
    {
      //check if finished
      if(isFinished)
      {
        isDeploying = false;
        isFinished = false;
        break;
      }
      if(Core::master.getDigital(ControllerDigital::X))
      {
        isDeploying = false;
        isFinished = false;
        break;
      }
      pros::delay(20);
    }
  }
  //run the deploy sequence for the wide goal
  // void DeployWide()
  // {
  //   //start the sequence
  //   isDeploying = true;
  //   isFinished = false;
  //   isWide = true;
  //   Deploy::Move(0.00F);
  //   Arm::SetPosition(0);
  //   while(true)
  //   {
  //     //check if finished
  //     if(isFinished)
  //     {
  //       isDeploying = false;
  //       isFinished = false;
  //       break;
  //     }
  //     if(Core::master.getDigital(ControllerDigital::X))
  //     {
  //       isDeploying = false;
  //       isFinished = false;
  //       break;
  //     }
  //     pros::delay(20);
  //   }
  // }

  void Initialize()
  {
    pros::Task deploy_task(_deploy, (void*)"", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Deploy Task");
  }
}

namespace Arm
{
  std::shared_ptr<AsyncPositionController<double, double>> controller;
  void Initialize()
  {
    controller = AsyncPosControllerBuilder()
    .withMotor(Ports::arm)
    .build();
  }
  int cur_pos = 0;
  //set the position of the arm
  void SetPosition(int pos)
  {
    //check bounds
    if(pos < 0)
    {
      cur_pos = 0;
    }
    else if(pos > maxHeight)
    {
      cur_pos = maxHeight;
    }
    else
    {
      cur_pos = pos;
    }
    //set the motor
    controller->setTarget(cur_pos);
  }
}
